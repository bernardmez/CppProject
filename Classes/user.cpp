#include "User.h"
#include <iostream>

// Constructors
User::User() : username(""), password("") {}

User::User(const std::string& username, const std::string& password)
    : username(username), password(password) {}

// Getters and Setters
std::string User::getUsername() const {
    return username;
}

void User::setUsername(const std::string& username) {
    this->username = username;
}

std::string User::getPassword() const {
    return password;
}

void User::setPassword(const std::string& password) {
    this->password = password;
}

// Methods
bool User::login(const std::string& inputUsername, const std::string& inputPassword) const {
    return (inputUsername == username && inputPassword == password);
}

void User::logout() const {
    std::cout << "User logged out successfully." << std::endl;
}

void User::displayInfo() const {
    std::cout << "Username: " << username << std::endl;
}

// Destructor
User::~User() {
    // Virtual destructor for proper cleanup in derived classes
}
