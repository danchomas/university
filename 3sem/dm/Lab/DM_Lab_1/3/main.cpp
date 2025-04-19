#include <iostream>
#include <vector>
#include <windows.h>


using namespace std;


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
            if ((x == 2 || x == 4 || x == 6 || x == 8) &&
                (y == 1 || y == 7 || y == 9)) {
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


vector<vector<int>> reflectivity_(vector<vector<bool>> &matrix) {
    for (int i = 0; i < matrix.size(); i++) {
        if (!matrix[i][i]) {
            return vector<vector<int >>{{i, i}};
        }
    }
    return vector<vector<int >>{};
}


void reflectivity(vector<vector<bool>> &matrix) {
    vector<vector<int>> reflectivity = reflectivity_(matrix);
    if (reflectivity.empty()) {
        cout << "Рефлексивно" << endl;
    } else {
        int i = reflectivity[0][0];
        int j = reflectivity[0][1];

        cout << "Не рефлексивно, т. к. по индексу (" << i << ", " << j << ") находится " << matrix[i][j] << endl;
    }
}


vector<vector<int>> antireflectivity_(vector<vector<bool>> &matrix) {
    for (int i = 0; i < matrix.size(); i++) {
        if (matrix[i][i]) {
            return vector<vector<int >>{{i, i}};
        }
    }
    return vector<vector<int >>{};
}


void antireflectivity(vector<vector<bool>> &matrix) {
    vector<vector<int>> antireflectivity = antireflectivity_(matrix);

    if (antireflectivity.empty()) {
        cout << "Антирефлексивно" << endl;
    } else {
        int i = antireflectivity[0][0];
        int j = antireflectivity[0][1];

        cout << "Не антирефлексивно, т. к. по индексу (" << i << ", " << j << ") находится " << matrix[i][j] << endl;
    }
}


vector<vector<int>> symmetry_(vector<vector<bool>> &matrix) {
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = i + 1; j < matrix[0].size(); j++) {
            if (matrix[i][j] != matrix[j][i]) {
                return vector<vector<int >>{{i, j},
                                            {j, i}};
            }
        }
    }
    return vector<vector<int >>{};
}


void symmetry(vector<vector<bool>> &matrix) {
    vector<vector<int>> symmetry = symmetry_(matrix);
    if (symmetry.empty()) {
        cout << "Симметрично" << endl;
    } else {
        int i1 = symmetry[0][0];
        int j1 = symmetry[0][1];
        int i2 = symmetry[1][0];
        int j2 = symmetry[1][1];
        cout << "Не симметрично, т. к. по индексам (" << i1 << ", " << j1 << ") и ("
             << i2 << ", " << j2 << ") находятся " << matrix[i1][j1] << " и " << matrix[i2][j2] << endl;
    }
}


vector<vector<int>> antisymmetry_(vector<vector<bool>> &matrix) {
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = i + 1; j < matrix[0].size(); j++) {
            if (matrix[i][j] && matrix[j][i]) {
                return vector<vector<int >>{{i, j},
                                            {j, i}};
            }
        }
    }
    return vector<vector<int >>{};
}


void antisymmetry(vector<vector<bool>> &matrix) {
    vector<vector<int>> antisymmetry = antisymmetry_(matrix);
    if (antisymmetry.empty()) {
        cout << "Антисимметрично" << endl;
    } else {
        int i1 = antisymmetry[0][0];
        int j1 = antisymmetry[0][1];
        int i2 = antisymmetry[1][0];
        int j2 = antisymmetry[1][1];
        cout << "Не антисимметрично, т. к. по индексам (" << i1 << ", " << j1 << ") и ("
             << i2 << ", " << j2 << ") находятся " << matrix[i1][j1] << " и " << matrix[i2][j2] << endl;
    }
}


vector<vector<int>> transitivity_(vector<vector<bool>> &matrix) {
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[0].size(); j++) {
            for (int z = 0; z < matrix.size(); z++) {
                if (matrix[i][z] && matrix[z][j]) {
                    if (!matrix[i][j]) {
                        return vector<vector<int >>{{i, z},
                                                    {z, j},
                                                    {i, j}};
                    }
                }
            }
        }
    }

    return vector<vector<int >>{};
}


void transitivity(vector<vector<bool>> &matrix) {
    vector<vector<int>> transitivity = transitivity_(matrix);
    if (transitivity.empty()) {
        cout << "Транзитивно" << endl;
    } else {
        int i1 = transitivity[0][0];
        int j1 = transitivity[0][1];
        int i2 = transitivity[1][0];
        int j2 = transitivity[1][1];
        int i3 = transitivity[2][0];
        int j3 = transitivity[2][1];
        cout << "Не транзитивно, т. к. по индексам (" << i1 << ", " << j1 << "), ("
             << i2 << ", " << j2 << ") и (" << i3 << ", " << j3 << ") находятся " << matrix[i1][j1] << ", "
             << matrix[i2][j2] << " и " << matrix[i3][j3] << endl;

    }
}


vector<vector<int>> antitransitivity_(vector<vector<bool>> &matrix) {
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[0].size(); j++) {
            for (int z = 0; z < matrix.size(); z++) {
                if (matrix[i][z] && matrix[z][j]) {
                    if (matrix[i][j]) {
                        return vector<vector<int >>{{i, z},
                                                    {z, j},
                                                    {i, j}};
                    }
                }
            }
        }
    }
    return vector<vector<int >>{};
}


void antitransitivity(vector<vector<bool>> &matrix) {
    vector<vector<int>> antitransitivity = antitransitivity_(matrix);
    if (antitransitivity.empty()) {
        cout << "Антитранзитивно" << endl;
    } else {
        int i1 = antitransitivity[0][0];
        int j1 = antitransitivity[0][1];
        int i2 = antitransitivity[1][0];
        int j2 = antitransitivity[1][1];
        int i3 = antitransitivity[2][0];
        int j3 = antitransitivity[2][1];
        cout << "Не антитранзитивно, т. к. по индексам (" << i1 << ", " << j1 << "), ("
             << i2 << ", " << j2 << ") и (" << i3 << ", " << j3 << ") находятся " << matrix[i1][j1] << ", "
             << matrix[i2][j2] << " и " << matrix[i3][j3] << endl;
    }
}


vector<vector<int>> completeness_(vector<vector<bool>> &matrix) {
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = i + 1; j < matrix[0].size(); j++) {
            if (!matrix[i][j] && !matrix[j][i]) {
                return vector<vector<int >>{{i, j},
                                            {j, i}};
            }
        }
    }
    return vector<vector<int >>{};
}


void completeness(vector<vector<bool>> &matrix) {
    vector<vector<int>> completeness = completeness_(matrix);
    if (completeness.empty()) {
        cout << "Полно" << endl;
    } else {
        int i1 = completeness[0][0];
        int j1 = completeness[0][1];
        int i2 = completeness[1][0];
        int j2 = completeness[1][1];
        cout << "Не полно, т. к. по индексам (" << i1 << ", " << j1 << ") и ("
             << i2 << ", " << j2 << ") находятся " << matrix[i1][j1] << " и " << matrix[i2][j2] << endl;
    }
}


bool tolerance_(vector<vector<bool>> &matrix) {
    return reflectivity_(matrix).empty() && symmetry_(matrix).empty();
}


void tolerance(vector<vector<bool>> &matrix) {
    if (tolerance_(matrix)) {
        cout << "Является отношением толерантности" << endl;
    } else {
        cout << "Не является отношением толерантности" << endl;
    }
}


bool equivalence_(vector<vector<bool>> &matrix) {
    return reflectivity_(matrix).empty() && symmetry_(matrix).empty() && transitivity_(matrix).empty();
}


void equivalence(vector<vector<bool>> &matrix) {
    if (equivalence_(matrix)) {
        cout << "Является отношением эквивалентности" << endl;
    } else {
        cout << "Не является отношением эквивалентности" << endl;
    }
}


bool order_(vector<vector<bool>> &matrix) {
    return antisymmetry_(matrix).empty() && transitivity_(matrix).empty();
}


void order(vector<vector<bool>> &matrix) {
    if (order_(matrix)) {
        cout << "Является отношением порядка" << endl;
    } else {
        cout << "Не является отношением порядка" << endl;
    }
}


bool notStrictOrder_(vector<vector<bool>> &matrix) {
    return order_(matrix) && reflectivity_(matrix).empty();
}


void notStrictOrder(vector<vector<bool>> &matrix) {
    if (notStrictOrder_(matrix)) {
        cout << "Является отношением нестрогого порядка" << endl;
    } else {
        cout << "Не является отношением нестрогого порядка" << endl;
    }
}


bool strictOrder_(vector<vector<bool>> &matrix) {
    return order_(matrix) && antireflectivity_(matrix).empty();
}


void strictOrder(vector<vector<bool>> &matrix) {
    if (strictOrder_(matrix)) {
        cout << "Является отношением строгого порядка" << endl;
    } else {
        cout << "Не является отношением строгого порядка" << endl;
    }
}


bool linearOrder_(vector<vector<bool>> &matrix) {
    return order_(matrix) && completeness_(matrix).empty();
}


void linearOrder(vector<vector<bool>> &matrix) {
    if (linearOrder_(matrix)) {
        cout << "Является отношением линейного порядка" << endl;
    } else {
        cout << "Не является отношением линейного порядка" << endl;
    }
}


bool notStrictLinearOrder_(vector<vector<bool>> &matrix) {
    return notStrictOrder_(matrix) && completeness_(matrix).empty();
}


void notStrictLinearOrder(vector<vector<bool>> &matrix) {
    if (notStrictLinearOrder_(matrix)) {
        cout << "Является отношением нестрогого линейного порядка" << endl;
    } else {
        cout << "Не является отношением нестрогого линейного порядка" << endl;
    }
}


bool strictLinearOrder_(vector<vector<bool>> &matrix) {
    return strictOrder_(matrix) && completeness_(matrix).empty();
}


void strictLinearOrder(vector<vector<bool>> &matrix) {
    if (strictLinearOrder_(matrix)) {
        cout << "Является отношением строгого линейного порядка" << endl;
    } else {
        cout << "Не является отношением строгого линейного порядка" << endl;
    }
}


void defProperties(vector<vector<bool>> &matrix) {
    reflectivity(matrix);
    antireflectivity(matrix);
    symmetry(matrix);
    antisymmetry(matrix);
    transitivity(matrix);
    antitransitivity(matrix);
    completeness(matrix);

    tolerance(matrix);
    equivalence(matrix);
    order(matrix);
    if (order_(matrix)) {
        notStrictOrder(matrix);
        strictOrder(matrix);
        linearOrder(matrix);
        notStrictLinearOrder(matrix);
        strictLinearOrder(matrix);
    }
    cout << endl;
}


int main() {
    SetConsoleOutputCP(CP_UTF8);

    vector<vector<bool>> matrixA(10, vector<bool>(10));
    MatrixA(matrixA);
    vector<vector<bool>> matrixB(10, vector<bool>(10));
    MatrixB(matrixB);
    vector<vector<bool>> matrixC(10, vector<bool>(10));
    MatrixC(matrixC);

    cout << "Matrix A:" << endl;
    defProperties(matrixA);
    cout << "Matrix B:" << endl;
    defProperties(matrixB);
    cout << "Matrix C:" << endl;
    defProperties(matrixC);

    return 0;
}
