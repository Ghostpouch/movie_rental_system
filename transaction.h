#ifndef TRANSACTION_H // Check if TRANSACTION_H is not already defined
#define TRANSACTION_H // Define TRANSACTION_H to prevent multiple inclusions

#include <string> // String library for handling text
#include <iostream> // Input-output library
#include "customer.h" // Include this file
#include "movie.h" // Include this file

using namespace std; // Don't need to use prefixes

// Define owner class
class Transaction {
private:
    static int nextTransactionID;
    int transactionID;
    Customer* customer;
    Movie* movie;
    string rentalDate;
    string dueDate;
    static constexpr float LATE_FEE_PER_DAY = 1.00f;  

    string calculateDueDate(const string& rentDate) const {  
        int day = stoi(rentDate.substr(0, 2));
        int month = stoi(rentDate.substr(3, 2));
        int year = stoi(rentDate.substr(6, 4));

        day += 7;
        if (day > 30) {
            day -= 30;
            month += 1;
            if (month > 12) {
                month = 1;
                year += 1;
            }
        }

        return (day < 10 ? "0" : "") + to_string(day) + "/" +
               (month < 10 ? "0" : "") + to_string(month) + "/" +
               to_string(year);
    }

public:
    Transaction(Customer* cust, Movie* mov, const string& rentDate) 
        : customer(cust), movie(mov), rentalDate(rentDate) {
        transactionID = nextTransactionID++;
        dueDate = calculateDueDate(rentDate);
    }

    int convertToTotalDays(const string& date) const {
        int day = stoi(date.substr(0, 2));
        int month = stoi(date.substr(3, 2));
        int year = stoi(date.substr(6, 4));
        
        return day + (month * 30) + (year * 365);
    }

    float calculateLateFee(const string& returnDate) const {
        int dueDays = convertToTotalDays(dueDate);
        int returnDays = convertToTotalDays(returnDate);
        
        int overdueDays = returnDays - dueDays;
        return overdueDays > 0 ? overdueDays * LATE_FEE_PER_DAY : 0.0f;
    }

    const Movie* getMovie() const { return movie; }

    void displayTransaction() const {
        cout << "Transaction ID: " << transactionID << "\n"
             << "Customer: " << customer->getName() << "\n"
             << "Movie: " << movie->getTitle() << "\n"
             << "Rental Date: " << rentalDate << "\n"
             << "Due Date: " << dueDate << "\n";
    }
};

#endif