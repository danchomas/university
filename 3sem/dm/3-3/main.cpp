#include <iostream>
#include <vector>
#include <cassert>
#include <math.h>

using namespace std;

class Relation {
    public:

    Relation() = default;

    Relation(int r, int c, int v) : rows(r), columns(c) {
        values.assign(rows, vector<bool>(columns, v));
    }

    Relation(const vector<vector<bool>> v) : rows(v.size()), columns(v.size() ? v[0].size() : 0), values{v} {}

    bool inclusion(const Relation& sec) const{
        bool res = true;
        for (int i = 0; i < rows; i++){
            for (int j = 0; j < columns; j++){
                if (values[i][j] == 1 && values[i][j] != sec.values[i][j]){
                    res = false;
                }
            }
        }
        return res;
    }

    bool equation(const Relation& sec) const{
        return this->inclusion(sec) && sec.inclusion(*this);
    }

    Relation _intersection(const Relation& sec) const{
        Relation result(rows, columns, false);

        for (int i = 0; i < rows; ++i){
            for (int j = 0; j < columns; ++j){
                if (values[i][j] == true && sec.values[i][j] == true){
                    result.values[i][j] = true;
                }
            }
        }
        return result;
    }

    Relation difference(const Relation& sec) const{
        Relation result(rows, columns, false);

        for (int i = 0; i < rows; i++){
            for (int j = 0; j < columns; j++){
                if (values[i][j] == true && sec.values[i][j] == false){
                    result.values[i][j] = true;
                }   
            }
        } 
        return result;
    }

    Relation sym_difference(const Relation& sec) const{
        Relation result(rows, columns, true);

        for (int i = 0; i < rows; ++i){
            for (int j = 0; j < columns; ++j){
                if (values[i][j] == sec.values[i][j]){
                    result.values[i][j] = false;
                }
            }
        }
        return result;   
    }

    Relation _addition() const{ 
        Relation result(rows, columns, true);

        for (int i = 0; i < rows; i++){
            for (int j = 0; j < columns; j++){
                if (values[i][j]){
                    result.values[i][j] = false;
                }
            }
        }
        return result;
    }

    Relation appeal() const{
        Relation result(rows, columns, false);

        for (int i = 0; i < rows; i++){
            for (int j = 0; j < columns; j++){
                result.values[i][j] = values[j][i];
            }
        }
        return result;
    }

    Relation _composition(const Relation& sec) const{
        Relation result(rows, columns, false);

        for (int i = 0; i < rows; i++){
            for (int j = 0; j < columns; j++){
                for (int k = 0; k < columns; k++){
                    if (values[i][k] && sec.values[k][j]){
                        result.values[i][j] = true;
                        break;
                    }
                }
            }
        }
        return result;
    }

    Relation exponentiation(const int degree) {
        Relation result(rows, columns, false);

        if (degree == 0){
            for (int i = 0; i < rows; i++){
                result.values[i][i] = true;
            }
        }
        else if (degree >= 1){
            result.values = values;

            if (degree != 1){
                for (int i = 0; i < degree; i++){
                    result = result._composition(*this);
                }
            }
        }
        return result;
    }

    Relation strict_order() const{
        Relation result

= *this;

        for (int i = 0; i < rows; i++){
            result.values[i][i] = 0;
        }
        return result;
    }

    Relation domination() const{
        Relation A = strict_order();
        Relation B = A._composition(A);

        return A.difference(B);
    }

        bool checkReflect() const{
        bool res = true;
        for (int i = 0; i < rows; i++){
            if (values[i][i] == 0){
                    res = false;
                    cout << "��������� R �� �����������, ������ ��� ���� (" << i + 1 << "," << i + 1 << ") �� ����������� R" << endl;
                    return res;
            }
        }
        cout << "��������� �����������" << endl;
        return res;
    }

    bool checkAntiReflect() const{
        bool res = true;
        for (int i = 0; i < rows; i++){
            if (values[i][i] == 1){
                res = false;
                cout << "��������� R �� ���������������, ������ ��� ���� (" << i + 1 << "," << i + 1<< ") ����������� R" << endl;
                return res;
            }
        }
        cout << "��������� ���������������" << endl;
        return res;
    }

    bool checkSymmetric() const {
        bool res = true;
        for (int i = 0; i < rows; i++){
            for (int j = 0; j < columns; j++){
                if (values[i][j] != values[j][i]){
                    res = false;
                    cout << "��������� R �� �����������, ������ ��� ���� (" << i + 1 << "," << j + 1 << ") ����������� R, � ���� (" << j + 1 << "," << i + 1 << ") � �� �����������." << endl;
                    return res;
                }
            }
        }
        cout << "��������� �����������" << endl;
        return res;
    }

    bool checkAntiSymmetric() const {
        bool res = true;
        for (int i = 0; i < rows; i++){
            for (int j = 0; j < columns; j++){
                if (i != j && values[i][j] && values[j][i]){
                    res = false;
                    cout << "��������� R �� ���������������, ������ ��� ���� (" << i + 1 << "," << j + 1 << ") ����������� R � ���� (" << j + 1 << "," << i + 1 << ") ���� ����������� R." << endl;
                    return res;
                }
            }
        }
        cout << "��������� ���������������" << endl;
        return res;
    }

    bool checkTransitive() const{
        bool res = true;
        for (int i = 0; i < rows; i++){
            for (int z = 0; z < rows; z++){
                if (values[i][z] == true) {
                    for (int j = 0; j < columns; j++){
                        if (values[z][j] == true && values[i][j] != true){
                            res = false;
                            cout << "��������� R �� �����������, ������ ��� ���� (" << i + 1 << "," << z + 1 << ") ����������� R, ���� (" << z + 1 << "," << j + 1 << ") ����������� R, � ���� (" << i + 1 << "," << j + 1 << ") �� ����������� R." << endl;
                            return res;
                        }
                    }
                }
            }
        }
        cout << "��������� �����������" << endl;
        return res;
    }

    bool checkAntiTransitive() const{
        bool res = true;
        for (int i = 0; i < rows; i++){
            for (int z = 0; z < rows; z++){
                if (values[i][z] == true){
                    for (int j = 0; j < columns; j++){
                        if (values[z][j] == true && values[i][j] == true){
                            res = false;
                            cout << "��������� R �� ���������������, ������ ��� ���� (" << i + 1 << "," << z + 1 << ") ����������� R, ���� (" << z + 1 << "," << j + 1 << ") ����������� R � ���� (" << i + 1 << "," << j + 1 << ") ����������� R." << endl;
                            return res;
                        }
                    }
                }
            }
        }
        cout << "��������� ���������������" << endl;
        return res;
    }

bool checkFull() const{
        bool res = true;
        for (int i = 0; i < rows; i++){
            for (int j = 0; j < columns; j++){
                if (i != j && values[i][j] == 0 && values[j][i] == 0){
                    res = false;
                    cout << "��������� R �� �����, ������ ��� � ��� ��� ���� (" << i + 1 << "," << j + 1 << ") � ��� ���� (" << j + 1 << "," << i + 1 << ")" << endl;
                    return res;
                }
            }
        }
        cout << "��������� �����" << endl;
        return res;
    }

    void findPartition() const{
        vector<int> S(columns, 0);
        int k = 0;
        for (int i = 0; i < columns; i++){
            if (S[i] == 0){
                k++;
                for (int j = 0; j < columns; j++){
                    if (values[i][j] == 1){
                        S[j] = k;
                    }
                }
            }
        }

        cout << "������ S: ";
        for (int i = 0; i < columns; i++){
            cout << S[i] << " ";
        }
        cout << endl;
    }


    void out() const{
        for (int i = 0; i < rows; i++){
            const auto& row = values[i];
            for (int j = 0; j < columns; j++){
                const auto& value = row[j];
                cout << value << ' ';
            }
            cout << endl;
        }
        cout << endl;
    }

    int rows;
    int columns;
    vector<vector<bool>> values;
};

void getFeatures(const Relation& rel) {
    bool is_rel_reflect = rel.checkReflect();
    bool is_rel_antireflect = rel.checkAntiReflect();
    bool is_rel_symmetric = rel.checkSymmetric();
    bool is_rel_antisymmetric = rel.checkAntiSymmetric();
    bool is_rel_transitive = rel.checkTransitive();
    bool is_rel_antitransitive = rel.checkAntiTransitive();
    bool is_rel_full = rel.checkFull();
}

Relation makeRelFromM(const vector<pair<int, int>>& M){
    Relation result(M.size(), M.size(), 0);

    for (int i = 0; i < result.rows; i++){
        for (int j = 0; j < result.columns; j++){
            if ((pow(M[i].first, 2) + pow(M[i].second, 2)) < (pow(M[j].first, 2) + pow(M[j].second, 2))) { //����� - M[i].first * M[i].second > M[j].first * M[j].second
                result.values[i][j] = 1;
            }
        }
    }
    return result;
}

Relation makeA(){
    Relation res(6, 6, false);

    for (int i = 1; i <= 6; i++){
        for (int j = 1; j <= 6; j++){
            if (i > j){
                res.values[i - 1][j - 1] = true;
            }
        }
    }
    return res;
}

Relation makeD(){
    Relation result(10, 10, false);

    for (int x = 1; x <= 10; x++){
        for (int y = 1; y <= 10; y++){
            if (((x < 7 && y < 7) && (x % 2 == 0 && y % 2 == 0)) || (x==y)){
                result.values[x - 1][y - 1] = true;
            }
        }
    }
    return result;
}

bool isElPositive(const vector<int>& W){
    for (const auto& value : W){
        if (value >= 0){
            return true;
        }
    }
    return false;
}

void topologicSort(const Relation& R, vector<pair<int, int>>& M){
    // i = -1
    int i = -1;

    //����� ����� ��������� �� ���� �������� ������� � ��������� �� � ������� W
    vector<int> W(R.rows, 0);
    for (int j = 0; j < R.rows; j++){
        for (int k = 0; k < R.columns; k++){
            W[j] += R.values[k][j];
        }
    }
    
    //���� � ������� W ��� �������� �������������, �� ����� ���������
    while (isElPositive(W)){
        cout << abs(i) << "-� �������: ";

        //������� �������� ������� W �������� �� i
        for (int j = 0; j < W.size(); j++){
            if (W[j] == 0){
                cout << '{' << M[j].first << ", " << M[j].second << "}, ";
                W[j] = i;
            }
        }

        //������� �� ������� W ����������� ������ ������ �������, ��������������� ������� �������� ������� W �� ��������� i;
        for (int j = 0; j < W.size(); j++){
            if (W[j] == i){
                for (int k = 0; k < W.size(); k++){
                    W[k] -= R.values[j][k];
                }
            }
        }

//i := i � 1, ������� � �. 3
        i--;

        cout << endl;
    }
    for (size_t j = 0; j < W.size(); j++) {
        cout <<"Element " << j <<" is on level " <<-W[j] << endl;
    }
}

int main(){
    setlocale(LC_ALL, "Russian");

    Relation A = makeD();
    A.findPartition();

    return 0;
}