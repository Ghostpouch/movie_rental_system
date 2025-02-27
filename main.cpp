#include <iostream>  // Input-output library
#include <string>    // String library for handling text
#include <limits>    // Limits library, handle input validation
#include <ctime>     // ctime library for handling date and time functions
#include "owner.h"   // Include this file

using namespace std; // Don't need to use prefixes

// GET CURRENT DATE
string getCurrentDate() {
    time_t now = time(0); // Get current time in seconds since Jan 1, 1970
    tm* ltm = localtime(&now); // Convert that time into local time details (D/M/Y)

    // Get the day, month, and year from local time
    string day = to_string(ltm->tm_mday);         // Day of month
    string month = to_string(ltm->tm_mon + 1);     // Month (add 1 since tm_mon starts at 0)
    string year = to_string(ltm->tm_year + 1900); // Year (tm_year is years since 1900)

    // Make day and month two digits 
    if (day.length() == 1) day = "0" + day;
    if (month.length() == 1) month = "0" + month;

    // Return formatted date as "DD/MM/YYYY"
    return day + "/" + month + "/" + year;
}

// MENU DISPLAY
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

//DISPLAY SEPARATOR FOR AFTER EACH ACTION
void displaySeparator() {
    cout << "\n---------------------------------\n";
}

// GET USER INPUT AND VALIDATE
int getMenuChoice() {
    int choice; // Variable to store users choice

    // Loop to handle invalid input and prompt user to enter a valid number
    while (!(cin >> choice)) { // Input validation
        cin.clear(); // Reset input stream after error
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        cout << "Invalid input. Please enter a number (1-9): "; // Prompt user again
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Remove extra characters from the input

    return choice; // Return the valid input entered by user
}

//MAIN FUNCTION
int main() {

    Owner owner; // Owner object to manage movies, customers, and transactions

    while (true) { // Loop to keep showing the menu until the user chooses exit
        showMenu(); // Display menu options
        int choice = getMenuChoice(); // Get users choice (validated input)
        displaySeparator(); // Print separator for readability

        // OPTIONS
        switch (choice) {
           
            case 1: // VIEW MOVIE INVENTORY
                owner.viewInventory();
                break;


            case 2: // VIEW CUSTOMER LIST
                owner.viewCustomers();
                break;


            case 3: { // RENT MOVIE - Prompts for Customer ID and Movie Title, validates input, and processes rental
                int customerID; // Store customer ID
                string movieTitle; //Store movie title chosen

                cout << "Enter Customer ID: "; // Prompt for customer ID and validate input
                while (!(cin >> customerID)) { // Input validation
                    cin.clear(); // Reset input stream after error
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                    cout << "Invalid ID. Please enter a number: "; // Prompt again
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Remove extra characters from the input

                // Prompt for movie title (allows spaces)
                cout << "Enter Movie Title: ";
                getline(cin, movieTitle); // Read the full movie title including spaces

                // Get the current system date for the rental
                string rentalDate = getCurrentDate();

                // Find the customer by ID using the owner object
                Customer* customer = owner.findCustomer(customerID);
                if (customer) {
                    customer->rentMovie(movieTitle, owner, rentalDate); // If customer exists, rent the movie
                } else {
                    cout << "Customer not found.\n"; // If customer not found, display error message
                }
                break;
            }


            case 4: { // RETURN MOVIE - Prompts for Customer ID, Movie Title, Return Date. Validates input. Processes return.
                int customerID; // Store customer ID
                string movieTitle; //Store movie title chosen

                // Prompt for customer ID and validate input
                cout << "Enter Customer ID: ";
                while (!(cin >> customerID)) { // Ensure input is a valid integer
                    cin.clear(); // Reset input stream after error
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                    cout << "Invalid ID. Please enter a number: "; // Prompt again
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Remove extra characters from the input

                // Prompt for Movie Title (allows spaces)
                cout << "Enter Movie Title: ";
                getline(cin, movieTitle); // Read the full movie title including spaces

                // Prompt for Return Date or use the current date (Can enter future date to test for late fees)
                string returnDate;
                cout << "Enter Return Date (DD/MM/YYYY) or press Enter for today's date: ";
                getline(cin, returnDate); // Read return date
                if (returnDate.empty()) { // If no return date provided, use current date
                    returnDate = getCurrentDate(); 
                }

                // Find customer by ID using the owner object
                Customer* customer = owner.findCustomer(customerID);
                if (customer) {
                    customer->returnMovie(movieTitle, owner, returnDate); // If customer exists, return movie
                } else {
                    cout << "Customer not found.\n"; // If customer not found, display error message
                }
                break;
            }


            case 5: { // VIEW RENTED MOVIES - Prompts for Customer ID, validates input, displays list of rented movies.
                int customerID; // Store customer ID

                cout << "Enter Customer ID: "; // Prompt for Customer ID
                while (!(cin >> customerID)) { // Input validation
                    cin.clear(); // Reset input stream after error
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                    cout << "Invalid ID. Please enter a number: "; // Prompt again
                }

                // Find customer by ID using Owner object
                Customer* customer = owner.findCustomer(customerID);
                if (customer) {
                    customer->viewRentedMovies(owner); // If customer exists, call viewRentedMovies to display rented movies
                } else {
                    cout << "Customer not found.\n"; // If customer not found, display error message
                }
                break;
            }


            case 6: { // ADD NEW MOVIE - Prompts for Movie Title and Genre, then adds the new movie to inventory.
                string movieTitle, genre; // Store movie title and genre
                
                // Prompt for movie title and read input
                cout << "Enter Movie Title: ";
                getline(cin, movieTitle); 

                // Prompt for movie genre and read input
                cout << "Enter Movie Genre: ";
                getline(cin, genre);

                // Create new movie object with the title and genre
                Movie newMovie(movieTitle, genre);

                // Add new movie to the owners inventory
                owner.addMovie(newMovie);

                // Confirm movie was added
                cout << "Movie added to inventory: " << movieTitle << endl;
                break;
            }


            case 7: { // REMOVE MOVIE - Prompts for Movie Title and removes the movie from the inventory.
                string movieTitle; // Store movie title
                
                // Prompt for movie title to be removed and read input
                cout << "Enter Movie Title to Remove: ";
                getline(cin, movieTitle);

                // Call removeMovie method to remove movie from inventory
                owner.removeMovie(movieTitle);
                break; // removeMovie will print confirmation
            }


            case 8: { // Only the owner can see transactions
                owner.viewTransactions();
                break;
            }

            case 9:// EXIT PROGRAM - Display goodbye message and exits program. 
                cout << "\nThank you for using the Movie Rental System. Goodbye!\n"; // Print message
                return 0; // Exit the program

            default: // Handle invalid menu choices
                cout << "Invalid choice. Please enter a number between 1 and 9.\n";
                break;
        }
        displaySeparator(); // Print separator after each menu option is processed
    }

    return 0; // Confirm exit
}


