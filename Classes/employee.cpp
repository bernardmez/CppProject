#include "Employee.h"
#include <iostream>
#include <algorithm>

// -------------------- Constructors --------------------

// Default constructor
// Initializes all attributes to default values
Employee::Employee() : User(), employeeId(0), name(""), position("") {}

// Parameterized constructor
// Initializes attributes with provided values and calls the User constructor
Employee::Employee(const std::string& username, const std::string& password,
                   int id, const std::string& name, const std::string& position)
    : User(username, password), employeeId(id), name(name), position(position) {}

// -------------------- Getters and Setters --------------------

// Returns the employee's ID
int Employee::getEmployeeId() const {
    return employeeId;
}

// Sets the employee's ID
void Employee::setEmployeeId(int id) {
    employeeId = id;
}

// Returns the employee's name
std::string Employee::getName() const {
    return name;
}

// Sets the employee's name
void Employee::setName(const std::string& name) {
    this->name = name;
}

// Returns the employee's job position
std::string Employee::getPosition() const {
    return position;
}

// Sets the employee's job position
void Employee::setPosition(const std::string& position) {
    this->position = position;
}

// -------------------- Methods --------------------

// Displays employee's information including inherited user info
void Employee::displayInfo() const {
    User::displayInfo(); // Display username
    std::cout << "Employee ID: " << employeeId << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Position: " << position << std::endl;
}

// Manages customer data through a simple menu system
void Employee::manageCustomers(std::vector<Customer>& customers) {
    int choice;
    std::cout << "\nCustomer Management Menu:" << std::endl;
    std::cout << "1. View all customers" << std::endl;
    std::cout << "2. Search for customer" << std::endl;
    std::cout << "3. Back to main menu" << std::endl;
    std::cout << "Enter your choice: ";
    std::cin >> choice;

    switch (choice) {
        case 1: {
            // View all customers
            std::cout << "\n--- All Customers ---" << std::endl;
            for (const auto& customer : customers) {
                customer.displayInfo();
                std::cout << "-------------------" << std::endl;
            }
            break;
        }
        case 2: {
            // Search for a customer by name
            std::string searchName;
            std::cout << "Enter customer name to search: ";
            std::cin.ignore(); // Clear newline from previous input
            std::getline(std::cin, searchName);
            
            bool found = false;
            for (const auto& customer : customers) {
                if (customer.getName().find(searchName) != std::string::npos) {
                    customer.displayInfo();
                    std::cout << "-------------------" << std::endl;
                    found = true;
                }
            }

            if (!found) {
                std::cout << "No customers found with that name." << std::endl;
            }
            break;
        }
        case 3:
            // Return to previous menu
            return;
        default:
            // Handle invalid input
            std::cout << "Invalid choice." << std::endl;
    }
}

// Allows employee to view a customer's transaction history by entering their ID
void Employee::viewTransactions(const std::vector<Customer>& customers) {
    int customerId;
    std::cout << "Enter customer ID to view transactions: ";
    std::cin >> customerId;

    bool found = false;
    for (const auto& customer : customers) {
        if (customer.getCustomerId() == customerId) {
            found = true;
            std::cout << "\nTransactions for " << customer.getName() << ":" << std::endl;
            const auto& transactions = customer.getTransactions();

            if (transactions.empty()) {
                std::cout << "No transactions found." << std::endl;
            } else {
                for (const auto& transaction : transactions) {
                    transaction.displayDetails();
                    std::cout << "-------------------" << std::endl;
                }
            }
            break;
        }
    }

    if (!found) {
        std::cout << "Customer not found." << std::endl;
    }
}

// Destructor
// Clean-up if needed (currently empty, but required if any dynamic memory is used later)
Employee::~Employee() {
    // Destructor implementation (currently empty)
}
