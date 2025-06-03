#ifndef LIBRARY_INTERFACE_H
#define LIBRARY_INTERFACE_H
#include <string>
#include <vector>
#include <utility>

struct Author {
    std::string name;
    int birthYear;
};

struct Publisher {
    std::string name;
    std::string address;
};

struct Genre {
    std::string name;
};

struct Book {
    std::string title;
    Author author;
    Publisher publisher;
    Genre genre;
    int publicationYear;
    std::string isbn;
};

struct Reader {
    std::string id;
    std::string name;
    std::string email;
};

class ILibrary {
public:
    void addBook(const Book& book);
    void removeBook(const std::string& isbn);
    Book* findBookByISBN(const std::string& isbn);
    std::vector<Book> listBooks() const;
    void updateBook(const std::string& isbn, const Book& newBook);
    std::vector<Book> findBooksByAuthor(const std::string& authorName) const;
    int countBooks() const;

    void addReader(const Reader& reader);
    std::vector<Reader> listReaders() const;

    bool assignBookToReader(const std::string& isbn, const std::string& readerId);
    bool returnBookFromReader(const std::string& isbn, const std::string& readerId);

private:
    std::vector<Book> books;
    std::vector<Reader> readers;
    std::vector<std::pair<std::string, std::string>> borrowed;
};

#endif // LIBRARY_INTERFACE_H
