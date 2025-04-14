#include "CRMSystem.h"
#include <iostream>
#include <stdexcept>

int main() {
    try {
        // File paths for data storage
        std::string customerFile = "customers.txt";
        std::string employeeFile = "employees.txt";
        std::string adminFile = "admins.txt";
        std::string transactionFile = "transactions.txt";
        
        // Create and run the CRM system
        CRMSystem crm(customerFile, employeeFile, adminFile, transactionFile);
        crm.run();
        
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}
