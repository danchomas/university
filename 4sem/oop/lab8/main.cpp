#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <stdexcept>
#include <sstream>
#include <vector>
#include "set.hpp"

class SetException : public std::runtime_error {
public:
    SetException(const std::string& msg) : std::runtime_error(msg) {}
};

class Subject {
private:
    std::string grade;
    std::string type;
    std::string name;

public:
    Subject() : grade(""), type(""), name("") {}

    Subject(std::string g, std::string t, std::string n)
        : grade(g), type(t), name(n) {}

    int getGrade() const {
        if (grade == "отл" || grade == "зачет" || grade == "5") {
            return 5;
        } else if (grade == "хор" || grade == "4") {
            return 4;
        } else if (grade == "уд" || grade == "3") {
            return 3;
        } else {
            return 2;
        }
    }

    const std::string& getName() const {
        return name;
    }

    const std::string& getType() const {
        return type;
    }

    const std::string& getGradeString() const {
        return grade;
    }

    bool operator==(const Subject& other) const {
        return (name == other.name) && (type == other.type) && (grade == other.grade);
    }

    bool operator!=(const Subject& other) const {
        return !(*this == other);
    }

    bool operator<(const Subject& other) const {
        if (type < other.type) {
            return true;
        } else if (type == other.type) {
            return name < other.name;
        } else {
            return false;
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const Subject& subject) {
        os << subject.name << " (" << subject.type << "): " << subject.grade;
        return os;
    }
};

class Student {
private:
    std::string name;
    Set<Subject> grades;

public:
    // Конструктор по умолчанию
    Student() : name("") {}

    Student(std::string n) : name(n) {}

    void addGrade(const Subject& s) {
        grades.add(s);
    }

    std::string getName() const {
        return name;
    }

    double getAvgGrade() const {
        double sum = 0;
        int size = grades.size();
        if (size == 0) {
            return 0.0;
        }
        for (size_t i = 0; i < size; ++i) {
            sum += grades[i].getGrade();
        }
        return sum / size;
    }

    void print() const {
        std::cout << "- cтудент: " << name << "\n";
        std::cout << "- cредний балл: " << std::fixed << std::setprecision(2) <<
            getAvgGrade() << "\n";
        for (size_t i = 0; i < grades.size(); ++i) {
            std::cout << " --- " << grades[i] << "\n";
        }
    }

    bool operator==(const Student& other) const {
        return name == other.name;
    }

    bool operator!=(const Student& other) const {
        return !(*this == other);
    }

    bool operator<(const Student& other) const {
        return name < other.name;
    }

    friend std::ostream& operator<<(std::ostream& os, const Student& student) {
        student.print();
        return os;
    }
};

class Group {
private:
    std::string name;
    Set<Student> students;

public:
    Group(std::string n) : name(n) {}

    void addStudent(const Student& s) {
        students.add(s);
    }

    std::string getName() const {
        return name;
    }

    Set<Student>& getStudents() {
        return students;
    }

    void SortByGrades() {
        bool swapped;
        size_t n = students.size();
        do {
            swapped = false;
            for (size_t i = 1; i < n; i++) {
                if (students[i-1].getAvgGrade() < students[i].getAvgGrade()) {
                    std::swap(students[i-1], students[i]);
                    swapped = true;
                }
            }
            n--;
        } while (swapped);
    }

    void print() const {
        std::cout << "группа: " << name << "\ncписок студентов:\n";
        for (size_t i = 0; i < students.size(); ++i) {
            std::cout << students[i] << "\n";
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const Group& group) {
        group.print();
        return os;
    }
};

class GroupReader {
public:
    static std::vector<Group> readFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file) throw std::runtime_error("Cannot open file: " + filename);

        std::vector<Group> groups;
        std::string line;

        while (std::getline(file, line)) {
            auto parts = split(line, '>');
            if (parts.size() != 6) continue;

            Group& group = findOrCreateGroup(groups, parts[1]);
            Student& student = findOrCreateStudent(group, parts[2]);
            student.addGrade(Subject(parts[5], parts[4], parts[3]));
        }

        return groups;
    }

private:
    static std::vector<std::string> split(std::string& s, char delim) {
        std::vector<std::string> res;
        std::stringstream ss(s);
        std::string item;

        while (std::getline(ss, item, delim)) {
            res.push_back(item);
        }

        return res;
    }

    static Group& findOrCreateGroup(std::vector<Group>& groups, const std::string& name) {
        for (auto& group : groups) {
            if (group.getName() == name) return group;
        }
        groups.emplace_back(name);
        return groups.back();
    }

    static Student& findOrCreateStudent(Group& group, const std::string& name) {
        for (size_t i = 0; i < group.getStudents().size(); i++) {
            if (group.getStudents()[i].getName() == name) {
                return group.getStudents()[i];
            }
        }
        group.addStudent(Student(name));

        for (size_t i = 0; i < group.getStudents().size(); i++) {
            if (group.getStudents()[i].getName() == name) {
                return group.getStudents()[i];
            }
        }
        throw std::runtime_error("Failed to create student: " + name);
    }
};

int main() {
    try {
        auto groups = GroupReader::readFromFile("students.txt");
        for (auto& group : groups) {
            group.SortByGrades();
            std::cout << group << "\n";
        }
    } catch (const std::exception& e) {
        std::cerr << "ошибка: " << e.what() << "\n";
        return 1;
    }
    return 0;
}
