#include "header.hpp"

Money::Money() : nominal(0), count(0) {}

Money::Money(int f, int s) : nominal(f), count(s) {}

void Money::print() const {
    std::cout << "номинал - " << nominal << " количество - " << count << std::endl;
}

bool Money::canAfford(int price) const {
    return (nominal * count) >= price;
}

int Money::howManyItems(int price) const {
    return (nominal * count) / price;
}

Money operator+= (Money& a1, const Money& a2) {
    if (a1.nominal == a2.nominal) a1.count += a2.count;
    else {
        int exchangeRate;
        if (a1.nominal > a2.nominal) {
            exchangeRate = a1.nominal / a2.nominal;
            a1.count += a2.count / exchangeRate;
        }
        else {
            exchangeRate = a2.nominal / a1.nominal;
            a1.count += a2.count * exchangeRate;
        }
    }
    return a1;
}

const Money operator++(Money& a1, int) {
    Money oldCount = a1;
    a1.count++;
    return oldCount;
}