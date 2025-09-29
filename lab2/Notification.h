#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <string>
#include <chrono>

// Перерахування типів повідомлень
enum class NotificationType {
    SUBSCRIPTION_EXPIRY,    // Закінчення підписки
    PAYMENT_REMINDER,       // Нагадування про оплату
    DISCOUNT_OFFER,         // Пропозиція знижки
    REVIEW_REQUEST,         // Запрошення залишити відгук
    SYSTEM_MESSAGE          // Системне повідомлення
};

// Клас для представлення повідомлення
class Notification {
private:
    int notificationId;
    int clientId;
    NotificationType type;
    std::string title;
    std::string message;
    std::chrono::system_clock::time_point createdDate;
    std::chrono::system_clock::time_point sentDate;
    bool isSent;
    bool isRead;

public:
    // Конструктори
    Notification();
    Notification(int notificationId, int clientId, NotificationType type, 
                const std::string& title, const std::string& message);
    
    // Деструктор
    ~Notification();
    
    // Геттери
    int getNotificationId() const;
    int getClientId() const;
    NotificationType getType() const;
    std::string getTitle() const;
    std::string getMessage() const;
    std::string getCreatedDate() const;
    std::string getSentDate() const;
    bool getSentStatus() const;
    bool getReadStatus() const;
    
    // Сеттери
    void setTitle(const std::string& title);
    void setMessage(const std::string& message);
    void setSentStatus(bool status);
    void setReadStatus(bool status);
    
    // Методи для роботи з повідомленням
    void send();
    void markAsRead();
    void displayInfo() const;
    std::string getTypeString() const;
    
    // Статичні методи для створення різних типів повідомлень
    static Notification createExpiryNotification(int notificationId, int clientId, 
                                               const std::string& publicationName, int daysLeft);
    static Notification createPaymentReminder(int notificationId, int clientId, 
                                            double amount, const std::string& deadline);
    static Notification createDiscountOffer(int notificationId, int clientId, 
                                          double discountPercent, const std::string& condition);
    
    // Оператори порівняння
    bool operator==(const Notification& other) const;
    bool operator<(const Notification& other) const;
};

#endif // NOTIFICATION_H