#include <iostream>
#include <vector>


using namespace std;


void outputMatrix(vector<vector<bool>> &matrix) {
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {
            cout << matrix[i][j] << ' ';
        }
        cout << endl;
    }
    cout << endl;
}


void MatrixA(vector<vector<bool>> &matrix) {
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {
            int x = i + 1;
            int y = j + 1;
            if ((x + y) % x == 0) {
                matrix[i][j] = true;
            } else {
                matrix[i][j] = false;
            }
        }
    }
    cout << "Matrix A:" << endl;
    outputMatrix(matrix);
}


void MatrixB(vector<vector<bool>> &matrix) {
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {
            int x = i + 1;
            int y = j + 1;
            if ((x == 2 || x == 4 || x == 6 || x == 8) &&
                (y == 1 || y == 7 || y == 9)) {
                matrix[i][j] = true;
            } else {
                matrix[i][j] = false;
            }
        }
    }
    cout << "Matrix B:" << endl;
    outputMatrix(matrix);
}


void MatrixC(vector<vector<bool>> &matrix) {
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {
            int x = i + 1;
            int y = j + 1;
            if ((x + y) % 2 == 0 && x * y < 20) {
                matrix[i][j] = true;
            } else {
                matrix[i][j] = false;
            }
        }
    }
    cout << "Matrix C:" << endl;
    outputMatrix(matrix);
}


int main() {
    vector<vector<bool>> matrix(10, vector<bool>(10));

    MatrixA(matrix);
    MatrixB(matrix);
    MatrixC(matrix);

    return 0;
}
