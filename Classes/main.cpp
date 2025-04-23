#include "CRMSystem.h"
#include <iostream>
#include <stdexcept>

int main() {
    try {
        // -------------------- File Paths --------------------
        // Define the file paths for data persistence.
        // These files are used to store and load customer, employee, admin, and transaction data.
        std::string customerFile = "customers.txt";
        std::string employeeFile = "employees.txt";
        std::string adminFile = "admins.txt";
        std::string transactionFile = "transactions.txt";
        
        // -------------------- System Initialization --------------------
        // Create an instance of the CRM system using the file paths
        // This likely loads existing data from the files into the program
        CRMSystem crm(customerFile, employeeFile, adminFile, transactionFile);
        
        // -------------------- Run the System --------------------
        // Start the main loop or menu system of the CRM
        // This is likely where user interaction takes place
        crm.run();
        
        // Exit successfully
        return 0;
    } catch (const std::exception& e) {
        // Catch and display any runtime errors (e.g., file not found, parsing errors)
        std::cerr << "Error: " << e.what() << std::endl;
        return 1; // Exit with error code
    }
}
