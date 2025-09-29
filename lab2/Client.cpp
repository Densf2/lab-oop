#include "Client.h"
#include <iostream>
#include <regex>
#include <ctime>

// Конструктор за замовчуванням
Client::Client() : clientId(0), firstName(""), lastName(""), email(""), 
                  phone(""), isBlacklisted(false) {
    registrationDate = std::chrono::system_clock::now();
}

// Конструктор з параметрами
Client::Client(int id, const std::string& firstName, const std::string& lastName, 
               const std::string& email, const std::string& phone) 
    : clientId(id), firstName(firstName), lastName(lastName), 
      email(email), phone(phone), isBlacklisted(false) {
    registrationDate = std::chrono::system_clock::now();
}

// Деструктор
Client::~Client() {}

// Геттери
int Client::getClientId() const { 
    return clientId; 
}

std::string Client::getFirstName() const { 
    return firstName; 
}

std::string Client::getLastName() const { 
    return lastName; 
}

std::string Client::getFullName() const { 
    return firstName + " " + lastName; 
}

std::string Client::getEmail() const { 
    return email; 
}

std::string Client::getPhone() const { 
    return phone; 
}

bool Client::getBlacklistStatus() const { 
    return isBlacklisted; 
}

std::string Client::getRegistrationDate() const {
    std::time_t time = std::chrono::system_clock::to_time_t(registrationDate);
    std::string timeStr = std::ctime(&time);
    // Видаляємо символ нового рядка в кінці
    if (!timeStr.empty() && timeStr.back() == '\n') {
        timeStr.pop_back();
    }
    return timeStr;
}

// Сеттери
void Client::setFirstName(const std::string& firstName) {
    this->firstName = firstName;
}

void Client::setLastName(const std::string& lastName) {
    this->lastName = lastName;
}

void Client::setEmail(const std::string& email) {
    if (isValidEmail(email)) {
        this->email = email;
    }
}

void Client::setPhone(const std::string& phone) {
    if (isValidPhone(phone)) {
        this->phone = phone;
    }
}

void Client::setBlacklistStatus(bool status) {
    isBlacklisted = status;
}

// Виведення інформації про клієнта
void Client::displayInfo() const {
    std::cout << "\n=== Інформація про клієнта ===" << std::endl;
    std::cout << "ID: " << clientId << std::endl;
    std::cout << "Ім'я: " << getFullName() << std::endl;
    std::cout << "Email: " << email << std::endl;
    std::cout << "Телефон: " << phone << std::endl;
    std::cout << "Дата реєстрації: " << getRegistrationDate() << std::endl;
    std::cout << "Статус: " << (isBlacklisted ? "В чорному списку" : "Активний") << std::endl;
    std::cout << "==============================" << std::endl;
}

// Перевірка валідності email
bool Client::isValidEmail(const std::string& email) const {
    const std::regex pattern(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
    return std::regex_match(email, pattern);
}

// Перевірка валідності телефону
bool Client::isValidPhone(const std::string& phone) const {
    // Простий шаблон для українського номера телефону
    const std::regex pattern(R"(\+380\d{9}|\d{10})");
    return std::regex_match(phone, pattern);
}

// Оператор рівності
bool Client::operator==(const Client& other) const {
    return clientId == other.clientId;
}

// Оператор порівняння для сортування за прізвищем
bool Client::operator<(const Client& other) const {
    if (lastName != other.lastName) {
        return lastName < other.lastName;
    }
    return firstName < other.firstName;
}