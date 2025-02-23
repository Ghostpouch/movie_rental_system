#include <iostream>
#include <string>
#include <limits>
#include "owner.h"

using namespace std;

void showMenu() {
    cout << "\n=================================\n";
    cout << "     Movie Rental System Menu     \n";
    cout << "=================================\n";
    cout << "1. View Movie Inventory\n";
    cout << "2. View Customer List\n";
    cout << "3. Rent a Movie\n";
    cout << "4. Return a Movie\n";
    cout << "5. View Rented Movies\n";
    cout << "6. Add a New Movie\n";
    cout << "7. Remove a Movie\n";
    cout << "8. View All Transactions\n";
    cout << "9. Exit\n";
    cout << "=================================\n";
    cout << "Choose an option (1-9): ";
}

void displaySeparator() {
    cout << "\n---------------------------------\n";
}


int getMenuChoice() {
    int choice;
    while (!(cin >> choice)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a number (1-9): ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return choice;
}

int main() {
    Owner owner;

    while (true) {
        showMenu();
        int choice = getMenuChoice();
        displaySeparator();

        switch (choice) {
            case 1:
                owner.viewInventory();
                break;

            case 2:
                owner.viewCustomers();
                break;

            case 3: {
                int customerID;
                string movieTitle;

                cout << "Enter Customer ID: ";
                while (!(cin >> customerID)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid ID. Please enter a number: ";
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "Enter Movie Title: ";
                getline(cin, movieTitle);

                // Automatically use today's date
                string rentalDate = "23/02/2025";  // Today's date in DD/MM/YYYY format

                Customer* customer = owner.findCustomer(customerID);
                if (customer) {
                    customer->rentMovie(movieTitle, owner, rentalDate);
                } else {
                    cout << "Customer not found.\n";
                }
                break;
            }

            case 4: {
                int customerID;
                string movieTitle;

                cout << "Enter Customer ID: ";
                while (!(cin >> customerID)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid ID. Please enter a number: ";
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "Enter Movie Title: ";
                getline(cin, movieTitle);

                string returnDate;
                cout << "Enter Return Date (DD/MM/YYYY) or press Enter for today's date: ";
                getline(cin, returnDate);
                if (returnDate.empty()) {
                    returnDate = "23/02/2025";  // Today's date
                }

                Customer* customer = owner.findCustomer(customerID);
                if (customer) {
                    customer->returnMovie(movieTitle, owner, returnDate);
                } else {
                    cout << "Customer not found.\n";
                }
                break;
            }

            case 5: {
                int customerID;
                cout << "Enter Customer ID: ";
                while (!(cin >> customerID)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid ID. Please enter a number: ";
                }

                Customer* customer = owner.findCustomer(customerID);
                if (customer) {
                    customer->viewRentedMovies(owner);
                } else {
                    cout << "Customer not found.\n";
                }
                break;
            }

            case 6: {
                string movieTitle, genre;
                cout << "Enter Movie Title: ";
                getline(cin, movieTitle);
                cout << "Enter Movie Genre: ";
                getline(cin, genre);

                Movie newMovie(movieTitle, genre);
                owner.addMovie(newMovie);
                cout << "Movie added to inventory: " << movieTitle << endl;
                break;
            }

            case 7: {
                string movieTitle;
                cout << "Enter Movie Title to Remove: ";
                getline(cin, movieTitle);
                owner.removeMovie(movieTitle);
                break;
            }

            case 8: {
                cout << "\n--- All Transactions ---\n";
                for (const auto& transaction : owner.getTransactions()) {
                    transaction.displayTransaction();
                    cout << endl;
                }
                break;
            }

            case 9:
                cout << "\nThank you for using the Movie Rental System. Goodbye!\n";
                return 0;

            default:
                cout << "Invalid choice. Please enter a number between 1 and 9.\n";
                break;
        }
        displaySeparator();
    }

    return 0;
}