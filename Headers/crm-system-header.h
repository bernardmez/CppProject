#ifndef CRM_SYSTEM_H
#define CRM_SYSTEM_H

#include <vector>
#include <memory>
#include <string>
#include <unordered_map>
#include "Customer.h"
#include "Employee.h"
#include "Admin.h"
#include "Transaction.h"

class CRMSystem {
private:
    std::vector<Customer> customers;
    std::vector<Employee> employees;
    std::vector<Admin> admins;
    std::unordered_map<int, Customer*> customerMap; // For fast lookup by ID
    
    // Currently logged in user
    User* currentUser;
    
    // File paths
    std::string customerFilePath;
    std::string employeeFilePath;
    std::string adminFilePath;
    std::string transactionFilePath;
    
public:
    // Constructor
    CRMSystem(const std::string& customerFile, const std::string& employeeFile, 
              const std::string& adminFile, const std::string& transactionFile);
    
    // File operations
    void loadData();
    void saveData();
    
    // Customer operations
    void addCustomer();
    void removeCustomer();
    void searchCustomer();
    void modifyCustomer();
    void displayAllCustomers();
    
    // Transaction operations
    void addTransaction();
    
    // Employee operations
    void addEmployee();
    void removeEmployee();
    
    // Search and sort functions
    template<typename T>
    void sortByName(std::vector<T>& items);
    
    template<typename T>
    std::vector<T> searchByName(const std::vector<T>& items, const std::string& searchName);
    
    // Authentication
    bool login();
    void logout();
    
    // Menu functions
    void showMainMenu();
    void showAdminMenu();
    void showEmployeeMenu();
    
    // Run the system
    void run();
};

#endif // CRM_SYSTEM_H
