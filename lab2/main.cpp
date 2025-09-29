#include <iostream>
#include <string>
#include <limits>
#include "PublicationSystem.h"

using namespace std;

// Функція для очищення буферу вводу
void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Функція для безпечного вводу цілого числа
int getIntInput() {
    int value;
    while (!(cin >> value)) {
        cout << "Помилка! Введіть коректне число: ";
        clearInputBuffer();
    }
    clearInputBuffer();
    return value;
}

// Функція для безпечного вводу числа з плаваючою комою
double getDoubleInput() {
    double value;
    while (!(cin >> value)) {
        cout << "Помилка! Введіть коректне число: ";
        clearInputBuffer();
    }
    clearInputBuffer();
    return value;
}

// Функція для вводу рядка
string getStringInput() {
    string input;
    getline(cin, input);
    return input;
}

// Меню для роботи з виданнями
void publicationMenu(PublicationSystem& system) {
    int choice;
    do {
        cout << "\n=== МЕНЮ ВИДАНЬ ===" << endl;
        cout << "1. Додати видання" << endl;
        cout << "2. Переглянути всі видання" << endl;
        cout << "3. Знайти видання за ID" << endl;
        cout << "4. Пошук видань за категорією" << endl;
        cout << "5. Пошук видань за ключовим словом" << endl;
        cout << "6. Видалити видання" << endl;
        cout << "0. Повернутися до головного меню" << endl;
        cout << "Ваш вибір: ";
        choice = getIntInput();
        
        switch (choice) {
            case 1: {
                cout << "Введіть назву видання: ";
                string title = getStringInput();
                cout << "Введіть опис: ";
                string description = getStringInput();
                cout << "Введіть ціну за місяць: ";
                double price = getDoubleInput();
                cout << "Введіть категорію: ";
                string category = getStringInput();
                
                int id = system.addPublication(title, description, price, category);
                cout << "Видання додано з ID: " << id << endl;
                break;
            }
            case 2:
                system.displayAllPublications();
                break;
            case 3: {
                cout << "Введіть ID видання: ";
                int id = getIntInput();
                Publication* pub = system.findPublication(id);
                if (pub) {
                    pub->displayInfo();
                } else {
                    cout << "Видання з таким ID не знайдено!" << endl;
                }
                break;
            }
            case 4: {
                cout << "Введіть категорію: ";
                string category = getStringInput();
                vector<Publication> pubs = system.getPublicationsByCategory(category);
                if (pubs.empty()) {
                    cout << "Видань у цій категорії не знайдено!" << endl;
                } else {
                    for (const auto& pub : pubs) {
                        pub.displayInfo();
                    }
                }
                break;
            }
            case 5: {
                cout << "Введіть ключове слово: ";
                string keyword = getStringInput();
                vector<Publication> pubs = system.searchPublications(keyword);
                if (pubs.empty()) {
                    cout << "Видань за цим запитом не знайдено!" << endl;
                } else {
                    for (const auto& pub : pubs) {
                        pub.displayInfo();
                    }
                }
                break;
            }
            case 6: {
                cout << "Введіть ID видання для видалення: ";
                int id = getIntInput();
                if (system.removePublication(id)) {
                    cout << "Видання успішно видалено!" << endl;
                } else {
                    cout << "Не вдалося видалити видання!" << endl;
                }
                break;
            }
            case 0:
                break;
            default:
                cout << "Невірний вибір!" << endl;
        }
    } while (choice != 0);
}

// Меню для роботи з клієнтами
void clientMenu(PublicationSystem& system) {
    int choice;
    do {
        cout << "\n=== МЕНЮ КЛІЄНТІВ ===" << endl;
        cout << "1. Додати клієнта" << endl;
        cout << "2. Переглянути всіх клієнтів" << endl;
        cout << "3. Знайти клієнта за ID" << endl;
        cout << "4. Знайти клієнта за email" << endl;
        cout << "5. Додати клієнта до чорного списку" << endl;
        cout << "6. Видалити клієнта з чорного списку" << endl;
        cout << "7. Переглянути чорний список" << endl;
        cout << "8. Видалити клієнта" << endl;
        cout << "0. Повернутися до головного меню" << endl;
        cout << "Ваш вибір: ";
        choice = getIntInput();
        
        switch (choice) {
            case 1: {
                cout << "Введіть ім'я: ";
                string firstName = getStringInput();
                cout << "Введіть прізвище: ";
                string lastName = getStringInput();
                cout << "Введіть email: ";
                string email = getStringInput();
                cout << "Введіть телефон: ";
                string phone = getStringInput();
                
                int id = system.addClient(firstName, lastName, email, phone);
                cout << "Клієнта додано з ID: " << id << endl;
                break;
            }
            case 2:
                system.displayAllClients();
                break;
            case 3: {
                cout << "Введіть ID клієнта: ";
                int id = getIntInput();
                Client* client = system.findClient(id);
                if (client) {
                    client->displayInfo();
                } else {
                    cout << "Клієнта з таким ID не знайдено!" << endl;
                }
                break;
            }
            case 4: {
                cout << "Введіть email: ";
                string email = getStringInput();
                Client* client = system.findClientByEmail(email);
                if (client) {
                    client->displayInfo();
                } else {
                    cout << "Клієнта з таким email не знайдено!" << endl;
                }
                break;
            }
            case 5: {
                cout << "Введіть ID клієнта: ";
                int id = getIntInput();
                system.addToBlacklist(id);
                cout << "Клієнта додано до чорного списку!" << endl;
                break;
            }
            case 6: {
                cout << "Введіть ID клієнта: ";
                int id = getIntInput();
                system.removeFromBlacklist(id);
                cout << "Клієнта видалено з чорного списку!" << endl;
                break;
            }
            case 7: {
                vector<Client> blacklisted = system.getBlacklistedClients();
                if (blacklisted.empty()) {
                    cout << "Чорний список порожній!" << endl;
                } else {
                    for (const auto& client : blacklisted) {
                        client.displayInfo();
                    }
                }
                break;
            }
            case 8: {
                cout << "Введіть ID клієнта для видалення: ";
                int id = getIntInput();
                if (system.removeClient(id)) {
                    cout << "Клієнта успішно видалено!" << endl;
                } else {
                    cout << "Не вдалося видалити клієнта!" << endl;
                }
                break;
            }
            case 0:
                break;
            default:
                cout << "Невірний вибір!" << endl;
        }
    } while (choice != 0);
}

// Меню для роботи з замовленнями
void orderMenu(PublicationSystem& system) {
    int choice;
    do {
        cout << "\n=== МЕНЮ ЗАМОВЛЕНЬ ===" << endl;
        cout << "1. Створити замовлення" << endl;
        cout << "2. Додати видання до замовлення" << endl;
        cout << "3. Оплатити замовлення" << endl;
        cout << "4. Переглянути замовлення клієнта" << endl;
        cout << "5. Переглянути всі замовлення" << endl;
        cout << "6. Переглянути прострочені замовлення" << endl;
        cout << "7. Скасувати замовлення" << endl;
        cout << "8. Обробити прострочені замовлення" << endl;
        cout << "0. Повернутися до головного меню" << endl;
        cout << "Ваш вибір: ";
        choice = getIntInput();
        
        switch (choice) {
            case 1: {
                cout << "Введіть ID клієнта: ";
                int clientId = getIntInput();
                int orderId = system.createOrder(clientId);
                if (orderId > 0) {
                    cout << "Замовлення створено з ID: " << orderId << endl;
                } else {
                    cout << "Не вдалося створити замовлення!" << endl;
                }
                break;
            }
            case 2: {
                cout << "Введіть ID замовлення: ";
                int orderId = getIntInput();
                cout << "Введіть ID видання: ";
                int pubId = getIntInput();
                cout << "Введіть кількість місяців підписки: ";
                int months = getIntInput();
                
                if (system.addPublicationToOrder(orderId, pubId, months)) {
                    cout << "Видання додано до замовлення!" << endl;
                } else {
                    cout << "Не вдалося додати видання до замовлення!" << endl;
                }
                break;
            }
            case 3: {
                cout << "Введіть ID замовлення для оплати: ";
                int orderId = getIntInput();
                if (system.processOrderPayment(orderId)) {
                    cout << "Замовлення успішно оплачено!" << endl;
                } else {
                    cout << "Не вдалося оплатити замовлення!" << endl;
                }
                break;
            }
            case 4: {
                cout << "Введіть ID клієнта: ";
                int clientId = getIntInput();
                vector<Order> orders = system.getClientOrders(clientId);
                if (orders.empty()) {
                    cout << "У клієнта немає замовлень!" << endl;
                } else {
                    for (const auto& order : orders) {
                        order.displayInfo();
                    }
                }
                break;
            }
            case 5:
                system.displayAllOrders();
                break;
            case 6: {
                vector<Order> expired = system.getExpiredOrders();
                if (expired.empty()) {
                    cout << "Прострочених замовлень немає!" << endl;
                } else {
                    for (const auto& order : expired) {
                        order.displayInfo();
                    }
                }
                break;
            }
            case 7: {
                cout << "Введіть ID замовлення для скасування: ";
                int orderId = getIntInput();
                if (system.cancelOrder(orderId)) {
                    cout << "Замовлення успішно скасовано!" << endl;
                } else {
                    cout << "Не вдалося скасувати замовлення!" << endl;
                }
                break;
            }
            case 8:
                system.processExpiredOrders();
                cout << "Прострочені замовлення оброблено!" << endl;
                break;
            case 0:
                break;
            default:
                cout << "Невірний вибір!" << endl;
        }
    } while (choice != 0);
}

// Головне меню
void mainMenu(PublicationSystem& system) {
    int choice;
    do {
        cout << "\n========================================" << endl;
        cout << "    СИСТЕМА ПЕРІОДИЧНИХ ВИДАНЬ" << endl;
        cout << "========================================" << endl;
        cout << "1. Управління виданнями" << endl;
        cout << "2. Управління клієнтами" << endl;
        cout << "3. Управління замовленнями" << endl;
        cout << "4. Додати відгук на видання" << endl;
        cout << "5. Переглянути відгуки видання" << endl;
        cout << "6. Надіслати нагадування про підписку" << endl;
        cout << "7. Переглянути повідомлення клієнта" << endl;
        cout << "8. Згенерувати звіт системи" << endl;
        cout << "9. Ініціалізувати тестові дані" << endl;
        cout << "0. Вихід" << endl;
        cout << "========================================" << endl;
        cout << "Ваш вибір: ";
        choice = getIntInput();
        
        switch (choice) {
            case 1:
                publicationMenu(system);
                break;
            case 2:
                clientMenu(system);
                break;
            case 3:
                orderMenu(system);
                break;
            case 4: {
                cout << "Введіть ID клієнта: ";
                int clientId = getIntInput();
                cout << "Введіть ID видання: ";
                int pubId = getIntInput();
                cout << "Введіть оцінку (1-5): ";
                int rating = getIntInput();
                cout << "Введіть коментар: ";
                string comment = getStringInput();
                
                int reviewId = system.addReview(clientId, pubId, rating, comment);
                if (reviewId > 0) {
                    cout << "Відгук додано з ID: " << reviewId << endl;
                } else {
                    cout << "Не вдалося додати відгук!" << endl;
                }
                break;
            }
            case 5: {
                cout << "Введіть ID видання: ";
                int pubId = getIntInput();
                vector<Review> reviews = system.getPublicationReviews(pubId);
                if (reviews.empty()) {
                    cout << "Відгуків для цього видання немає!" << endl;
                } else {
                    for (const auto& review : reviews) {
                        review.displayInfo();
                    }
                }
                break;
            }
            case 6:
                system.sendExpiryNotifications();
                system.sendPaymentReminders();
                cout << "Нагадування надіслано!" << endl;
                break;
            case 7: {
                cout << "Введіть ID клієнта: ";
                int clientId = getIntInput();
                vector<Notification> notifications = system.getClientNotifications(clientId);
                if (notifications.empty()) {
                    cout << "Повідомлень для клієнта немає!" << endl;
                } else {
                    for (const auto& notification : notifications) {
                        notification.displayInfo();
                    }
                }
                break;
            }
            case 8:
                system.generateSystemReport();
                break;
            case 9:
                system.initializeTestData();
                cout << "Тестові дані ініціалізовано!" << endl;
                break;
            case 0:
                cout << "До побачення!" << endl;
                break;
            default:
                cout << "Невірний вибір! Спробуйте ще раз." << endl;
        }
    } while (choice != 0);
}

int main() {
    cout << "Ініціалізація системи періодичних видань..." << endl;
    
    PublicationSystem system;
    
    cout << "Система готова до роботи!" << endl;
    
    mainMenu(system);
    
    return 0;
}