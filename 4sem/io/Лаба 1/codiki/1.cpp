#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const double EPS = 1e-9; // �������� ��� ��������� ����� � ��������� ������

// ������� ��� ���������� ������� � ����������� ������������ ����
void gaussJordan(vector<vector<double>>& a) {
    int n = a.size();    // ���������� ���������
    int m = a[0].size(); // ���������� ���������� + 1 (������� ��������� ������)

    for (int row = 0, col = 0; row < n && col < m - 1; ++col) {
        // ����� ������ � ������������ ��������� � ������� �������
        int pivot = row;
        for (int i = row + 1; i < n; ++i)
            if (abs(a[i][col]) > abs(a[pivot][col]))
                pivot = i;

        // ���� ��� �������� � ������� �������, ��������� � ���������� �������
        if (abs(a[pivot][col]) < EPS)
            continue;

        // ������ ������ �������
        if (pivot != row)
            swap(a[pivot], a[row]);

        // ������������ ������� ������ (������ ������� ������� ������ 1)
        double div = a[row][col];
        for (int j = col; j < m; ++j)
            a[row][j] /= div;

        // �������� ��� �������� � ������� �������, ����� ��������
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
    cout << "������� ���������� ��������� � ����������: ";
    cin >> n >> m;

    // ������� ������������� (n x (m + 1))
    vector<vector<double>> a(n, vector<double>(m + 1));

    cout << "������� ������������ ������� ���������:" << endl;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j <= m; ++j)
            cin >> a[i][j];

    // ���������� ������� � ����������� ������������ ����
    gaussJordan(a);

    // ����� ����������
    cout << "������� � ���������� ����������� ����:" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= m; ++j)
            cout << a[i][j] << " ";
        cout << endl;
    }

    // ������ �������
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
        cout << "������� �� ����� �������." << endl;
    }
    else {
        cout << "������� ����� �������:" << endl;
        for (int j = 0; j < m; ++j) {
            bool isFree = true;
            for (int i = 0; i < n; ++i)
                if (abs(a[i][j] - 1.0) < EPS) {
                    isFree = false;
                    cout << "x" << j + 1 << " = " << a[i][m] << endl;
                    break;
                }
            if (isFree)
                cout << "x" << j + 1 << " - ��������� ����������" << endl;
        }
    }

    return 0;
}