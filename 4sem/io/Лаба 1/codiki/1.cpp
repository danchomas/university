#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const double EPS = 1e-9; // Точность для сравнения чисел с плавающей точкой

// Функция для приведения матрицы к приведённому ступенчатому виду
void gaussJordan(vector<vector<double>>& a) {
    int n = a.size();    // Количество уравнений
    int m = a[0].size(); // Количество переменных + 1 (столбец свободных членов)

    for (int row = 0, col = 0; row < n && col < m - 1; ++col) {
        // Поиск строки с максимальным элементом в текущем столбце
        int pivot = row;
        for (int i = row + 1; i < n; ++i)
            if (abs(a[i][col]) > abs(a[pivot][col]))
                pivot = i;

        // Если все элементы в столбце нулевые, переходим к следующему столбцу
        if (abs(a[pivot][col]) < EPS)
            continue;

        // Меняем строки местами
        if (pivot != row)
            swap(a[pivot], a[row]);

        // Нормализация текущей строки (делаем ведущий элемент равным 1)
        double div = a[row][col];
        for (int j = col; j < m; ++j)
            a[row][j] /= div;

        // Обнуляем все элементы в текущем столбце, кроме ведущего
        for (int i = 0; i < n; ++i)
            if (i != row && abs(a[i][col]) > EPS) {
                double factor = a[i][col];
                for (int j = col; j < m; ++j)
                    a[i][j] -= a[row][j] * factor;
            }

        ++row;
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int n, m;
    cout << "Введите количество уравнений и переменных: ";
    cin >> n >> m;

    // Матрица коэффициентов (n x (m + 1))
    vector<vector<double>> a(n, vector<double>(m + 1));

    cout << "Введите коэффициенты системы уравнений:" << endl;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j <= m; ++j)
            cin >> a[i][j];

    // Приведение матрицы к приведённому ступенчатому виду
    gaussJordan(a);

    // Вывод результата
    cout << "Матрица в приведённом ступенчатом виде:" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= m; ++j)
            cout << a[i][j] << " ";
        cout << endl;
    }

    // Анализ решения
    bool hasSolution = true;
    for (int i = 0; i < n; ++i) {
        bool allZero = true;
        for (int j = 0; j < m; ++j)
            if (abs(a[i][j]) > EPS) {
                allZero = false;
                break;
            }
        if (allZero && abs(a[i][m]) > EPS) {
            hasSolution = false;
            break;
        }
    }

    if (!hasSolution) {
        cout << "Система не имеет решений." << endl;
    }
    else {
        cout << "Система имеет решение:" << endl;
        for (int j = 0; j < m; ++j) {
            bool isFree = true;
            for (int i = 0; i < n; ++i)
                if (abs(a[i][j] - 1.0) < EPS) {
                    isFree = false;
                    cout << "x" << j + 1 << " = " << a[i][m] << endl;
                    break;
                }
            if (isFree)
                cout << "x" << j + 1 << " - свободная переменная" << endl;
        }
    }

    return 0;
}