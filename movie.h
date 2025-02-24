#ifndef MOVIE_H  // Check if MOVIE_H is not already defined to avoid multiple inclusions
#define MOVIE_H  // Define MOVIE_H to prevent multiple inclusions

#include <string> // String library for handling text
#include <iostream> // Input-output library

using namespace std; // Don't need to use prefixes

// Define movie class
class Movie {
private:
    string title; // Movie title
    string genre; // Movie genre
    bool available; // Availability status

public:
    Movie(string t, string g) : title(t), genre(g), available(true) {} // Constructor to initialise movie with a title and genre, and set as available

    string getTitle() const { return title; } // Getter for movie title
    string getGenre() const { return genre; } // Getter for movie genre
    bool isAvailable() const { return available; } // Check movie available method
    void rentMovie() { available = false; } // Mark as not available (rented) method
    void returnMovie() { available = true; } // Mark as available (returned) method

    void display() const { // Display movie title and availability
        cout << title << " - " << (available ? "Available" : "Not Available") << endl;
    }
};

#endif // End of header guard