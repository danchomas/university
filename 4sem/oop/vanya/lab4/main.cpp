#include <iostream>
#include <cmath>
#include <clocale>

class Triangle {
private:
    int a, b, c;
public:
    Triangle(int sideA, int sideB, int sideC) : a(sideA), b(sideB), c(sideC) {}

    void displaySides() const {
        std::cout << "Стороны треугольника: " << a << ", " << b << ", " << c << std::endl;
    }

    int getPerimeter() const {
        return a + b + c;
    }

    double getArea() const {
        double p = getPerimeter() / 2.0;
        return sqrt(p * (p - a) * (p - b) * (p - c));
    }

    friend bool operator>(const Triangle& t1, const Triangle& t2) {
        return t1.getArea() > t2.getArea();
    }

    Triangle& operator++() {
        ++a;
        ++b;
        ++c;
        return *this;
    }
};

int main() {
    Triangle t1(3, 4, 5);
    Triangle t2(6, 8, 10);

    t1.displaySides();
    std::cout << "Периметр: " << t1.getPerimeter() << std::endl;
    std::cout << "Площадь: " << t1.getArea() << std::endl;

    if (t2 > t1) {
        std::cout << "t2 больше t1 по площади.\n";
    } else {
        std::cout << "t1 больше или равен t2 по площади.\n";
    }

    ++t1;
    t1.displaySides();

    return 0;
}