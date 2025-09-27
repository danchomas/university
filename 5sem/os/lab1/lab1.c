#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <time.h>

#define N 2                // общее число процессов (включая родителя)
#define MAX_ROUNDS 3
#define SIG_RING (SIGRTMIN + 1)

static volatile sig_atomic_t current_round = 0;
static pid_t *child_pids = NULL;
static int num_children = 0;
static pid_t g_next_pid = -1;          // кому отправлять сигнал
static pid_t g_original_parent = -1;   // PID родителя (для идентификации)

void sigterm_handler(int signo) {
    exit(EXIT_SUCCESS);
}

void sigint_handler(int signo) {
    // Родитель завершает всех потомков
    for (int i = 0; i < num_children; ++i) {
        if (child_pids[i] > 0) {
            kill(child_pids[i], SIGTERM);
        }
    }
    exit(EXIT_SUCCESS);
}

void ring_handler(int signo, siginfo_t *info, void *context) {
    int value = info->si_value.sival_int;
    pid_t self = getpid();
    pid_t parent = getppid();

    printf("[PID=%d, PPID=%d] Получено: %d\n", (int)self, (int)parent, value);

    if (self == g_original_parent) {
        // Это родитель — он получил сигнал после полного круга
        current_round++;
        if (current_round < MAX_ROUNDS) {
            printf("[Parent %d] Начинает раунд %d\n", (int)self, current_round);
            const union sigval sv = {.sival_int = 0};
            if (sigqueue(g_next_pid, SIG_RING, sv) == -1) {
                perror("sigqueue (next round)");
            }
        } else {
            // Завершаем всех
            for (int i = 0; i < num_children; ++i) {
                if (child_pids[i] > 0) {
                    kill(child_pids[i], SIGTERM);
                }
            }
            exit(EXIT_SUCCESS);
        }
    } else {
        // Это потомок — просто передаём дальше
        int new_value = value + 1;
        const union sigval sv = {.sival_int = new_value};
        if (sigqueue(g_next_pid, SIG_RING, sv) == -1) {
            perror("sigqueue forward");
            // Если ошибка — возможно, next уже мёртв → завершаемся
            exit(EXIT_FAILURE);
        }
    }
}

int main(void) {
    setvbuf(stdout, NULL, _IONBF, 0);
    srand(time(NULL));

    g_original_parent = getpid();
    num_children = N - 1;
    child_pids = calloc(num_children, sizeof(pid_t));
    if (!child_pids) {
        perror("calloc");
        exit(EXIT_FAILURE);
    }

    // Установка обработчика SIGINT только у родителя
    if (signal(SIGINT, sigint_handler) == SIG_ERR) {
        perror("signal SIGINT");
        exit(EXIT_FAILURE);
    }

    // Создаём всех потомков напрямую от родителя
    pid_t current_next = g_original_parent; // последний потомок будет отправлять сюда

    for (int i = N - 1; i >= 1; i--) {
        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        if (pid == 0) {
            // Дочерний процесс
            g_next_pid = current_next;
            current_next = getpid();

            // Установка обработчиков
            struct sigaction sa = {0};
            sa.sa_sigaction = ring_handler;
            sa.sa_flags = SA_SIGINFO;
            sigemptyset(&sa.sa_mask);
            if (sigaction(SIG_RING, &sa, NULL) == -1) {
                perror("sigaction child");
                exit(EXIT_FAILURE);
            }

            if (signal(SIGTERM, sigterm_handler) == SIG_ERR) {
                perror("signal SIGTERM");
                exit(EXIT_FAILURE);
            }

            // Ждём сигналов ВЕЧНО
            while (1) {
                pause();
            }
        } else {
            // Родитель: запоминаем PID потомка
            child_pids[i - 1] = pid; // i от N-1 до 1 → индекс от N-2 до 0
            current_next = pid;
        }
    }

    // Родитель: первый в кольце — тот, кто был создан последним (current_next)
    g_next_pid = current_next;

    // Обработчик сигнала у родителя
    struct sigaction sa = {0};
    sa.sa_sigaction = ring_handler;
    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);
    if (sigaction(SIG_RING, &sa, NULL) == -1) {
        perror("sigaction parent");
        exit(EXIT_FAILURE);
    }

    sleep(1); // дать потомкам завершить инициализацию

    printf("[Parent %d] Инициирует передачу числа 0 в кольцо.\n", (int)getpid());
    const union sigval sv = {.sival_int = 0};
    if (sigqueue(g_next_pid, SIG_RING, sv) == -1) {
        perror("sigqueue init");
        exit(EXIT_FAILURE);
    }

    // Родитель ждёт сигналов
    while (1) {
        pause();
    }

    free(child_pids);
    return 0;
}
