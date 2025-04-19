#include <iostream>
#include <ctime>
#include <string>

using namespace std;

class Software {
protected:
    string name;
    string manufacturer;
public:
    Software(const string& name, const string& manufacturer)
        : name(name), manufacturer(manufacturer) {}

    virtual void printInfo() const = 0;
    virtual bool isUsable() const = 0;
};

class FreeSoftware : public Software {
public:
    FreeSoftware(const string& name, const string& manufacturer)
        : Software(name, manufacturer) {}

    void printInfo() const override {
        cout << "Бесплатное программное обеспечение: " << name << " от " << manufacturer << endl;
    }

    bool isUsable() const override {
        return true;
    }
};

class Shareware : public Software {
private:
    time_t installDate;
    int freeTrialDays;
public:
    Shareware(const string& name, const string& manufacturer, time_t installDate, int freeTrialDays)
        : Software(name, manufacturer), installDate(installDate), freeTrialDays(freeTrialDays) {}

    void printInfo() const override {
        cout << "Условно-бесплатное программное обеспечение: " << name << " от " << manufacturer << endl;
        cout << "Дата установки: " << ctime(&installDate);
        cout << "Дни бесплатного использования: " << freeTrialDays << endl;
    }

    bool isUsable() const override {
        time_t now = time(0);
        return difftime(now, installDate) < freeTrialDays * 86400;
    }
};

class CommercialSoftware : public Software {
private:
    double price;
    time_t installDate;
    int usageDays;
public:
    CommercialSoftware(const string& name, const string& manufacturer, double price, time_t installDate, int usageDays)
        : Software(name, manufacturer), price(price), installDate(installDate), usageDays(usageDays) {}

    void printInfo() const override {
        cout << "Коммерческое программное обеспечение: " << name << " от " << manufacturer << endl;
        cout << "Цена: $" << price << endl;
        cout << "Дата установки: " << ctime(&installDate);
        cout << "Дни использования: " << usageDays << endl;
    }

    bool isUsable() const override {
        time_t now = time(0);
        return difftime(now, installDate) < usageDays * 86400;
    }
};

class SoftwareDatabase {
private:
    static const int MAX_SOFTWARE = 10;
    Software* softwareList[MAX_SOFTWARE];
    int count = 0;

public:
    void addSoftware(Software& software) {
        if (count < MAX_SOFTWARE) {
            softwareList[count++] = &software;
        }
    }

    void printAllSoftware() const {
        cout << "Полный список программного обеспечения" << endl;
        for (int i = 0; i < count; ++i) {
            softwareList[i]->printInfo();
            cout << "-------------------------" << endl;
        }
    }

    void printUsableSoftware() const {
        cout << "Доступное программное обеспечение:" << endl;
        for (int i = 0; i < count; ++i) {
            if (softwareList[i]->isUsable()) {
                softwareList[i]->printInfo();
                cout << "-------------------------" << endl;
            }
        }
    }
};

int main() {
    FreeSoftware linuxOS("Linux", "GNU Project");
    Shareware winrar("WinRAR", "RARLAB", time(0), 30);
    CommercialSoftware office("Microsoft Office", "Microsoft", 200, time(0), 365);

    SoftwareDatabase database;
    
    database.addSoftware(linuxOS);
    database.addSoftware(winrar);
    database.addSoftware(office);

    database.printAllSoftware();
    database.printUsableSoftware();

    return 0;
}