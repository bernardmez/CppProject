#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <iostream>

class Transaction {
private:
    int transactionId;
    int customerId;
    std::string date;
    double amount;
    std::string productName;

public:
    // Constructors
    Transaction();
    Transaction(int transId, int custId, const std::string& date, 
                double amount, const std::string& productName);
    
    // Getters and Setters
    int getTransactionId() const;
    void setTransactionId(int id);
    int getCustomerId() const;
    void setCustomerId(int id);
    std::string getDate() const;
    void setDate(const std::string& date);
    double getAmount() const;
    void setAmount(double amount);
    std::string getProductName() const;
    void setProductName(const std::string& name);
    
    // Methods
    void displayDetails() const;
    
    // Operators
    friend std::ostream& operator<<(std::ostream& os, const Transaction& transaction);
    friend std::istream& operator>>(std::istream& is, Transaction& transaction);
};

#endif // TRANSACTION_H
