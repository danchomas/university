/*#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <numeric>

using namespace std;

const double EPS = 1e-9; // Точность для сравнения чисел с плавающей точкой

// Функция приведения матрицы к ступенчато-улучшенной форме методом Гаусса-Жордана
void gauss_jordan(vector<vector<double>>& matrix) {
    int rows = matrix.size();    // Количество уравнений
    int cols = matrix[0].size(); // Количество столбцов (переменные + свободные члены)
    int lead = 0; // Текущий ведущий столбец

    // Поочередная обработка каждой строки
    for (int r = 0; r < rows; r++) {
        if (lead >= cols) break; // Выход, если все столбцы обработаны

        // Поиск ненулевого элемента в текущем столбце
        int i = r;
        while (i < rows && abs(matrix[i][lead]) < EPS) i++;
        if (i == rows) { // Если столбец нулевой, переходим к следующему
            lead++;
            r--;
            continue;
        }

        swap(matrix[i], matrix[r]); // Перемещаем строку с ненулевым элементом наверх

        // Нормировка строки по ведущему элементу
        double lv = matrix[r][lead];
        for (int j = 0; j < cols; j++) {
            matrix[r][j] /= lv;
        }

        // Обнуление элементов текущего столбца в других строках
        for (int i = 0; i < rows; i++) {
            if (i != r) {
                double factor = matrix[i][lead];
                for (int j = 0; j < cols; j++) {
                    matrix[i][j] -= factor * matrix[r][j];
                }
            }
        }
        lead++; // Переход к следующему столбцу
    }
}

// Функция вывода решения системы в зависимости от базиса
void print_solution(const vector<vector<double>>& matrix, const vector<int>& basis) {
    int rows = matrix.size();
    int cols = matrix[0].size();

    // Вывод информации о базисных переменных
    cout << "Базисные переменные: ";
    for (int b : basis) cout << "x" << b + 1 << " ";
    cout << "\nРешение:\n";

    // Определение свободных переменных (не входящих в базис)
    vector<bool> is_free(cols - 1, true);
    for (int b : basis) is_free[b] = false;

    bool contradiction = false;

    // Построение уравнений для базисных переменных
    for (int r = 0; r < rows; r++) {
        int lead_col = -1;
        // Поиск ведущего элемента (1 в ступенчатом виде)
        for (int c = 0; c < cols - 1; c++) {
            if (abs(matrix[r][c] - 1.0) < EPS) {
                lead_col = c;
                break;
            }
        }

        if (lead_col == -1) { // Случай нулевой строки
            if (abs(matrix[r][cols - 1]) > EPS) {
                cout << "Нет решений (противоречие)\n";
                contradiction = true;
            }
            continue;
        }

        // Формирование уравнения для базисной переменной
        cout << "x" << lead_col + 1 << " = " << matrix[r][cols - 1];
        // Добавление свободных переменных в уравнение
        for (int c = 0; c < cols - 1; c++) {
            if (c != lead_col && is_free[c] && abs(matrix[r][c]) > EPS) {
                cout << " - (" << matrix[r][c] << ")*x" << c + 1;
            }
        }
        cout << endl;
    }
    if (!contradiction) cout << "-------------------------" << endl;
}

// Функция перебора всех возможных базисных решений
void find_basic_solutions(vector<vector<double>> matrix, int num_vars) {
    int num_eqs = matrix.size(); // Количество уравнений
    vector<int> vars(num_vars);
    iota(vars.begin(), vars.end(), 0); // Заполнение 0,1,2,...,num_vars-1

    // Генерация сочетаний для выбора базисных переменных
    vector<bool> selector(num_vars);
    fill(selector.begin(), selector.begin() + num_eqs, true);

    do {
        // Формирование текущего базиса
        vector<int> basis;
        for (int i = 0; i < num_vars; i++) {
            if (selector[i]) basis.push_back(i);
        }

        // Копирование исходной матрицы для сохранения исходных данных
        auto temp_matrix = matrix;

        // Применение метода Гаусса-Жордана
        gauss_jordan(temp_matrix);
        print_solution(temp_matrix, basis);

    } while (prev_permutation(selector.begin(), selector.end())); // Перебор всех сочетаний
}

int main() {
    setlocale(LC_ALL, "Russian");
    // Исходная расширенная матрица системы:
    // Каждая строка имеет вид [коэффициенты | свободный член]
    vector<vector<double>> matrix = {
        {-1, 5, -4, -6, 0, 1, -9},
        {8, 1, -1, 0, 2, 3, 8},
        {4, 3, -2, 9, 1, 7, 1}
    };
    // Поиск всех базисных решений для системы с 6 переменными
    find_basic_solutions(matrix, 6);
    return 0;
}*/