#include <iostream>
#include <vector>
#include <cassert>

using namespace std;


void matrixOutput(vector <vector<bool>> &matrix) {
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix.size(); j++) {
            cout << matrix[i][j] << ' ';
        }
        cout << endl;
    }
    cout << endl;
}


void matrixOutput(vector<int> &matrix) {
    for (int i = 0; i < matrix.size(); ++i) {
        cout << matrix[i] << ' ';
    }
    cout << endl;
}


vector <vector<bool>> createRelationship(vector <vector<int>> &matrix) {
    vector <vector<bool>> newMatrix(matrix.size(),
                                    vector<bool>(matrix.size()));
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix.size(); j++) {
            int ax = matrix[i][0];
            int ay = matrix[i][1];
            int bx = matrix[j][0];
            int by = matrix[j][1];
            newMatrix[i][j] = ax * ay < bx * by;
        }
    }

    return newMatrix;
}


vector <vector<bool>> createDominance(vector <vector<bool>> &matrix) {
    vector <vector<bool>> newMatrix(matrix.size(),
                                    vector<bool>(matrix.size()));
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix.size(); j++) {
            for (int k = 0; k < matrix.size(); k++) {
                newMatrix[i][j] = 1;
                if (matrix[i][k] && matrix[k][j] || !matrix[i][j]) {
                    newMatrix[i][j] = 0;
                    break;
                }
            }
        }
    }

    return newMatrix;
}


vector<int> sortTopological(vector <vector<bool>> &matrix) {
    vector<int> newMatrix(matrix.size());

    for (int i = 0; i < matrix.size(); i++) {
        int counter = 0;
        for (int j = 0; j < matrix.size(); j++) {
            counter += matrix[j][i];
        }
        newMatrix[i] = counter;
    }

    return newMatrix;
}


void sortTopologicalOutput(vector<int> &matrix1, vector <vector<int>> &matrix2) {
    assert(matrix1.size() == matrix2.size());
    for (int i = 0; i < matrix1.size(); i++) {
        bool flagOfNull = false;
        for (int j = 0; j < matrix1.size(); j++) {
            if (matrix1[j] == 0) {
                flagOfNull = true;
            }
        }
        if (flagOfNull) {
            for (int j = 0; j < matrix1.size(); j++) {
                matrix1[j]--;
            }
        } else {
            for (int j = 0; j < matrix1.size(); j++) {
                if (matrix1[j] > 0) {
                    matrix1[j]--;
                }
            }
        }
    }

    int val = -1;
    for (int i = 0; i < matrix1.size(); i++) {
        bool flag = false;
        for (int j = 0; j < matrix1.size(); j++) {
            if (matrix1[j] == val) {
                flag = true;
                break;
            }
        }

        if (flag) {
            cout << i << " level: ";
            for (int j = 0; j < matrix1.size(); j++) {
                if (matrix1[j] == val) {
                    //cout << '(' << matrix2[j][0] << ", " << matrix2[j][1] << "), ";
                    cout << j + 1 << " ";
                }
            }
            cout << endl;
        }

        val--;
    }
}


int main() {
    vector <vector<int>> m1(9, vector<int>(2));
    int index = 0;
    for (int x = -1; x <= 1; x++) {
        for (int y = -1; y <= 1; y++) {
            m1[index++] = {x, y};
        }
    }

    vector <vector<int>> m2(13, vector<int>(2));
    index = 0;
    for (int x = -2; x <= 2; x++) {
        for (int y = -2; y <= 2; y++) {
            if (abs(x) <= 1 && abs(y) <= 1 ||
                (y == 0 || x == 0)) {
                m2[index++] = {x, y};
            }
        }
    }

    vector <vector<bool>> matrixRel1 = createRelationship(m1);
    vector <vector<bool>> matrixRel2 = createRelationship(m2);

    cout << "M1:" << endl;
    matrixOutput(matrixRel1);
    cout << "M2:" << endl;
    matrixOutput(matrixRel2);

    vector <vector<bool>> matrixDom1 = createDominance(matrixRel1);
    vector <vector<bool>> matrixDom2 = createDominance(matrixRel2);

    cout << "M1 Dominance:" << endl;
    matrixOutput(matrixDom1);
    cout << "M2 Dominance:" << endl;
    matrixOutput(matrixDom2);

    vector<int> matrixTop1 = sortTopological(matrixDom1);
    vector<int> matrixTop2 = sortTopological(matrixDom2);

    cout << "M1 Topological Sort:" << endl;
    sortTopologicalOutput(matrixTop1, m1);
    cout << "M2 Topological Sort:" << endl;
    sortTopologicalOutput(matrixTop2, m2);

    return 0;
}