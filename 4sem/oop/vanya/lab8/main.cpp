#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include "stack.h"

class Subject {
private:
    std::string grade;
    std::string type;
    std::string name;
public:
    Subject() : grade(""), type(""), name("") {}

    Subject(std::string g, std::string t, std::string n)
        : grade(g), type(t), name(n) {
    }

    int getGrade() const {
        if (grade == "отл" || grade == "зачет" || grade == "5") {
            return 5;
        }
        else if (grade == "хор" || grade == "4") {
            return 4;
        }
        else if (grade == "уд" || grade == "3") {
            return 3;
        }
        else {
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
        if (name == other.name && type == other.type && grade == other.grade) {
            return true;
        }
        else {
            return false;
        }
    }

    bool operator!=(const Subject& other) const {
        return !(*this == other);
    }

    bool operator<(const Subject& other) const {
        if (type < other.type) {
            return true;
        }
        else if (type == other.type) {
            return name < other.name;
        }
        else {
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
    SingleLinkedList<Subject> grades;

public:
    Student() : name("") {}

    Student(std::string n) : name(n) {}

    void addGrade(const Subject& s) {
        grades.pushBack(s);
    }

    std::string getName() const {
        return name;
    }

    double getAvgGrade() const {
        double sum = 0;
        int count = grades.getSize();
        if (count == 0) {
            return 0.0;
        }

        for (size_t i = 0; i < count; ++i) {
            sum += grades.getAt(i).getGrade();
        }

        return sum / count;
    }

    void sortSubjects() {
        bool swapped;
        size_t n = grades.getSize();

        do {
            swapped = false;
            for (size_t i = 1; i < n; ++i) {
                Subject a = grades.getAt(i - 1);
                Subject b = grades.getAt(i);

                if (b < a) {
                    grades.setAt(i - 1, b);
                    grades.setAt(i, a);
                    swapped = true;
                }
            }
            n--;
        } while (swapped);
    }

    friend std::ostream& operator<<(std::ostream& os, const Student& student) {
        os << "- студент: " << student.name << "\n";
        os << "- средний балл: " << std::fixed << std::setprecision(2) << student.getAvgGrade() << "\n";

        for (size_t i = 0; i < student.grades.getSize(); ++i) {
            os << " --- " << student.grades.getAt(i) << "\n";
        }

        return os;
    }
};

class Group {
private:
    std::string name;
    SingleLinkedList<Student> students;

public:
    Group(std::string n) : name(n) {}

    void addStudent(const Student& s) {
        students.pushBack(s);
    }

    std::string getName() const {
        return name;
    }

    SingleLinkedList<Student>& getStudents() {
        return students;
    }

    void SortByGrades() {
        bool swapped;
        size_t n = students.getSize();

        do {
            swapped = false;
            for (size_t i = 1; i < n; ++i) {
                Student a = students.getAt(i - 1);
                Student b = students.getAt(i);

                if (a.getAvgGrade() < b.getAvgGrade()) {
                    students.setAt(i - 1, b);
                    students.setAt(i, a);
                    swapped = true;
                }
            }
            n--;
        } while (swapped);
    }

    friend std::ostream& operator<<(std::ostream& os, const Group& group) {
        os << "группа: " << group.name << "\nсписок студентов:\n";

        for (size_t i = 0; i < group.students.getSize(); ++i) {
            os << group.students.getAt(i) << "\n";
        }

        return os;
    }
};

class GroupReader {
public:
    static std::vector<Group> readFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file) {
            throw std::runtime_error("Cannot open file: " + filename);
        }

        std::vector<Group> groups;
        std::string line;

        while (std::getline(file, line)) {
            auto parts = split(line, '>');
            if (parts.size() != 6) {
                continue;
            }

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
            if (group.getName() == name) {
                return group;
            }
        }

        groups.emplace_back(name);
        return groups.back();
    }

    static Student& findOrCreateStudent(Group& group, const std::string& name) {
        SingleLinkedList<Student>& students = group.getStudents();

        for (size_t i = 0; i < students.getSize(); ++i) {
            if (students.getAtRef(i).getName() == name) {
                return students.getAtRef(i);
            }
        }

        group.addStudent(Student(name));

        for (size_t i = 0; i < students.getSize(); ++i) {
            if (students.getAtRef(i).getName() == name) {
                return students.getAtRef(i);
            }
        }

        throw std::runtime_error("Failed to create student: " + name);
    }
};

int main() {

    try {
        auto groups = GroupReader::readFromFile("students.txt");

        for (auto& group : groups) {
            for (size_t i = 0; i < group.getStudents().getSize(); ++i) {
                Student& student = group.getStudents().getAtRef(i);
                student.sortSubjects();
            }

            group.SortByGrades();
            std::cout << group << "\n";
        }

    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
