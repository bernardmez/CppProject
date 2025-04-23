#include "Admin.h"
#include <iostream>
#include <algorithm>
#include <iomanip>

// -------------------- Constructors --------------------

// Default constructor
// Initializes an Admin object with default values
Admin::Admin() : Employee() {}

// Parameterized constructor
// Initializes an Admin with specific credentials and personal details
Admin::Admin(const std::string& username, const std::string& password,
             int id, const std::string& name)
    : Employee(username, password, id, name, "Admin") {}


// -------------------- Admin-Specific Methods --------------------

// Adds a new employee to the system
void Admin::addEmployee(std::vector<Employee>& employees) {
    std::string username, password, name, position;
    int id;

    // Prompt for employee details
    std::cout << "Enter new employee details:" << std::endl;
    std::cout << "Username: ";
    std::cin >> username;
    std::cout << "Password: ";
    std::cin >> password;
    std::cout << "ID: ";
    std::cin >> id;
    std::cin.ignore(); // Clear newline from buffer
    std::cout << "Name: ";
    std::getline(std::cin, name);
    std::cout << "Position: ";
    std::getline(std::cin, position);

    // Add new employee to vector
    employees.emplace_back(username, password, id, name, position);
    std::cout << "Employee added successfully." << std::endl;
}

// Removes an employee based on their ID
void Admin::removeEmployee(std::vector<Employee>& employees) {
    int id;
    std::cout << "Enter employee ID to remove: ";
    std::cin >> id;

    // Find employee by ID
    auto it = std::find_if(employees.begin(), employees.end(),
        [id](const Employee& emp) { return emp.getEmployeeId() == id; });

    if (it != employees.end()) {
        employees.erase(it);
        std::cout << "Employee removed successfully." << std::endl;
    } else {
        std::cout << "Employee not found." << std::endl;
    }
}

// Generates administrative reports
void Admin::generateReports(const std::vector<Customer>& customers) {
    int choice;
    std::cout << "\nReport Menu:" << std::endl;
    std::cout << "1. Top customers by spending" << std::endl;
    std::cout << "2. Customer count summary" << std::endl;
    std::cout << "3. Back" << std::endl;
    std::cout << "Enter your choice: ";
    std::cin >> choice;

    switch (choice) {
        case 1: {
            // Sort customers by total amount spent in descending order
            std::vector<Customer> sortedCustomers = customers;
            std::sort(sortedCustomers.begin(), sortedCustomers.end(),
                [](const Customer& a, const Customer& b) {
                    return a.calculateTotalSpent() > b.calculateTotalSpent();
                });

            // Display top 5 customers
            std::cout << "\n--- Top Customers by Spending ---" << std::endl;
            std::cout << std::left << std::setw(5) << "ID" 
                      << std::setw(20) << "Name" 
                      << std::right << std::setw(10) << "Total($)" << std::endl;
            std::cout << std::string(35, '-') << std::endl;

            int count = 0;
            for (const auto& customer : sortedCustomers) {
                std::cout << std::left << std::setw(5) << customer.getCustomerId() 
                          << std::setw(20) << customer.getName() 
                          << std::right << std::fixed << std::setprecision(2)
                          << std::setw(10) << customer.calculateTotalSpent() << std::endl;

                if (++count >= 5) break; // Limit to top 5
            }
            break;
        }
        case 2:
            // Display total number of customers
            std::cout << "\n--- Customer Summary ---" << std::endl;
            std::cout << "Total customers: " << customers.size() << std::endl;
            break;
        case 3:
            return; // Exit report menu
        default:
            std::cout << "Invalid choice." << std::endl;
    }
}

// -------------------- Method Overrides --------------------

// Displays admin's info with added privilege note
void Admin::displayInfo() const {
    Employee::displayInfo(); // Call base method to display employee info
    std::cout << "Admin privileges: Full system access" << std::endl;
}

// -------------------- Destructor --------------------

// Admin destructor
Admin::~Admin() {
    // Optional cleanup logic if needed
}
