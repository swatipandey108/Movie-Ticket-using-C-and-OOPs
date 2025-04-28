#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

// Class to manage seat map for a single show
class SeatMap {
private:
    vector<vector<int>> seats; // 2D vector: 1 = available, 0 = booked

public:
    SeatMap(int rows = 5, int cols = 10) {
        seats = vector<vector<int>>(rows, vector<int>(cols, 1)); // Initialize all seats to available
    }

    // Display seat layout
    void display() {
        cout << "\n    ";
        for (int i = 0; i < seats[0].size(); i++)
            cout << setw(2) << i + 1;
        cout << endl;

        for (int i = 0; i < seats.size(); i++) {
            cout << "R" << i + 1 << " ";
            for (int j = 0; j < seats[i].size(); j++) {
                cout << (seats[i][j] == 1 ? "- " : "X ");
            }
            cout << endl;
        }
    }

    // Book a seat if available
    bool reserveSeat(int row, int col) {
        if (row < 1 || row > seats.size() || col < 1 || col > seats[0].size()) {
            cout << "Invalid seat selection!" << endl;
            return false;
        }
        if (seats[row - 1][col - 1] == 0) {
            cout << "Seat already booked!" << endl;
            return false;
        }
        seats[row - 1][col - 1] = 0;
        return true;
    }

    // Check how many seats are still available
    int availableSeats() {
        int count = 0;
        for (auto &row : seats) {
            for (auto seat : row) {
                if (seat == 1) count++;
            }
        }
        return count;
    }
};

// Class to manage a show (specific time)
class Show {
public:
    string time;
    SeatMap seatMap;

    Show(string t) : time(t), seatMap(5, 10) {}
};

// Class to manage a movie with multiple shows
class Movie {
public:
    string title;
    vector<Show> shows;

    Movie(string name, vector<string> times) : title(name) {
        for (string t : times) {
            shows.push_back(Show(t));
        }
    }

    // Display available shows
    void displayShows() {
        cout << "\nAvailable Shows for \"" << title << "\":" << endl;
        for (int i = 0; i < shows.size(); i++) {
            cout << i + 1 << ". " << shows[i].time 
                 << " | Available Seats: " << shows[i].seatMap.availableSeats() << endl;
        }
    }
};

// Ticket booking system
class TicketSystem {
private:
    vector<Movie> movies;

public:
    TicketSystem() {
        // Initializing some movies and show timings
        movies.push_back(Movie("Avengers: Endgame", {"10:00 AM", "1:00 PM", "6:00 PM"}));
        movies.push_back(Movie("Inception", {"11:00 AM", "3:00 PM", "9:00 PM"}));
        movies.push_back(Movie("The Dark Knight", {"12:00 PM", "4:00 PM", "8:00 PM"}));
    }

    void run() {
        int movieChoice, showChoice;
        bool exit = false;

        while (!exit) {
            cout << "\nWelcome to the Movie Ticket Booking System" << endl;
            cout << "---------------------------------------------" << endl;
            
            // Show available movies
            for (int i = 0; i < movies.size(); i++) {
                cout << i + 1 << ". " << movies[i].title << endl;
            }
            cout << movies.size() + 1 << ". Exit" << endl;
            cout << "Select a movie (number): ";
            cin >> movieChoice;

            // Handle exit
            if (movieChoice == movies.size() + 1) {
                exit = true;
                cout << "\nThank you for visiting! Have a great day!\n" << endl;
                break;
            }

            // Invalid movie selection
            if (movieChoice < 1 || movieChoice > movies.size()) {
                cout << "Invalid movie selection! Try again.\n" << endl;
                continue;
            }

            // Valid movie selected
            Movie &selectedMovie = movies[movieChoice - 1];
            selectedMovie.displayShows();

            cout << "Select a showtime (number): ";
            cin >> showChoice;

            // Invalid showtime
            if (showChoice < 1 || showChoice > selectedMovie.shows.size()) {
                cout << "Invalid showtime selection! Try again.\n" << endl;
                continue;
            }

            // Valid show selected
            Show &selectedShow = selectedMovie.shows[showChoice - 1];
            selectedShow.seatMap.display();

            // Booking multiple seats
            int seatsToBook;
            cout << "\nHow many seats would you like to book? ";
            cin >> seatsToBook;

            for (int i = 0; i < seatsToBook; i++) {
                int row, col;
                cout << "\nBooking Seat " << i + 1 << " of " << seatsToBook << ":" << endl;
                cout << "Enter Row (1-5): ";
                cin >> row;
                cout << "Enter Seat Number (1-10): ";
                cin >> col;

                // Try booking seat
                if (selectedShow.seatMap.reserveSeat(row, col)) {
                    cout << "Seat booked successfully at Row " << row << ", Seat " << col << "!" << endl;
                } else {
                    cout << "Failed to book this seat. Try another one." << endl;
                    i--; // Retry this seat
                }
            }

            // Show updated seat map
            cout << "\nUpdated Seat Map:" << endl;
            selectedShow.seatMap.display();

            // Booking summary
            cout << "\nBooking Confirmed for: \"" << selectedMovie.title 
                 << "\" at " << selectedShow.time << endl;
            cout << "Enjoy your movie!" << endl;
        }
    }
};

// Main function
int main() {
    TicketSystem system;
    system.run();
    return 0;
}
