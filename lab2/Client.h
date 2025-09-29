#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <vector>
#include <chrono>

// Клас для представлення клієнта системи
class Client {
private:
    int clientId;
    std::string firstName;
    std::string lastName;
    std::string email;
    std::string phone;
    bool isBlacklisted;
    std::chrono::system_clock::time_point registrationDate;

public:
    // Конструктори
    Client();
    Client(int id, const std::string& firstName, const std::string& lastName, 
           const std::string& email, const std::string& phone);
    
    // Деструктор
    ~Client();
    
    // Геттери
    int getClientId() const;
    std::string getFirstName() const;
    std::string getLastName() const;
    std::string getFullName() const;
    std::string getEmail() const;
    std::string getPhone() const;
    bool getBlacklistStatus() const;
    std::string getRegistrationDate() const;
    
    // Сеттери
    void setFirstName(const std::string& firstName);
    void setLastName(const std::string& lastName);
    void setEmail(const std::string& email);
    void setPhone(const std::string& phone);
    void setBlacklistStatus(bool status);
    
    // Методи для роботи з клієнтом
    void displayInfo() const;
    bool isValidEmail(const std::string& email) const;
    bool isValidPhone(const std::string& phone) const;
    
    // Оператори порівняння
    bool operator==(const Client& other) const;
    bool operator<(const Client& other) const;
};

#endif // CLIENT_H