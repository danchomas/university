#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

uint64_t rand_uint64() {
    uint64_t r = 0;
    for (int i = 0; i < 64; i += 8) {
        r |= ((uint64_t)rand() & 0xFF) << i;
    }
    return r;
}

void shuffle(size_t *array, size_t n) {
    for (size_t i = n - 1; i > 0; i--) {
        size_t j = rand() % (i + 1);
        size_t temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

size_t calculate_file_size(size_t size_mb, long page_size) {
    size_t N = size_mb * 1024ULL * 1024;
    return (N / page_size) * page_size;
}

void generate_data_file(const char *filename, size_t file_size) {
    int fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0666);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    if (ftruncate(fd, file_size) == -1) {
        perror("ftruncate");
        close(fd);
        exit(1);
    }

    uint64_t *fill_map = mmap(NULL, file_size, PROT_WRITE, MAP_SHARED, fd, 0);
    if (fill_map == MAP_FAILED) {
        perror("mmap for fill");
        close(fd);
        exit(1);
    }

    size_t num_elements = file_size / sizeof(uint64_t);
    for (size_t i = 0; i < num_elements; i++) {
        fill_map[i] = rand_uint64();
    }

    if (msync(fill_map, file_size, MS_SYNC) == -1) {
        perror("msync");
    }

    if (munmap(fill_map, file_size) == -1) {
        perror("munmap fill");
    }

    close(fd);
}

uint64_t *map_file(const char *filename, size_t file_size) {
    int fd = open(filename, O_RDWR);
    if (fd == -1) {
        perror("open for mapping");
        exit(1);
    }

    uint64_t *map = mmap(NULL, file_size, PROT_READ, MAP_SHARED, fd, 0);
    if (map == MAP_FAILED) {
        perror("mmap for compute");
        close(fd);
        exit(1);
    }

    close(fd);
    return map;
}

void apply_madvise(uint64_t *map, size_t file_size, const char *advice_str) {
    int advice = -1;
    if (strcmp(advice_str, "seq") == 0) {
        advice = MADV_SEQUENTIAL;
    } else if (strcmp(advice_str, "rand") == 0) {
        advice = MADV_RANDOM;
    } else if (strcmp(advice_str, "will") == 0) {
        advice = MADV_WILLNEED;
    } else if (strcmp(advice_str, "none") != 0) {
        fprintf(stderr, "Invalid advice\n");
        exit(1);
    }

    if (advice != -1 && madvise(map, file_size, advice) == -1) {
        perror("madvise");
    }
}

uint64_t sequential_access(uint64_t *map, size_t num_elements) {
    uint64_t sum = 0;
    for (size_t i = 0; i < num_elements; i++) {
        uint64_t val = map[i];
        sum += val * val;
    }
    return sum;
}

uint64_t random_access(uint64_t *map, size_t num_elements) {
    size_t *indices = malloc(num_elements * sizeof(size_t));
    if (indices == NULL) {
        fprintf(stderr, "Cannot allocate indices array\n");
        exit(1);
    }

    for (size_t i = 0; i < num_elements; i++) {
        indices[i] = i;
    }

    shuffle(indices, num_elements);

    uint64_t sum = 0;
    for (size_t i = 0; i < num_elements; i++) {
        uint64_t val = map[indices[i]];
        sum += val * val;
    }

    free(indices);
    return sum;
}

double measure_time(uint64_t (*access_func)(uint64_t *, size_t), uint64_t *map, size_t num_elements) {
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    uint64_t sum = access_func(map, num_elements);

    clock_gettime(CLOCK_MONOTONIC, &end);
    double time_taken = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    printf("Sum: %llu\n", (unsigned long long)sum);
    printf("Time taken: %.6f seconds\n", time_taken);

    return time_taken;
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <size_mb> <access_mode: seq/rand> <advice: none/seq/rand/will>\n", argv[0]);
        return 1;
    }

    size_t size_mb = strtoull(argv[1], NULL, 10);
    char *access_mode = argv[2];
    char *advice_str = argv[3];

    srand(time(NULL));

    long page_size = sysconf(_SC_PAGE_SIZE);
    if (page_size == -1) {
        perror("sysconf");
        return 1;
    }

    size_t file_size = calculate_file_size(size_mb, page_size);
    if (file_size == 0) {
        fprintf(stderr, "Size too small\n");
        return 1;
    }

    size_t num_elements = file_size / sizeof(uint64_t);

    const char *filename = "/tmp/nums.bin";
    generate_data_file(filename, file_size);

    uint64_t *map = map_file(filename, file_size);
    apply_madvise(map, file_size, advice_str);

    uint64_t (*access_func)(uint64_t *, size_t);
    if (strcmp(access_mode, "seq") == 0) {
        access_func = sequential_access;
    } else if (strcmp(access_mode, "rand") == 0) {
        access_func = random_access;
    } else {
        fprintf(stderr, "Invalid access mode\n");
        munmap(map, file_size);
        return 1;
    }

    measure_time(access_func, map, num_elements);

    if (munmap(map, file_size) == -1) {
        perror("munmap");
    }

    return 0;
}
