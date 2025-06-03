#include "audio_collection.h"
#include <iostream>
#include <string>

int main() {

    AudioCollection myCollection;
    std::string genre, artist, album, track, choice = "0";
    int year, h, m, s;

    std::cout << "Добро пожаловать в домашнюю аудио-коллекцию. Что вы хотите сделать?" << std::endl;

    while (choice != "3") {
        std::cout << "\n1 - Добавить трек.\n2 - Просмотреть аудио-коллекцию.\n3 - Закончить сеанс." << std::endl;
        std::getline(std::cin, choice);

        if (choice == "1") {
            std::cout << "Введите жанр: ";
            std::getline(std::cin, genre);
            myCollection.addGenre(genre);

            std::cout << "Введите имя исполнителя: ";
            std::getline(std::cin, artist);
            myCollection.addArtist(genre, artist);

            std::cout << "Введите название альбома: ";
            std::getline(std::cin, album);
            std::cout << "Введите год выпуска альбома: ";
            std::cin >> year;
            std::cin.ignore();

            myCollection.addAlbum(genre, artist, album, year);

            std::cout << "Сколько треков в альбоме? ";
            int trackCount;
            std::cin >> trackCount;
            std::cin.ignore();

            for (int i = 0; i < trackCount; ++i) {
                std::cout << "Введите название трека: ";
                std::getline(std::cin, track);
                std::cout << "Введите продолжительность трека (часы минуты секунды): ";
                std::cin >> h >> m >> s;
                std::cin.ignore();
                myCollection.addTrack(genre, artist, album, track, h, m, s);
            }
        }
        else if (choice == "2") {
            std::cout << "\nМоя аудио-коллекция:\n";
            myCollection.displayCollection();
        }
        else if (choice == "3") {
            std::cout << "Приятного времени суток!" << std::endl;
        }
        else {
            std::cout << "Пожалуйста, выберите номер команды из представленных." << std::endl;
        }
    }

    return 0;
}