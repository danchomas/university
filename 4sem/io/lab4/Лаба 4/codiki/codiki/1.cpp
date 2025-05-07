#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int get_step(vector<int>& a, vector<int>& b, vector<vector<int>>& C) {
    int min_el = C[0][0];
    pair<int, int> min_el_ind = { 0, 0 };

    // Находим минимальную стоимость перевозки
    for (size_t i = 0; i < a.size(); ++i) {
        for (size_t j = 0; j < b.size(); ++j) {
            if (C[i][j] < min_el) {
                min_el = C[i][j];
                min_el_ind = { i, j };
            }
        }
    }

    // Количество перевезённого груза
    int sum = min(a[min_el_ind.first], b[min_el_ind.second]);

    // Корректируем запас и потребность
    a[min_el_ind.first] -= sum;
    b[min_el_ind.second] -= sum;

    // Считаем стоимость перевозки
    sum *= C[min_el_ind.first][min_el_ind.second];

    // Помечаем клетку как использованную
    C[min_el_ind.first][min_el_ind.second] = INT_MAX;

    return sum;
}

int solve_distributive_method(vector<int>& a, vector<int>& b, vector<vector<int>>& C) {
    int total_sum = 0;

    // Выполняем шаги пока есть потребности
    int total_b = 0;
    for (int val : b) total_b += val;

    while (total_b > 0) {
        total_sum += get_step(a, b, C);
        total_b = 0;
        for (int val : b) total_b += val;
    }

    return total_sum;
}

int main() {
    setlocale(LC_ALL, "Russian");

    vector<int> a = { 23, 24, 21, 15 };       // Вектор запасов
    vector<int> b = { 19, 16, 16, 16, 16 };   // Вектор потребностей
    vector<vector<int>> C = {                // Матрица стоимостей
        {8, 28, 17, 19, 11},
        {27, 5, 10, 6, 19},
        {29, 11, 3, 7, 8},
        {25, 16, 19, 24, 13}
    };

    int result = solve_distributive_method(a, b, C);
    cout << "Минимальная стоимость перевозок: " << result << endl;

    return 0;
}