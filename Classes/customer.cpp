#include "Customer.h"
#include <iostream>
#include <iomanip>

// Constructors
Customer::Customer() : customerId(0), name(""), email(""), phone("") {}

Customer::Customer(int id, const std::string& name, const std::string& email, const std::string& phone)
    : customerId(id), name(name), email(email), phone(phone) {}

// Getters and Setters
int Customer::getCustomerId() const {
    return customerId;
}

void Customer::setCustomerId(int id) {
    customerId = id;
}

std::string Customer::getName() const {
    return name;
}

void Customer::setName(const std::string& name) {
    this->name = name;
}

std::string Customer::getEmail() const {
    return email;
}

void Customer::setEmail(const std::string& email) {
    this->email = email;
}

std::string Customer::getPhone() const {
    return phone;
}

void Customer::setPhone(const std::string& phone) {
    this->phone = phone;
}

// Transaction methods
void Customer::addTransaction(const Transaction& transaction) {
    transactions.push_back(transaction);
}

const std::vector<Transaction>& Customer::getTransactions() const {
    return transactions;
}

double Customer::calculateTotalSpent() const {
    double total = 0.0;
    for (const auto& transaction : transactions) {
        total += transaction.getAmount();
    }
    return total;
}

// Display method
void Customer::displayInfo() const {
    std::cout << "Customer ID: " << customerId << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Email: " << email << std::endl;
    std::cout << "Phone: " << phone << std::endl;
    std::cout << "Total spent: $" << std::fixed << std::setprecision(2) << calculateTotalSpent() << std::endl;
}

// Operators
std::ostream& operator<<(std::ostream& os, const Customer& customer) {
    os << customer.customerId << " " << customer.name << " " 
       << customer.email << " " << customer.phone;
    return os;
}

std::istream& operator>>(std::istream& is, Customer& customer) {
    is >> customer.customerId >> customer.name >> customer.email >> customer.phone;
    return is;
}
