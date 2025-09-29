#include "Order.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <ctime>

// Конструктор за замовчуванням
Order::Order() : orderId(0), clientId(0), totalAmount(0.0), discountPercent(0.0), 
                finalAmount(0.0), status(OrderStatus::PENDING) {
    orderDate = std::chrono::system_clock::now();
    setPaymentDeadline(7); // 7 днів на оплату за замовчуванням
}

// Конструктор з параметрами
Order::Order(int orderId, int clientId) : orderId(orderId), clientId(clientId), 
    totalAmount(0.0), discountPercent(0.0), finalAmount(0.0), status(OrderStatus::PENDING) {
    orderDate = std::chrono::system_clock::now();
    setPaymentDeadline(7);
}

// Деструктор
Order::~Order() {}

// Геттери
int Order::getOrderId() const { 
    return orderId; 
}

int Order::getClientId() const { 
    return clientId; 
}

std::vector<int> Order::getPublicationIds() const { 
    return publicationIds; 
}

std::vector<int> Order::getSubscriptionMonths() const { 
    return subscriptionMonths; 
}

double Order::getTotalAmount() const { 
    return totalAmount; 
}

double Order::getDiscountPercent() const { 
    return discountPercent; 
}

double Order::getFinalAmount() const { 
    return finalAmount; 
}

OrderStatus Order::getStatus() const { 
    return status; 
}

std::string Order::getOrderDate() const {
    std::time_t time = std::chrono::system_clock::to_time_t(orderDate);
    std::string timeStr = std::ctime(&time);
    if (!timeStr.empty() && timeStr.back() == '\n') {
        timeStr.pop_back();
    }
    return timeStr;
}

std::string Order::getPaymentDeadline() const {
    std::time_t time = std::chrono::system_clock::to_time_t(paymentDeadline);
    std::string timeStr = std::ctime(&time);
    if (!timeStr.empty() && timeStr.back() == '\n') {
        timeStr.pop_back();
    }
    return timeStr;
}

std::string Order::getSubscriptionEndDate() const {
    std::time_t time = std::chrono::system_clock::to_time_t(subscriptionEndDate);
    std::string timeStr = std::ctime(&time);
    if (!timeStr.empty() && timeStr.back() == '\n') {
        timeStr.pop_back();
    }
    return timeStr;
}

// Сеттери
void Order::setClientId(int clientId) {
    this->clientId = clientId;
}

void Order::setStatus(OrderStatus status) {
    this->status = status;
}

void Order::setDiscountPercent(double discount) {
    if (discount >= 0 && discount <= 100) {
        this->discountPercent = discount;
    }
}

// Додавання видання до замовлення
void Order::addPublication(int publicationId, int months) {
    if (months > 0) {
        publicationIds.push_back(publicationId);
        subscriptionMonths.push_back(months);
    }
}

// Видалення видання з замовлення
void Order::removePublication(int publicationId) {
    auto it = std::find(publicationIds.begin(), publicationIds.end(), publicationId);
    if (it != publicationIds.end()) {
        int index = std::distance(publicationIds.begin(), it);
        publicationIds.erase(it);
        subscriptionMonths.erase(subscriptionMonths.begin() + index);
    }
}

// Розрахунок загальної суми
void Order::calculateTotal(const std::vector<Publication>& publications) {
    totalAmount = 0.0;
    
    for (size_t i = 0; i < publicationIds.size(); ++i) {
        int pubId = publicationIds[i];
        int months = subscriptionMonths[i];
        
        // Знаходимо видання за ID
        for (const auto& pub : publications) {
            if (pub.getId() == pubId) {
                totalAmount += pub.getPrice() * months;
                break;
            }
        }
    }
    
    // Застосовуємо знижку
    finalAmount = totalAmount * (1.0 - discountPercent / 100.0);
}

// Застосування знижки
void Order::applyDiscount() {
    finalAmount = totalAmount * (1.0 - discountPercent / 100.0);
}

// Обробка платежу
bool Order::processPayment() {
    if (status == OrderStatus::PENDING && !isExpired()) {
        status = OrderStatus::PAID;
        updateSubscriptionEndDate();
        return true;
    }
    return false;
}

// Перевірка чи прострочене замовлення
bool Order::isExpired() const {
    auto now = std::chrono::system_clock::now();
    return now > paymentDeadline && status == OrderStatus::PENDING;
}

// Продовження підписки
void Order::extendSubscription(int months) {
    if (status == OrderStatus::ACTIVE && months > 0) {
        auto duration = std::chrono::hours(24 * 30 * months); // Приблизно місяці
        subscriptionEndDate += duration;
    }
}

// Встановлення терміну оплати
void Order::setPaymentDeadline(int days) {
    auto duration = std::chrono::hours(24 * days);
    paymentDeadline = orderDate + duration;
}

// Оновлення дати закінчення підписки
void Order::updateSubscriptionEndDate() {
    if (!subscriptionMonths.empty()) {
        int maxMonths = *std::max_element(subscriptionMonths.begin(), subscriptionMonths.end());
        auto duration = std::chrono::hours(24 * 30 * maxMonths);
        subscriptionEndDate = std::chrono::system_clock::now() + duration;
        status = OrderStatus::ACTIVE;
    }
}

// Кількість днів до закінчення підписки
int Order::getDaysUntilExpiration() const {
    auto now = std::chrono::system_clock::now();
    if (subscriptionEndDate > now) {
        auto duration = subscriptionEndDate - now;
        return std::chrono::duration_cast<std::chrono::hours>(duration).count() / 24;
    }
    return 0;
}

// Виведення інформації про замовлення
void Order::displayInfo() const {
    std::cout << "\n=== Інформація про замовлення ===" << std::endl;
    std::cout << "ID замовлення: " << orderId << std::endl;
    std::cout << "ID клієнта: " << clientId << std::endl;
    std::cout << "Дата замовлення: " << getOrderDate() << std::endl;
    std::cout << "Статус: " << getStatusString() << std::endl;
    
    std::cout << "Видання (ID:місяці): ";
    for (size_t i = 0; i < publicationIds.size(); ++i) {
        std::cout << publicationIds[i] << ":" << subscriptionMonths[i];
        if (i < publicationIds.size() - 1) std::cout << ", ";
    }
    std::cout << std::endl;
    
    std::cout << "Загальна сума: " << std::fixed << std::setprecision(2) << totalAmount << " грн" << std::endl;
    if (discountPercent > 0) {
        std::cout << "Знижка: " << discountPercent << "%" << std::endl;
    }
    std::cout << "До сплати: " << std::fixed << std::setprecision(2) << finalAmount << " грн" << std::endl;
    
    if (status == OrderStatus::PENDING) {
        std::cout << "Термін оплати до: " << getPaymentDeadline() << std::endl;
    } else if (status == OrderStatus::ACTIVE) {
        std::cout << "Підписка діє до: " << getSubscriptionEndDate() << std::endl;
        std::cout << "Днів залишилося: " << getDaysUntilExpiration() << std::endl;
    }
    std::cout << "=================================" << std::endl;
}

// Отримання рядкового представлення статусу
std::string Order::getStatusString() const {
    switch (status) {
        case OrderStatus::PENDING: return "Очікує оплати";
        case OrderStatus::PAID: return "Оплачено";
        case OrderStatus::EXPIRED: return "Прострочено";
        case OrderStatus::CANCELLED: return "Скасовано";
        case OrderStatus::ACTIVE: return "Активна підписка";
        default: return "Невідомий статус";
    }
}

// Оператори порівняння
bool Order::operator==(const Order& other) const {
    return orderId == other.orderId;
}

bool Order::operator<(const Order& other) const {
    return orderDate < other.orderDate;
}