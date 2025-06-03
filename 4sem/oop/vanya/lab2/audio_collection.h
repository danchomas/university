#ifndef AUDIO_COLLECTION_H
#define AUDIO_COLLECTION_H

#include <iostream>
#include <vector>
#include <string>

class Time {
private:
    int h;
    int m;
    int s;

public:
    Time(int h = 0, int m = 0, int s = 0);
    void display() const;
};

class Track {
private:
    std::string title;
    std::vector<Time> durations;

public:
    Track(const std::string& title);
    void addDuration(int h, int m, int s);
    void display() const;
    const std::string& getTitle() const;
};

class Album {
private:
    std::string name;
    int year;
    std::vector<Track> tracks;

public:
    Album(const std::string& name, int year);
    void addTrack(const std::string& title, int h, int m, int s);
    void display() const;
    const std::string& getName() const;
};

class Artist {
private:
    std::string name;
    std::vector<Album> albums;

public:
    Artist(const std::string& name);
    void addAlbum(const std::string& albumName, int year);
    void displayAlbums() const;
    const std::string& getName() const;
    Album* findAlbum(const std::string& albumName);
};

class Genre {
private:
    std::string name;
    std::vector<Artist> artists;

public:
    Genre(const std::string& name);
    void addArtist(const std::string& artistName);
    void addAlbumToArtist(const std::string& artistName, const std::string& albumName, int year);
    void addTrackToAlbum(const std::string& artistName, const std::string& albumName, const std::string& trackTitle, int h, int m, int s);
    void display() const;
    const std::string& getName() const;
    Artist* findArtist(const std::string& artistName);
};

class AudioCollection {
private:
    std::vector<Genre> genres;

public:
    void addGenre(const std::string& genreName);
    void addArtist(const std::string& genreName, const std::string& artistName);
    void addAlbum(const std::string& genreName, const std::string& artistName, const std::string& albumName, int year);
    void addTrack(const std::string& genreName, const std::string& artistName, const std::string& albumName, const std::string& trackTitle, int h, int m, int s);
    void displayCollection() const;
};

#endif