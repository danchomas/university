#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 7
#define MAX_PATH_LENGTH 10 // Задаем максимальную длину пути

void matrixInput(bool matrix[MAX_SIZE][MAX_SIZE]) {
    for (int i = 0; i < MAX_SIZE; i++) {
        for (int j = 0; j < MAX_SIZE; j++) {
            int buf;
            scanf("%d", &buf);
            matrix[i][j] = buf != 0; // Если buf не равен 0, устанавливаем true
        }
    }
}

void outputVector(int v[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");
}

void outputVertex(int res[][MAX_PATH_LENGTH], int sizes[], int sizeCount) {
    for (int i = 0; i < sizeCount; i++) {
        outputVector(res[i], sizes[i]);
    }
}

void GetMaxChains_(bool matrix[MAX_SIZE][MAX_SIZE], int G[], int gSize, int res[][MAX_PATH_LENGTH], int *resultCount, int sizes[]) {
    bool areNoWaysToAnyPoint = true;

    for (int i = 0; i < MAX_SIZE && gSize <= MAX_SIZE; i++) {
        if (matrix[i][G[gSize - 1] - 1]) {
            bool isNoPointInG = true;
            for (int j = 0; j < gSize && isNoPointInG; j++) {
                if (G[j] == (i + 1)) {
                    isNoPointInG = false;
                }
            }

            areNoWaysToAnyPoint = areNoWaysToAnyPoint && !isNoPointInG;

            if (isNoPointInG) {
                G[gSize] = i + 1;
                GetMaxChains_(matrix, G, gSize + 1, res, resultCount, sizes);
            }
        }
    }

    if (areNoWaysToAnyPoint) {
        for (int j = 0; j < gSize; j++) {
            res[*resultCount][j] = G[j];
        }
        sizes[*resultCount] = gSize;
        (*resultCount)++;
    }
}

void GetMaxChains(bool matrix[MAX_SIZE][MAX_SIZE], int v, int res[][MAX_PATH_LENGTH], int *resultCount, int sizes[]) {
    int G[MAX_PATH_LENGTH] = {0};
    G[0] = v; // Начинаем с вершины v
    GetMaxChains_(matrix, G, 1, res, resultCount, sizes);
}

int main() {
    bool matrix[MAX_SIZE][MAX_SIZE] = { false };
    matrixInput(matrix); 

    int res[MAX_SIZE * MAX_SIZE][MAX_PATH_LENGTH] = {0}; // Массив для хранения цепочек
    int sizes[MAX_SIZE * MAX_SIZE] = {0}; // Для хранения длин цепочек
    int resultCount = 0; // Количество найденных цепочек

    GetMaxChains(matrix, 1, res, &resultCount, sizes);
    outputVertex(res, sizes, resultCount);

    return 0;
}
