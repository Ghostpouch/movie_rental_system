#include "customer.h"
#include "owner.h"

using namespace std;

void Customer::rentMovie(const string& movieTitle, Owner& owner, const string& rentalDate) {
    Movie* movie = owner.findMovie(movieTitle);
    if (movie && movie->isAvailable()) {
        movie->rentMovie();
        rentedMovies.push_back(movie);  // Add to customer's rented movies list
        owner.rentMovieToCustomer(this, movieTitle, rentalDate);
    } else if (movie) {
        cout << "Sorry, " << movieTitle << " is not available for rent.\n";
    } else {
        cout << "Movie not found.\n";
    }
}

void Customer::returnMovie(const string& movieTitle, Owner& owner, const string& returnDate) {
    Movie* movie = owner.findMovie(movieTitle);
    if (movie && !movie->isAvailable()) {
        // Find and remove the movie from rentedMovies list
        for (auto it = rentedMovies.begin(); it != rentedMovies.end(); ++it) {
            if ((*it)->getTitle() == movieTitle) {
                rentedMovies.erase(it);
                movie->returnMovie();  // Make sure the movie is marked as available

                // Calculate and display late fee if return date is provided
                if (!returnDate.empty()) {
                    float lateFee = owner.calculateLateFee(movieTitle, returnDate);
                    cout << name << " has returned " << movie->getTitle() << ".\n";
                    if (lateFee > 0) {
                        cout << "Late Fee: £" << lateFee << endl;  // Changed $ to £
                    }
                } else {
                    cout << name << " has returned " << movie->getTitle() << ".\n";
                }
                return;
            }
        }
    }
    cout << "You haven't rented " << movieTitle << " or it's already returned.\n";
}

void Customer::viewRentedMovies(const Owner& owner) const {
    cout << name << "'s rented movies:\n";
    if (rentedMovies.empty()) {
        cout << "No rented movies.\n";
        return;
    }
    for (const auto& movie : rentedMovies) {
        cout << "- " << movie->getTitle() << endl;
    }
}