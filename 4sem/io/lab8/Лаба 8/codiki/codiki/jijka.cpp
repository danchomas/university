#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

using namespace std;

const double EPS = 1e-9;

struct SimplexResult {
    bool success;
    double optimal_z;
    vector<double> x;
};

vector<vector<double>> create_tableau(const vector<vector<double>>& A, const vector<double>& b, const vector<double>& c, bool phase1, int& num_artificial) {
    int m = A.size();
    int n_vars = A[0].size();
    num_artificial = phase1 ? m : 0;

    vector<vector<double>> tableau(m + 1, vector<double>(n_vars + m + num_artificial + 1, 0.0));

    // Заполнение ограничений
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n_vars; ++j) {
            tableau[i][j] = A[i][j];
        }
        tableau[i][n_vars + i] = 1.0; // Slack переменные
        if (phase1) {
            tableau[i][n_vars + m + i] = 1.0; // Искусственные переменные
        }
        tableau[i].back() = b[i];
    }

    // Целевая функция фазы 1
    if (phase1) {
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < tableau[0].size(); ++j) {
                tableau[m][j] -= tableau[i][j];
            }
        }
    }
    else {
        for (int j = 0; j < c.size(); ++j) {
            tableau[m][j] = -c[j]; // Минимизация в стандартной форме
        }
    }

    return tableau;
}

SimplexResult simplex_method(vector<vector<double>> tableau, int num_vars, bool phase1, int num_artificial) {
    int m = tableau.size() - 1;
    int n = tableau[0].size() - 1;

    while (true) {
        // Выбор входящей переменной
        int pivot_col = -1;
        double min_val = 0;
        for (int j = 0; j < n; ++j) {
            if (tableau[m][j] < min_val - EPS) {
                min_val = tableau[m][j];
                pivot_col = j;
            }
        }
        if (pivot_col == -1) break;

        // Выбор исходящей переменной
        int pivot_row = -1;
        double min_ratio = numeric_limits<double>::max();
        for (int i = 0; i < m; ++i) {
            if (tableau[i][pivot_col] > EPS) {
                double ratio = tableau[i][n] / tableau[i][pivot_col];
                if (ratio < min_ratio - EPS) {
                    min_ratio = ratio;
                    pivot_row = i;
                }
            }
        }
        if (pivot_row == -1) return { false, 0.0, {} };

        // Нормализация строки
        double pivot = tableau[pivot_row][pivot_col];
        for (int j = 0; j <= n; ++j) {
            tableau[pivot_row][j] /= pivot;
        }

        // Исключение Гаусса
        for (int i = 0; i <= m; ++i) {
            if (i != pivot_row && abs(tableau[i][pivot_col]) > EPS) {
                double factor = tableau[i][pivot_col];
                for (int j = 0; j <= n; ++j) {
                    tableau[i][j] -= factor * tableau[pivot_row][j];
                }
            }
        }
    }

    // Проверка допустимости (фаза 1)
    if (phase1 && abs(tableau[m][n]) > EPS) {
        return { false, 0.0, {} };
    }

    // Извлечение решения
    vector<double> solution(num_vars, 0.0);
    for (int j = 0; j < num_vars; ++j) {
        bool is_basic = true;
        int pivot_row = -1;
        for (int i = 0; i < m; ++i) {
            if (abs(tableau[i][j]) > EPS) {
                if (abs(tableau[i][j] - 1.0) < EPS && pivot_row == -1) {
                    pivot_row = i;
                }
                else {
                    is_basic = false;
                    break;
                }
            }
        }
        if (is_basic && pivot_row != -1) {
            solution[j] = tableau[pivot_row][n];
        }
    }

    return { true, phase1 ? 0.0 : -tableau[m][n], solution };
}

SimplexResult solve_dlp() {
    // Исходные ограничения (Ax <= b)
    vector<vector<double>> A = {
        {6, 1, 1, 3},    // 6x1 + x2 + x3 + 3x4 <= 280
        {1, 0, 3, 2},    // x1 + 3x3 + 2x4 <= 70
        {2, 4, 1, 0}     // 2x1 + 4x2 + x3 <= 320
    };
    vector<double> b = { 280, 70, 320 };
    vector<double> c = { 9, 3, 2, 1 };  // Числитель
    vector<double> d = { 2, 1, 3, 1 };  // Знаменатель

    // Преобразование переменных x_i = y_i / t
    int m = A.size();
    int n = A[0].size();

    // Добавляем переменную t и slack-переменные
    vector<vector<double>> new_A;
    vector<double> new_b;
    for (int i = 0; i < m; ++i) {
        vector<double> row(n + 1, 0.0); // y1, y2, y3, y4, t
        for (int j = 0; j < n; ++j) {
            row[j] = A[i][j];
        }
        row[n] = -b[i]; // -b_i * t
        new_A.push_back(row);
        new_b.push_back(0.0); // <= 0
    }

    // Ограничение знаменателя: 2y1 + y2 + 3y3 + y4 = 1
    vector<double> denom_row(n + 1, 0.0);
    for (int j = 0; j < n; ++j) {
        denom_row[j] = d[j];
    }
    denom_row[n] = -1.0; // 2y1 + y2 + 3y3 + y4 - t = 1
    new_A.push_back(denom_row);
    new_b.push_back(1.0);

    // Целевая функция: 9y1 + 3y2 + 2y3 + y4 -> max
    vector<double> new_c(n + 1, 0.0);
    for (int j = 0; j < n; ++j) {
        new_c[j] = c[j];
    }

    // Фаза 1: Поиск допустимого решения
    int num_artificial;
    auto tableau_phase1 = create_tableau(new_A, new_b, new_c, true, num_artificial);
    auto phase1_result = simplex_method(tableau_phase1, n + 1, true, num_artificial);

    if (!phase1_result.success) {
        return { false, 0.0, {} };
    }

    // Фаза 2: Оптимизация
    auto tableau_phase2 = create_tableau(new_A, new_b, new_c, false, num_artificial);
    auto phase2_result = simplex_method(tableau_phase2, n + 1, false, 0);

    if (!phase2_result.success) {
        return { false, 0.0, {} };
    }

    // Извлечение решения
    double t = phase2_result.x[n];
    if (t < EPS) {
        return { false, 0.0, {} };
    }

    vector<double> x(n);
    for (int i = 0; i < n; ++i) {
        x[i] = phase2_result.x[i] / t;
    }

    double numerator = 0.0, denominator = 0.0;
    for (int i = 0; i < n; ++i) {
        numerator += c[i] * x[i];
        denominator += d[i] * x[i];
    }
    double z = numerator / denominator;

    return { true, z, x };
}

int main() {
    SimplexResult result = solve_dlp();
    if (result.success) {
        cout << "Optimal solution found:\n";
        cout << "x1 = " << result.x[0] << "\n";
        cout << "x2 = " << result.x[1] << "\n";
        cout << "x3 = " << result.x[2] << "\n";
        cout << "x4 = " << result.x[3] << "\n";
        cout << "z = " << result.optimal_z << "\n";
    }
    else {
        cout << "No feasible solution exists\n";
    }
    return 0;
}