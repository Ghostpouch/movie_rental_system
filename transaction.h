#ifndef TRANSACTION_H // Check if TRANSACTION_H is not already defined
#define TRANSACTION_H // Define TRANSACTION_H to prevent multiple inclusions

#include <string> // String library for handling text
#include <iostream> // Input-output library
#include "customer.h" // Include this file
#include "movie.h" // Include this file

using namespace std; // Don't need to use prefixes

// Define transaction class
class Transaction {
private:
    static int nextTransactionID; // Tracks next available unique transaction ID
    int transactionID; // Unique ID for each transaction
    Customer* customer; // Pointer to customer involved in transaction
    Movie* movie; // Pointer to rented movie in the transaction
    string rentalDate; // Date when movie was rented
    string dueDate; // Date when movie is due to be returned
    static constexpr float LATE_FEE_PER_DAY = 1.00f; // Fee charged per day if returned late

    // Calculate rental due date
    string calculateDueDate(const string& rentDate) const {  
        int day = stoi(rentDate.substr(0, 2)); // Extract day from rental date
        int month = stoi(rentDate.substr(3, 2)); // Extract month
        int year = stoi(rentDate.substr(6, 4)); // Extract year

        day += 7; // Add 7 days to rental date to calculate due date
        if (day > 30) { // If day exceeds 30 move to next month
            day -= 30; // Reset day to start of next month
            month += 1; // Increase month by 1
            if (month > 12) { // If month goes past december, resert to january
                month = 1;
                year += 1;
            }
        }
        // Return new due date as a string, with day and month as two digits
        return (day < 10 ? "0" : "") + to_string(day) + "/" +
               (month < 10 ? "0" : "") + to_string(month) + "/" +
               to_string(year);
    }

public:
    // Constructor initialises a new transaction with customer, movie, rental date
    Transaction(Customer* cust, Movie* mov, const string& rentDate) 
        : customer(cust), movie(mov), rentalDate(rentDate) {
        transactionID = nextTransactionID++; // Assign unique transaction ID
        dueDate = calculateDueDate(rentDate); // Calculate due date from rental date
    }

    // Convert a date (DD/MM/YYYY) into total days for easy comparison
    int convertToTotalDays(const string& date) const {
        int day = stoi(date.substr(0, 2)); // Extract day
        int month = stoi(date.substr(3, 2)); // Extract month
        int year = stoi(date.substr(6, 4)); // Extract year
        
        return day + (month * 30) + (year * 365); // Convert date to total days
    }

    // Calculate late fee by comparing return date and due date
    float calculateLateFee(const string& returnDate) const {
        int dueDays = convertToTotalDays(dueDate); // Convert due date to total days
        int returnDays = convertToTotalDays(returnDate); // Convert return date to total days
        
        int overdueDays = returnDays - dueDays; // Calculate overdue days
        return overdueDays > 0 ? overdueDays * LATE_FEE_PER_DAY : 0.0f; // Return fee if overdue, otherwise 0
    }

    const Movie* getMovie() const { return movie; } // Getter for movie in transaction

    // Display transaction details
    void displayTransaction() const {
        cout << "Transaction ID: " << transactionID << "\n"
             << "Customer: " << customer->getName() << "\n"
             << "Movie: " << movie->getTitle() << "\n"
             << "Rental Date: " << rentalDate << "\n"
             << "Due Date: " << dueDate << "\n";
    }
};

#endif // End of header guard