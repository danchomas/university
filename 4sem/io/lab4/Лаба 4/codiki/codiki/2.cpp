#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <string>
#include <sstream>

using namespace std;

const int INF = numeric_limits<int>::max();

struct Cell {
    int i, j;
};

vector<Cell> find_cycle(const vector<Cell>& basis, Cell entering_cell) {
    unordered_map<string, vector<string>> graph;
    unordered_map<string, string> parent;
    unordered_set<string> visited;

    // Строим граф
    for (size_t idx = 0; idx < basis.size(); ++idx) {
        const Cell& cell = basis[idx];
        string row = "r" + std::to_string(cell.i);
        string col = "c" + std::to_string(cell.j);
        graph[row].push_back(col);
        graph[col].push_back(row);
    }

    // Добавляем входящую клетку
    string start_row = "r" + std::to_string(entering_cell.i);
    string start_col = "c" + std::to_string(entering_cell.j);
    graph[start_row].push_back(start_col);
    graph[start_col].push_back(start_row);

    // Ищем цикл
    stack<pair<string, string>> s;
    s.push(make_pair(start_row, ""));
    vector<string> cycle;

    while (!s.empty()) {
        pair<string, string> node_pair = s.top();
        s.pop();
        string node = node_pair.first;
        string prev = node_pair.second;

        if (visited.count(node)) {
            // Нашли цикл
            string current = node;
            while (current != "") {
                cycle.push_back(current);
                current = parent[current];
            }
            reverse(cycle.begin(), cycle.end());
            break;
        }

        visited.insert(node);
        parent[node] = prev;

        for (size_t i = 0; i < graph[node].size(); ++i) {
            const string& neighbor = graph[node][i];
            if (neighbor != prev) {
                s.push(make_pair(neighbor, node));
            }
        }
    }

    // Преобразуем в координаты клеток
    vector<Cell> cycle_coords;
    for (size_t i = 0; i < cycle.size(); ++i) {
        if (cycle[i][0] == 'r') {
            if (i + 1 < cycle.size()) {
                string row_str = cycle[i].substr(1);
                string col_str = cycle[i + 1].substr(1);
                int row = atoi(row_str.c_str());
                int col = atoi(col_str.c_str());
                cycle_coords.push_back({ row, col });
            }
        }
    }

    return cycle_coords;
}

vector<vector<int>> solve_potentials_method(vector<int> a, vector<int> b, vector<vector<int>> C) {
    int m = static_cast<int>(a.size());
    int n = static_cast<int>(b.size());
    vector<vector<int>> X(m, vector<int>(n, 0));
    vector<int> remaining_a = a;
    vector<int> remaining_b = b;

    // Построение начального опорного плана методом минимальной стоимости
    while (true) {
        bool has_remaining = false;
        for (size_t i = 0; i < remaining_a.size(); ++i) {
            if (remaining_a[i] > 0) {
                has_remaining = true;
                break;
            }
        }
        if (!has_remaining) break;

        int min_cost = INF;
        Cell min_cell = { -1, -1 };

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (remaining_a[i] > 0 && remaining_b[j] > 0 && C[i][j] < min_cost) {
                    min_cost = C[i][j];
                    min_cell.i = i;
                    min_cell.j = j;
                }
            }
        }

        if (min_cell.i == -1) break;

        int amount = min(remaining_a[min_cell.i], remaining_b[min_cell.j]);
        X[min_cell.i][min_cell.j] = amount;
        remaining_a[min_cell.i] -= amount;
        remaining_b[min_cell.j] -= amount;
    }

    // Метод потенциалов
    int iteration = 0;
    const int max_iterations = 100;

    while (iteration++ < max_iterations) {
        vector<int> u(m, 0);
        vector<int> v(n, 0);
        vector<Cell> basis;

        // Собираем базисные клетки
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (X[i][j] > 0) {
                    Cell cell;
                    cell.i = i;
                    cell.j = j;
                    basis.push_back(cell);
                }
            }
        }

        // Вычисляем потенциалы
        bool changed;
        do {
            changed = false;
            for (size_t idx = 0; idx < basis.size(); ++idx) {
                const Cell& cell = basis[idx];
                if (u[cell.i] != 0 && v[cell.j] == 0) {
                    v[cell.j] = C[cell.i][cell.j] - u[cell.i];
                    changed = true;
                }
                else if (v[cell.j] != 0 && u[cell.i] == 0) {
                    u[cell.i] = C[cell.i][cell.j] - v[cell.j];
                    changed = true;
                }
            }
        } while (changed);

        // Проверка оптимальности
        bool optimal = true;
        Cell entering_cell = { -1, -1 };
        int min_delta = 0;

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (X[i][j] == 0) {
                    int delta = C[i][j] - (u[i] + v[j]);
                    if (delta < min_delta) {
                        min_delta = delta;
                        optimal = false;
                        entering_cell.i = i;
                        entering_cell.j = j;
                    }
                }
            }
        }

        if (optimal) break;

        // Находим цикл пересчета
        vector<Cell> cycle = find_cycle(basis, entering_cell);

        // Находим минимальное значение в минусовых клетках
        int theta = INF;
        for (size_t i = 1; i < cycle.size(); i += 2) {
            theta = min(theta, X[cycle[i].i][cycle[i].j]);
        }

        // Корректируем план
        for (size_t i = 0; i < cycle.size(); ++i) {
            int row = cycle[i].i;
            int col = cycle[i].j;
            if (i % 2 == 0) { // Плюсовые клетки
                X[row][col] += theta;
            }
            else { // Минусовые клетки
                X[row][col] -= theta;
            }
        }
    }

    return X;
}

int main() {
    setlocale(LC_ALL, "Russian");

    vector<int> a = { 23, 24, 21, 15 };
    vector<int> b = { 19, 16, 16, 16, 16 };
    vector<vector<int>> C = {
        {8, 28, 17, 19, 11},
        {27, 5, 10, 6, 19},
        {29, 11, 3, 7, 8},
        {25, 16, 19, 24, 13}
    };

    vector<vector<int>> solution = solve_potentials_method(a, b, C);

    // Вычисляем общую стоимость
    int total_cost = 0;
    for (size_t i = 0; i < solution.size(); ++i) {
        for (size_t j = 0; j < solution[i].size(); ++j) {
            total_cost += solution[i][j] * C[i][j];
        }
    }

    cout << "Минимальная стоимость перевозок: " << total_cost << endl;

    return 0;
}