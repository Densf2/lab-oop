#include "Notification.h"
#include <iostream>
#include <ctime>

// Конструктор за замовчуванням
Notification::Notification() : notificationId(0), clientId(0), 
    type(NotificationType::SYSTEM_MESSAGE), title(""), message(""), 
    isSent(false), isRead(false) {
    createdDate = std::chrono::system_clock::now();
}

// Конструктор з параметрами
Notification::Notification(int notificationId, int clientId, NotificationType type, 
                          const std::string& title, const std::string& message)
    : notificationId(notificationId), clientId(clientId), type(type), 
      title(title), message(message), isSent(false), isRead(false) {
    createdDate = std::chrono::system_clock::now();
}

// Деструктор
Notification::~Notification() {}

// Геттери
int Notification::getNotificationId() const { 
    return notificationId; 
}

int Notification::getClientId() const { 
    return clientId; 
}

NotificationType Notification::getType() const { 
    return type; 
}

std::string Notification::getTitle() const { 
    return title; 
}

std::string Notification::getMessage() const { 
    return message; 
}

std::string Notification::getCreatedDate() const {
    std::time_t time = std::chrono::system_clock::to_time_t(createdDate);
    std::string timeStr = std::ctime(&time);
    if (!timeStr.empty() && timeStr.back() == '\n') {
        timeStr.pop_back();
    }
    return timeStr;
}

std::string Notification::getSentDate() const {
    std::time_t time = std::chrono::system_clock::to_time_t(sentDate);
    std::string timeStr = std::ctime(&time);
    if (!timeStr.empty() && timeStr.back() == '\n') {
        timeStr.pop_back();
    }
    return timeStr;
}

bool Notification::getSentStatus() const { 
    return isSent; 
}

bool Notification::getReadStatus() const { 
    return isRead; 
}

// Сеттери
void Notification::setTitle(const std::string& title) {
    this->title = title;
}

void Notification::setMessage(const std::string& message) {
    this->message = message;
}

void Notification::setSentStatus(bool status) {
    isSent = status;
    if (status) {
        sentDate = std::chrono::system_clock::now();
    }
}

void Notification::setReadStatus(bool status) {
    isRead = status;
}

// Надіслати повідомлення
void Notification::send() {
    if (!isSent) {
        setSentStatus(true);
        std::cout << "Повідомлення надіслано клієнту " << clientId << std::endl;
    }
}

// Позначити як прочитане
void Notification::markAsRead() {
    isRead = true;
}

// Виведення інформації про повідомлення
void Notification::displayInfo() const {
    std::cout << "\n=== Повідомлення ===" << std::endl;
    std::cout << "ID: " << notificationId << std::endl;
    std::cout << "Клієнт: " << clientId << std::endl;
    std::cout << "Тип: " << getTypeString() << std::endl;
    std::cout << "Заголовок: " << title << std::endl;
    std::cout << "Повідомлення: " << message << std::endl;
    std::cout << "Створено: " << getCreatedDate() << std::endl;
    if (isSent) {
        std::cout << "Надіслано: " << getSentDate() << std::endl;
    }
    std::cout << "Статус: " << (isRead ? "Прочитано" : "Не прочитано") << std::endl;
    std::cout << "===================" << std::endl;
}

// Отримання рядкового представлення типу
std::string Notification::getTypeString() const {
    switch (type) {
        case NotificationType::SUBSCRIPTION_EXPIRY: return "Закінчення підписки";
        case NotificationType::PAYMENT_REMINDER: return "Нагадування про оплату";
        case NotificationType::DISCOUNT_OFFER: return "Пропозиція знижки";
        case NotificationType::REVIEW_REQUEST: return "Запрошення залишити відгук";
        case NotificationType::SYSTEM_MESSAGE: return "Системне повідомлення";
        default: return "Невідомий тип";
    }
}

// Статичні методи для створення різних типів повідомлень
Notification Notification::createExpiryNotification(int notificationId, int clientId, 
                                                   const std::string& publicationName, int daysLeft) {
    std::string title = "Закінчення підписки";
    std::string message = "Ваша підписка на \"" + publicationName + "\" закінчується через " + 
                         std::to_string(daysLeft) + " днів. Продовжіть підписку вчасно!";
    
    return Notification(notificationId, clientId, NotificationType::SUBSCRIPTION_EXPIRY, title, message);
}

Notification Notification::createPaymentReminder(int notificationId, int clientId, 
                                                double amount, const std::string& deadline) {
    std::string title = "Нагадування про оплату";
    std::string message = "У вас є неоплачене замовлення на суму " + std::to_string(amount) + 
                         " грн. Термін оплати до: " + deadline;
    
    return Notification(notificationId, clientId, NotificationType::PAYMENT_REMINDER, title, message);
}

Notification Notification::createDiscountOffer(int notificationId, int clientId, 
                                              double discountPercent, const std::string& condition) {
    std::string title = "Спеціальна пропозиція!";
    std::string message = "Отримайте знижку " + std::to_string(discountPercent) + 
                         "% при " + condition + ". Скористайтеся пропозицією!";
    
    return Notification(notificationId, clientId, NotificationType::DISCOUNT_OFFER, title, message);
}

// Оператори порівняння
bool Notification::operator==(const Notification& other) const {
    return notificationId == other.notificationId;
}

bool Notification::operator<(const Notification& other) const {
    return createdDate < other.createdDate;
}