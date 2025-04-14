#include "Admin.h"
#include <iostream>
#include <algorithm>
#include <iomanip>

// Constructors
Admin::Admin() : Employee() {}

Admin::Admin(const std::string& username, const std::string& password,
          int id, const std::string& name)
    : Employee(username, password, id, name, "Admin") {}

// Admin-specific methods
void Admin::addEmployee(std::vector<Employee>& employees) {
    std::string username, password, name, position;
    int id;
    
    std::cout << "Enter new employee details:" << std::endl;
    std::cout << "Username: ";
    std::cin >> username;
    std::cout << "Password: ";
    std::cin >> password;
    std::cout << "ID: ";
    std::cin >> id;
    std::cin.ignore();
    std::cout << "Name: ";
    std::getline(std::cin, name);
    std::cout << "Position: ";
    std::getline(std::cin, position);
    
    employees.emplace_back(username, password, id, name, position);
    std::cout << "Employee added successfully." << std::endl;
}

void Admin::removeEmployee(std::vector<Employee>& employees) {
    int id;
    std::cout << "Enter employee ID to remove: ";
    std::cin >> id;
    
    auto it = std::find_if(employees.begin(), employees.end(),
                         [id](const Employee& emp) { return emp.getEmployeeId() == id; });
    
    if (it != employees.end()) {
        employees.erase(it);
        std::cout << "Employee removed successfully." << std::endl;
    } else {
        std::cout << "Employee not found." << std::endl;
    }
}

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
            std::vector<Customer> sortedCustomers = customers;
            std::sort(sortedCustomers.begin(), sortedCustomers.end(),
                    [](const Customer& a, const Customer& b) {
                        return a.calculateTotalSpent() > b.calculateTotalSpent();
                    });
            
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
                
                count++;
                if (count >= 5) break; // Show top 5
            }
            break;
        }
        case 2:
            std::cout << "\n--- Customer Summary ---" << std::endl;
            std::cout << "Total customers: " << customers.size() << std::endl;
            break;
        case 3:
            return;
        default:
            std::cout << "Invalid choice." << std::endl;
    }
}

// Override methods
void Admin::displayInfo() const {
    Employee::displayInfo(); // Call base class method
    std::cout << "Admin privileges: Full system access" << std::endl;
}

// Destructor
Admin::~Admin() {
    // Destructor implementation
}
