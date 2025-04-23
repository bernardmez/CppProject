#include "Transaction.h"
#include <iostream>
#include <iomanip>

// -------------------- Constructors --------------------

// Default constructor
// Initializes all member variables to default values
Transaction::Transaction() 
    : transactionId(0), customerId(0), date(""), amount(0), productName("") {}

// Parameterized constructor
// Initializes all member variables using provided values
Transaction::Transaction(int transId, int custId, const std::string& date, 
                         double amount, const std::string& productName)
    : transactionId(transId), customerId(custId), date(date), 
      amount(amount), productName(productName) {}

// -------------------- Getters and Setters --------------------

// Returns the transaction ID
int Transaction::getTransactionId() const {
    return transactionId;
}

// Sets the transaction ID
void Transaction::setTransactionId(int id) {
    transactionId = id;
}

// Returns the customer ID
int Transaction::getCustomerId() const {
    return customerId;
}

// Sets the customer ID
void Transaction::setCustomerId(int id) {
    customerId = id;
}

// Returns the transaction date
std::string Transaction::getDate() const {
    return date;
}

// Sets the transaction date
void Transaction::setDate(const std::string& date) {
    this->date = date;
}

// Returns the transaction amount
double Transaction::getAmount() const {
    return amount;
}

// Sets the transaction amount
void Transaction::setAmount(double amount) {
    this->amount = amount;
}

// Returns the product name
std::string Transaction::getProductName() const {
    return productName;
}

// Sets the product name
void Transaction::setProductName(const std::string& name) {
    productName = name;
}

// -------------------- Methods --------------------

// Displays transaction details in a readable format
void Transaction::displayDetails() const {
    std::cout << "Transaction ID: " << transactionId << std::endl;
    std::cout << "Customer ID: " << customerId << std::endl;
    std::cout << "Date: " << date << std::endl;
    std::cout << "Amount: $" << std::fixed << std::setprecision(2) << amount << std::endl;
    std::cout << "Product: " << productName << std::endl;
}

// -------------------- Operator Overloading --------------------

// Overloads the output stream operator to print transaction details in a single line
std::ostream& operator<<(std::ostream& os, const Transaction& transaction) {
    os << transaction.transactionId << " " << transaction.customerId << " " 
       << transaction.date << " " << transaction.amount << " " << transaction.productName;
    return os;
}

// Overloads the input stream operator to read transaction data from input
std::istream& operator>>(std::istream& is, Transaction& transaction) {
    is >> transaction.transactionId >> transaction.customerId >> transaction.date 
       >> transaction.amount >> transaction.productName;
    return is;
}
