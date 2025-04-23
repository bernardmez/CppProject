#ifndef USER_H
#define USER_H

#include <string>

class User {
private:
    std::string username;
    std::string password;

public:
    // Constructors
    User();
    User(const std::string& username, const std::string& password);
    
    // Getters and Setters
    std::string getUsername() const;
    void setUsername(const std::string& username);
    std::string getPassword() const;
    void setPassword(const std::string& password);
    
    // Methods
    bool login(const std::string& inputUsername, const std::string& inputPassword) const;
    void logout() const;
    virtual void displayInfo() const;
    
    // Destructor
    virtual ~User();
};

#endif // USER_H
