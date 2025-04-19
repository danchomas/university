#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <iomanip>

using namespace std;

const double EPS = 1e-9;

// Функция для перестановки столбцов в матрице
void rearrangeColumns(vector<vector<double>>& matrix, const vector<int>& basis) {
    int cols = matrix[0].size() - 1; // Исключаем столбец свободных членов
    for (auto& row : matrix) {
        vector<double> new_row;
        // Добавляем базисные столбцы
        for (int b : basis) new_row.push_back(row[b]);
        // Добавляем оставшиеся небазисные столбцы
        for (int c = 0; c < cols; ++c) {
            if (find(basis.begin(), basis.end(), c) == basis.end()) {
                new_row.push_back(row[c]);
            }
        }
        // Добавляем свободный член
        new_row.push_back(row.back());
        row = new_row;
    }
}

// Улучшенный метод Гаусса-Жордана с ведением журнала ведущих столбцов
void gauss_jordan(vector<vector<double>>& matrix, vector<int>& leading_columns) {
    int rows = matrix.size();
    int cols = matrix[0].size() - 1;
    leading_columns.clear();
    int lead = 0;

    for (int r = 0; r < rows && lead < cols; ++r) {
        // Поиск ненулевого элемента в столбце lead начиная с текущей строки
        int i = r;
        while (i < rows && abs(matrix[i][lead]) < EPS) ++i;
        if (i == rows) {
            ++lead;
            --r;
            continue;
        }

        swap(matrix[i], matrix[r]);
        double div = matrix[r][lead];
        for (int j = lead; j <= cols; ++j) matrix[r][j] /= div;

        for (i = 0; i < rows; ++i) {
            if (i != r) {
                double factor = matrix[i][lead];
                for (int j = lead; j <= cols; ++j)
                    matrix[i][j] -= factor * matrix[r][j];
            }
        }
        leading_columns.push_back(lead);
        ++lead;
    }
}

// Функция для проверки допустимости решения (все переменные >= 0)
bool is_feasible(const vector<double>& solution) {
    for (double x : solution) {
        if (x < -EPS) return false;
    }
    return true;
}

// Целевая функция (сумма свободных членов)
double objective_function(const vector<double>& solution) {
    double sum = 0.0;
    for (double x : solution) sum += x;
    return sum;
}

// Функция для проверки, является ли базис допустимым
bool is_valid_basis(const vector<int>& basis, const vector<int>& leading_columns) {
    // Проверяем, что все ведущие столбцы находятся в пределах базиса
    for (int lc : leading_columns) {
        if (lc >= basis.size()) return false;
    }
    return true;
}

// Функция для вывода решения с учетом переставленных столбцов
void print_solution(const vector<vector<double>>& matrix, const vector<int>& basis, const vector<double>& solution) {
    cout << "Базисные переменные: ";
    for (int b : basis) cout << "x" << b + 1 << " ";
    cout << "\nРешение:\n";

    // Создаем список небазисных переменных
    vector<int> non_basis;
    for (int i = 0; i < matrix[0].size() - 1; ++i) {
        if (find(basis.begin(), basis.end(), i) == basis.end()) {
            non_basis.push_back(i);
        }
    }

    for (size_t r = 0; r < matrix.size(); ++r) {
        int lead_col = -1;
        for (size_t c = 0; c < basis.size(); ++c) {
            if (abs(matrix[r][c] - 1.0) < EPS) {
                lead_col = c;
                break;
            }
        }

        if (lead_col == -1) {
            if (abs(matrix[r].back()) > EPS)
                cout << "Система несовместна\n";
            continue;
        }

        int actual_var = basis[lead_col];
        cout << "x" << actual_var + 1 << " = " << fixed << setprecision(2) << matrix[r].back();

        for (size_t c = basis.size(); c < matrix[r].size() - 1; ++c) {
            double coeff = matrix[r][c];
            if (abs(coeff) > EPS) {
                int var_index = non_basis[c - basis.size()];
                if (coeff < 0) {
                    cout << " + " << fixed << setprecision(2) << -coeff << "*x" << var_index + 1;
                }
                else {
                    cout << " - " << fixed << setprecision(2) << coeff << "*x" << var_index + 1;
                }
            }
        }
        cout << endl;
    }
    cout << "-------------------------\n";
}

// Функция для нахождения всех опорных планов
void find_basic_solutions(vector<vector<double>> original, int num_vars) {
    int num_eqs = original.size();
    vector<int> vars(num_vars);
    iota(vars.begin(), vars.end(), 0);

    vector<bool> selector(num_vars);
    fill(selector.begin(), selector.begin() + num_eqs, true);

    vector<vector<double>> feasible_solutions;
    int count = 0;

    do {
        vector<int> basis;
        for (int i = 0; i < num_vars; ++i)
            if (selector[i]) basis.push_back(i);
        if (basis.size() != num_eqs) continue;

        vector<vector<double>> matrix = original;
        rearrangeColumns(matrix, basis);

        vector<int> leading_columns;
        gauss_jordan(matrix, leading_columns);

        cout << "Комбинация базиса " << ++count << ":\n";
        cout << "Преобразованная матрица:\n";
        for (const auto& row : matrix) {
            for (double val : row) cout << fixed << setprecision(2) << setw(8) << val;
            cout << endl;
        }

        if (is_valid_basis(basis, leading_columns)) {
            vector<double> solution(num_vars, 0.0);
            for (size_t r = 0; r < matrix.size(); ++r) {
                for (size_t c = 0; c < basis.size(); ++c) {
                    if (abs(matrix[r][c] - 1.0) < EPS) {
                        solution[basis[c]] = matrix[r].back();
                        break;
                    }
                }
            }

            if (is_feasible(solution)) {
                feasible_solutions.push_back(solution);
                print_solution(matrix, basis, solution);
                cout << "Целевая функция: " << objective_function(solution) << "\n";
                cout << "-------------------------\n";
            }
            else {
                cout << "Решение недопустимо (есть отрицательные переменные)\n";
                cout << "-------------------------\n";
            }
        }
        else {
            cout << "Не является допустимым базисом\n";
            cout << "-------------------------\n";
        }

    } while (prev_permutation(selector.begin(), selector.end()));

    // Поиск оптимального решения
    if (!feasible_solutions.empty()) {
        auto optimal_solution = *min_element(feasible_solutions.begin(), feasible_solutions.end(),
            [](const vector<double>& a, const vector<double>& b) {
                return objective_function(a) < objective_function(b);
            });

        cout << "\nОптимальный опорный план:\n";
        for (double x : optimal_solution) cout << fixed << setprecision(2) << x << " ";
        cout << "\nЦелевая функция: " << objective_function(optimal_solution) << "\n";
    }
    else {
        cout << "\nДопустимые решения отсутствуют!\n";
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    vector<vector<double>> matrix = {
        {-1, 5, -4, -6, 0, 1, -9},
        {8, 1, -1, 0, 2, 3, 8},
        {4, 3, -2, 9, 1, 7, 1}
    };
    find_basic_solutions(matrix, 6);
    return 0;
}