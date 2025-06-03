#include "interface.h"
#include <iostream>
#include <algorithm>

void ILibrary::addBook(const Book& book) {
    books.push_back(book);
}

void ILibrary::removeBook(const std::string& isbn) {
    auto it = std::remove_if(books.begin(), books.end(), [&](const Book& b) {
        return b.isbn == isbn;
    });
    if (it != books.end()) {
        books.erase(it, books.end());
        std::cout << "Книга удалена.\n";
    }
    else {
        std::cout << "Книга не найдена.\n";
    }
}

Book* ILibrary::findBookByISBN(const std::string& isbn) {
    for (auto& b : books) {
        if (b.isbn == isbn)
            return &b;
    }
    return nullptr;
}

std::vector<Book> ILibrary::listBooks() const {
    return books;
}

void ILibrary::updateBook(const std::string& isbn, const Book& newBook) {
    for (auto& b : books) {
        if (b.isbn == isbn) {
            b = newBook;
            std::cout << "Информация о книге обновлена.\n";
            return;
        }
    }
    std::cout << "Книга не найдена для обновления.\n";
}

std::vector<Book> ILibrary::findBooksByAuthor(const std::string& authorName) const {
    std::vector<Book> result;
    for (const auto& b : books) {
        if (b.author.name == authorName) {
            result.push_back(b);
        }
    }
    return result;
}

int ILibrary::countBooks() const {
    return books.size();
}

void ILibrary::addReader(const Reader& reader) {
    readers.push_back(reader);
}

std::vector<Reader> ILibrary::listReaders() const {
    return readers;
}

bool ILibrary::assignBookToReader(const std::string& isbn, const std::string& readerId) {
    if (!findBookByISBN(isbn)) {
        std::cout << "Книга не найдена.\n";
        return false;
    }

    auto readerIt = std::find_if(readers.begin(), readers.end(), [&](const Reader& r) {
        return r.id == readerId;
    });
    if (readerIt == readers.end()) {
        std::cout << "Читатель не найден.\n";
        return false;
    }

    auto borrowedIt = std::find_if(borrowed.begin(), borrowed.end(), [&](const std::pair<std::string, std::string>& p) {
        return p.first == isbn;
    });
    if (borrowedIt != borrowed.end()) {
        std::cout << "Книга уже выдана.\n";
        return false;
    }

    borrowed.push_back({ isbn, readerId });
    std::cout << "Книга выдана читателю " << readerId << ".\n";
    return true;
}

bool ILibrary::returnBookFromReader(const std::string& isbn, const std::string& readerId) {
    auto it = std::find_if(borrowed.begin(), borrowed.end(), [&](const std::pair<std::string, std::string>& p) {
        return p.first == isbn && p.second == readerId;
    });
    if (it != borrowed.end()) {
        borrowed.erase(it);
        std::cout << "Книга возвращена.\n";
        return true;
    }
    std::cout << "Запись о выдаче книги не найдена.\n";
    return false;
}
