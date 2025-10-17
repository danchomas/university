#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

#define N 4                // общее число процессов (включая родителя)
#define SIG_RING (SIGRTMIN + 1)

static pid_t g_original_parent = -1;   // PID исходного родителя
static pid_t g_next_pid = -1;          // кому отправлять сигнал

void sigterm_handler(int signo) {
    exit(EXIT_SUCCESS);
}

void sigint_handler(int signo) {
    // Только исходный родитель обрабатывает SIGINT
    if (getpid() == g_original_parent) {
        printf("\n[Parent] Получен SIGINT. Завершение...\n");
        exit(EXIT_SUCCESS);
    }
}

void ring_handler(int signo, siginfo_t *info, void *context) {
    int value = info->si_value.sival_int;
    pid_t self = getpid();
    pid_t parent = getppid();

    printf("[PID=%d, PPID=%d] Получено: %d\n", (int)self, (int)parent, value);

    // Увеличиваем значение
    int new_value = value + 1;

    // Отправляем дальше
    const union sigval sv = {.sival_int = new_value};
    if (sigqueue(g_next_pid, SIG_RING, sv) == -1) {
        perror("sigqueue forward");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]) {
    setvbuf(stdout, NULL, _IONBF, 0);

    // Определяем PID исходного родителя
    if (argc == 1) {
        // Это исходный родитель
        g_original_parent = getpid();
    } else {
        // Это потомок — получаем PID родителя из аргумента
        g_original_parent = (pid_t)atol(argv[1]);
    }

    pid_t self_pid = getpid();

    // Устанавливаем обработчики сигналов
    struct sigaction sa = {0};
    sa.sa_sigaction = ring_handler;
    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);
    if (sigaction(SIG_RING, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    if (signal(SIGTERM, sigterm_handler) == SIG_ERR) {
        perror("signal SIGTERM");
        exit(EXIT_FAILURE);
    }

    // Только исходный родитель ловит SIGINT
    if (self_pid == g_original_parent) {
        if (signal(SIGINT, sigint_handler) == SIG_ERR) {
            perror("signal SIGINT");
            exit(EXIT_FAILURE);
        }
    }

    // === ЦЕПОЧКА ПОРОЖДЕНИЯ ===
    if (self_pid == g_original_parent) {
        // Родитель: создаёт первого потомка, если N > 1
        if (N > 1) {
            char orig_pid_str[32];
            snprintf(orig_pid_str, sizeof(orig_pid_str), "%ld", (long)g_original_parent);
            pid_t first_child = fork();
            if (first_child == -1) {
                perror("fork");
                exit(EXIT_FAILURE);
            }
            if (first_child == 0) {
                execl(argv[0], argv[0], orig_pid_str, "1", NULL); // "1" = уровень/номер
                perror("execl first child");
                exit(EXIT_FAILURE);
            }
            g_next_pid = first_child;
        } else {
            // N == 1: кольцо из одного процесса (сам себе)
            g_next_pid = g_original_parent;
        }
    } else {
        // Это потомок. Определяем, сколько процессов уже создано.
        // Мы передаём "глубину" через argv[2]: 1, 2, ..., N-1
        int depth = (argc >= 3) ? atoi(argv[2]) : 1;

        if (depth < N - 1) {
            // Нужно создать следующего потомка
            char orig_pid_str[32];
            char next_depth_str[32];
            snprintf(orig_pid_str, sizeof(orig_pid_str), "%ld", (long)g_original_parent);
            snprintf(next_depth_str, sizeof(next_depth_str), "%d", depth + 1);

            pid_t next_child = fork();
            if (next_child == -1) {
                perror("fork in child");
                exit(EXIT_FAILURE);
            }
            if (next_child == 0) {
                execl(argv[0], argv[0], orig_pid_str, next_depth_str, NULL);
                perror("execl next child");
                exit(EXIT_FAILURE);
            }
            g_next_pid = next_child;
        } else {
            // Это последний потомок (глубина = N-1)
            // === ВОТ ЭТОТ МОМЕНТ — ЗАМЫКАНИЕ КОЛЬЦА ===
            // Последний процесс в цепочке отправляет сигнал
            // обратно исходному родителю, замыкая кольцо:
            // ... → Потомок N-1 → Родитель → Потомок 1 → ...
            // ===================================================
            g_next_pid = g_original_parent;
        }
    }

    // Инициация передачи: только исходный родитель
    if (self_pid == g_original_parent) {
        sleep(1); // дать потомкам завершить инициализацию
        printf("[Parent %d] Инициирует передачу числа 0 в кольцо.\n", (int)self_pid);
        const union sigval sv = {.sival_int = 0};
        if (sigqueue(g_next_pid, SIG_RING, sv) == -1) {
            perror("sigqueue init");
            exit(EXIT_FAILURE);
        }
    }

    while (1) {
        pause();
    }

    return 0;
}
