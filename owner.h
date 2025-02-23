#ifndef OWNER_H
#define OWNER_H

#include <vector>
#include <string>
#include "movie.h"
#include "customer.h"
#include "transaction.h"

using namespace std;

class Owner {
private:
    vector<Movie> movies;
    vector<Customer> customers;
    vector<Transaction> transactions;

public:
    Owner() {
        // Initialize with sample movies
        movies = {
            Movie("Alien", "Horror/Sci-Fi"),
            Movie("Shrek", "Comedy/Animation"),
            Movie("Paul", "Comedy"),
            Movie("Army of the Dead", "Horror/Comedy"),
            Movie("The Birdcage", "Comedy"),
            Movie("The Mummy", "Action/Adventure"),
            Movie("Twister", "Action")
        };

        // Initialize with sample customers
        customers = {
            Customer("George Gill", 1),
            Customer("Christopher Taylor", 2),
            Customer("Martha Geldard", 3),
            Customer("Hamilton Boffey", 4),
            Customer("Remy Baker", 5),
            Customer("Mary Forge", 6),
            Customer("Betty Crowley", 7)
        };
    }

    Movie* findMovie(const string& movieTitle) {
        for (auto& movie : movies) {
            if (movie.getTitle() == movieTitle) {
                return &movie;
            }
        }
        return nullptr;
    }

    void addMovie(const Movie& movie) {
        movies.push_back(movie);
    }

    void removeMovie(const string& movieTitle) {
        for (auto it = movies.begin(); it != movies.end(); ++it) {
            if (it->getTitle() == movieTitle) {
                movies.erase(it);
                cout << movieTitle << " has been removed from inventory.\n";
                return;
            }
        }
        cout << "Movie not found in inventory.\n";
    }

    void viewInventory() const {
        cout << "Current Inventory:\n";
        if (movies.empty()) {
            cout << "No movies available in inventory.\n";
            return;
        }
        for (const auto& movie : movies) {
            cout << movie.getTitle() << " - " << movie.getGenre()
                 << " (" << (movie.isAvailable() ? "Available" : "Rented") << ")\n";
        }
    }

    const vector<Movie>& getMovies() const { return movies; }
    const vector<Transaction>& getTransactions() const { return transactions; }

    Customer* findCustomer(int customerID) {
        for (auto& customer : customers) {
            if (customer.getCustomerID() == customerID) {
                return &customer;
            }
        }
        return nullptr;
    }

    void viewCustomers() const {
        cout << "List of Customers:\n";
        for (const auto& customer : customers) {
            cout << customer.getName() << " (ID: " << customer.getCustomerID() << ")\n";
        }
    }

    void rentMovieToCustomer(Customer* customer, const string& movieTitle, const string& rentalDate) {
        Movie* movie = findMovie(movieTitle);
        if (movie && customer) {
            Transaction newTransaction(customer, movie, rentalDate);
            transactions.push_back(newTransaction);
            cout << customer->getName() << " has rented " << movie->getTitle() << ".\n";
        }
    }

    float calculateLateFee(const string& movieTitle, const string& returnDate) {
        for (const auto& transaction : transactions) {
            if (transaction.getMovie()->getTitle() == movieTitle) {
                return transaction.calculateLateFee(returnDate);
            }
        }
        return 0.0f;
    }
};

#endif