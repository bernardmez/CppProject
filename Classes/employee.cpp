#include "Employee.h"
#include <iostream>
#include <algorithm>

// Constructors
Employee::Employee() : User(), employeeId(0), name(""), position("") {}

Employee::Employee(const std::string& username, const std::string& password,
                 int id, const std::string& name, const std::string& position)
    : User(username, password), employeeId(id), name(name), position(position) {}

// Getters and Setters
int Employee::getEmployeeId() const {
    return employeeId;
}

void Employee::setEmployeeId(int id) {
    employeeId = id;
}

std::string Employee::getName() const {
    return name;
}

void Employee::setName(const std::string& name) {
    this->name = name;
}

std::string Employee::getPosition() const {
    return position;
}

void Employee::setPosition(const std::string& position) {
    this->position = position;
}

// Methods
void Employee::displayInfo() const {
    User::displayInfo();
    std::cout << "Employee ID: " << employeeId << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Position: " << position << std::endl;
}

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
            std::cout << "\n--- All Customers ---" << std::endl;
            for (const auto& customer : customers) {
                customer.displayInfo();
                std::cout << "-------------------" << std::endl;
            }
            break;
        }
        case 2: {
            std::string searchName;
            std::cout << "Enter customer name to search: ";
            std::cin.ignore();
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
            return;
        default:
            std::cout << "Invalid choice." << std::endl;
    }
}

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
Employee::~Employee() {
    // Destructor implementation
}
