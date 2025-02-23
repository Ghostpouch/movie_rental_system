#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <iostream>
#include <vector>
#include "movie.h"

using namespace std;

class Owner;  // Forward declaration

class Customer {
private:
    string name;
    int customerID;
    vector<Movie*> rentedMovies;  // Added rentedMovies list as per class diagram

public:
    Customer(string n, int id) : name(n), customerID(id) {}

    string getName() const { return name; }
    int getCustomerID() const { return customerID; }

    void rentMovie(const string& movieTitle, Owner& owner, const string& rentalDate);
    void returnMovie(const string& movieTitle, Owner& owner, const string& returnDate = "");  // Added returnDate parameter
    void viewRentedMovies(const Owner& owner) const;
    const vector<Movie*>& getRentedMovies() const { return rentedMovies; }
};

#endif