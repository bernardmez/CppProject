#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <vector>
#include "Transaction.h"

class Transaction; // Forward declaration

class Customer {
private:
    int customerId;
    std::string name;
    std::string email;
    std::string phone;
    std::vector<Transaction> transactions;

public:
    // Constructors
    Customer();
    Customer(int id, const std::string& name, const std::string& email, const std::string& phone);
    
    // Getters and Setters
    int getCustomerId() const;
    void setCustomerId(int id);
    std::string getName() const;
    void setName(const std::string& name);
    std::string getEmail() const;
    void setEmail(const std::string& email);
    std::string getPhone() const;
    void setPhone(const std::string& phone);
    
    // Transaction methods
    void addTransaction(const Transaction& transaction);
    const std::vector<Transaction>& getTransactions() const;
    double calculateTotalSpent() const;
    
    // Display method
    void displayInfo() const;
    
    // Operators
    friend std::ostream& operator<<(std::ostream& os, const Customer& customer);
    friend std::istream& operator>>(std::istream& is, Customer& customer);
};

#endif // CUSTOMER_H
