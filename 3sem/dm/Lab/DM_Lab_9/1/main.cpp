#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>


using namespace std;


void matrixOutput(vector<vector<bool>> &matrix) {
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix.size(); j++) {
            cout << matrix[i][j] << ' ';
        }
        cout << endl;
    }
    cout << endl;
}


void matrixInput(vector<vector<bool>> &matrix) {
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix.size(); j++) {
            int buf;
            cin >> buf;
            matrix[i][j] = buf;
        }
    }
}


void matrixInput(vector<vector<int>> &matrix) {
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix.size(); j++) {
            int buf;
            cin >> buf;
            matrix[i][j] = buf;
        }
    }
}


void outputVector(vector<int> &v) {
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl;
}


void outputVertex(vector<vector<int>> &v) {
    for (int i = 0; i < v.size(); i++) {
        outputVector(v[i]);
    }
}


bool IsAll(vector<bool> &v) {
    bool isAll = true;

    for (int i = 0; i < v.size() && isAll; ++i) {
        isAll = isAll && v[i];
    }

    return isAll;
}


vector<int> GetAdjacent(vector<vector<int>> &matrix, int v) {
    vector<int> adjacentVertexes;

    for (int i = 0; i < matrix.size(); ++i) {
        if (matrix[v - 1][i] > 0) {
            adjacentVertexes.push_back(i + 1);
        }
    }

    return adjacentVertexes;

}


vector<int> GetMinWays(vector<vector<int>> &matrix, int vStart) {
    vector<int> t(matrix.size(), -1);
    vector<int> d(matrix.size(), -1);
    vector<bool> v(matrix.size(), false);

    t[vStart - 1] = 0;
    v[vStart - 1] = true;
    d[vStart - 1] = 0;

    int nextYw = 0;
    int nextY = vStart;
    while (!IsAll(v) && nextYw != -1) {
        vector<int> adjacent = GetAdjacent(matrix, vStart);
        nextYw = -1;

        for (int i = 0; i < adjacent.size(); ++i) {

            if (d[adjacent[i] - 1] == -1) {
                d[adjacent[i] - 1] = d[vStart - 1] + matrix[vStart - 1][adjacent[i] - 1];
                t[adjacent[i] - 1] = vStart;
            } else {
                if (d[adjacent[i] - 1] > d[vStart - 1] + matrix[vStart - 1][adjacent[i] - 1]) {
                    d[adjacent[i] - 1] = d[vStart - 1] + matrix[vStart - 1][adjacent[i] - 1];
                    t[adjacent[i] - 1] = vStart;
                }
            }
        }

        for (int i = 0; i < d.size(); ++i) {
            if (d[i] != -1 && !v[i]) {
                if (nextYw == -1) {
                    nextYw = d[i];
                    nextY = i + 1;
                } else {
                    if (d[i] < nextYw) {
                        nextYw = d[i];
                        nextY = i + 1;
                    }
                }
            }
        }

        vStart = nextY;
        if (vStart != -1) {
            v[vStart - 1] = true;
        }
    }

    return t;
}


int TreeToLen(vector<vector<int>> &matrix, vector<int> &tree, int start, int end) {
    int sumLen = 0;

    while (end != start && end != -1) {
        if (tree[end - 1] != -1) {
            sumLen += matrix[tree[end - 1] - 1][end - 1];
        }
        end = tree[end - 1];
    }

    if (end == -1) {
        return -1;
    } else {
        return sumLen;
    }
}


vector<vector<int>> GetAllPairsMinWays(vector<vector<int>> &matrix) {
    vector<vector<int>> minWays(matrix.size(), vector<int>(matrix.size(), 0));

    for (int i = 0; i < matrix.size(); ++i) {
        vector<int> tree = GetMinWays(matrix, i + 1);

        for (int j = 0; j < minWays.size(); ++j) {
            minWays[i][j] = TreeToLen(matrix, tree, i + 1, j + 1);
        }
    }

    return minWays;
}


vector<int> GetLessInThanOut(vector<vector<int>> &matrix) {
    vector<int> vertexes;

    vector<vector<int>> allPairsMinWays = GetAllPairsMinWays(matrix);

    for (int i = 0; i < allPairsMinWays.size(); ++i) {
        int sumInVertex = 0;
        int sumOutVertex = 0;
        for (int j = 0; j < allPairsMinWays.size(); ++j) {
            if (allPairsMinWays[j][i] != -1) {
                sumInVertex += allPairsMinWays[j][i];
            }

            if (allPairsMinWays[i][j] != -1) {
                sumOutVertex += allPairsMinWays[i][j];
            }
        }

        if (sumInVertex < sumOutVertex) {
            vertexes.push_back(i + 1);
        }
    }

    return vertexes;
}


/*


0 0 11 100 0 0 0 0
1 0 0 0 0 0 0 0
0 0 0 0 11 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 11 0 0
0 0 0 0 0 0 11 0
0 0 0 11 0 0 0 0
0 0 0 0 0 0 0 0


 */


int main() {
    int sz = 6;
    vector<vector<int>> buf(sz, vector<int>(sz, 0));
    matrixInput(buf);

    vector<int> tr = GetMinWays(buf, 1);

    vector<int> test_ = GetLessInThanOut(buf);

    outputVector(test_);

    return 0;
}

