#ifndef ORDER_H
#define ORDER_H

#include <string>
#include <vector>
#include <chrono>
#include "Publication.h"
#include "Client.h"

// Перерахування статусів замовлення
enum class OrderStatus {
    PENDING,      // Очікує оплати
    PAID,         // Оплачено
    EXPIRED,      // Прострочено
    CANCELLED,    // Скасовано
    ACTIVE        // Активна підписка
};

// Клас для представлення замовлення
class Order {
private:
    int orderId;
    int clientId;
    std::vector<int> publicationIds;
    std::vector<int> subscriptionMonths; // Кількість місяців підписки для кожного видання
    double totalAmount;
    double discountPercent;
    double finalAmount;
    OrderStatus status;
    std::chrono::system_clock::time_point orderDate;
    std::chrono::system_clock::time_point paymentDeadline;
    std::chrono::system_clock::time_point subscriptionEndDate;

public:
    // Конструктори
    Order();
    Order(int orderId, int clientId);
    
    // Деструктор
    ~Order();
    
    // Геттери
    int getOrderId() const;
    int getClientId() const;
    std::vector<int> getPublicationIds() const;
    std::vector<int> getSubscriptionMonths() const;
    double getTotalAmount() const;
    double getDiscountPercent() const;
    double getFinalAmount() const;
    OrderStatus getStatus() const;
    std::string getOrderDate() const;
    std::string getPaymentDeadline() const;
    std::string getSubscriptionEndDate() const;
    
    // Сеттери
    void setClientId(int clientId);
    void setStatus(OrderStatus status);
    void setDiscountPercent(double discount);
    
    // Методи для роботи з замовленням
    void addPublication(int publicationId, int months);
    void removePublication(int publicationId);
    void calculateTotal(const std::vector<Publication>& publications);
    void applyDiscount();
    bool processPayment();
    bool isExpired() const;
    void extendSubscription(int months);
    
    // Методи для роботи з датами
    void setPaymentDeadline(int days);
    void updateSubscriptionEndDate();
    int getDaysUntilExpiration() const;
    
    // Метод виведення інформації
    void displayInfo() const;
    std::string getStatusString() const;
    
    // Оператори порівняння
    bool operator==(const Order& other) const;
    bool operator<(const Order& other) const;
};

#endif // ORDER_H