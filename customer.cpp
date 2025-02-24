#include "customer.h" // Include this file
#include "owner.h" // Include this file

using namespace std; // Don't need to use prefixes

// Rent a movie for the customer if available, otherwise display appropriate message
void Customer::rentMovie(const string& movieTitle, Owner& owner, const string& rentalDate) {
    Movie* movie = owner.findMovie(movieTitle); // Find movie by title in the owners inventory
    
    if (movie && movie->isAvailable()) { // Check if the movie is found and available
        movie->rentMovie(); // Mark movie as rented
        rentedMovies.push_back(movie);  // Add to customer's rented movies list
        owner.rentMovieToCustomer(this, movieTitle, rentalDate); // Register the rental in the owners records
    } 
    else if (movie) { // If movie is found but not available
        cout << "Sorry, " << movieTitle << " is not available for rent.\n";
    } 
    else { // If the movie not found
        cout << "Movie not found.\n";
    }
}

// Return a rented movie, mark it as available and calculate any late fees if needed
void Customer::returnMovie(const string& movieTitle, Owner& owner, const string& returnDate) {
    Movie* movie = owner.findMovie(movieTitle); // Find movie by title in the owners inventory
    
    if (movie && !movie->isAvailable()) { // Check if movie is found and is not available
        // Find and remove the movie from rentedMovies list
        for (auto it = rentedMovies.begin(); it != rentedMovies.end(); ++it) {
            if ((*it)->getTitle() == movieTitle) { // Search through customers rented movies to find matching one
                rentedMovies.erase(it); // Remove movie from the rented list
                movie->returnMovie();  // Mark movie as available again

                // If return date is provided, calculate and display late fee
                if (!returnDate.empty()) {
                    float lateFee = owner.calculateLateFee(movieTitle, returnDate);
                    cout << name << " has returned " << movie->getTitle() << ".\n"; // Print customer has returned movie
                    if (lateFee > 0) { // If late fee is greater than 0
                        cout << "Late Fee: £" << lateFee << endl; // Print late fee
                    }
                } else {
                    cout << name << " has returned " << movie->getTitle() << ".\n"; // Print customer has returned movie (No late fee)
                }
                return;
            }
        }
    }
    cout << "You haven't rented " << movieTitle << " or it's already returned.\n"; // Print if neither of the others happened
}

// Display the list of movies rented by customer
void Customer::viewRentedMovies(const Owner& owner) const {
    cout << name << "'s rented movies:\n"; // Print customers name and rented movies heading
    if (rentedMovies.empty()) { // Check if customer has rented any movies
        cout << "No rented movies.\n"; // If none rented, print this
        return;
    }
    for (const auto& movie : rentedMovies) { // Loop through each rented movie and display its title
        cout << "- " << movie->getTitle() << endl; // Print title of each rented movie
    }
}