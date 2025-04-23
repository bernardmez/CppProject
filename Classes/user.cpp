#include "User.h"
#include <iostream>

// Default constructor
// Initializes username and password to empty strings
User::User() : username(""), password("") {}
// Parameterized constructor
// Initializes username and password with given values
User::User(const std::string& username, const std::string& password)
    : username(username), password(password) {}
// Getter for username
std::string User::getUsername() const {
    return username;
}
// Setter for username
void User::setUsername(const std::string& username) {
    this->username = username;
}
// Getter for password
std::string User::getPassword() const {
    return password;
}
// Setter for password
void User::setPassword(const std::string& password) {
    this->password = password;
}
// Login method
// Returns true if the input credentials match the stored ones
bool User::login(const std::string& inputUsername, const std::string& inputPassword) const {
    return (inputUsername == username && inputPassword == password);
}
// Logout method
// Displays a message indicating the user has logged out
void User::logout() const {
    std::cout << "User logged out successfully." << std::endl;
}

// Display user information (currently only username)
void User::displayInfo() const {
    std::cout << "Username: " << username << std::endl;
}

// Destructor
// Virtual to ensure proper cleanup when using inheritance
User::~User() {
    // Virtual destructor for proper cleanup in derived classes
}
