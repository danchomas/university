#include <iostream>

class Money {
private:
    int nominal;
    int count;

public:
    Money() : nominal(0), count(0) {}
    Money(int f, int s) : nominal(f), count(s) {}

    void print() const {
        std::cout << "номинал - " << nominal << " количество - " << count << std::endl;
    }

    bool canAfford(int price) const {
        return (nominal * count) >= price;
    }

    int howManyItems(int price) const {
        return (nominal * count) / price;
    }

    friend Money operator+= (Money& a1, const Money& a2){
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

    void operator++(int) {
        count++;
    }
};

int main() {
    Money wallet(100, 5);
    Money extra(500, 1);
    Money less(50, 5);
    wallet.print();
    extra.print();
    less.print();

    int productPrice = 450;

    if (wallet.canAfford(productPrice)) {
        std::cout << "можете купить " << wallet.howManyItems(productPrice) << " товаров" << std::endl;
    } else {
        std::cout << "не хватит" << std::endl;
    }

    wallet++;
    wallet.print();

    wallet += extra;
    wallet.print();

    wallet += less;
    wallet.print();

    return 0;
}