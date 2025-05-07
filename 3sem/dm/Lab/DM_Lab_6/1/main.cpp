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


void GenAllMatrixByVerEdge_(vector<vector<bool>> matrix,
                            vector<vector<int>> matrixOfIndex,
                            int indexNow,
                            size_t countOfEdges,
                            vector<vector<vector<bool>>> &resMatrix,
                            int lim) {

    if (countOfEdges > 0 && matrixOfIndex.size() - indexNow >= countOfEdges && resMatrix.size() < lim) {
        matrix[matrixOfIndex[indexNow][0]][matrixOfIndex[indexNow][1]] = true;
        matrix[matrixOfIndex[indexNow][1]][matrixOfIndex[indexNow][0]] = true;
        GenAllMatrixByVerEdge_(matrix,
                               matrixOfIndex,
                               indexNow + 1,
                               countOfEdges - 1,
                               resMatrix,
                               lim);

        matrix[matrixOfIndex[indexNow][0]][matrixOfIndex[indexNow][1]] = false;
        matrix[matrixOfIndex[indexNow][1]][matrixOfIndex[indexNow][0]] = false;
        GenAllMatrixByVerEdge_(matrix,
                               matrixOfIndex,
                               indexNow + 1,
                               countOfEdges,
                               resMatrix,
                               lim);
    } else if (countOfEdges == 0) {
        resMatrix.push_back(matrix);
    }
}


vector<vector<vector<bool>>> GenAllMatrixByVerEdge(size_t countOfVertexes,
                                                   size_t countOfEdges,
                                                   int lim) {
    if (lim == -1) {
        lim = 1000000;
    }


    vector<vector<vector<bool>>> resMatrix;

    vector<vector<int>> matrixOfIndex;

    for (int index_x = 0; index_x < countOfVertexes && countOfEdges; ++index_x) {
        for (int index_y = index_x + 1; index_y < countOfVertexes; ++index_y) {
            matrixOfIndex.push_back({index_x, index_y});
        }
    }

    GenAllMatrixByVerEdge_(vector<vector<bool>>(countOfVertexes, vector<bool>(countOfVertexes, false)),
                           matrixOfIndex,
                           0,
                           countOfEdges,
                           resMatrix,
                           lim);

    return resMatrix;
}


void GenRandomMatrixByVerEdge_(vector<vector<bool>> &matrix,
                               vector<vector<int>> matrixOfIndex,
                               size_t countOfEdges,
                               vector<vector<vector<bool>>> &resMatrix,
                               int lim) {

    if (matrixOfIndex.size() > 0 && matrixOfIndex.size() >= countOfEdges && countOfEdges > 0 &&
        resMatrix.size() < lim) {
        unsigned int indexNow = rand() % matrixOfIndex.size();
        srand(indexNow);

        int indexNowX = matrixOfIndex[indexNow][0];
        int indexNowY = matrixOfIndex[indexNow][1];
        matrixOfIndex.erase((matrixOfIndex.cbegin() + indexNow));

        matrix[indexNowX][indexNowY] = true;
        matrix[indexNowY][indexNowX] = true;
        GenRandomMatrixByVerEdge_(matrix,
                                  matrixOfIndex,
                                  countOfEdges - 1,
                                  resMatrix,
                                  lim);

        matrix[indexNowX][indexNowY] = false;
        matrix[indexNowY][indexNowX] = false;
        GenRandomMatrixByVerEdge_(matrix,
                                  matrixOfIndex,
                                  countOfEdges,
                                  resMatrix,
                                  lim);
    } else if (countOfEdges == 0) {
        vector<vector<bool>> buf;
        buf.assign(matrix.begin(), matrix.end());
        resMatrix.push_back(buf);
    }
}

vector<vector<vector<bool>>> GenRandomMatrixByVerEdge(size_t countOfVertexes,
                                                      size_t countOfEdges,
                                                      int lim) {
    if (lim == -1) {
        lim = 1000000;
    }


    vector<vector<vector<bool>>> resMatrix;

    vector<vector<int>> matrixOfIndex;

    for (int index_x = 0; index_x < countOfVertexes && countOfEdges; ++index_x) {
        for (int index_y = index_x + 1; index_y < countOfVertexes; ++index_y) {
            matrixOfIndex.push_back({index_x, index_y});
        }
    }
    vector<vector<bool>> matrix(countOfVertexes, vector<bool>(countOfVertexes, false));
    GenRandomMatrixByVerEdge_(matrix,
                              matrixOfIndex,
                              countOfEdges,
                              resMatrix,
                              lim);

    return resMatrix;
}


bool IsHamilton_(vector<vector<bool>> &matrix, vector<int> &G) {
    bool isHamilton = false;
    bool areNoWaysToAnyPoint = true;
    for (int i = 0; i < matrix.size() && G.size() <= matrix.size() && !isHamilton; i++) {
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
                isHamilton = IsHamilton_(matrix, G);
                G.pop_back();
            }
        }
    }

    if (areNoWaysToAnyPoint && G.size() == matrix.size() && matrix[G[0] - 1][G[G.size() - 1] - 1] && G.size() > 2) {
        return true;
    }

    return isHamilton;
}

bool IsHamilton(vector<vector<bool>> &matrix) {
    vector<int> G{1};
    return IsHamilton_(matrix, G);
}


void GetHamilton_(vector<vector<bool>> &matrix, vector<int> G, vector<vector<int>> &res) {

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
                GetHamilton_(matrix, G, res);
                G.pop_back();
            }
        }
    }

    if (areNoWaysToAnyPoint && G.size() == matrix.size() && matrix[G[0] - 1][G[G.size() - 1] - 1] && G.size() > 2) {
        G.push_back(G[0]);
        res.push_back(G);
    }
}


vector<vector<int>> GetHamilton(vector<vector<bool>> &matrix, int v) {
    vector<vector<int>> res = {};
    GetHamilton_(matrix, vector<int>(1, v), res);

    return res;
}


vector<vector<int>> GetAllHamilton(vector<vector<bool>> &matrix) {
    vector<vector<int>> res = {};

    for (int i = 1; i <= matrix.size(); i++) {
        vector<vector<int>> buf = GetHamilton(matrix, i);
        res.insert(res.end(), buf.begin(), buf.end());
    }

    return res;
}


bool IsEuler_(vector<vector<bool>> &matrix, vector<int> &G, int countOfEdges) {
    bool isEuler = false;
    for (int i = 0; i < matrix.size() && G.size() <= countOfEdges && !isEuler; i++) {
        if (matrix[i][G[G.size() - 1] - 1]) {
            bool isNoEdgeInG = true;
            for (int j = 0; j < G.size() - 1 && isNoEdgeInG; j++) {
                if (G[j] == G[G.size() - 1] && G[j + 1] == (i + 1) ||
                    G[j] == (i + 1) && G[j + 1] == G[G.size() - 1]) {
                    isNoEdgeInG = false;
                }
            }


            if (isNoEdgeInG) {
                G.push_back(i + 1);
                isEuler = IsEuler_(matrix, G, countOfEdges);
                G.pop_back();
            }
        }
    }

    if (G[0] == G[G.size() - 1]) {
        if (countOfEdges == (G.size() - 1)) {
            return true;
        }
    }

    return isEuler;
}


void GetEuler_2(vector<vector<bool>> &matrix, vector<vector<bool>> &G, vector<int> &stack, vector<int> &res) {

    for (int i = 0; i < matrix.size(); i++) {
        if (G[i][stack.back() - 1]) {
            G[i][stack.back() - 1] = false;
            G[stack.back() - 1][i] = false;

            stack.push_back(i+1);

            GetEuler_2(matrix, G, stack, res);
        }
    }

    res.push_back(stack.back());
    stack.pop_back();
}


bool IsEuler(vector<vector<bool>> &matrix) {
    int countOfEdges = 0;
    bool edgesEven = true;

    for (int i = 0; i < matrix.size() && edgesEven; ++i) {
        int bufSum = 0;
        for (int j = 0; j < matrix.size(); ++j) {
            bufSum += matrix[i][j];
        }
        edgesEven = edgesEven && (bufSum % 2 == 0);

    }

    if (edgesEven) {
        for (int i = 0; i < matrix.size() && edgesEven; ++i) {
            for (int j = i + 1; j < matrix.size(); ++j) {
                countOfEdges += matrix[i][j];
            }
        }

        vector<int> G{1};

        return edgesEven && IsEuler_(matrix, G, countOfEdges);

    }

    return false;
}


void GetEuler_(vector<vector<bool>> &matrix, vector<int> G, vector<vector<int>> &res) {
    bool areNoWaysToAnyPoint = true;
    for (int i = 0; i < matrix.size(); i++) {
        if (matrix[i][G[G.size() - 1] - 1]) {
            bool isNoEdgeInG = true;
            for (int j = 0; j < G.size() - 1 && isNoEdgeInG; j++) {
                if (G[j] == G[G.size() - 1] && G[j + 1] == (i + 1) ||
                    G[j] == (i + 1) && G[j + 1] == G[G.size() - 1]) {
                    isNoEdgeInG = false;
                }
            }

            areNoWaysToAnyPoint = areNoWaysToAnyPoint && !isNoEdgeInG;

            if (isNoEdgeInG) {
                G.push_back(i + 1);
                GetEuler_(matrix, G, res);
                G.pop_back();
            }
        }
    }

    if (areNoWaysToAnyPoint && G[0] == G[G.size() - 1]) {
        int countOfEdges = 0;
        for (int i = 0; i < matrix.size(); ++i) {
            for (int j = i + 1; j < matrix.size(); ++j) {
                countOfEdges += matrix[i][j];
            }
        }

        if (countOfEdges == (G.size() - 1)) {
            res.push_back(G);
        }
    }

}


bool IsEuler2(vector<vector<bool>> &matrix) {
    vector<int> res = {};
    vector<vector<bool>> G;
    G.assign(matrix.cbegin(), matrix.cend());
    vector<int> s(1, 1);

    bool edgesEven = true;

    for (int i = 0; i < matrix.size() && edgesEven; ++i) {
        int bufSum = 0;
        for (int j = 0; j < matrix.size(); ++j) {
            bufSum += matrix[i][j];
        }
        edgesEven = edgesEven && (bufSum % 2 == 0);

    }

    if (edgesEven) {
        GetEuler_2(matrix, G, s, res);

        if (res[0] == res.back()) {
            return true;
        }
    }

    return false;
}

vector<vector<int>> GetEuler(vector<vector<bool>> &matrix, int v) {
    vector<vector<int>> res = {};

    GetEuler_(matrix, vector<int> (1, v), res);

    return res;
}


vector<vector<int>> GetAllEuler(vector<vector<bool>> &matrix) {
    vector<vector<int>> res = {};

    for (int i = 1; i <= matrix.size(); i++) {
        vector<vector<int>> buf = GetEuler(matrix, i);
        res.insert(res.end(), buf.begin(), buf.end());
    }

    return res;
}


int EulerCount(vector<vector<vector<bool>>> &matrix) {
    int counter = 0;
    for (int i = 0; i < matrix.size(); ++i) {
        counter += IsEuler(matrix[i]);
    }

    return counter;
}

int HamiltonCount(vector<vector<vector<bool>>> &matrix) {
    int counter = 0;
    for (int i = 0; i < matrix.size(); ++i) {
        counter += IsHamilton(matrix[i]);
    }
    return counter;
}


void CountOfEulerHamilton(int n, int limitOfEdges) {
    int h = 1;
    int limitMax = 30;

    int countStr = 0;
    int m = n;
    while (countStr < limitMax && m < limitOfEdges) {
        countStr++;
        vector<vector<vector<bool>>> res = GenRandomMatrixByVerEdge(n, m, 100000);

        int eulerCount = EulerCount(res);
        int hamiltonCount = HamiltonCount(res);

        cout << n << "\t"
             << m << "\t"
             << eulerCount << "\t"
             << hamiltonCount << "\t"
             << res.size() << endl;
        m += h;
    }
    cout << endl;
}


int main() {

//    CountOfEulerHamilton(8, 28);
//    CountOfEulerHamilton(9, 36);
//    CountOfEulerHamilton(10, 45);



    /*
    vector<vector<bool>> buf(5, vector<bool>(5, false));
    matrixInput(buf);

    //vector<vector<vector<bool>>> res = GenAllMatrixByVerEdge(8, 8);
    matrixOutput(buf);

    vector<vector<int>> buf_ = GetAllEuler(buf);
    outputVertex(buf_);

    cout << IsEuler(buf) << endl;

    */

    // cout << "Res: " << res.size() << endl;


    //cout << IsEuler(buf) << IsHamilton(buf) << endl;

    /*
    vector<vector<int>> buf_ = GetAllEuler(buf);
    vector<vector<int>> buf_1 = GetAllHamilton(buf);
*/



    vector<vector<vector<bool>>> bb = GenAllMatrixByVerEdge(8, 9, 1000000);
    bool test = true;
    int iter = 0;


    while (test && iter < bb.size()) {
        bool res1 = IsEuler(bb[iter]);
        bool res2 = IsEuler2(bb[iter]);

        test = res1 == res2;
        if (!test) {
            matrixOutput(bb[iter]);
            cout << "Res 1 for : " << res1 <<endl;
            cout << "Res 2 for : " << res2 <<endl;
        }
        iter++;
    }



    //outputVector(res);
    //outputVertex(buf_);

    return 0;
}