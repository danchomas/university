#ifndef HEADER_HPP
#define HEADER_HPP


class Money {
private:
    int nominal;
    int count;

public:
    Money();
    Money(int f, int s);
    void print() const;
    bool canAfford(int price) const;
    int howManyItems(int price) const;
    friend Money operator+= (Money& a1, const Money& a2);
    friend const Money operator++(Money& a1, int);
};

#endif