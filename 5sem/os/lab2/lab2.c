#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <time.h>

// Размер буфера в байтах (например, 128 МБ, чтобы было заметно, но не слишком много)
// Подберите под свою систему, чтобы не вызвать OOM
#define BUFFER_SIZE (128 * 1024 * 1024)

// Функция для чтения значения из /sys/kernel/mm/ksm/*
long read_ksm_stat(const char *stat_name) {
    char path[256];
    snprintf(path, sizeof(path), "/sys/kernel/mm/ksm/%s", stat_name);
    FILE *fp = fopen(path, "r");
    if (!fp) {
        perror("fopen ksm stat");
        return -1;
    }
    long value;
    if (fscanf(fp, "%ld", &value) != 1) {
        value = -1;
    }
    fclose(fp);
    return value;
}

// Функция для вывода VmRSS процесса (в КБ)
long get_vm_rss(pid_t pid) {
    char path[256];
    snprintf(path, sizeof(path), "/proc/%d/status", pid);
    FILE *fp = fopen(path, "r");
    if (!fp) {
        perror("fopen proc status");
        return -1;
    }
    char line[256];
    long rss = -1;
    while (fgets(line, sizeof(line), fp)) {
        if (sscanf(line, "VmRSS: %ld kB", &rss) == 1) {
            break;
        }
    }
    fclose(fp);
    return rss;
}

// Функция для вывода текущих KSM статистик и VmRSS
void print_stats(pid_t parent_pid, pid_t child_pid) {
    printf("KSM Stats:\n");
    printf("  pages_shared: %ld\n", read_ksm_stat("pages_shared"));
    printf("  pages_sharing: %ld\n", read_ksm_stat("pages_sharing"));
    printf("  full_scans: %ld\n", read_ksm_stat("full_scans"));

    // CPU usage ksmd - это сложнее, используем top или ps вручную, здесь пропустим
    // Для простоты можно добавить: ps -p $(pgrep ksmd) -o %cpu
    // Но для автоматизации вызовем system
    system("ps -p $(pgrep ksmd) -o %cpu | tail -n 1");

    printf("VmRSS (parent %d): %ld kB\n", parent_pid, get_vm_rss(parent_pid));
    if (child_pid > 0) {
        printf("VmRSS (child %d): %ld kB\n", child_pid, get_vm_rss(child_pid));
    }
}

int main() {
    // Убедимся, что KSM включен (должен быть выполнен echo 1 > /sys/kernel/mm/ksm/run заранее)
    if (read_ksm_stat("run") != 1) {
        fprintf(stderr, "KSM не включен! Выполните: echo 1 | sudo tee /sys/kernel/mm/ksm/run\n");
        return 1;
    }

    pid_t parent_pid = getpid();
    printf("До эксперимента:\n");
    print_stats(parent_pid, 0);

    // Fork для создания двух процессов
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return 1;
    }

    // В обоих процессах выделяем память
    void *buffer;
    if (pid == 0) {  // Child
        printf("Child (%d): Выделяю и заполняю буфер...\n", getpid());
    } else {  // Parent
        printf("Parent (%d): Выделяю и заполняю буфер...\n", getpid());
    }

    // Выделяем анонимную память с mmap (лучше для KSM, чем malloc)
    buffer = mmap(NULL, BUFFER_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (buffer == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    // Помечаем область как подходящую для KSM (MADV_MERGEABLE)
    if (madvise(buffer, BUFFER_SIZE, MADV_MERGEABLE) < 0) {
        perror("madvise MADV_MERGEABLE");
        munmap(buffer, BUFFER_SIZE);
        return 1;
    }

    // Заполняем буфер идентичными данными (простой паттерн для демонстрации)
    // Чтобы страницы были идентичны, заполняем одним и тем же во всех процессах
    srand(42);  // Фиксированный seed для идентичности
    for (size_t i = 0; i < BUFFER_SIZE / sizeof(int); i++) {
        ((int *)buffer)[i] = rand();  // Идентичные случайные числа
    }

    // Чтобы страницы стали резидентными, коснемся их (touch)
    for (size_t i = 0; i < BUFFER_SIZE; i += getpagesize()) {
        ((volatile char *)buffer)[i] = ((char *)buffer)[i];  // Чтение для резиденции
    }

    if (pid > 0) {  // Parent ждет немного, чтобы child тоже заполнил
        sleep(5);
    }

    // Держим паузу, чтобы ksmd успел просканировать и слить страницы
    // KSM сканирует периодически, подождем 30-60 секунд
    printf("Процесс %d: Держу буфер 60 секунд для KSM...\n", getpid());
    sleep(60);

    // Выводим статистику после
    if (pid == 0) {  // Child выводит свою
        printf("После в child:\n");
        print_stats(parent_pid, getpid());
    } else {  // Parent ждет child и выводит
        wait(NULL);
        printf("После в parent:\n");
        print_stats(parent_pid, 0);  // Child уже завершился
    }

    // Освобождаем память
    munmap(buffer, BUFFER_SIZE);

    return 0;
}
