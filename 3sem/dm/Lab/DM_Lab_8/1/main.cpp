#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>


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


void matrixInput(vector <vector<bool>> &matrix) {
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix.size(); j++) {
            int buf;
            scanf("%d", &buf);
            matrix[i][j] = buf;
        }
    }
}


void matrixInput(vector <vector<int>> &matrix) {
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix.size(); j++) {
            int buf;
            scanf("%d", &buf);
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


void outputVertex(vector <vector<int>> &v) {
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


vector<int> GetAdjacent(vector <vector<int>> &matrix, int v) {
    vector<int> adjacentVertexes;

    for (int i = 0; i < matrix.size(); ++i) {
        if (matrix[v - 1][i] > 0) {
            adjacentVertexes.push_back(i + 1);
        }
    }

    return adjacentVertexes;

}


vector<int> GetMinWays(vector <vector<int>> &matrix, int vStart, int vEnd) {
    vector<int> t(matrix.size(), -1);
    vector<int> d(matrix.size(), -1);
    vector<bool> v(matrix.size(), false);

    t[vStart - 1] = 0;
    v[vStart - 1] = true;
    d[vStart - 1] = 0;

    int nextYw = 0;
    int nextY = vStart;
    while (!IsAll(v) && vStart != vEnd && nextYw != -1) {
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
        v[vStart - 1] = true;
    }

    return t;
}


vector<int> GetMinWays_(vector <vector<int>> &matrix, int vStart) {
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
        v[vStart - 1] = true;
    }

    return t;
}


vector<int> TreeToSq(vector<int> &tree, int start, int end) {
    vector<int> sq;

    int out = end;
    while (out != start && out != -1) {
        sq.push_back(out);
        out = tree[out - 1];
    }
    sq.push_back(start);
    reverse(sq.begin(), sq.end());
    if (out == -1) {
        return vector < int > {};
    } else {
        return sq;
    }
}


void GetOftenVertex(vector <vector<int>> &matrix, int vStart) {
    vector<int> v(matrix.size(), 0);
    vector<bool> G(matrix.size(), false);
    G[vStart - 1] = true;

    vector <vector<int>> allSq;

    vector<int> tree = GetMinWays_(matrix, vStart);

    for (int i = 0; i < matrix.size(); ++i) {
        if (G[i] == false && tree[i] != -1) {
            vector<int> sq = TreeToSq(tree, vStart, i + 1);
            G[i] = true;

            allSq.push_back(sq);

            for (int j = 0; j < sq.size(); ++j) {
                v[sq[j] - 1]++;
            }
        }
    }

    int maxV;
    int maxSum = -1;

    for (int i = 0; i < v.size(); ++i) {
        if (vStart != i + 1) {
            if (v[i] > maxSum) {
                maxSum = v[i];
                maxV = i + 1;
            }
        }
    }

    if (allSq.empty()) {
        cout << "Not vertex" << endl;
    } else {
        cout << "Vertex: " << maxV << endl;
    }

    outputVertex(allSq);
}


int main() {
    int sz = 6;
    vector <vector<int>> buf(sz, vector<int>(sz, 0));
    matrixInput(buf);

    GetOftenVertex(buf, 5);

    return 0;
}