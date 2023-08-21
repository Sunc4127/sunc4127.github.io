//
// Created by Cheng Sun on 2023/8/20.
//
#include "../../include/library.h"

struct Date {
    short year = 1900; // default value
    short month = 1;
    short day = 1;
};
struct Movie {
    string title; // default value: empty string
    Date releaseDate;
    bool isPopular; // default value: false

    [[nodiscard]] bool equals(const Movie& other) const { // const: this method does not modify the object
        return (
            title == other.title &&
            releaseDate.year == other.releaseDate.year &&
            releaseDate.month == other.releaseDate.month &&
            releaseDate.day == other.releaseDate.day
        );
    }
};

// operator overloading, output stream
ostream& operator<<(ostream& os, const Movie& movie) {
    os << movie.title << " (" << movie.releaseDate.year << ")";
    return os;
}

bool operator==(const Movie& lhs, const Movie& rhs) {
    return (
        lhs.title == rhs.title &&
        lhs.releaseDate.year == rhs.releaseDate.year &&
        lhs.releaseDate.month == rhs.releaseDate.month &&
        lhs.releaseDate.day == rhs.releaseDate.day
    );
}

Movie getMovie() {
    return {"The Matrix", {1999, 1, 1}};
}

Movie showMovie(const Movie& movie) {
    cout << movie.title << " (" << movie.releaseDate.year << ")" << endl;
    return movie;
}

Movie demonstrateMovie(Movie* movie) {
    cout << movie->title << " (" << movie->releaseDate.year << ")" << endl; // -> operator: structure pointer operator
    return *movie;
}

// internally represented as integers
enum class Action {
    List = 1,
    Add, // = 2
    Update
};



int main() {

    cout << endl << "01. defining and initializing nested structures" << endl;
    // assign values to struct members in order
    Movie movie = {
            "The Matrix",
            {1999, 1, 1}
    };
    cout << movie.title << " (" << movie.releaseDate.year << ")" << endl;



    cout << endl << "03. unpacking structures" << endl;
    // c++: structured binding
    // JS: destructuring assignment
    // Python: unpacking
    auto [title, releaseDate, isPopular] {movie};
    cout << title << " (" << releaseDate.year << ")" << endl;



    cout << endl << "04. arrays of structures" << endl;
    vector<Movie> movies;
    movies.push_back(movie);
    movies.push_back({"The Matrix Reloaded", 2003});
    for (const auto& m : movies) {
        cout << m.title << " (" << m.releaseDate.year << ")" << endl;
    }



    cout << endl << "07. comparing structures using methods" << endl;
    Movie movie7 = {"The Matrix7", {1999, 1, 1}};
    // need to compare all members
    if (movie7.equals(movie)) {
        cout << "movie7 is the same as movie" << endl;
    } else {
        cout << "movie7 is not the same as movie" << endl;
    }



    cout << endl << "09. operator overloading" << endl;
    // overloading operator << to output the object
    cout << movie << endl;



    cout << endl << "10. structures and functions" << endl;
    Movie movie10 = getMovie();
    showMovie(movie10);



    cout << endl << "11. pointers to structures" << endl;
    auto movie11 = getMovie();
    demonstrateMovie(&movie11);



    cout << endl << "12. defining enumerations" << endl;
    int input = random() % 3 + 1;
    if (input == static_cast<int>(Action::List)) {
        cout << "action is:" << input << endl;
    } else {
        cout << "action is:" << input << " not list" << endl;
    }



    // avoid using enum, use strongly typed enum instead, because it can avoid name collision
    cout << endl << "13. strongly typed enumerations" << endl;
}