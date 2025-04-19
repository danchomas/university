#include <iostream>
#include <stdexcept>
#include <algorithm>

using namespace std;

template<typename T, size_t N = 100>
class Set {
private:
    T data[N];      // Статический массив для хранения элементов
    size_t count;   // Количество элементов в множестве

public:
    Set() : count(0) {}

    void insert(const T& value) {
        if (count >= N) {
            throw invalid_argument("Множество заполнено");
        }
        if (contains(value)) {
            throw invalid_argument("Элемент уже существует");
        }
        data[count++] = value;
    }

    void remove(const T& value) {
        for (size_t i = 0; i < count; ++i) {
            if (data[i] == value) {
                swap(data[i], data[count - 1]);
                --count;
                return;
            }
        }
        throw invalid_argument("Элемент отсутствует в множестве");
    }

    void removeInd(const T& ind) {
        for (size_t i = 0; i < count; ++i){
            if (i == ind){
                swap(data[i], data[count - 1]);
                --count;
                return;
            }
        }
        throw invalid_argument("Индекс отсутствует в множестве");
    }

    bool contains(const T& value) const {
        for (size_t i = 0; i < count; ++i) {
            if (data[i] == value) {
                return true;
            }
        }
        return false;
    }

    void clear() {
        count = 0;
    }

    size_t size() const {
        return count;
    }

    bool isEmpty() const{
        return count == 0;
    }

    void print() const{
        cout << "{";
        for (size_t i = 0; i < count; i++){
            cout << data[i];
            if (i != count - 1) cout << ", ";
        }
        cout << "}" << endl;
    }

    Set<T> copy() const{
        Set<T> newSet;
        size_t i = 0;
        while(i < count){
            newSet.insert(data[i]);
            i++;
        }
        return newSet;
    }
};


int main(){
    Set<int> mySet;
    mySet.insert(1);
    mySet.insert(2);
    mySet.insert(3);
    mySet.insert(4);

    mySet.removeInd(0);
    mySet.print();
}
