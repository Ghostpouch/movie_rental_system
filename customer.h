#ifndef CUSTOMER_H // Check if CUSTOMER_H has not been defined already
#define CUSTOMER_H // Define CUSTOMER_H to prevent multiple inclusions

#include <string> // String library for handling text
#include <iostream> // Input-output library
#include <vector> // Vector library for dynamic arrays
#include "movie.h" // Include this file

using namespace std; // Don't need to use prefixes

class Owner;  // Forward declaration

// Define customer class
class Customer {
private:
    string name; // Name of customer
    int customerID; // ID number of customer
    vector<Movie*> rentedMovies;  // List of movies rented by customer (pointers to Movie objects)

public:
    Customer(string n, int id) : name(n), customerID(id) {} // Constructor - Initialises the customer with a name and ID

    // Destructor - Clears the list of rented movies when a Customer object is destroyed
    ~Customer() {
        rentedMovies.clear();
    }

    string getName() const { return name; } // Getter for customer name
    int getCustomerID() const { return customerID; } // Getter for customer ID

    void rentMovie(const string& movieTitle, Owner& owner, const string& rentalDate); // Rent movie method
    void returnMovie(const string& movieTitle, Owner& owner, const string& returnDate = ""); // Return movie method, with optional return date
    void viewRentedMovies(const Owner& owner) const; // View rented movies method
    const vector<Movie*>& getRentedMovies() const { return rentedMovies; } // Getter method for list of rented movies
};

#endif // End header guard