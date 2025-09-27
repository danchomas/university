#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <time.h>

static volatile pid_t child_pid = 0;
static volatile sig_atomic_t stop_flag = 0;

// Обработчик в родителе: получает "понг" от дочернего процесса
void parent_handler(int signo, siginfo_t *si, void *context) {
    int val = si->si_value.sival_int;
    printf("[Parent %d] получил число: %d\n", (int)getpid(), val);

    sleep(1); // Пауза для наглядности

    int new_val = rand() % 100;
    printf("[Parent %d] отправляет число: %d\n", (int)getpid(), new_val);

    union sigval sv;
    sv.sival_int = new_val;
    sigqueue(child_pid, SIGUSR1, sv);
}

// Обработчик в дочернем процессе: получает "пинг" от родителя
void child_handler(int signo, siginfo_t *si, void *context) {
    int val = si->si_value.sival_int;
    printf("[Child %d] получил число: %d\n", (int)getpid(), val);

    sleep(1); // Пауза для наглядности

    int new_val = rand() % 100;
    printf("[Child %d] отправляет число: %d\n", (int)getpid(), new_val);

    union sigval sv;
    sv.sival_int = new_val;
    sigqueue(getppid(), SIGUSR2, sv);
}

// Обработчик SIGINT (Ctrl+C) — только для родителя
void stop_handler(int signo) {
    printf("\n[Parent %d] Получен SIGINT. Завершение...\n", (int)getpid());
    if (child_pid > 0) {
        kill(child_pid, SIGTERM);
    }
    stop_flag = 1;
}

int main() {
    setvbuf(stdout, NULL, _IONBF, 0); // Отключаем буферизацию
    srand(time(NULL));

    // Устанавливаем обработчик для "понга" (SIGUSR2)
    struct sigaction sa;
    sa.sa_sigaction = parent_handler;
    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGUSR2, &sa, NULL);

    // Обработчик завершения
    signal(SIGINT, stop_handler);

    child_pid = fork();
    if (child_pid == -1) {
        perror("fork");
        exit(1);
    }

    if (child_pid == 0) {
        // Дочерний процесс
        signal(SIGINT, SIG_DFL); // Восстанавливаем стандартное поведение

        struct sigaction sa_ch;
        sa_ch.sa_sigaction = child_handler;
        sa_ch.sa_flags = SA_SIGINFO;
        sigemptyset(&sa_ch.sa_mask);
        sigaction(SIGUSR1, &sa_ch, NULL);

        while (1) {
            pause(); // Ждём сигнал
        }
    } else {
        // Родительский процесс
        sleep(1); // Даём ребёнку время установить обработчик

        int first = rand() % 100;
        printf("[Parent %d] отправляет число: %d\n", (int)getpid(), first);

        union sigval sv;
        sv.sival_int = first;
        sigqueue(child_pid, SIGUSR1, sv);

        while (!stop_flag) {
            pause(); // Ждём сигнала от ребёнка
        }

        wait(NULL);
        printf("[Parent %d] Дочерний процесс завершён. Выход.\n", (int)getpid());
    }

    return 0;
}
