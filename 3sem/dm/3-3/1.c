#include <stdio.h>
#include <stdlib.h>

// Функция для создания матрицы отношений
int** create_relation_matrix(int m_size) {
    int** R = (int**)malloc(m_size * sizeof(int*));
    for (int i = 0; i < m_size; i++) {
        R[i] = (int*)calloc(m_size, sizeof(int)); // calloc автоматически обнуляет элементы
    }

    // Заполняем матрицу R согласно условию
    for (int x = 1; x <= m_size; x++) {
        for (int y = 1; y <= m_size; y++) {
            if ((x % 2 == 0 && y % 2 == 0 && (x < 7) && (y < 7)) || x == y) {
                R[x-1][y-1] = 1;
            }
        }
    }

    return R;
}

// Функция для формирования массива S
void form_array_S(int* M, int m_size, int** R, int* S) {
    int k = 0;
    for (int i = 0; i < m_size; i++) {
        if (S[i] == 0) {
            k++;
            S[i] = k;
            for (int j = i + 1; j < m_size; j++) {
                if (R[i][j] == 1) {
                    S[j] = k;
                }
            }
        }
    }
}

// Функция для освобождения памяти, выделенной под rez
void deallocate_rez_memory(int** rez, int rows) {
    for (int i = 0; i < rows; i++) {
        free(rez[i]);
    }
    free(rez);
}

void fill_and_print_rez(int** rez, int m_size, int* S, int* x) {
    for (int i = 1; i <= m_size; ++i) {
        rez[S[i - 1]][x[S[i - 1]]] = i;
        x[S[i-1]] += 1;
    }

    for (int i = 1; i < m_size - 1; ++i) {
        for (int j = 0; j < m_size; ++j)
            if (rez[i][j] != 0) printf("%d ", rez[i][j]);
        printf("\n");
    }
}

int main() {
    int M[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int m_size = sizeof(M) / sizeof(M[0]);
    int** A = create_relation_matrix(m_size);
    int* S = (int*)calloc(m_size, sizeof(int));

    form_array_S(M, m_size, A, S);

    int** rez = (int**)malloc(m_size * sizeof(int*));
    for (int i = 0; i < m_size; i++) {
        rez[i] = (int*)malloc(m_size * sizeof(int));
    } // Динамическое выделение памяти для rez

    int x[m_size];
    for (int i = 0; i < m_size; ++i) {
        x[i] = 0;
    }

    fill_and_print_rez(rez, m_size, S, x);

   
    for (int i = 0; i < m_size; i++) {
        free(rez[i]);
    }
    free(rez);

    printf("Матрица отношения A:\n");
    for (int i = 0; i < m_size; i++) {
        for (int j = 0; j < m_size; j++) {
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }

    printf("Массив S: ");
    for (int i = 0; i < m_size; i++) {
        printf("%d ", S[i]);
    }
    printf("\n");

    for (int i = 0; i < m_size; i++) {
        free(A[i]);
    }
    free(A);
    free(S);

    return 0;
}