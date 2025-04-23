#include "Customer.h"
#include <iostream>
#include <iomanip>

// -------------------- Constructors --------------------

// Default constructor
// Initializes a customer with default values
Customer::Customer() : customerId(0), name(""), email(""), phone("") {}

// Parameterized constructor
// Initializes a customer with provided ID, name, email, and phone number
Customer::Customer(int id, const std::string& name, const std::string& email, const std::string& phone)
    : customerId(id), name(name), email(email), phone(phone) {}

// -------------------- Getters and Setters --------------------

// Returns the customer ID
int Customer::getCustomerId() const {
    return customerId;
}

// Sets the customer ID
void Customer::setCustomerId(int id) {
    customerId = id;
}

// Returns the customer name
std::string Customer::getName() const {
    return name;
}

// Sets the customer name
void Customer::setName(const std::string& name) {
    this->name = name;
}

// Returns the customer email
std::string Customer::getEmail() const {
    return email;
}

// Sets the customer email
void Customer::setEmail(const std::string& email) {
    this->email = email;
}

// Returns the customer phone number
std::string Customer::getPhone() const {
    return phone;
}

// Sets the customer phone number
void Customer::setPhone(const std::string& phone) {
    this->phone = phone;
}

// -------------------- Transaction Methods --------------------

// Adds a new transaction to the customer's transaction history
void Customer::addTransaction(const Transaction& transaction) {
    transactions.push_back(transaction);
}

// Returns a const reference to the vector of transactions
const std::vector<Transaction>& Customer::getTransactions() const {
    return transactions;
}

// Calculates and returns the total amount spent by the customer
double Customer::calculateTotalSpent() const {
    double total = 0.0;
    for (const auto& transaction : transactions) {
        total += transaction.getAmount();
    }
    return total;
}

// -------------------- Display Method --------------------

// Displays detailed customer info including total spent
void Customer::displayInfo() const {
    std::cout << "Customer ID: " << customerId << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Email: " << email << std::endl;
    std::cout << "Phone: " << phone << std::endl;
    std::cout << "Total spent: $" << std::fixed << std::setprecision(2) << calculateTotalSpent() << std::endl;
}

// -------------------- Stream Operators --------------------

// Output stream operator overload
// Used to print customer data in a space-separated format (e.g., for file writing)
std::ostream& operator<<(std::ostream& os, const Customer& customer) {
    os << customer.customerId << " " << customer.name << " " 
       << customer.email << " " << customer.phone;
    return os;
}

// Input stream operator overload
// Used to read customer data from a stream (e.g., from a file)
std::istream& operator>>(std::istream& is, Customer& customer) {
    is >> customer.customerId >> customer.name >> customer.email >> customer.phone;
    return is;
}
