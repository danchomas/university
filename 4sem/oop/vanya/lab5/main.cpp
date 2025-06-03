#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

class TelephoneDirectory {
public:
    virtual void printInfo() const = 0;
    virtual bool matchesSearch(const string& searchTerm) const = 0;
    virtual ~TelephoneDirectory() = default;
};

class Person : public TelephoneDirectory {
private:
    string surname;
    string address;
    string phoneNumber;

public:
    Person(const string& s, const string& a, const string& p)
        : surname(s), address(a), phoneNumber(p) {}

    void printInfo() const override {
        cout << "Тип: Персона\n";
        cout << "Фамилия: " << surname << "\n";
        cout << "Адрес: " << address << "\n";
        cout << "Телефон: " << phoneNumber << "\n\n";
    }

    bool matchesSearch(const string& searchTerm) const override {
        return surname.find(searchTerm) != string::npos;
    }
};

class Organization : public TelephoneDirectory {
private:
    string name;
    string address;
    string phoneNumber;
    string fax;
    string contactPerson;

public:
    Organization(const string& n, const string& a, const string& p, 
                 const string& f, const string& cp)
        : name(n), address(a), phoneNumber(p), fax(f), contactPerson(cp) {}

    void printInfo() const override {
        cout << "Тип: Организация\n";
        cout << "Название: " << name << "\n";
        cout << "Адрес: " << address << "\n";
        cout << "Телефон: " << phoneNumber << "\n";
        cout << "Факс: " << fax << "\n";
        cout << "Контактное лицо: " << contactPerson << "\n\n";
    }

    bool matchesSearch(const string& searchTerm) const override {
        return name.find(searchTerm) != string::npos || 
               contactPerson.find(searchTerm) != string::npos;
    }
};

class Friend : public TelephoneDirectory {
private:
    string surname;
    string address;
    string phoneNumber;
    string birthDate;

public:
    Friend(const string& s, const string& a, const string& p, const string& bd)
        : surname(s), address(a), phoneNumber(p), birthDate(bd) {}

    void printInfo() const override {
        cout << "Тип: Друг\n";
        cout << "Фамилия: " << surname << "\n";
        cout << "Адрес: " << address << "\n";
        cout << "Телефон: " << phoneNumber << "\n";
        cout << "Дата рождения: " << birthDate << "\n\n";
    }

    bool matchesSearch(const string& searchTerm) const override {
        return surname.find(searchTerm) != string::npos;
    }
};

int main() {
    vector<unique_ptr<TelephoneDirectory>> directory;

    directory.push_back(make_unique<Person>("Шпак", "ул. Пупкина", "123"));
    directory.push_back(make_unique<Organization>("ООО тмыв денег", "ул. Лупкина", "1234", "12345", "Шпак"));
    directory.push_back(make_unique<Friend>("Фриков", "ул. Матюк", "576", "11.11.1111"));

    cout << "=== Полная информация из телефонного справочника ===\n";
    for (const auto& entry : directory) {
        entry->printInfo();
    }

    string searchTerm;
    cout << "Введите фамилию или название для поиска: ";
    getline(cin, searchTerm);

    cout << "\n=== Результаты поиска ===\n";
    bool found = false;
    for (const auto& entry : directory) {
        if (entry->matchesSearch(searchTerm)) {
            entry->printInfo();
            found = true;
        }
    }

    if (!found) {
        cout << "Записи, соответствующие критерию поиска, не найдены.\n";
    }

    return 0;
}