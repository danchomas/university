#include <iostream>
#include <vector>
#include <random>


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


void outputVertex(vector<vector<int>> &v) {
    for (int i = 0; i < v.size(); i++) {
        outputVector(v[i]);
    }
}


vector<vector<bool>> GetCoveringTree(vector<vector<bool>> matrix) {
    vector<int> b(matrix.size());
    for (int i = 0; i < b.size(); ++i) {
        b[i] = i + 1;
    }

    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = i + 1; j < matrix.size(); ++j) {
            if (matrix[i][j]) {

                if (b[i] != b[j]) {
                    int groupBouquet = b[j];
                    for (int k = 0; k < b.size(); ++k) {
                        if (b[k] == groupBouquet) {
                            b[k] = b[i];
                        }
                    }
                } else {
                    matrix[i][j] = false;
                    matrix[j][i] = false;
                }
            }
        }
    }

    return matrix;
}


int CountBouquet(vector<vector<bool>> &matrix) {
    vector<int> bouquet(matrix.size());
    for (int i = 0; i < bouquet.size(); ++i) {
        bouquet[i] = i + 1;
    }
    int counter = matrix.size();

    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = i + 1; j < matrix.size(); ++j) {
            if (matrix[i][j]) {

                if (bouquet[i] != bouquet[j]) {
                    counter--;
                    int groupBouquet = bouquet[j];
                    for (int k = 0; k < bouquet.size(); ++k) {
                        if (bouquet[k] == groupBouquet) {
                            bouquet[k] = bouquet[i];
                        }
                    }
                }
            }
        }
    }

    return counter;
}


void GetAllCombinations(vector<vector<int>> &matrix,
                        vector<vector<int>> edges,
                        int start,
                        int n,
                        vector<vector<vector<int>>> &res) {
    for (int i = start; i < matrix.size() - n && n > 0; ++i) {
        edges.push_back(matrix[i]);
        GetAllCombinations(matrix, edges, i + 1, n - 1, res);
        edges.pop_back();
    }

    if (n == 0) {
        res.push_back(edges);
    }
}


vector<vector<int>> GetSetUnlinkedEdges(vector<vector<bool>> &matrix) {
    vector<vector<int>> res = {};
    int countBouquet = CountBouquet(matrix);
    if (countBouquet == 1) {
        vector<vector<int>> pairV;
        for (int i = 0; i < matrix.size(); ++i) {
            for (int j = i + 1; j < matrix.size(); ++j) {
                if (matrix[i][j]) {
                    vector<int> buf = {i + 1, j + 1};
                    pairV.push_back(buf);
                }
            }
        }

        int n = 1;
        while (countBouquet == 1 && n < matrix.size()) {
            vector<vector<vector<int>>> buf;
            GetAllCombinations(pairV, vector<vector<int>>{}, 0, n, buf);
            vector<vector<bool>> matrixCopy;

            for (int i = 0; i < buf.size() && countBouquet == 1; ++i) {
                matrixCopy.assign(matrix.begin(), matrix.end());
                res.assign(buf[i].cbegin(), buf[i].cend());
                for (int j = 0; j < buf[i].size(); ++j) {
                    matrixCopy[res[j][0] - 1][res[j][1] - 1] = false;
                    matrixCopy[res[j][1] - 1][res[j][0] - 1] = false;
                }

                countBouquet = CountBouquet(matrixCopy);
            }

            n++;
        }
    }

    return res;
}


int main() {
    int sz = 4;
    vector<vector<bool>> buf(sz, vector<bool>(sz, false));
    matrixInput(buf);

    vector<vector<int>> setUnlinkedEdges = GetSetUnlinkedEdges(buf);

    for (int i = 0; i < setUnlinkedEdges.size(); ++i) {
        cout << setUnlinkedEdges[i][0] << " " << setUnlinkedEdges[i][1] << endl;
    }

    return 0;
}