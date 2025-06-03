#pragma once
#include <iostream>
#include <stdexcept>

class EmptyListException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Список пуст";
    }
};

class ListOverflowException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Список заполнен";
    }
};

class IndexOutOfBoundsException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Индекс выходит за пределы списка";
    }
};

template <typename T>
struct Node {
    T data;
    Node* next;
    explicit Node(T value) : data(value), next(nullptr) {}
};

template <typename T>
class SingleLinkedList {
private:
    Node<T>* head;
    size_t size;
    size_t capacity;

public:
    SingleLinkedList(size_t maxCapacity = 100)
        : head(nullptr), size(0), capacity(maxCapacity) {
    }

    ~SingleLinkedList() {
        while (!isEmpty()) {
            popFront();
        }
    }

    void pushFront(T value) {
        if (size >= capacity) {
            throw ListOverflowException();
        }
        Node<T>* newNode = new Node<T>(value);
        newNode->next = head;
        head = newNode;
        size++;
    }

    void popFront() {
        if (isEmpty()) {
            throw EmptyListException();
        }
        Node<T>* temp = head;
        head = head->next;
        delete temp;
        size--;
    }

    T front() const {
        if (isEmpty()) {
            throw EmptyListException();
        }
        return head->data;
    }

    bool isEmpty() const {
        if (head == nullptr) {
            return true;
        }
        else {
            return false;
        }
    }

    void print() const {
        if (isEmpty()) {
            std::cout << "Список пуст" << std::endl;
            return;
        }

        Node<T>* current = head;
        while (current) {
            std::cout << current->data << " -> ";
            current = current->next;
        }

        std::cout << "nullptr" << std::endl;
    }

    size_t getSize() const {
        return size;
    }

    T getAt(size_t index) const {
        if (index >= size) {
            throw IndexOutOfBoundsException();
        }

        Node<T>* current = head;
        for (size_t i = 0; i < index; ++i) {
            current = current->next;
        }

        return current->data;
    }

    void removeAt(size_t index) {
        if (index >= size) {
            throw IndexOutOfBoundsException();
        }

        if (index == 0) {
            popFront();
            return;
        }

        Node<T>* current = head;
        for (size_t i = 0; i < index - 1; ++i) {
            current = current->next;
        }

        Node<T>* temp = current->next;
        current->next = temp->next;
        delete temp;
        size--;
    }

    void insertAt(size_t index, T value) {
        if (index > size) {
            throw IndexOutOfBoundsException();
        }

        if (index == 0) {
            pushFront(value);
            return;
        }

        Node<T>* current = head;
        for (size_t i = 0; i < index - 1; ++i) {
            current = current->next;
        }

        Node<T>* newNode = new Node<T>(value);
        newNode->next = current->next;
        current->next = newNode;
        size++;
    }

    void pushBack(T value) {
        if (size >= capacity) {
            throw ListOverflowException();
        }

        Node<T>* newNode = new Node<T>(value);

        if (!head) {
            head = newNode;
        }
        else {
            Node<T>* current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = newNode;
        }

        size++;
    }

    void setAt(size_t index, T value) {
        if (index >= size) {
            throw IndexOutOfBoundsException();
        }

        Node<T>* current = head;
        for (size_t i = 0; i < index; ++i) {
            current = current->next;
        }

        current->data = value;
    }

    T& getAtRef(size_t index) {
        if (index >= size) {
            throw IndexOutOfBoundsException();
        }

        Node<T>* current = head;
        for (size_t i = 0; i < index; ++i) {
            current = current->next;
        }

        return current->data;
    }

    SingleLinkedList(const SingleLinkedList& other)
        : head(nullptr), size(0), capacity(other.capacity) {

        Node<T>* current = other.head;
        Node<T>* tail = nullptr;

        while (current) {
            Node<T>* newNode = new Node<T>(current->data);
            if (!head) {
                head = newNode;
                tail = newNode;
            }
            else {
                tail->next = newNode;
                tail = newNode;
            }
            ++size;
            current = current->next;
        }
    }

    SingleLinkedList& operator=(const SingleLinkedList& other) {
        if (this == &other) {
            return *this;
        }

        while (head) {
            popFront();
        }

        capacity = other.capacity;
        Node<T>* current = other.head;
        Node<T>* tail = nullptr;

        while (current) {
            Node<T>* newNode = new Node<T>(current->data);
            if (!head) {
                head = newNode;
                tail = newNode;
            }
            else {
                tail->next = newNode;
                tail = newNode;
            }
            ++size;
            current = current->next;
        }

        return *this;
    }
};