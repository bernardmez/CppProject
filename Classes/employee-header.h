#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
#include <vector>
#include "User.h"
#include "Customer.h"
#include "Transaction.h"

class Employee : public User {
private:
    int employeeId;
    std::string name;
    std::string position;

public:
    // Constructors
    Employee();
    Employee(const std::string& username, const std::string& password,
             int id, const std::string& name, const std::string& position);
    
    // Getters and Setters
    int getEmployeeId() const;
    void setEmployeeId(int id);
    std::string getName() const;
    void setName(const std::string& name);
    std::string getPosition() const;
    void setPosition(const std::string& position);
    
    // Methods
    virtual void displayInfo() const override;
    void manageCustomers(std::vector<Customer>& customers);
    void viewTransactions(const std::vector<Customer>& customers);
    
    // Destructor
    virtual ~Employee();
};

#endif // EMPLOYEE_H
