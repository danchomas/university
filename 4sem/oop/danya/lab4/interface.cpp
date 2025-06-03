#include "interface.h"

Point::Point() : x(0), y(0), color(0) {}

Point::Point(int x, int y, int color) : x(x), y(y), color(color) {}

int Point::getX() const { return x; }
int Point::getY() const { return y; }
int Point::getColor() const { return color; }

void Point::setX(int x) { this->x = x; }
void Point::setY(int y) { this->y = y; }
void Point::setColor(int color) { this->color = color; }

void Point::print() const {
    std::cout << "Точка(" << x << ", " << y << "), Цвет: " << color << std::endl;
}

double Point::distanceFromOrigin() const {
    return std::sqrt(x * x + y * y);
}

void Point::move(int a, int b) {
    x += a;
    y += b;
}

Point& Point::operator=(const Point& other) {
    if (this == &other)
        return *this;
    x = other.x;
    y = other.y;
    color = other.color;
    return *this;
}

bool Point::operator==(const Point& other) const {
    return (x == other.x && y == other.y && color == other.color);
}
