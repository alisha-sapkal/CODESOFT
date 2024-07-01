#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

class Book {
public:
    string title;
    string author;
    string ISBN;
    bool isAvailable;

    Book(string t, string a, string i) : title(t), author(a), ISBN(i), isAvailable(true) {}
};

class User {
public:
    string name;
    int userID;
    vector<Book> borrowedBooks;

    User(string n, int id) : name(n), userID(id) {}
};

class Library {
private:
    vector<Book> books;
    vector<User> users;

    void display() {
        cout << "\nLibrary Management System\n";
        cout << "1. ADD BOOK\n";
        cout << "2. REMOVE BOOK\n";
        cout << "3. SEARCH BOOK\n";
        cout << "4. DISPLAY BOOKS\n";
        cout << "5. ADD USER\n";
        cout << "6. BORROW BOOK\n";
        cout << "7. RETURN BOOK\n";
        cout << "8. EXIT\n";
        cout << "ENTER YOUR CHOICE: ";
    }

    int getChoice() {
        int choice;
        cin >> choice;
        while (choice < 1 || choice > 8) {
            cout << "INVALID CHOICE. ENTER NUMBER BETWEEEN 1 & 8: ";
            cin >> choice;
        }
        return choice;
    }

public:
    void addBook() {
        string title, author, ISBN;
        cout << "ENTER BOOK TITLE: ";
        cin.ignore();
        getline(cin, title);
        cout << "ENTER BOOK AUTHOR: ";
        getline(cin, author);
        cout << "ENTER BOOK ISBN ";
        getline(cin, ISBN);
        books.emplace_back(title, author, ISBN);
        cout << "BOOK ADDED SUCCESSFULLY!\n";
    }

    void removeBook() {
        string ISBN;
        cout << "ENTER BOOK ISBN TO REMOVE: ";
        cin >> ISBN;
        auto i = find_if(books.begin(), books.end(), [&ISBN](Book& book) {
            return book.ISBN == ISBN;
        });

        if (i != books.end()) {
            books.erase(i);
            cout << "BOOK REMOVED SUCCESSFULLY!\n";
        } else {
            cout << "BOOK NOT FOUND.\n";
        }
    }

    void searchBook() {
        string query;
        cout << "ENTER BOOK TITLE, AUTHOR, OR ISBN TO SEARCH: ";
        cin.ignore();
        getline(cin, query);
        bool found = false;

        for (auto& book : books) {
            if (book.title == query || book.author == query || book.ISBN == query) {
                cout << "BOOK FOUND: " << book.title << " BY " << book.author << " (ISBN: " << book.ISBN << ")\n";
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "BOOK NOT FOUND.\n";
        }
    }

    void displayBooks() {
        if (books.empty()) {
            cout << "NO BOOKS IN THE LIBRARY.\n";
            return;
        }

        for (auto& book : books) {
            cout << book.title << " BY " << book.author << " (ISBN: " << book.ISBN << ") - "
                 << (book.isAvailable ? "AVAILABLE" : "NOT AVAILABLE") << endl;
        }
    }

    void addUser() {
        string name;
        int userID;
        cout << "ENTER USER NAME: ";
        cin.ignore();
        getline(cin, name);
        cout << "ENTER USER ID: ";
        cin >> userID;
        users.emplace_back(name, userID);
        cout << "USER ADDED SUCCESSFULLY!\n";
    }

    void borrowBook() {
        int userID;
        string ISBN;
        cout << "ENTER USER ID: ";
        cin >> userID;
        cout << "ENTER BOOK ISBN TO BORROW: ";
        cin >> ISBN;

        auto userIt = find_if(users.begin(), users.end(), [userID](User& user) {
            return user.userID == userID;
        });

        if (userIt == users.end()) {
            cout << "USER NOT FOUND.\n";
            return;
        }

        auto bookIt = find_if(books.begin(), books.end(), [&ISBN](Book& book) {
            return book.ISBN == ISBN;
        });

        if (bookIt == books.end()) {
            cout << "BOOK NOT FOUND.\n";
            return;
        }

        if (!bookIt->isAvailable) {
            cout << "BOOK IS CURRENTLY NOT AVAILABLE.\n";
            return;
        }

        bookIt->isAvailable = false;
        userIt->borrowedBooks.push_back(*bookIt);
        cout << "BOOK BORROWED SUCCESSFULLY!\n";
    }

    void returnBook() {
        int userID;
        string ISBN;
        cout << "ENTER USER ID: ";
        cin >> userID;
        cout << "ENTER BOOK ISBN TO RETURN: ";
        cin >> ISBN;

        auto userIt = find_if(users.begin(), users.end(), [userID](User& user) {
            return user.userID == userID;
        });

        if (userIt == users.end()) {
            cout << "USER NOT FOUND.\n";
            return;
        }

        auto bookIt = find_if(userIt->borrowedBooks.begin(), userIt->borrowedBooks.end(), [&ISBN](Book& book) {
            return book.ISBN == ISBN;
        });

        if (bookIt == userIt->borrowedBooks.end()) {
            cout << "BOOK NOT FOUND IN USER'S BORROWED BOOK.\n";
            return;
        }

        auto originalBookIt = find_if(books.begin(), books.end(), [&ISBN](Book& book) {
            return book.ISBN == ISBN;
        });

        originalBookIt->isAvailable = true;
        userIt->borrowedBooks.erase(bookIt);
        cout << "BOOK RETURNED SUCCESSFULLY!\n";
    }

    void userMenu() {
        while (true) {
            display();
            int choice = getChoice();

            switch (choice) {
                case 1:
                    addBook();
                    break;
                case 2:
                    removeBook();
                    break;
                case 3:
                    searchBook();
                    break;
                case 4:
                    displayBooks();
                    break;
                case 5:
                    addUser();
                    break;
                case 6:
                    borrowBook();
                    break;
                case 7:
                    returnBook();
                    break;
                case 8:
                    cout << "EXITING...\n";
                    return;
                default:
                    cout << "INVALID CHOICE, PLEASE TRY AGAIN.\n";
            }
        }
    }
};

int main() {
    Library library;
    library.userMenu();
    return 0;
}
