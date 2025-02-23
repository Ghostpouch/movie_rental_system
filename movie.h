#ifndef MOVIE_H
#define MOVIE_H

#include <string>
#include <iostream>

using namespace std;

class Movie {
private:
    string title;
    string genre;
    bool available;

public:
    Movie(string t, string g) : title(t), genre(g), available(true) {}

    string getTitle() const { return title; }
    string getGenre() const { return genre; }
    bool isAvailable() const { return available; }
    void rentMovie() { available = false; }
    void returnMovie() { available = true; }

    void display() const {
        cout << title << " - " << (available ? "Available" : "Not Available") << endl;
    }
};

#endif