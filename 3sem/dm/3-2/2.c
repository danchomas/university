#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_ROWS 100
#define MAX_COLS 100

typedef struct matrix {
    bool values[MAX_ROWS][MAX_COLS]; // элементы матрицы
    int nRows;                       // количество рядов
    int nCols;                       // количество столбцов
} matrix;

// Проверяет включение отношения между двумя матрицами
bool relationInclusion(const matrix A, const matrix B) {
    for (int x = 0; x < A.nRows; x++) {
        for (int y = 0; y < A.nCols; y++) {
            if (!(A.values[x][y] <= B.values[x][y])) {
                return false;
            }
        }
    }
    return true;
}

// Объединение двух матриц
void relationUnion(const matrix *A, const matrix *B, matrix *C) {
    for (int x = 0; x < A->nRows; x++) {
        for (int y = 0; y < A->nCols; y++) {
            C->values[x][y] = (A->values[x][y] || B->values[x][y]);
        }
    }
}

// Композиция двух матриц
void relationComposition(const matrix *A, const matrix *B, matrix *C) {
    for (int x = 0; x < A->nRows; x++) {
        for (int y = 0; y < A->nCols; y++) {
            C->values[x][y] = false;
            for (int z = 0; z < A->nCols; z++) {
                C->values[x][y] = C->values[x][y] || (A->values[x][z] && B->values[z][y]);
            }
        }
    }
}

// Копирование одной матрицы в другую
void copyMatrix(const matrix *A, matrix *B) {
    memcpy(B->values, A->values, sizeof(bool) * A->nRows * A->nCols);
    B->nRows = A->nRows;
    B->nCols = A->nCols;
}

// Вычисляет транзитивное замыкание матрицы
matrix calculateTransitiveClosureA(const matrix A) {
    matrix C = { .nRows = A.nRows, .nCols = A.nCols };
    matrix S = { .nRows = A.nRows, .nCols = A.nCols };
    copyMatrix(&A, &C);
    relationComposition(&C, &C, &S);
    while (!relationInclusion(S, C)) {
        relationUnion(&C, &S, &C);
        relationComposition(&S, &A, &S);
    }
    return C;
}

int main() {
    // Пример использования
    matrix A = { .nRows = 10, .nCols = 10 };
    for (int i = 0; i < .nRows - 1; i++){
        A[i][i+1] = 1;
    }

    matrix result = calculateTransitiveClosureA(A);

    printf("Транзитивное замыкание матрицы:\n");
    for (int i = 0; i < result.nRows; i++) {
        for (int j = 0; j < result.nCols; j++) {
            printf("%d ", result.values[i][j]);
        }
        printf("\n");
    }

    return 0;
}