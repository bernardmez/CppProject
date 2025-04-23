#ifndef ADMIN_H
#define ADMIN_H

#include <vector>
#include "Employee.h"

class Admin : public Employee {
public:
    // Constructors
    Admin();
    Admin(const std::string& username, const std::string& password,
          int id, const std::string& name);
    
    // Admin-specific methods
    void addEmployee(std::vector<Employee>& employees);
    void removeEmployee(std::vector<Employee>& employees);
    void generateReports(const std::vector<Customer>& customers);
    
    // Override methods
    virtual void displayInfo() const override;
    
    // Destructor
    virtual ~Admin();
};

#endif // ADMIN_H
