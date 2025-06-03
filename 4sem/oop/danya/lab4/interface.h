#pragma once

#include <iostream>
#include <cmath>

class Point {
private:
    int x, y;
    int color;

public:

    Point();

    Point(int x, int y, int color = 0);

    int getX() const;
    int getY() const;
    int getColor() const;

    void setX(int x);
    void setY(int y);
    void setColor(int color);

    void print() const;

    double distanceFromOrigin() const;

    void move(int a, int b);

    Point& operator=(const Point& other);

    bool operator==(const Point& other) const;
};
