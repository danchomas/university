#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

class Product {
protected:
    string name;
    double price;
public:
    Product(const string& name, double price) : name(name), price(price) {}
    virtual ~Product() {}
    virtual void printInfo() const = 0;
};

class ConcreteProduct : public Product {
public:
    ConcreteProduct(const string& n = "", double p = 0.0) : Product(n, p) {
        if (p < 0) throw invalid_argument("Цена должна быть положительной");
    }

    void printInfo() const override {
        cout << "Продукт: " << name << ", Цена: " << price << endl;
    }
};

class ProductStack {
private:
    static const int maxSize = 3;
    ConcreteProduct stack[maxSize];
    int topIndex;
public:
    ProductStack() : topIndex(-1) {}

    void push(const ConcreteProduct& item) {
        if (isFull()) {
            throw overflow_error("Стек переполнен");
        }
        stack[++topIndex] = item;
    }

    ConcreteProduct pop() {
        if (isEmpty()) {
            throw underflow_error("Стек пустой");
        }
        return stack[topIndex--];
    }

    bool isEmpty() const {
        return topIndex == -1;
    }

    bool isFull() const {
        return topIndex == maxSize - 1;
    }
};

int main() {
    try {
        ProductStack stack;

        stack.push(ConcreteProduct("Apple", 1.5));
        stack.push(ConcreteProduct("Bread", 2.3));
        stack.push(ConcreteProduct("Milk", 1.8));
        stack.push(ConcreteProduct("Fedya", 10.0));//  -> будет переполнение стека

        while (!stack.isEmpty()) {
            stack.pop().printInfo();
        }

    } catch (const exception& e) {
        cerr << "Ошибка - " << e.what() << endl;
        return 1;
    }

    return 0;
}
