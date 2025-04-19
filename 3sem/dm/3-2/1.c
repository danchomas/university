#include <stdio.h>
#include <stdbool.h>

#define SIZE 10

void composition(int A[SIZE][SIZE], int B[SIZE][SIZE], int result[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            result[i][j] = 0;
            for (int k = 0; k < SIZE; k++) {
                result[i][j] |= (A[i][k] && B[k][j]);
            }
        }
    }
}

void unionRelations(int A[SIZE][SIZE], int B[SIZE][SIZE], int result[SIZE][SIZE])
{
for (int i = 0; i < SIZE; i++) {
for (int j = 0; j < SIZE; j++) {
result[i][j] = A[i][j] || B[i][j];
}
}
}

void copyMatrix(int source[SIZE][SIZE], int destination[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            destination[i][j] = source[i][j];
        }
    }
}

bool isSubset(int A[SIZE][SIZE], int B[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (A[i][j] && !B[i][j]) {
                return false;
            }
        }
    }
    return true;
}


int transitiveClosure(int A[SIZE][SIZE], int C[SIZE][SIZE], int* comparisons) {
    int S[SIZE][SIZE];
    int compositions = 0;
    copyMatrix(A, C);

    composition(A, A, S);

    while (!isSubset(S, C)) {
        unionRelations(C, S, C);
        composition(S, A, S);
        compositions++;
    }
    return compositions;
}

void printMatrix(int matrix[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int A[SIZE][SIZE] = {0};
    for (int i = 0; i < SIZE - 1; i++){
        A[i][i+1] = 1;
    }

    int C[SIZE][SIZE];
    printf("Исходная матрица A:\n");
    printMatrix(A);
    
    int comparisons = 0;
    int comp = transitiveClosure(A, C, &comparisons);
    printf("Матрица транзитивного замыкания C:\n");
    printMatrix(C);
    
    printf("Количество композиций: %d\n", comp);
    
    return 0;
}