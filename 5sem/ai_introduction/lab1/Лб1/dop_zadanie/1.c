/*
*  Simulated Annealing for IDS Anomaly Detection — Full NSL-KDD version
*  Works with raw KDDTrain+.txt format
*  No preprocessing needed
*/

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>

#define MAX_LOG_ENTRIES 100000
#define NUM_FEATURES 4  // src_bytes, dst_bytes, count, serror_rate

// Структура записи лога
typedef struct {
    float src_bytes;
    float dst_bytes;
    float count;
    float serror_rate;
    int is_anomaly; // 1 = аномалия, 0 = норма
} LogEntry;

LogEntry logs[MAX_LOG_ENTRIES];
int log_count = 0;

// Структура решения (пороги)
typedef struct {
    float thresholds[NUM_FEATURES];
    float energy;
} Solution;

// Загрузка логов из оригинального NSL-KDD файла
int load_logs(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("❌ Не удалось открыть файл: %s\n", filename);
        return -1;
    }

    char line[2048];
    while (fgets(line, sizeof(line), fp) && log_count < MAX_LOG_ENTRIES) {
        // Удаляем \n в конце
        line[strcspn(line, "\n")] = 0;

        // Разбираем CSV
        char *tokens[50];
        int col = 0;
        char *token = strtok(line, ",");
        while (token && col < 50) {
            tokens[col++] = token;
            token = strtok(NULL, ",");
        }

        if (col < 42) continue; // пропускаем битые строки

        // Извлекаем нужные числовые поля
        LogEntry entry;
        entry.src_bytes = atof(tokens[4]);   // src_bytes
        entry.dst_bytes = atof(tokens[5]);   // dst_bytes
        entry.count = atof(tokens[22]);      // count
        entry.serror_rate = atof(tokens[23]); // serror_rate → в NSL-KDD это 23-я колонка для числового значения

        // Определяем аномалию: если метка НЕ "normal."
        entry.is_anomaly = (strcmp(tokens[41], "normal.") != 0) ? 1 : 0;

        logs[log_count++] = entry;
    }

    fclose(fp);
    printf(" Загружено %d записей из %s\n", log_count, filename);
    return log_count;
}

// Изменение решения (аналог tweakSolution)
void tweakSolution(Solution *sol) {
    int idx = rand() % NUM_FEATURES;
    // Изменяем порог на случайную величину (±20% от текущего значения, но не меньше 1)
    float delta = sol->thresholds[idx] * ((float)rand() / RAND_MAX * 0.4 - 0.2);
    sol->thresholds[idx] += delta;
    if (sol->thresholds[idx] < 1.0) sol->thresholds[idx] = 1.0; // порог не может быть слишком маленьким
}

// Вычисление энергии (ошибок классификации)
void computeEnergy(Solution *sol) {
    int fp = 0, fn = 0;

    for (int i = 0; i < log_count; i++) {
        int triggers = 0;
        if (logs[i].src_bytes > sol->thresholds[0]) triggers++;
        if (logs[i].dst_bytes > sol->thresholds[1]) triggers++;
        if (logs[i].count > sol->thresholds[2]) triggers++;
        if (logs[i].serror_rate > sol->thresholds[3]) triggers++;

        // Аномалия, если сработало ≥2 триггера
        int predicted_anomaly = (triggers >= 2) ? 1 : 0;

        if (predicted_anomaly && !logs[i].is_anomaly) fp++; // ложное срабатывание
        if (!predicted_anomaly && logs[i].is_anomaly) fn++; // пропущенная аномалия
    }

    sol->energy = (float)(fp + fn); // минимизируем общее число ошибок
}

// Копирование решения
void copySolution(Solution *dest, Solution *src) {
    for (int i = 0; i < NUM_FEATURES; i++) {
        dest->thresholds[i] = src->thresholds[i];
    }
    dest->energy = src->energy;
}

// Инициализация решения случайными порогами
void initializeSolution(Solution *sol) {
    sol->thresholds[0] = 1000.0 + ((float)rand() / RAND_MAX) * 5000.0; // src_bytes: 1000..6000
    sol->thresholds[1] = 1000.0 + ((float)rand() / RAND_MAX) * 5000.0; // dst_bytes
    sol->thresholds[2] = 10.0 + ((float)rand() / RAND_MAX) * 100.0;    // count
    sol->thresholds[3] = 0.1 + ((float)rand() / RAND_MAX) * 0.8;       // serror_rate: 0.1..0.9
    computeEnergy(sol);
}

// Вывод решения
void printSolution(Solution *sol) {
    printf("\n Лучшие пороги:\n");
    printf("   src_bytes  > %.1f\n", sol->thresholds[0]);
    printf("   dst_bytes  > %.1f\n", sol->thresholds[1]);
    printf("   count      > %.1f\n", sol->thresholds[2]);
    printf("   serror_rate > %.3f\n", sol->thresholds[3]);
    printf("❌ Ошибки (энергия): %.0f (FP+FN)\n", sol->energy);
}

// Вывод примеров аномалий по лучшим порогам
void printAnomalies(Solution *sol, int max_examples) {
    printf("\n🔍 Примеры обнаруженных аномалий (первые %d):\n", max_examples);
    int shown = 0;
    for (int i = 0; i < log_count && shown < max_examples; i++) {
        int triggers = 0;
        if (logs[i].src_bytes > sol->thresholds[0]) triggers++;
        if (logs[i].dst_bytes > sol->thresholds[1]) triggers++;
        if (logs[i].count > sol->thresholds[2]) triggers++;
        if (logs[i].serror_rate > sol->thresholds[3]) triggers++;

        int predicted_anomaly = (triggers >= 2) ? 1 : 0;
        if (predicted_anomaly) {
            printf("   [%d] src=%.0f, dst=%.0f, count=%.0f, serror=%.3f → %s (реальность: %s)\n",
                i+1,
                logs[i].src_bytes, logs[i].dst_bytes, logs[i].count, logs[i].serror_rate,
                "АНОМАЛИЯ", logs[i].is_anomaly ? "аномалия" : "норма");
            shown++;
        }
    }
}

// Главная функция
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Использование: %s <путь_к_файлу_логов>\n", argv[0]);
        printf("Пример: %s KDDTrain+.txt\n", argv[0]);
        return 1;
    }

    srand(time(NULL));

    // Загрузка логов
    if (load_logs(argv[1]) <= 0) {
        return 1;
    }

    // Параметры SA
    float temperature = 1.0;
    float final_temperature = 0.1;
    float alpha = 0.985;
    int steps_per_change = 100;

    Solution current, working, best;

    initializeSolution(&current);
    best.energy = 1e9; // большое число

    copySolution(&working, &current);

    int timer = 0;
    FILE *fp = fopen("sa_stats.txt", "w");
    if (!fp) {
        printf("❌ Не удалось создать файл sa_stats.txt\n");
        return 1;
    }

    printf("\n Запуск алгоритма отжига для поиска оптимальных порогов аномалий...\n");

    while (temperature > final_temperature) {
        int accepted = 0;

        for (int step = 0; step < steps_per_change; step++) {
            int useNew = 0;
            tweakSolution(&working);
            computeEnergy(&working);

            if (working.energy <= current.energy) {
                useNew = 1;
            } else {
                float test = (float)rand() / RAND_MAX;
                float delta = working.energy - current.energy;
                float calc = exp(-delta / temperature);
                if (calc > test) {
                    accepted++;
                    useNew = 1;
                }
            }

            if (useNew) {
                copySolution(&current, &working);
                if (current.energy < best.energy) {
                    copySolution(&best, &current);
                    printf("\n Новое лучшее решение (итерация %d, T=%.2f):\n", timer, temperature);
                    printSolution(&best);
                }
            } else {
                copySolution(&working, &current);
            }
        }

        fprintf(fp, "%d %.4f %.2f %d\n", timer, temperature, best.energy, accepted);
        printf("Итерация %d: T=%.2f, лучшая энергия=%.0f, принято плохих решений=%d\n",
            timer, temperature, best.energy, accepted);

        temperature *= alpha;
        timer++;

        if (best.energy == 0) {
            printf("\n Идеальное решение найдено! Ошибок нет.\n");
            break;
        }
    }

    fclose(fp);

    printf("\n\n ФИНАЛЬНЫЙ РЕЗУЛЬТАТ:\n");
    printSolution(&best);
    printAnomalies(&best, 10);

    return 0;
}
