#include "PublicationSystem.h"
#include <iostream>
#include <algorithm>

// Конструктор
PublicationSystem::PublicationSystem() 
    : nextPublicationId(1), nextClientId(1), nextOrderId(1), 
      nextReviewId(1), nextNotificationId(1),
      paymentDeadlineDays(7), reminderDaysBefore(3),
      multipleDiscountRate(10.0), longTermDiscountRate(15.0), longTermMonths(12) {
    std::cout << "Система періодичних видань ініціалізована." << std::endl;
}

// Деструктор
PublicationSystem::~PublicationSystem() {
    std::cout << "Система завершує роботу." << std::endl;
}

// Методи для роботи з виданнями
int PublicationSystem::addPublication(const std::string& title, const std::string& description, 
                                     double price, const std::string& category) {
    Publication pub(nextPublicationId, title, description, price, category);
    publications.push_back(pub);
    return nextPublicationId++;
}

bool PublicationSystem::removePublication(int publicationId) {
    auto it = std::find_if(publications.begin(), publications.end(),
        [publicationId](const Publication& p) { return p.getId() == publicationId; });
    
    if (it != publications.end()) {
        publications.erase(it);
        return true;
    }
    return false;
}

Publication* PublicationSystem::findPublication(int publicationId) {
    auto it = std::find_if(publications.begin(), publications.end(),
        [publicationId](const Publication& p) { return p.getId() == publicationId; });
    
    return (it != publications.end()) ? &(*it) : nullptr;
}

std::vector<Publication> PublicationSystem::getPublicationsByCategory(const std::string& category) {
    std::vector<Publication> result;
    for (const auto& pub : publications) {
        if (pub.getCategory() == category) {
            result.push_back(pub);
        }
    }
    return result;
}

std::vector<Publication> PublicationSystem::searchPublications(const std::string& keyword) {
    std::vector<Publication> result;
    for (const auto& pub : publications) {
        if (pub.getTitle().find(keyword) != std::string::npos ||
            pub.getDescription().find(keyword) != std::string::npos) {
            result.push_back(pub);
        }
    }
    return result;
}

void PublicationSystem::displayAllPublications() const {
    if (publications.empty()) {
        std::cout << "Видань немає!" << std::endl;
        return;
    }
    
    std::cout << "\n=== ВСІ ПЕРІОДИЧНІ ВИДАННЯ ===" << std::endl;
    for (const auto& pub : publications) {
        pub.displayInfo();
    }
}

// Методи для роботи з клієнтами
int PublicationSystem::addClient(const std::string& firstName, const std::string& lastName, 
                                const std::string& email, const std::string& phone) {
    Client client(nextClientId, firstName, lastName, email, phone);
    clients.push_back(client);
    return nextClientId++;
}

bool PublicationSystem::removeClient(int clientId) {
    auto it = std::find_if(clients.begin(), clients.end(),
        [clientId](const Client& c) { return c.getClientId() == clientId; });
    
    if (it != clients.end()) {
        clients.erase(it);
        return true;
    }
    return false;
}

Client* PublicationSystem::findClient(int clientId) {
    auto it = std::find_if(clients.begin(), clients.end(),
        [clientId](const Client& c) { return c.getClientId() == clientId; });
    
    return (it != clients.end()) ? &(*it) : nullptr;
}

Client* PublicationSystem::findClientByEmail(const std::string& email) {
    auto it = std::find_if(clients.begin(), clients.end(),
        [&email](const Client& c) { return c.getEmail() == email; });
    
    return (it != clients.end()) ? &(*it) : nullptr;
}

void PublicationSystem::addToBlacklist(int clientId) {
    Client* client = findClient(clientId);
    if (client) {
        client->setBlacklistStatus(true);
    }
}

void PublicationSystem::removeFromBlacklist(int clientId) {
    Client* client = findClient(clientId);
    if (client) {
        client->setBlacklistStatus(false);
    }
}

std::vector<Client> PublicationSystem::getBlacklistedClients() {
    std::vector<Client> result;
    for (const auto& client : clients) {
        if (client.getBlacklistStatus()) {
            result.push_back(client);
        }
    }
    return result;
}

void PublicationSystem::displayAllClients() const {
    if (clients.empty()) {
        std::cout << "Клієнтів немає!" << std::endl;
        return;
    }
    
    std::cout << "\n=== ВСІ КЛІЄНТИ ===" << std::endl;
    for (const auto& client : clients) {
        client.displayInfo();
    }
}

// Методи для роботи з замовленнями
int PublicationSystem::createOrder(int clientId) {
    if (findClient(clientId)) {
        Order order(nextOrderId, clientId);
        orders.push_back(order);
        return nextOrderId++;
    }
    return 0;
}

bool PublicationSystem::addPublicationToOrder(int orderId, int publicationId, int months) {
    auto it = std::find_if(orders.begin(), orders.end(),
        [orderId](const Order& o) { return o.getOrderId() == orderId; });
    
    if (it != orders.end() && findPublication(publicationId)) {
        it->addPublication(publicationId, months);
        it->calculateTotal(publications);
        it->applyDiscount();
        return true;
    }
    return false;
}

bool PublicationSystem::processOrderPayment(int orderId) {
    auto it = std::find_if(orders.begin(), orders.end(),
        [orderId](Order& o) { return o.getOrderId() == orderId; });
    
    if (it != orders.end()) {
        return it->processPayment();
    }
    return false;
}

bool PublicationSystem::cancelOrder(int orderId) {
    auto it = std::find_if(orders.begin(), orders.end(),
        [orderId](Order& o) { return o.getOrderId() == orderId; });
    
    if (it != orders.end()) {
        it->setStatus(OrderStatus::CANCELLED);
        return true;
    }
    return false;
}

std::vector<Order> PublicationSystem::getClientOrders(int clientId) {
    std::vector<Order> result;
    for (const auto& order : orders) {
        if (order.getClientId() == clientId) {
            result.push_back(order);
        }
    }
    return result;
}

std::vector<Order> PublicationSystem::getExpiredOrders() {
    std::vector<Order> result;
    for (const auto& order : orders) {
        if (order.isExpired()) {
            result.push_back(order);
        }
    }
    return result;
}

void PublicationSystem::displayAllOrders() const {
    if (orders.empty()) {
        std::cout << "Замовлень немає!" << std::endl;
        return;
    }
    
    std::cout << "\n=== ВСІ ЗАМОВЛЕННЯ ===" << std::endl;
    for (const auto& order : orders) {
        order.displayInfo();
    }
}

// Спрощені реалізації інших методів
int PublicationSystem::addReview(int clientId, int publicationId, int rating, const std::string& comment) {
    // Спрощена реалізація - просто повертаємо ID
    (void)clientId; (void)publicationId; (void)rating; (void)comment;
    return nextReviewId++;
}

std::vector<Review> PublicationSystem::getPublicationReviews(int publicationId) {
    (void)publicationId;
    return std::vector<Review>(); // Повертаємо порожній вектор
}

std::vector<Notification> PublicationSystem::getClientNotifications(int clientId) {
    (void)clientId;
    return std::vector<Notification>(); // Повертаємо порожній вектор
}

void PublicationSystem::sendExpiryNotifications() {
    std::cout << "Нагадування про закінчення підписки надіслано." << std::endl;
}

void PublicationSystem::sendPaymentReminders() {
    std::cout << "Нагадування про оплату надіслано." << std::endl;
}

void PublicationSystem::processExpiredOrders() {
    for (auto& order : orders) {
        if (order.isExpired() && order.getStatus() == OrderStatus::PENDING) {
            order.setStatus(OrderStatus::EXPIRED);
            // Додаємо клієнта до чорного списку
            addToBlacklist(order.getClientId());
        }
    }
}

void PublicationSystem::generateSystemReport() {
    std::cout << "\n=== ЗВІТ СИСТЕМИ ===" << std::endl;
    std::cout << "Загальна кількість видань: " << publications.size() << std::endl;
    std::cout << "Загальна кількість клієнтів: " << clients.size() << std::endl;
    std::cout << "Загальна кількість замовлень: " << orders.size() << std::endl;
    
    int activeOrders = 0, expiredOrders = 0;
    for (const auto& order : orders) {
        if (order.getStatus() == OrderStatus::ACTIVE) activeOrders++;
        if (order.getStatus() == OrderStatus::EXPIRED) expiredOrders++;
    }
    
    std::cout << "Активні підписки: " << activeOrders << std::endl;
    std::cout << "Прострочені замовлення: " << expiredOrders << std::endl;
    std::cout << "Клієнтів у чорному списку: " << getBlacklistedClients().size() << std::endl;
    std::cout << "===================" << std::endl;
}

void PublicationSystem::initializeTestData() {
    // Додаємо тестові видання
    addPublication("Наука і життя", "Популярний науковий журнал", 150.0, "Наука");
    addPublication("Комп'ютерне обозрення", "Журнал про IT технології", 120.0, "Технології");
    addPublication("Здоров'я", "Медичний журнал", 100.0, "Медицина");
    addPublication("Автосвіт", "Журнал для автолюбителів", 180.0, "Автомобілі");
    addPublication("Кулінарія", "Журнал рецептів", 90.0, "Кулінарія");
    
    // Додаємо тестових клієнтів
    addClient("Іван", "Петренко", "ivan.petrenko@example.com", "+380671234567");
    addClient("Марія", "Коваленко", "maria.kovalenko@example.com", "+380672345678");
    addClient("Олексій", "Сидоренко", "oleksiy.sidorenko@example.com", "+380673456789");
    
    std::cout << "Тестові дані успішно додано!" << std::endl;
}