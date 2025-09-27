#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <string.h>

#define NUM 5
#define SIG_NEXT SIGUSR2
#define SIG_DATA SIGUSR1

static volatile sig_atomic_t stop_flag = 0;
static pid_t next_pid = -1;
static int current_S = 0;

// Обработчик данных и настройки кольца
void data_handler(int sig, siginfo_t *info, void *ctx) {
    if (sig == SIG_NEXT) {
        next_pid = info->si_value.sival_int;
    } else if (sig == SIG_DATA) {
        current_S = info->si_value.sival_int;
        printf("[PID=%d, PPID=%d] S = %d\n", (int)getpid(), (int)getppid(), current_S);
        sleep(1);
        current_S++;
        if (next_pid != -1 && !stop_flag) {
            union sigval val = {.sival_int = current_S};
            sigqueue(next_pid, SIG_DATA, val);
        }
    }
}

// Обработчик завершения (для SIGINT и SIGTERM)
void stop_handler(int sig) {
    stop_flag = 1;
}

int main() {
    setvbuf(stdout, NULL, _IONBF, 0);
    printf("[Main] Запуск кольца из %d процессов...\n", NUM);

    // Устанавливаем обработчики
    struct sigaction sa_data = {.sa_sigaction = data_handler, .sa_flags = SA_SIGINFO};
    struct sigaction sa_stop = {.sa_handler = stop_handler};

    sigaction(SIG_NEXT, &sa_data, NULL);
    sigaction(SIG_DATA, &sa_data, NULL);
    sigaction(SIGINT,  &sa_stop, NULL);
    sigaction(SIGTERM, &sa_stop, NULL);

    pid_t children[NUM];
    pid_t parent = getpid();

    // Создаём дочерние процессы
    for (int i = 0; i < NUM; i++) {
        if ((children[i] = fork()) == 0) {
            // Дочерний процесс: сбрасываем обработчики завершения на умолчание,
            // но оставляем обработчик данных
            signal(SIGINT,  SIG_DFL);
            signal(SIGTERM, SIG_DFL);
            while (!stop_flag) {
                pause();
            }
            printf("[Child PID=%d] Завершаюсь.\n", (int)getpid());
            exit(0);
        }
    }

    // Настраиваем кольцо: parent → c0 → c1 → ... → c{NUM-1} → parent
    for (int i = 0; i < NUM; i++) {
        pid_t next = (i == NUM - 1) ? parent : children[i + 1];
        union sigval val = {.sival_int = next};
        sigqueue(children[i], SIG_NEXT, val);
    }
    next_pid = children[0]; // родитель передаёт первому ребёнку

    // Запускаем передачу
    union sigval start = {.sival_int = 0};
    sigqueue(children[0], SIG_DATA, start);

    // Ждём сигнала завершения
    while (!stop_flag) {
        pause();
    }

    printf("\n[Main] Получен сигнал завершения. Остановка кольца...\n");

    // Посылаем SIGTERM всем детям
    for (int i = 0; i < NUM; i++) {
        if (children[i] > 0) {
            kill(children[i], SIGTERM);
        }
    }

    // Ждём завершения всех
    for (int i = 0; i < NUM; i++) {
        wait(NULL);
    }

    printf("[Main] Все процессы завершены. Выход.\n");
    return 0;
}
