#include "CRMSystem.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <stdexcept>

// Constructor
CRMSystem::CRMSystem(const std::string& customerFile, const std::string& employeeFile, 
                   const std::string& adminFile, const std::string& transactionFile)
    : customerFilePath(customerFile), employeeFilePath(employeeFile),
      adminFilePath(adminFile), transactionFilePath(transactionFile),
      currentUser(nullptr) {}

// File operations
void CRMSystem::loadData() {
    try {
        // Load customers
        std::ifstream customerFile(customerFilePath);
        if (customerFile.is_open()) {
            int id;
            std::string name, email, phone;
            while (customerFile >> id >> name >> email >> phone) {
                customers.emplace_back(id, name, email, phone);
            }
            customerFile.close();
        }
        
        // Load employees
        std::ifstream employeeFile(employeeFilePath);
        if (employeeFile.is_open()) {
            std::string username, password, name, position;
            int id;
            while (employeeFile >> username >> password >> id >> name >> position) {
                employees.emplace_back(username, password, id, name, position);
            }
            employeeFile.close();
        }
        
        // Load admins
        std::ifstream adminFile(adminFilePath);
        if (adminFile.is_open()) {
            std::string username, password, name;
            int id;
            while (adminFile >> username >> password >> id >> name) {
                admins.emplace_back(username, password, id, name);
            }
            adminFile.close();
        }
        
        // Load transactions
        std::ifstream transactionFile(transactionFilePath);
        if (transactionFile.is_open()) {
            int transId, custId;
            std::string date, productName;
            double amount;
            
            while (transactionFile >> transId >> custId >> date >> amount >> productName) {
                Transaction transaction(transId, custId, date, amount, productName);
                
                // Find the customer and add the transaction
                for (auto& customer : customers) {
                    if (customer.getCustomerId() == custId) {
                        customer.addTransaction(transaction);
                        break;
                    }
                }
            }
            transactionFile.close();
        }
        
        // Build the customer map for fast lookups
        for (auto& customer : customers) {
            customerMap[customer.getCustomerId()] = &customer;
        }
        
        std::cout << "Data loaded successfully." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error loading data: " << e.what() << std::endl;
    }
}

void CRMSystem::saveData() {
    try {
        // Save customers
        std::ofstream customerFile(customerFilePath);
        if (customerFile.is_open()) {
            for (const auto& customer : customers) {
                customerFile << customer << std::endl;
            }
            customerFile.close();
        }
        
        // Save employees
        std::ofstream employeeFile(employeeFilePath);
        if (employeeFile.is_open()) {
            for (const auto& employee : employees) {
                employeeFile << employee.getUsername() << " " << employee.getPassword() << " "
                           << employee.getEmployeeId() << " " << employee.getName() << " "
                           << employee.getPosition() << std::endl;
            }
            employeeFile.close();
        }
        
        // Save admins
        std::ofstream adminFile(adminFilePath);
        if (adminFile.is_open()) {
            for (const auto& admin : admins) {
                adminFile << admin.getUsername() << " " << admin.getPassword() << " "
                        << admin.getEmployeeId() << " " << admin.getName() << std::endl;
            }
            adminFile.close();
        }
        
        // Save transactions
        std::ofstream transactionFile(transactionFilePath);
        if (transactionFile.is_open()) {
            for (const auto& customer : customers) {
                for (const auto& transaction : customer.getTransactions()) {
                    transactionFile << transaction << std::endl;
                }
            }
            transactionFile.close();
        }
        
        std::cout << "Data saved successfully." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error saving data: " << e.what() << std::endl;
    }
}

// Customer operations
void CRMSystem::addCustomer() {
    try {
        int id;
        std::string name, email, phone;
        
        std::cout << "Enter customer details:" << std::endl;
        std::cout << "ID: ";
        std::cin >> id;
        
        // Check if ID already exists
        if (customerMap.find(id) != customerMap.end()) {
            std::cout << "Error: Customer ID already exists." << std::endl;
            return;
        }
        
        std::cin.ignore();
        std::cout << "Name: ";
        std::getline(std::cin, name);
        std::cout << "Email: ";
        std::getline(std::cin, email);
        std::cout << "Phone: ";
        std::getline(std::cin, phone);
        
        Customer newCustomer(id, name, email, phone);
        customers.push_back(newCustomer);
        customerMap[id] = &customers.back();
        
        std::cout << "Customer added successfully." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error adding customer: " << e.what() << std::endl;
    }
}

void CRMSystem::removeCustomer() {
    try {
        int id;
        std::cout << "Enter customer ID to remove: ";
        std::cin >> id;
        
        auto it = std::find_if(customers.begin(), customers.end(),
                             [id](const Customer& c) { return c.getCustomerId() == id; });
        
        if (it != customers.end()) {
            customers.erase(it);
            customerMap.erase(id);
            std::cout << "Customer removed successfully." << std::endl;
        } else {
            std::cout << "Customer not found." << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error removing customer: " << e.what() << std::endl;
    }
}

void CRMSystem::searchCustomer() {
    try {
        int choice;
        std::cout << "Search by:" << std::endl;
        std::cout << "1. ID" << std::endl;
        std::cout << "2. Name" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        
        switch (choice) {
            case 1: {
                int id;
                std::cout << "Enter customer ID: ";
                std::cin >> id;
                
                auto it = customerMap.find(id);
                if (it != customerMap.end()) {
                    it->second->displayInfo();
                } else {
                    std::cout << "Customer not found." << std::endl;
                }
                break;
            }
            case 2: {
                std::string name;
                std::cout << "Enter customer name: ";
                std::cin.ignore();
                std::getline(std::cin, name);
                
                bool found = false;
                for (const auto& customer : customers) {
                    if (customer.getName().find(name) != std::string::npos) {
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
            default:
                std::cout << "Invalid choice." << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error searching for customer: " << e.what() << std::endl;
    }
}

void CRMSystem::modifyCustomer() {
    try {
        int id;
        std::cout << "Enter customer ID to modify: ";
        std::cin >> id;
        
        auto it = customerMap.find(id);
        if (it != customerMap.end()) {
            Customer* customer = it->second;
            
            int choice;
            std::cout << "What would you like to modify?" << std::endl;
            std::cout << "1. Name" << std::endl;
            std::cout << "2. Email" << std::endl;
            std::cout << "3. Phone" << std::endl;
            std::cout << "Enter your choice: ";
            std::cin >> choice;
            
            std::cin.ignore();
            std::string newValue;
            
            switch (choice) {
                case 1:
                    std::cout << "Enter new name: ";
                    std::getline(std::cin, newValue);
                    customer->setName(newValue);
                    break;
                case 2:
                    std::cout << "Enter new email: ";
                    std::getline(std::cin, newValue);
                    customer->setEmail(newValue);
                    break;
                case 3:
                    std::cout << "Enter new phone: ";
                    std::getline(std::cin, newValue);
                    customer->setPhone(newValue);
                    break;
                default:
                    std::cout << "Invalid choice." << std::endl;
                    return;
            }
            
            std::cout << "Customer updated successfully." << std::endl;
        } else {
            std::cout << "Customer not found." << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error modifying customer: " << e.what() << std::endl;
    }
}

void CRMSystem::displayAllCustomers() {
    if (customers.empty()) {
        std::cout << "No customers to display." << std::endl;
        return;
    }
    
    std::cout << "\n--- All Customers ---" << std::endl;
    for (const auto& customer : customers) {
        customer.displayInfo();
        std::cout << "-------------------" << std::endl;
    }
}

// Transaction operations
void CRMSystem::addTransaction() {
    try {
        int transId, custId;
        std::string date, productName;
        double amount;
        
        std::cout << "Enter transaction details:" << std::endl;
        std::cout << "Transaction ID: ";
        std::cin >> transId;
        std::cout << "Customer ID: ";
        std::cin >> custId;
        
        // Check if customer exists
        auto it = customerMap.find(custId);
        if (it == customerMap.end()) {
            std::cout << "Error: Customer ID not found." << std::endl;
            return;
        }
        
        std::cin.ignore();
        std::cout << "Date (YYYY-MM-DD): ";
        std::getline(std::cin, date);
        std::cout << "Amount: $";
        std::cin >> amount;
        std::cin.ignore();
        std::cout << "Product Name: ";
        std::getline(std::cin, productName);
        
        Transaction transaction(transId, custId, date, amount, productName);
        it->second->addTransaction(transaction);
        
        std::cout << "Transaction added successfully." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error adding transaction: " << e.what() << std::endl;
    }
}

// Search and sort template functions
template<typename T>
void CRMSystem::sortByName(std::vector<T>& items) {
    std::sort(items.begin(), items.end(),
            [](const T& a, const T& b) {
                return a.getName() < b.getName();
            });
}

template<typename T>
std::vector<T> CRMSystem::searchByName(const std::vector<T>& items, const std::string& searchName) {
    std::vector<T> results;
    std::copy_if(items.begin(), items.end(), std::back_inserter(results),
                [&searchName](const T& item) {
                    return item.getName().find(searchName) != std::string::npos;
                });
    return results;
}

// Authentication
bool CRMSystem::login() {
    std::string username, password;
    
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;
    
    // Check employees
    for (auto& employee : employees) {
        if (employee.login(username, password)) {
            currentUser = &employee;
            std::cout << "Logged in as Employee: " << employee.getName() << std::endl;
            return true;
        }
    }
    
    // Check admins
    for (auto& admin : admins) {
        if (admin.login(username, password)) {
            currentUser = &admin;
            std::cout << "Logged in as Admin: " << admin.getName() << std::endl;
            return true;
        }
    }
    
    std::cout << "Invalid username or password." << std::endl;
    return false;
}

void CRMSystem::logout() {
    if (currentUser) {
        currentUser->logout();
        currentUser = nullptr;
    }
}

// Menu functions
void CRMSystem::showMainMenu() {
    if (!currentUser) {
        return;
    }
    
    // Check if admin
    Admin* admin = dynamic_cast<Admin*>(currentUser);
    if (admin) {
        showAdminMenu();
    } else {
        showEmployeeMenu();
    }
}

void CRMSystem::showAdminMenu() {
    Admin* admin = dynamic_cast<Admin*>(currentUser);
    if (!admin) return;
    
    int choice;
    bool running = true;
    
    while (running) {
        std::cout << "\n--- Admin Menu ---" << std::endl;
        std::cout << "1. Manage Customers" << std::endl;
        std::cout << "2. Manage Employees" << std::endl;
        std::cout << "3. Generate Reports" << std::endl;
        std::cout << "4. Add Transaction" << std::endl;
        std::cout << "5. Logout" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        
        switch (choice) {
            case 1: {
                int custChoice;
                std::cout << "\nCustomer Management:" << std::endl;
                std::cout << "1. Add Customer" << std::endl;
                std::cout << "2. Remove Customer" << std::endl;
                std::cout << "3. Search Customer" << std::endl;
                std::cout << "4. Modify Customer" << std::endl;
                std::cout << "5. Display All Customers" << std::endl;
                std::cout << "6. Back" << std::endl;
                std::cout << "Enter your choice: ";
                std::cin >> custChoice;
                
                switch (custChoice) {
                    case 1: addCustomer(); break;
                    case 2: removeCustomer(); break;
                    case 3: searchCustomer(); break;
                    case 4: modifyCustomer(); break;
                    case 5: displayAllCustomers(); break;
                    case 6: break;
                    default: std::cout << "Invalid choice." << std::endl;
                }
                break;
            }
            case 2: {
                int empChoice;
                std::cout << "\nEmployee Management:" << std::endl;
                std::cout << "1. Add Employee" << std::endl;
                std::cout << "2. Remove Employee" << std::endl;
                std::cout << "3. Back" << std::endl;
                std::cout << "Enter your choice: ";
                std::cin >> empChoice;
                
                switch (empChoice) {
                    case 1: admin->addEmployee(employees); break;
                    case 2: admin->removeEmployee(employees); break;
                    case 3: break;
                    default: std::cout << "Invalid choice." << std::endl;
                }
                break;
            }
            case 3:
                admin->generateReports(customers);
                break;
            case 4:
                addTransaction();
                break;
            case 5:
                logout();
                running = false;
                break;
            default:
                std::cout << "Invalid choice." << std::endl;
        }
    }
}

void CRMSystem::showEmployeeMenu() {
    Employee* employee = dynamic_cast<Employee*>(currentUser);
    if (!employee) return;
    
    int choice;
    bool running = true;
    
    while (running) {
        std::cout << "\n--- Employee Menu ---" << std::endl;
        std::cout << "1. Manage Customers" << std::endl;
        std::cout << "2. View Transactions" << std::endl;
        std::cout << "3. Add Transaction" << std::endl;
        std::cout << "4. Logout" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        
        switch (choice) {
            case 1:
                employee->manageCustomers(customers);
                break;
            case 2:
                employee->viewTransactions(customers);
                break;
            case 3:
                addTransaction();
                break;
            case 4:
                logout();
                running = false;
                break;
            default:
                std::cout << "Invalid choice." << std::endl;
        }
    }
}

// Run the system
void CRMSystem::run() {
    loadData();
    
    bool running = true;
    while (running) {
        std::cout << "\n--- CRM System ---" << std::endl;
        std::cout << "1. Login" << std::endl;
        std::cout << "2. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        
        int choice;
        std::cin >> choice;
        
        switch (choice) {
            case 1:
                if (login()) {
                    showMainMenu();
                }
                break;
            case 2:
                saveData();
                running = false;
                std::cout << "Thank you for using the CRM System. Goodbye!" << std::endl;
                break;
            default:
                std::cout << "Invalid choice." << std::endl;
        }
    }
}
