#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <iostream>
#include "customer.h"
#include "movie.h"

using namespace std;

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

    float calculateLateFee(const string& returnDate) const {  
        int returnDay = stoi(returnDate.substr(0, 2));
        int returnMonth = stoi(returnDate.substr(3, 2));
        int returnYear = stoi(returnDate.substr(6, 4));

        int dueDay = stoi(dueDate.substr(0, 2));
        int dueMonth = stoi(dueDate.substr(3, 2));
        int dueYear = stoi(dueDate.substr(6, 4));

        if (returnYear > dueYear || 
            (returnYear == dueYear && returnMonth > dueMonth) || 
            (returnYear == dueYear && returnMonth == dueMonth && returnDay > dueDay)) {
            int overdueDays = (returnDay - dueDay) + (returnMonth - dueMonth) * 30 + (returnYear - dueYear) * 365;
            return overdueDays > 0 ? overdueDays * LATE_FEE_PER_DAY : 0.0f;
        }
        return 0.0f;
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