#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <time.h>

static volatile pid_t child_pid = 0;
static volatile sig_atomic_t stop_flag = 0;
static volatile sig_atomic_t exchange_count = 0; // Счётчик полных обменов

// Глобальное время старта (в наносекундах)
static struct timespec start_time;

// Преобразуем timespec в double (секунды)
double timespec_to_sec(const struct timespec *ts) {
    return ts->tv_sec + ts->tv_nsec / 1e9;
}

// Обработчик в родителе: получает "понг" от дочернего процесса (SIGUSR2)
void parent_handler(int signo, siginfo_t *si, void *context) {
    int val = si->si_value.sival_int;
    printf("[Parent %d] получил число: %d\n", (int)getpid(), val);

    exchange_count++; // Завершился один полный обмен

    // Генерируем новое число и отправляем "пинг"
    int new_val = rand() % 100;
    printf("[Parent %d] отправляет число: %d\n", (int)getpid(), new_val);
    union sigval sv;
    sv.sival_int = new_val;
    sigqueue(child_pid, SIGUSR1, sv);
}

// Обработчик в дочернем процессе: получает "пинг" от родителя (SIGUSR1)
void child_handler(int signo, siginfo_t *si, void *context) {
    int val = si->si_value.sival_int;
    printf("[Child %d] получил число: %d\n", (int)getpid(), val);

    int new_val = rand() % 100;
    printf("[Child %d] отправляет число: %d\n", (int)getpid(), new_val);
    union sigval sv;
    sv.sival_int = new_val;
    sigqueue(getppid(), SIGUSR2, sv);
}

// Обработчик SIGINT — только для родителя
void stop_handler(int signo) {
    if (stop_flag) return; // Защита от повторного вызова
    stop_flag = 1;

    printf("\n[Parent %d] Получен SIGINT. Завершение...\n", (int)getpid());

    if (child_pid > 0) {
        kill(child_pid, SIGTERM);
    }

    // Подсчёт времени и скорости
    struct timespec end_time;
    clock_gettime(CLOCK_MONOTONIC, &end_time);
    double elapsed = timespec_to_sec(&end_time) - timespec_to_sec(&start_time);

    if (elapsed <= 0) elapsed = 1e-9; // избегаем деления на ноль

    double exchanges_per_sec = (double)exchange_count / elapsed;
    printf("[Parent %d] Завершено обменов: %d за %.3f секунд → %.2f обменов/сек\n",
           (int)getpid(), (int)exchange_count, elapsed, exchanges_per_sec);
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

    signal(SIGINT, stop_handler);

    child_pid = fork();
    if (child_pid == -1) {
        perror("fork");
        exit(1);
    }

    if (child_pid == 0) {
        // Дочерний процесс
        signal(SIGINT, SIG_DFL); // Стандартное поведение (или можно игнорировать)
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
        // Ждём немного, чтобы дочерний успел установить обработчик
        usleep(10000); // 10 мс — достаточно, без sleep(1)

        // Запускаем таймер
        clock_gettime(CLOCK_MONOTONIC, &start_time);

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
