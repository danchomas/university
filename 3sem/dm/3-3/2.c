#include <stdio.h>
#include <stdlib.h>

void printEquivalenceClasses(int *arr, int size) {
    // Массив для отслеживания уже обработанных элементов
    int *visited = (int *)calloc(size, sizeof(int));

    printf("Классы эквивалентности:\n");

    for (int i = 0; i < size; i++) {
        if (!visited[i]) { // Если элемент еще не обработан
            printf("{ ");
            int current = arr[i];

            // Печатаем класс эквивалентности для текущего элемента
            for (int j = 0; j < size; j++) {
                if (arr[j] == current) {
                    printf("%d ", arr[j]);
                    visited[j] = 1; // Отмечаем элемент как обработанный
                }
            }
            printf("}\n");
        }
    }

    free(visited); // Освобождаем память
}

int main() {
    int arr[] = {1, 2, 2, 3, 1, 4, 4};
    int size = sizeof(arr) / sizeof(arr[0]);

    printEquivalenceClasses(arr, size);

    return 0;
}