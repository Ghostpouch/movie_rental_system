#ifndef OWNER_H // Check if OWNER_H is not already defined
#define OWNER_H // Define OWNER_H to prevent multiple inclusions

#include <vector> // Vector library for dynamic arrays
#include <string> // String library for handling text
#include "movie.h" // Include this file
#include "customer.h" // Include this file
#include "transaction.h" // Include this file

using namespace std; // Don't need to use prefixes

// Define owner class
class Owner {
private:
    vector<Movie> movies; // List of movies
    vector<Customer> customers; // List of customers
    vector<Transaction> transactions; // List of transactions

public:
    Owner() { // Constructor to initialise movies and customers
        
        movies = { // Initialise movies list with some predefined objects
            Movie("Alien", "Horror/Sci-Fi"),
            Movie("Shrek", "Comedy/Animation"),
            Movie("Paul", "Comedy"),
            Movie("Army of the Dead", "Horror/Comedy"),
            Movie("The Birdcage", "Comedy"),
            Movie("The Mummy", "Action/Adventure"),
            Movie("Twister", "Action")
        };

       
        customers = { // Initialise customer list with some predefined objects
            Customer("George Gill", 1),
            Customer("Christopher Taylor", 2),
            Customer("Martha Geldard", 3),
            Customer("Hamilton Boffey", 4),
            Customer("Remy Baker", 5),
            Customer("Mary Forge", 6),
            Customer("Betty Crowley", 7)
        };
    }

    // Find a movie by its title in the movies list
    Movie* findMovie(const string& movieTitle) {
        for (auto& movie : movies) { // Loop through list
            if (movie.getTitle() == movieTitle) { // If movie title matches
                return &movie; // Return address of the matching movie
            }
        }
        return nullptr; // If no movie is found - prints "Movie not found" from rentMovie function
    }

    // Adds a new movie to the inventory
    void addMovie(const Movie& movie) {
        movies.push_back(movie);
    }

    // Remove a movie from the inventory by title
    void removeMovie(const string& movieTitle) {
        for (auto it = movies.begin(); it != movies.end(); ++it) { // Loop through all movies in inventory
            if (it->getTitle() == movieTitle) { // If movie title matches the one to be removed
                movies.erase(it); // Remove movie from inventory
                cout << movieTitle << " has been removed from inventory.\n"; // Print this to confirm
                return;
            }
        }
        cout << "Movie not found in inventory.\n"; // Print this if movie not found
    }

    // Display current movie inventory
    void viewInventory() const {
        cout << "Current Inventory:\n"; // Print header
        if (movies.empty()) {
            cout << "No movies available in inventory.\n"; // Print this if there are none
            return;
        }
        for (const auto& movie : movies) { // Loop through all movies in inventory and display details
            cout << movie.getTitle() << " - " << movie.getGenre() 
                 << " (" << (movie.isAvailable() ? "Available" : "Rented") << ")\n"; // Print each title, genre and availability
        }
    }

    const vector<Movie>& getMovies() const { return movies; } // Return a reference to the list of movies
    const vector<Transaction>& getTransactions() const { return transactions; } // Return a reference to the list of transactions

    // Find a customer by their ID and return a pointer to the customer
    Customer* findCustomer(int customerID) {
        for (auto& customer : customers) {
            if (customer.getCustomerID() == customerID) {
                return &customer; // Return pointer if customer is found
            }
        }
        return nullptr;
    }

    // Display a list of all customers with their names and IDs
    void viewCustomers() const {
        cout << "List of Customers:\n"; // Print header
        for (const auto& customer : customers) {
            cout << customer.getName() << " (ID: " << customer.getCustomerID() << ")\n"; // Loop through customers list and print each customer name and ID
        }
    }

    // Register a movie rental transaction for a customer
    void rentMovieToCustomer(Customer* customer, const string& movieTitle, const string& rentalDate) {
        Movie* movie = findMovie(movieTitle); // Find movie in inventory
        
        if (movie && customer) { // If both movie and customer exist
            Transaction newTransaction(customer, movie, rentalDate); // Create new transaction
            transactions.push_back(newTransaction); // Add transaction to records
            cout << customer->getName() << " has rented " << movie->getTitle() << ".\n"; // Print confirmation
        }
    }

    // Calculate late fee for a returned movie based on return date
    float calculateLateFee(const string& movieTitle, const string& returnDate) {
        
        // Loop through all transactions to find matching movie rental
        for (const auto& transaction : transactions) {
            if (transaction.getMovie()->getTitle() == movieTitle) {
                return transaction.calculateLateFee(returnDate); // Calculate and return late fee 
            }
        }
        return 0.0f; // Return 0 if there is no late fee
    }
};

#endif // End of header guard