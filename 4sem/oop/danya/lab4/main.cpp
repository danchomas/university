#include "interface.h"

int main() {
    Point p1;
    Point p2(3, 4);
    Point p3(-1, 5, 10);
    
    p1.setX(2);
    p1.setY(3);
    p1.setColor(5);
    
    p2.move(-1, 2);
    
    std::cout << "Расстояние p2 от (0,0): " << p2.distanceFromOrigin() << std::endl;
    
    Point p4 = p3;
    
    std::cout << "p3 и p4 " << (p3 == p4 ? "равны" : "не равны") << std::endl;
    
    std::cout << "\nИтоговые точки:\n";
    p1.print();
    p2.print();
    p3.print();
    p4.print();
    
    return 0;
}
