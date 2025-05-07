/*#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <numeric>

using namespace std;

const double EPS = 1e-9; // �������� ��� ��������� ����� � ��������� ������

// ������� ���������� ������� � ����������-���������� ����� ������� ������-�������
void gauss_jordan(vector<vector<double>>& matrix) {
    int rows = matrix.size();    // ���������� ���������
    int cols = matrix[0].size(); // ���������� �������� (���������� + ��������� �����)
    int lead = 0; // ������� ������� �������

    // ����������� ��������� ������ ������
    for (int r = 0; r < rows; r++) {
        if (lead >= cols) break; // �����, ���� ��� ������� ����������

        // ����� ���������� �������� � ������� �������
        int i = r;
        while (i < rows && abs(matrix[i][lead]) < EPS) i++;
        if (i == rows) { // ���� ������� �������, ��������� � ����������
            lead++;
            r--;
            continue;
        }

        swap(matrix[i], matrix[r]); // ���������� ������ � ��������� ��������� ������

        // ���������� ������ �� �������� ��������
        double lv = matrix[r][lead];
        for (int j = 0; j < cols; j++) {
            matrix[r][j] /= lv;
        }

        // ��������� ��������� �������� ������� � ������ �������
        for (int i = 0; i < rows; i++) {
            if (i != r) {
                double factor = matrix[i][lead];
                for (int j = 0; j < cols; j++) {
                    matrix[i][j] -= factor * matrix[r][j];
                }
            }
        }
        lead++; // ������� � ���������� �������
    }
}

// ������� ������ ������� ������� � ����������� �� ������
void print_solution(const vector<vector<double>>& matrix, const vector<int>& basis) {
    int rows = matrix.size();
    int cols = matrix[0].size();

    // ����� ���������� � �������� ����������
    cout << "�������� ����������: ";
    for (int b : basis) cout << "x" << b + 1 << " ";
    cout << "\n�������:\n";

    // ����������� ��������� ���������� (�� �������� � �����)
    vector<bool> is_free(cols - 1, true);
    for (int b : basis) is_free[b] = false;

    bool contradiction = false;

    // ���������� ��������� ��� �������� ����������
    for (int r = 0; r < rows; r++) {
        int lead_col = -1;
        // ����� �������� �������� (1 � ����������� ����)
        for (int c = 0; c < cols - 1; c++) {
            if (abs(matrix[r][c] - 1.0) < EPS) {
                lead_col = c;
                break;
            }
        }

        if (lead_col == -1) { // ������ ������� ������
            if (abs(matrix[r][cols - 1]) > EPS) {
                cout << "��� ������� (������������)\n";
                contradiction = true;
            }
            continue;
        }

        // ������������ ��������� ��� �������� ����������
        cout << "x" << lead_col + 1 << " = " << matrix[r][cols - 1];
        // ���������� ��������� ���������� � ���������
        for (int c = 0; c < cols - 1; c++) {
            if (c != lead_col && is_free[c] && abs(matrix[r][c]) > EPS) {
                cout << " - (" << matrix[r][c] << ")*x" << c + 1;
            }
        }
        cout << endl;
    }
    if (!contradiction) cout << "-------------------------" << endl;
}

// ������� �������� ���� ��������� �������� �������
void find_basic_solutions(vector<vector<double>> matrix, int num_vars) {
    int num_eqs = matrix.size(); // ���������� ���������
    vector<int> vars(num_vars);
    iota(vars.begin(), vars.end(), 0); // ���������� 0,1,2,...,num_vars-1

    // ��������� ��������� ��� ������ �������� ����������
    vector<bool> selector(num_vars);
    fill(selector.begin(), selector.begin() + num_eqs, true);

    do {
        // ������������ �������� ������
        vector<int> basis;
        for (int i = 0; i < num_vars; i++) {
            if (selector[i]) basis.push_back(i);
        }

        // ����������� �������� ������� ��� ���������� �������� ������
        auto temp_matrix = matrix;

        // ���������� ������ ������-�������
        gauss_jordan(temp_matrix);
        print_solution(temp_matrix, basis);

    } while (prev_permutation(selector.begin(), selector.end())); // ������� ���� ���������
}

int main() {
    setlocale(LC_ALL, "Russian");
    // �������� ����������� ������� �������:
    // ������ ������ ����� ��� [������������ | ��������� ����]
    vector<vector<double>> matrix = {
        {-1, 5, -4, -6, 0, 1, -9},
        {8, 1, -1, 0, 2, 3, 8},
        {4, 3, -2, 9, 1, 7, 1}
    };
    // ����� ���� �������� ������� ��� ������� � 6 �����������
    find_basic_solutions(matrix, 6);
    return 0;
}*/