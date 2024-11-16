#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int MAX_MOVIES = 100;
const int MAX_SHOPS = 10;
// define the maximum number of movies and shops making it constant

enum class Genre {          //enum for movie genre (movie type)
    Action, Drama, Crime    //possible movie types (genres)
};

enum class Availability {       //enum for movies availability
    Available, NotAvailable     //possible status either available or not available
};
class Movie {

private:
    string title;
    Genre genre;
    string director;
    Availability availability;

public:
    //default constructor 
    Movie() : title(""), genre(Genre::Drama), director(""), availability(Availability::Available)
    {
    }

    //constructor with parameters that initialize movies with title (t) and genre(g), director(d) and availability
    Movie(string t, Genre g, string d) : title(t), genre(g), director(d), availability(Availability::Available)
    {
    }

    string getTitle() const     //a function that returns back the title of the movie
    {
        return title;
    }


    Genre getGenre() const     //a function that returns the genre (movie type)
    {
        return genre;
    }

    string getGenreAsString() const {
        switch (genre) {
        case Genre::Action:
            return "Action";
        case Genre::Drama:
            return "Drama";
        case Genre::Crime:
            return "Crime";
        default:
            return "Unknown";
        }
    }

    string getDirector() const       //function to get the director of the movie
    {
        return director;
    }

    Availability getAvailability() const     //a function to show the availability of the movie
    {
        return availability;
    }


    void displayDetails() {     //a function to display all details about every movie
        cout << "Title: " << title << endl;
        cout << "Genre: " << getGenreAsString() << endl;
        cout << "Director: " << director << endl;
        cout << "Availability: " << (availability == Availability::Available ? "Available" : "Not Available") << endl;
    }
    void rentMovie() {                      //a function to label movie as rented
        availability = Availability::NotAvailable;
    }
    void returnMovie() {                    //a function to label movie as returned
        availability = Availability::Available;
    }



};

/* the Movie class :
has private members to store title, genre, director and availability status of the movie.
why priavte? abecause private members in class are only accessible in the class and can't be accessed directly from outside the class.


The class has default constructor and a constructors with parameters to initialize the movie details. And has member functions to get title, display movie details, check the availability, rent movie, and return movie.
*/

class Shop {
private:
    Movie movies[MAX_MOVIES];
    string shopName;
    int prices[MAX_MOVIES];
    int numMovies;

public:
    //Default constructor
    Shop() : shopName(""), numMovies(0), prices{} {}

    //constructor with parameters for shop class
    Shop(string name) : shopName(name), numMovies(0), prices{}
    {
    }

    string getShopName() const {        //a function to get shop name
        return shopName;
    }

    void addMovie(const Movie& movie, int price) {      //function to add movies to the inventory of the shops
        if (numMovies < MAX_MOVIES) {
            movies[numMovies] = movie;
            prices[numMovies] = price;
            numMovies++;
        }
        else {
            cout << "Can't add more movies because maximum limit reached in shop " << shopName << "." << endl;
        }
    }

    void displayMovies() const {        //function to display available movies in the shops
        if (numMovies == 0) {
            cout << "No movies are available in " << shopName << "." << endl;
        }
        else {
            cout << "Available movies in shop " << shopName << ":" << endl;
            for (int i = 0; i < numMovies; i++) {
                if (movies[i].getAvailability() == Availability::Available) {
                    cout << i + 1 << "- " << movies[i].getTitle() << " (Genre: " << movies[i].getGenreAsString() << ", Price: L.E " << prices[i] << ")" << endl;
                }
            }
        }
    }

    string rentMovie(int movieNumber) {       //a function to rent a movie from a shop
        if (movieNumber > 0 && movieNumber <= numMovies && movies[movieNumber - 1].getAvailability() == Availability::Available) {
            movies[movieNumber - 1].rentMovie();
            return movies[movieNumber - 1].getTitle();
        }
        return "";
    }

    string returnMovie(int movieNumber) {     //a function to return a movie to the shop if wanted
        if (movieNumber > 0 && movieNumber <= numMovies && movies[movieNumber - 1].getAvailability() == Availability::NotAvailable) {
            movies[movieNumber - 1].returnMovie();
            return movies[movieNumber - 1].getTitle();
        }
        return "";
    }

    int getMoviePrice(int movieNumber) const {      //function to display prices of each movie in shops
        if (movieNumber > 0 && movieNumber <= numMovies) {
            return prices[movieNumber - 1];
        }
        return -1;
    }

    int getNumMovies() const {      //function that displays number of movies in shops
        return numMovies;
    }

    const Movie& getMovie(int index) const {        //a function that gets a movie object by index
        return movies[index];
    };
};

class RentalSystem {
private:
    Shop shops[MAX_SHOPS];
    int numShops;

public:
    RentalSystem() : numShops(0) {}      //default constructor for rentalsystem class

    void addShop(const Shop& shop) {        //function to add shops to the rental system if maximum limit isn't reached
        if (numShops < MAX_SHOPS) {
            shops[numShops++] = shop;
        }
        else {
            cout << "Cannot add more shops. Maximum limit reached." << endl;
        }
    }

    void displayMovies() {      //function to display title of available movies in system
        if (numShops == 0) {
            cout << "No shops available." << endl;
        }
        else {
            for (int i = 0; i < numShops; ++i) {
                shops[i].displayMovies();
                cout << endl;
            }
        }
    }

    string rentMovie(int shopNumber, int movieNumber) {       //function to rent movie from a specific shop
        if (shopNumber > 0 && shopNumber <= numShops) {
            return shops[shopNumber - 1].rentMovie(movieNumber);
        }
        return "";
    }

    string returnMovie(int shopNumber, int movieNumber) {     //a function to return a specific movie to its shop
        if (shopNumber > 0 && shopNumber <= numShops) {
            return shops[shopNumber - 1].returnMovie(movieNumber);
        }
        return "";
    }
};

int main() {
    RentalSystem rentalSystem;

    Shop shop1("Shop 1");       //creates two objects for shops
    Shop shop2("Shop 2");

    shop1.addMovie(Movie("The Shawshank Redemption", Genre::Drama, "Frank Darabont"), 15);      //add movies to shop 1
    shop1.addMovie(Movie("The Godfather", Genre::Crime, "Francis Ford Coppola"), 20);
    shop1.addMovie(Movie("The Dark Knight", Genre::Action, "Christopher Nolan"), 25);

    shop2.addMovie(Movie("The Shawshank Redemption", Genre::Drama, "Frank Darabont"), 20);      //add movies to shop 2
    shop2.addMovie(Movie("The Godfather", Genre::Crime, "Francis Ford Coppola"), 25);
    shop2.addMovie(Movie("The Dark Knight", Genre::Action, "Christopher Nolan"), 30);

    rentalSystem.addShop(shop1);        //add shops to system
    rentalSystem.addShop(shop2);

    int choice;
    int shopNumber;
    int movieNumber;

    do {                                                        //Displays the main menu for the user
        cout << "\n===== Main Menu =====" << endl;
        cout << "1. Display available movies" << endl;
        cout << "2. Rent a movie" << endl;
        cout << "3. Return a movie" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:                                 //display available movies in shops for user 
            rentalSystem.displayMovies();
            break;
        case 2:                                             //rent a movie from a specific store that the user chooses
            cout << "Enter the shop number: ";
            cin >> shopNumber;
            cout << "Enter the movie number you want to rent: ";
            cin >> movieNumber;
            {
                string rentedMovie = rentalSystem.rentMovie(shopNumber, movieNumber);
                if (!rentedMovie.empty()) {
                    cout << "You have rented the movie: " << rentedMovie << endl;
                }
                else {
                    cout << "Movie not available" << endl;
                }
            }
            break;
        case 3:                                             //return a specific movie that the user rented from a specific shop
            cout << "Enter the shop number: ";
            cin >> shopNumber;
            cout << "Enter the movie number you want to return: ";
            cin >> movieNumber;
            {
                string returnedMovie = rentalSystem.returnMovie(shopNumber, movieNumber);
                if (!returnedMovie.empty()) {
                    cout << "You have returned the movie: " << returnedMovie << endl;
                }
                else {
                    cout << "Movie already available" << endl;
                }
            }
            break;
        case 4:                                 //exit the program
            cout << "Exiting" << endl;
            break;
        default:
            cout << "Invalid choice. Please enter a number between 1 and 4." << endl;
        }
    } while (choice != 4);        //it will continue to loop as long as choice is not equal to 4
}