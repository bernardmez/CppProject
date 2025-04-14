#include "Transaction.h"
#include <iostream>
#include <iomanip>

// Constructors
Transaction::Transaction() : transactionId(0), customerId(0), date(""), amount(0), productName("") {}

Transaction::Transaction(int transId, int custId, const std::string& date, 
                        double amount, const std::string& productName)
    : transactionId(transId), customerId(custId), date(date), 
      amount(amount), productName(productName) {}

// Getters and Setters
int Transaction::getTransactionId() const {
    return transactionId;
}

void Transaction::setTransactionId(int id) {
    transactionId = id;
}

int Transaction::getCustomerId() const {
    return customerId;
}

void Transaction::setCustomerId(int id) {
    customerId = id;
}

std::string Transaction::getDate() const {
    return date;
}

void Transaction::setDate(const std::string& date) {
    this->date = date;
}

double Transaction::getAmount() const {
    return amount;
}

void Transaction::setAmount(double amount) {
    this->amount = amount;
}

std::string Transaction::getProductName() const {
    return productName;
}

void Transaction::setProductName(const std::string& name) {
    productName = name;
}

// Methods
void Transaction::displayDetails() const {
    std::cout << "Transaction ID: " << transactionId << std::endl;
    std::cout << "Customer ID: " << customerId << std::endl;
    std::cout << "Date: " << date << std::endl;
    std::cout << "Amount: $" << std::fixed << std::setprecision(2) << amount << std::endl;
    std::cout << "Product: " << productName << std::endl;
}

// Operators
std::ostream& operator<<(std::ostream& os, const Transaction& transaction) {
    os << transaction.transactionId << " " << transaction.customerId << " " 
       << transaction.date << " " << transaction.amount << " " << transaction.productName;
    return os;
}

std::istream& operator>>(std::istream& is, Transaction& transaction) {
    is >> transaction.transactionId >> transaction.customerId >> transaction.date 
       >> transaction.amount >> transaction.productName;
    return is;
}
