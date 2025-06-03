#include "interface.h"
#include <iostream>

int main() {
    setlocale(LC_ALL, "Russian");
    ILibrary library;

    Author author1 = { "Гради Буч", 1955 };
    Publisher publisher1 = { "Питер", "Санкт-Петербург" };
    Genre genre1 = { "Программирование" };
    Book book1 = { "ООП: Граф Буч", author1, publisher1, genre1, 1992, "978-5-4461-0000-1" };

    Author author2 = { "Роберт Мартин", 1952 };
    Publisher publisher2 = { "Питер", "Санкт-Петербург" };
    Genre genre2 = { "Программирование" };
    Book book2 = { "Clean Code", author2, publisher2, genre2, 2008, "978-5-4461-0000-2" };

    library.addBook(book1);
    library.addBook(book2);

    std::cout << "Список книг:\n";
    for (const Book& b : library.listBooks()) {
        std::cout << "Название: " << b.title << ", ISBN: " << b.isbn << "\n";
    }

    Book updatedBook = { "ООП: Граф Бух (обновлённое издание)", author1, publisher1, genre1, 2001, "978-5-4461-0000-1" };
    library.updateBook("978-5-4461-0000-1", updatedBook);

    std::cout << "\nКниги автора " << author1.name << ":\n";
    std::vector<Book> booksByAuthor = library.findBooksByAuthor("Гради Бух");
    for (const Book& b : booksByAuthor) {
        std::cout << "Название: " << b.title << "\n";
    }

    std::cout << "\nОбщее количество книг: " << library.countBooks() << "\n";

    Reader reader1 = { "R001", "Иван Иванов", "ivan@mail.ru" };
    Reader reader2 = { "R002", "Петр Петров", "petr@mail.ru" };
    library.addReader(reader1);
    library.addReader(reader2);

    std::cout << "\nСписок читателей:\n";
    for (const Reader& r : library.listReaders()) {
        std::cout << "ID: " << r.id << ", Имя: " << r.name << "\n";
    }

    library.assignBookToReader("978-5-4461-0000-2", "R001");
    library.assignBookToReader("978-5-4461-0000-2", "R002");

    library.returnBookFromReader("978-5-4461-0000-2", "R001");
    library.returnBookFromReader("978-5-4461-0000-2", "R001");

    return 0;
}
