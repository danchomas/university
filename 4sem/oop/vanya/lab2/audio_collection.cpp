#include "audio_collection.h"
#include <iomanip>

// === Реализация Time ===
Time::Time(int h, int m, int s) : h(h), m(m), s(s) {}

void Time::display() const {
    std::cout << h << ":" 
              << std::setw(2) << std::setfill('0') << m << ":" 
              << std::setw(2) << std::setfill('0') << s;
}

// === Реализация Track ===
Track::Track(const std::string& title) : title(title) {}

void Track::addDuration(int h, int m, int s) {
    durations.push_back(Time(h, m, s));
}

void Track::display() const {
    std::cout << "     Трек: " << title << " — ";
    for (const auto& t : durations) {
        t.display();
    }
    std::cout << std::endl;
}

const std::string& Track::getTitle() const {
    return title;
}

// === Реализация Album ===
Album::Album(const std::string& name, int year) : name(name), year(year) {}

void Album::addTrack(const std::string& title, int h, int m, int s) {
    for (const auto& track : tracks) {
        if (track.getTitle() == title) {
            std::cerr << "Трек \"" << title << "\" уже существует в альбоме \"" << name << "\"!" << std::endl;
            return;
        }
    }
    tracks.emplace_back(title);
    tracks.back().addDuration(h, m, s);
}

void Album::display() const {
    std::cout << "   Альбом: " << name << " (" << year << ")" << std::endl;
    for (const auto& track : tracks) {
        track.display();
    }
}

const std::string& Album::getName() const {
    return name;
}

Album* Artist::findAlbum(const std::string& albumName) {
    for (auto& album : albums) {
        if (album.getName() == albumName)
            return &album;
    }
    return nullptr;
}

// === Реализация Artist ===
Artist::Artist(const std::string& name) : name(name) {}

void Artist::addAlbum(const std::string& albumName, int year) {
    for (const auto& album : albums) {
        if (album.getName() == albumName) {
            std::cerr << "Альбом \"" << albumName << "\" уже существует у исполнителя \"" << name << "\"!" << std::endl;
            return;
        }
    }
    albums.emplace_back(albumName, year);
}

void Artist::displayAlbums() const {
    std::cout << "Исполнитель: " << name << std::endl;
    for (const auto& album : albums) {
        album.display();
    }
}

const std::string& Artist::getName() const {
    return name;
}

// === Реализация Genre ===
Genre::Genre(const std::string& name) : name(name) {}

void Genre::addArtist(const std::string& artistName) {
    for (const auto& artist : artists) {
        if (artist.getName() == artistName) {
            std::cerr << "Исполнитель \"" << artistName << "\" уже существует в жанре \"" << name << "\"!" << std::endl;
            return;
        }
    }
    artists.emplace_back(artistName);
}

void Genre::addAlbumToArtist(const std::string& artistName, const std::string& albumName, int year) {
    Artist* artist = findArtist(artistName);
    if (artist)
        artist->addAlbum(albumName, year);
    else
        std::cerr << "Исполнитель \"" << artistName << "\" не найден в жанре \"" << name << "\"!" << std::endl;
}

void Genre::addTrackToAlbum(const std::string& artistName, const std::string& albumName, const std::string& trackTitle, int h, int m, int s) {
    Artist* artist = findArtist(artistName);
    if (!artist) {
        std::cerr << "Исполнитель \"" << artistName << "\" не найден в жанре \"" << name << "\"!" << std::endl;
        return;
    }

    Album* album = artist->findAlbum(albumName);
    if (!album) {
        std::cerr << "Альбом \"" << albumName << "\" не найден у исполнителя \"" << artistName << "\"!" << std::endl;
        return;
    }

    album->addTrack(trackTitle, h, m, s);
}

void Genre::display() const {
    std::cout << "Жанр: " << name << std::endl;
    for (const auto& artist : artists) {
        artist.displayAlbums();
    }
    std::cout << std::endl;
}

const std::string& Genre::getName() const {
    return name;
}

Artist* Genre::findArtist(const std::string& artistName) {
    for (auto& artist : artists) {
        if (artist.getName() == artistName)
            return &artist;
    }
    return nullptr;
}

// === Реализация AudioCollection ===
void AudioCollection::addGenre(const std::string& genreName) {
    for (auto& genre : genres) {
        if (genre.getName() == genreName) {
            std::cerr << "Жанр \"" << genreName << "\" уже существует!" << std::endl;
            return;
        }
    }
    genres.emplace_back(genreName);
}

void AudioCollection::addArtist(const std::string& genreName, const std::string& artistName) {
    for (auto& genre : genres) {
        if (genre.getName() == genreName) {
            genre.addArtist(artistName);
            return;
        }
    }
    std::cerr << "Жанр \"" << genreName << "\" не найден!" << std::endl;
}

void AudioCollection::addAlbum(const std::string& genreName, const std::string& artistName, const std::string& albumName, int year) {
    for (auto& genre : genres) {
        if (genre.getName() == genreName) {
            genre.addAlbumToArtist(artistName, albumName, year);
            return;
        }
    }
    std::cerr << "Жанр \"" << genreName << "\" не найден!" << std::endl;
}

void AudioCollection::addTrack(const std::string& genreName, const std::string& artistName, const std::string& albumName, const std::string& trackTitle, int h, int m, int s) {
    for (auto& genre : genres) {
        if (genre.getName() == genreName) {
            genre.addTrackToAlbum(artistName, albumName, trackTitle, h, m, s);
            return;
        }
    }
    std::cerr << "Жанр \"" << genreName << "\" не найден!" << std::endl;
}

void AudioCollection::displayCollection() const {
    if (genres.empty()) {
        std::cout << "Аудио-коллекция пуста!" << std::endl;
        return;
    }

    for (const auto& genre : genres) {
        genre.display();
    }
}