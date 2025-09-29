#ifndef PUBLICATION_SYSTEM_H
#define PUBLICATION_SYSTEM_H

#include <vector>
#include <map>
#include <string>
#include <memory>
#include "Publication.h"
#include "Client.h"
#include "Order.h"
#include "Review.h"
#include "Notification.h"

// Основний клас системи управління періодичними виданнями
class PublicationSystem {
private:
    std::vector<Publication> publications;
    std::vector<Client> clients;
    std::vector<Order> orders;
    std::vector<Review> reviews;
    std::vector<Notification> notifications;
    
    // Лічильники для генерації ID
    int nextPublicationId;
    int nextClientId;
    int nextOrderId;
    int nextReviewId;
    int nextNotificationId;
    
    // Налаштування системи
    int paymentDeadlineDays;      // Дні до прострочення платежу
    int reminderDaysBefore;       // За скільки днів нагадувати про закінчення
    double multipleDiscountRate;  // Знижка за кілька видань
    double longTermDiscountRate;  // Знижка за довгострокову підписку
    int longTermMonths;           // Мінімальна кількість місяців для довгострокової підписки

public:
    // Конструктор і деструктор
    PublicationSystem();
    ~PublicationSystem();
    
    // Методи для роботи з виданнями
    int addPublication(const std::string& title, const std::string& description, 
                      double price, const std::string& category);
    bool removePublication(int publicationId);
    Publication* findPublication(int publicationId);
    std::vector<Publication> getPublicationsByCategory(const std::string& category);
    std::vector<Publication> searchPublications(const std::string& keyword);
    void displayAllPublications() const;
    
    // Методи для роботи з клієнтами
    int addClient(const std::string& firstName, const std::string& lastName, 
                 const std::string& email, const std::string& phone);
    bool removeClient(int clientId);
    Client* findClient(int clientId);
    Client* findClientByEmail(const std::string& email);
    void addToBlacklist(int clientId);
    void removeFromBlacklist(int clientId);
    std::vector<Client> getBlacklistedClients();
    void displayAllClients() const;
    
    // Методи для роботи з замовленнями
    int createOrder(int clientId);
    bool addPublicationToOrder(int orderId, int publicationId, int months);
    bool removePublicationFromOrder(int orderId, int publicationId);
    bool processOrderPayment(int orderId);
    bool cancelOrder(int orderId);
    Order* findOrder(int orderId);
    std::vector<Order> getClientOrders(int clientId);
    std::vector<Order> getExpiredOrders();
    void displayAllOrders() const;
    
    // Методи для роботи з відгуками
    int addReview(int clientId, int publicationId, int rating, const std::string& comment);
    bool removeReview(int reviewId);
    bool moderateReview(int reviewId, bool approve);
    std::vector<Review> getPublicationReviews(int publicationId);
    std::vector<Review> getClientReviews(int clientId);
    void updatePublicationRating(int publicationId);
    void displayAllReviews() const;
    
    // Методи для роботи з повідомленнями
    void sendExpiryNotifications();
    void sendPaymentReminders();
    void sendDiscountOffers(int clientId);
    void markNotificationAsRead(int notificationId);
    std::vector<Notification> getClientNotifications(int clientId);
    void displayAllNotifications() const;
    
    // Методи для роботи зі знижками
    double calculateDiscount(const Order& order);
    void applyDiscount(int orderId);
    
    // Методи адміністрування
    void processExpiredOrders();
    void generateSystemReport();
    void cleanupOldNotifications(int daysOld);
    
    // Методи налаштування системи
    void setPaymentDeadline(int days);
    void setReminderDays(int days);
    void setDiscountRates(double multipleRate, double longTermRate);
    void setLongTermMonths(int months);
    
    // Допоміжні методи
    void initializeTestData();
    void saveToFile(const std::string& filename);
    void loadFromFile(const std::string& filename);
    
    // Статистичні методи
    int getTotalPublications() const;
    int getTotalClients() const;
    int getTotalOrders() const;
    int getTotalReviews() const;
    double getTotalRevenue() const;
    Publication getMostPopularPublication() const;
};

#endif // PUBLICATION_SYSTEM_H