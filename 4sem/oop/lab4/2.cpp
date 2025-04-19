#include <iostream>

class Car {
 float speed;
 float mass;
 char name[10];

 public:
 Car(char* n){
     for(int i=0; i<10; i++)
        name[i]=n[i];
        speed=10;
 };
 void printCar(){
 std::cout<<name<<' '<< speed <<std::endl;
 };

friend const Car operator+ (const Car& a1, const Car& a2){

    char *name = new char[10];
    for(int i=0; i<10; i++)
        name[i]=a1.name[i];
    Car a3 (name);
    a3.speed=a1.speed+a2.speed;
    return a3;

}

};

int main ()
{   char *name = new char[10];
    name = "nissan";
    Car almera(name);
    almera.printCar();

    name = "nissan1";
    Car almera1(name);
    almera1.printCar();

    name = "nissan2";
    Car almera2(name);
    almera2.printCar();

    almera = almera1+almera2;
    almera.printCar();
    return 0;
}