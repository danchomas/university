#include <iostream>
#include <vector>
#include <cassert>
#include <windows.h>


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
}


void MatrixB(vector<vector<bool>> &matrix) {
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {
            int x = i + 1;
            int y = j + 1;
            if ((x == 2 || x == 4 || x == 6 || x == 8) && (y == 1 || y == 7 || y == 9)) {
                matrix[i][j] = true;
            } else {
                matrix[i][j] = false;
            }
        }
    }
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
}


// равенство
bool equality(vector<vector<bool>> &matrix1,
              vector<vector<bool>> &matrix2) {
    size_t xSize = 0;
    size_t ySize = 0;
    if ((matrix1.size() == matrix2.size()) && (matrix1[0].size() == matrix2[0].size())) {
        xSize = matrix1.size();
        ySize = matrix1[0].size();
    } else {
        assert(matrix1.size() == matrix2.size());
        assert(matrix1[0].size() == matrix2[0].size());
    }

    for (int i = 0; i < xSize; i++) {
        for (int j = 0; j < ySize; j++) {
            if (matrix1[i][j] != matrix2[i][j]) {
                return false;
            }
        }
    }

    return true;
}

// включение
bool inclusion(vector<vector<bool>> &matrix1,
               vector<vector<bool>> &matrix2) {
    size_t xSize = 0;
    size_t ySize = 0;
    if ((matrix1.size() == matrix2.size()) && (matrix1[0].size() == matrix2[0].size())) {
        xSize = matrix1.size();
        ySize = matrix1[0].size();
    } else {
        assert(matrix1.size() == matrix2.size());
        assert(matrix1[0].size() == matrix2[0].size());
    }

    for (int i = 0; i < xSize; i++) {
        for (int j = 0; j < ySize; j++) {
            if (matrix1[i][j] > matrix2[i][j]) {
                return false;
            }
        }
    }

    return true;
}


// строгое включение
bool strictInclusion(vector<vector<bool>> &matrix1,
                     vector<vector<bool>> &matrix2) {
    size_t xSize = 0;
    size_t ySize = 0;
    if ((matrix1.size() == matrix2.size()) && (matrix1[0].size() == matrix2[0].size())) {
        xSize = matrix1.size();
        ySize = matrix1[0].size();
    } else {
        assert(matrix1.size() == matrix2.size());
        assert(matrix1[0].size() == matrix2[0].size());
    }

    for (int i = 0; i < xSize; i++) {
        for (int j = 0; j < ySize; j++) {
            if (matrix1[i][j] >= matrix2[i][j]) {
                return false;
            }
        }
    }

    return true;
}


// объединение
void union_(vector<vector<bool>> &matrix1,
            vector<vector<bool>> &matrix2,
            vector<vector<bool>> &resultMatrix) {
    size_t xSize = 0;
    size_t ySize = 0;
    if ((matrix1.size() == matrix2.size()) &&
        (matrix1[0].size() == matrix2[0].size())) {
        xSize = matrix1.size();
        ySize = matrix1[0].size();
    } else {
        assert(matrix1.size() == matrix2.size());
        assert(matrix1[0].size() == matrix2[0].size());
    }

    for (int i = 0; i < xSize; i++) {
        for (int j = 0; j < ySize; j++) {
            resultMatrix[i][j] = matrix1[i][j] || matrix2[i][j];
        }
    }
}


// пересечение
void intersection(vector<vector<bool>> &matrix1,
                  vector<vector<bool>> &matrix2,
                  vector<vector<bool>> &resultMatrix) {
    size_t xSize = 0;
    size_t ySize = 0;
    if ((matrix1.size() == matrix2.size() == resultMatrix.size()) &&
        (matrix1[0].size() == matrix2[0].size() == resultMatrix[0].size())) {
        xSize = matrix1.size();
        ySize = matrix1[0].size();
    } else {
        assert(matrix1.size() == matrix2.size() == resultMatrix.size());
        assert(matrix1[0].size() == matrix2[0].size() == resultMatrix[0].size());
    }

    for (int i = 0; i < xSize; i++) {
        for (int j = 0; j < ySize; j++) {
            resultMatrix[i][j] = matrix1[i][j] && matrix2[i][j];
        }
    }
}


// разность
void difference(vector<vector<bool>> &matrix1,
                vector<vector<bool>> &matrix2,
                vector<vector<bool>> &resultMatrix) {
    size_t xSize = 0;
    size_t ySize = 0;
    if ((matrix1.size() == matrix2.size()) &&
        (matrix1[0].size() == matrix2[0].size())) {
        xSize = matrix1.size();
        ySize = matrix1[0].size();
    } else {
        assert(matrix1.size() == matrix2.size());
        assert(matrix1[0].size() == matrix2[0].size());
    }

    for (int i = 0; i < xSize; i++) {
        for (int j = 0; j < ySize; j++) {
            resultMatrix[i][j] = matrix1[i][j] && !matrix2[i][j];
        }
    }
}


// симметрическая разность
void symmetricDifference(vector<vector<bool>> &matrix1,
                         vector<vector<bool>> &matrix2,
                         vector<vector<bool>> &resultMatrix) {
    size_t xSize = 0;
    size_t ySize = 0;
    if ((matrix1.size() == matrix2.size()) &&
        (matrix1[0].size() == matrix2[0].size())) {
        xSize = matrix1.size();
        ySize = matrix1[0].size();
    } else {
        assert(matrix1.size() == matrix2.size());
        assert(matrix1[0].size() == matrix2[0].size());
    }

    for (int i = 0; i < xSize; i++) {
        for (int j = 0; j < ySize; j++) {
            resultMatrix[i][j] = matrix1[i][j] != matrix2[i][j];
        }
    }
}


// дополнение
void addition(vector<vector<bool>> &matrix,
              vector<vector<bool>> &resultMatrix) {

    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[0].size(); j++) {
            resultMatrix[i][j] = !matrix[i][j];
        }
    }
}


// обращение
void appeal(vector<vector<bool>> &matrix,
            vector<vector<bool>> &resultMatrix) {

    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[0].size(); j++) {
            resultMatrix[i][j] = matrix[j][i];
        }
    }
}


// композиция
void composition(vector<vector<bool>> &matrix1,
                 vector<vector<bool>> &matrix2,
                 vector<vector<bool>> &resultMatrix) {
    size_t xSize = 0;
    size_t ySize = 0;
    if ((matrix1.size() == matrix2.size()) &&
        (matrix1[0].size() == matrix2[0].size())) {
        xSize = matrix1.size();
        ySize = matrix1[0].size();
    } else {
        assert(matrix1.size() == matrix2.size());
        assert(matrix1[0].size() == matrix2[0].size());
    }

    for (int i = 0; i < xSize; i++) {
        for (int j = 0; j < ySize; j++) {
            bool flag = false;
            for (int z = 0; !flag && z < max(xSize, ySize); z++) {
                if (matrix1[i][z] && matrix2[z][j]) {
                    flag = true;
                }
            }
            resultMatrix[i][j] = flag;
        }
    }
}


int main() {
    SetConsoleOutputCP(CP_UTF8);

    vector<vector<bool>> matrixA(10, vector<bool>(10));
    MatrixA(matrixA);
    vector<vector<bool>> matrixB(10, vector<bool>(10));
    MatrixB(matrixB);
    vector<vector<bool>> matrixC(10, vector<bool>(10));
    MatrixC(matrixC);

    vector<vector<bool>> _1(10, vector<bool>(10));
    composition(matrixA, matrixA, _1);

    outputMatrix(_1);

    /*
    vector<vector<bool>> _1(10, vector<bool>(10));
    appeal(matrixA, _1);

    cout << "Результат действия 1:" << endl;
    outputMatrix(_1);

    vector<vector<bool>> _2(10, vector<bool>(10));
    composition(matrixA, matrixB, _2);

    cout << "Результат действия 2:" << endl;
    outputMatrix(_2);

    vector<vector<bool>> _3(10, vector<bool>(10));
    composition(_2, matrixC, _3);

    cout << "Результат действия 3:" << endl;
    outputMatrix(_3);

    vector<vector<bool>> _4(10, vector<bool>(10));
    difference(_3, _1, _4);

    cout << "Результат действия 4:" << endl;
    outputMatrix(_4);

    vector<vector<bool>> _5(10, vector<bool>(10));
    symmetricDifference(_4, matrixC, _5);

    cout << "Результат действия 5:" << endl;
    outputMatrix(_5);
    */
    return 0;
}
