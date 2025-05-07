#include <iostream>
#include <vector>


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


bool IsRout(vector<vector<bool>> &matrix, vector<int> &rout) {
    for (int i = 0; i < rout.size() - 1; i++) {
        if (!matrix[rout[i] - 1][rout[i + 1] - 1]) {
            return false;
        }
    }

    return true;
}


bool IsChain(vector<vector<bool>> &matrix, vector<int> &rout) {
    vector<vector<int>> chain;
    bool isNotChain = false;
    for (int i = 0; i < rout.size() - 1; i++) {
        isNotChain = false;
        for (int j = 0; j < chain.size(); j++) {
            if (chain[j][0] == rout[i] && chain[j][1] == rout[i + 1] ||
                chain[j][1] == rout[i] && chain[j][0] == rout[i + 1]) {
                isNotChain = true;
            }
        }

        if (!matrix[rout[i] - 1][rout[i + 1] - 1] || isNotChain) {
            return false;
        }
        vector<int> buf = {rout[i], rout[i + 1]};

        chain.push_back(buf);
    }

    return !isNotChain;
}


bool IsPrimeChain(vector<vector<bool>> &matrix, vector<int> &rout) {
    if (!IsRout(matrix, rout)) {
        return false;
    }

    for (int i = 0; i < rout.size() - 1; i++) {
        for (int j = i + 1; j < rout.size(); j++) {
            if (rout[i] == rout[j]) {
                return false;
            }
        }
    }

    return true;
}


bool IsCycle(vector<vector<bool>> &matrix, vector<int> &rout) {
    if (rout[0] != rout[rout.size() - 1]) {
        return false;
    }

    if (!IsChain(matrix, rout)) {
        return false;
    }

    return true;
}


bool IsPrimeCycle(vector<vector<bool>> &matrix, vector<int> &rout) {
    if (rout[0] != rout[rout.size() - 1]) {
        return false;
    }

    for (int i = 0; i < rout.size() - 1; i++) {
        for (int j = i + 1; j < rout.size(); j++) {
            if (i == 0 && j == rout.size() - 1) {
                continue;
            } else if (rout[i] == rout[j]) {
                return false;
            }
        }
    }

    return true;
}


void outputVector(vector<int> &v) {
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl;
}


void outputSequenceProperty(vector<vector<bool>> &matrix, vector<int> &sequence) {
    cout << "For ";
    outputVector(sequence);
    cout << "IsRout: " << IsRout(matrix, sequence) << endl;
    cout << "IsChain: " << IsChain(matrix, sequence) << endl;
    cout << "IsPrimeChain: " << IsPrimeChain(matrix, sequence) << endl;
    cout << "IsCycle: " << IsCycle(matrix, sequence) << endl;
    cout << "IsPrimeCycle: " << IsPrimeCycle(matrix, sequence) << endl << endl;
}


void outputVertex(vector<vector<int>> &v) {
    for (int i = 0; i < v.size(); i++) {
        outputVector(v[i]);
    }
}


void outputSumRoutes(vector<vector<int>> &v) {
    for (int i = 0; i < v.size(); i++) {
        for (int j = 0; j < v[i].size(); j++) {
            if (v[i].size() == 1) {
                cout << ": " << v[i][j] << endl;
            } else {
                cout << v[i][j] << " ";
            }
        }
    }
}


void GetRoutes_(vector<vector<bool>> &matrix, int maxLen, vector<int> G, vector<vector<int>> &res) {
    for (int i = 0; i < matrix.size(); i++) {
        if (matrix[i][G[G.size() - 1] - 1]) {
            G.push_back(i + 1);
            if (G.size() - 1 == maxLen) {
                res.push_back(G);
            } else {
                GetRoutes_(matrix, maxLen, G, res);
            }
            G.pop_back();
        }
    }
}


vector<vector<int>> GetRoutes(vector<vector<bool>> &matrix, int v, int maxLen) {
    vector<vector<int>> routs = {};
    GetRoutes_(matrix, maxLen, vector<int>(1, v), routs);

    return routs;
}


vector<vector<int>> GetAllRoutes(vector<vector<bool>> &matrix, int maxLen) {
    vector<vector<int>> res = {};

    for (int i = 1; i <= matrix.size(); i++) {
        vector<vector<int>> buf = GetRoutes(matrix, i, maxLen);
        res.insert(res.end(), buf.begin(), buf.end());
    }

    return res;
}


int GetSumRoutes_(vector<vector<bool>> &matrix, int maxLen, vector<int> G, int vEnd) {
    int sumRoutes = 0;
    for (int i = 0; i < matrix.size(); i++) {
        if (matrix[i][G[G.size() - 1] - 1]) {
            G.push_back(i + 1);
            if (G.size() - 1 == maxLen && vEnd == i + 1) {
                return 1;
            } else if (G.size() - 1 != maxLen) {
                sumRoutes += GetSumRoutes_(matrix, maxLen, G, vEnd);
            }
            G.pop_back();
        }
    }
    return sumRoutes;
}


int GetSumRoutes(vector<vector<bool>> &matrix, int v, int maxLen, int vEnd) {
    int sumRoutes = GetSumRoutes_(matrix, maxLen, vector<int>(1, v), vEnd);

    return sumRoutes;
}


vector<vector<int>> GetAllSumRoutes(vector<vector<bool>> &matrix, int maxLen) {
    vector<vector<int>> res = {};

    for (int i = 1; i <= matrix.size(); i++) {
        for (int j = 1; j <= matrix.size(); j++) {
            int buf = GetSumRoutes(matrix, i, maxLen, j);

            res.push_back(vector<int>{i, j});
            res.push_back(vector<int>{buf});
        }
    }

    return res;
}


void GetPairRoutes_(vector<vector<bool>> &matrix, int maxLen, vector<int> G, int vEnd, vector<vector<int>> &res) {
    for (int i = 0; i < matrix.size(); i++) {
        if (matrix[i][G[G.size() - 1] - 1]) {
            G.push_back(i + 1);
            if (G.size() - 1 == maxLen && vEnd == (i + 1)) {
                res.push_back(G);
            } else if (G.size() - 1 != maxLen) {
                GetPairRoutes_(matrix, maxLen, G, vEnd, res);
            }
            G.pop_back();
        }
    }
}


vector<vector<int>> GetPairRoutes(vector<vector<bool>> &matrix, int v, int maxLen, int vEnd) {
    vector<vector<int>> routs = {};
    GetPairRoutes_(matrix, maxLen, vector<int>(1, v), vEnd, routs);

    return routs;
}


vector<vector<int>> GetAllPairRoutes(vector<vector<bool>> &matrix, int maxLen) {

    vector<vector<int>> res = {};

    for (int i = 1; i <= matrix.size(); i++) {
        for (int j = 1; j <= matrix.size(); j++) {
            vector<vector<int>> buf = GetPairRoutes(matrix, i, maxLen, j);
            res.insert(res.end(), buf.begin(), buf.end());
        }
    }

    return res;
}


void GetMaxChains_(vector<vector<bool>> &matrix, vector<int> G, vector<vector<int>> &res) {
    bool areNoWaysToAnyPoint = true;
    for (int i = 0; i < matrix.size() && G.size() <= matrix.size(); i++) {
        if (matrix[i][G[G.size() - 1] - 1]) {
            bool isNoPointInG = true;
            for (int j = 0; j < G.size() && isNoPointInG; j++) {
                if (G[j] == (i + 1)) {
                    isNoPointInG = false;
                }
            }

            areNoWaysToAnyPoint = areNoWaysToAnyPoint && !isNoPointInG;

            if (isNoPointInG) {
                G.push_back(i + 1);
                GetMaxChains_(matrix, G, res);
                G.pop_back();
            }
        }
    }

    if (areNoWaysToAnyPoint) {
        res.push_back(G);
    }
}


vector<vector<int>> GetMaxChains(vector<vector<bool>> &matrix, int v) {
    vector<vector<int>> res = {};
    GetMaxChains_(matrix, vector<int>(1, v), res);

    return res;
}


vector<vector<int>> GetAllMaxChains(vector<vector<bool>> &matrix) {
    vector<vector<int>> res = {};

    for (int i = 1; i <= matrix.size(); i++) {
        vector<vector<int>> buf = GetMaxChains(matrix, i);
        res.insert(res.end(), buf.begin(), buf.end());
    }

    return res;
}


int main() {
    vector<vector<bool>> matrix(7, vector<bool>(7, false));
    matrixInput(matrix);

    /*
    vector<int> rout_1 = {7, 6, 2, 1};
    vector<int> rout_2 = {2, 6, 5, 3, 6, 2, 1};
    vector<int> rout_3 = {6, 7, 1, 2, 6};
    vector<int> rout_4 = {7, 1, 5, 2, 1, 6, 7};
    vector<int> rout_5 = {3, 6, 2, 7, 6, 2, 1};

    outputSequenceProperty(matrix, rout_1);
    outputSequenceProperty(matrix, rout_2);
    outputSequenceProperty(matrix, rout_3);
    outputSequenceProperty(matrix, rout_4);
    outputSequenceProperty(matrix, rout_5);
    */

    // vector<vector<int>> vertexArray = GetRoutes(matrix, 1, 2);
    // outputVertex(vertexArray);

    // cout << "5 -> 1 : " << GetSumRoutes(matrix, 5, 3, 1) << endl;

    // vector<vector<int>> vertexArray = GetAllSumRoutes(matrix, 3);
    // outputSumRoutes(vertexArray);

//    vector<vector<int>> vertexArray = GetPairRoutes(matrix, 5, 3, 1);
//    outputVertex(vertexArray);

    vector<vector<int>> vertexArray = GetMaxChains(matrix, 1);
    outputVertex(vertexArray);

    return 0;
}