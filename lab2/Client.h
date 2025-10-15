#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <fstream>
#include "Publication.h"  // Пункт 3: Зв'язок між класами

// Пункт 1: Клас Client з не менше 8 полів
class Client {
 private:  // Пункт 2: 5 приватних елементів
  int client_id_;
  std::string first_name_;
  std::string last_name_;
  std::string email_;
  std::string phone_;
  bool is_blacklisted_;
  double balance_;
  int subscription_months_;
  Publication subscribed_publication_;  // Пункт 3: Об'єкт іншого класу

  // Лаб 3, Пункт 3: Статичне поле для спільного використання
  static int total_clients_count_;

 public:  // Пункт 2: 3 загальні елементи
  // Лаб 3, Пункт 1: Конструктори
  Client();  // Конструктор без параметрів
  Client(int id, const std::string& first_name, const std::string& last_name,
         const std::string& email, const std::string& phone, double balance);  // З параметрами
  Client(const Client& other);  // Конструктор копіювання

  // Лаб 3, Пункт 2: Конструктор зі списком ініціалізації
  Client(int id, const std::string& first_name, const std::string& last_name);

  // Деструктор
  ~Client();

  // Пункт 4: 6 методів (2 перевантажені)
  // Метод 1: Перевантажений метод поповнення балансу
  void AddBalance(double amount);
  void AddBalance(double amount, double bonus);  // Перевантажений

  // Метод 2: Перевантажений метод підписки
  bool Subscribe(const Publication& pub, int months);
  bool Subscribe(const Publication& pub);  // Перевантажений (1 місяць)

  // Пункт 10: Метод 3 - Приймає об'єкт класу (сценарій взаємодії)
  bool PurchaseSubscription(const Publication& publication, int months);

  // Метод 4: Повертає об'єкт класу
  Publication GetSubscribedPublication() const;

  // Метод 5: Розрахунок знижки
  double CalculateDiscount(int months) const;

  // Метод 6: Перевірка можливості покупки
  bool CanAfford(const Publication& pub, int months) const;

  // Пункт 5: Методи для роботи з файлами
  void SaveToFile(std::ofstream& file) const;
  void LoadFromFile(std::ifstream& file);

  // Пункт 12: Метод з динамічною пам'яттю та сортуванням
  int* GenerateAndSortMonths(int& size) const;

  // Лаб 3, Пункт 3: Статичний метод для роботи зі статичним полем
  static int GetTotalClientsCount();
  static void ResetClientsCount();

  // Геттери
  int GetClientId() const { return client_id_; }
  std::string GetFirstName() const { return first_name_; }
  std::string GetLastName() const { return last_name_; }
  std::string GetFullName() const;
  std::string GetEmail() const { return email_; }
  std::string GetPhone() const { return phone_; }
  bool IsBlacklisted() const { return is_blacklisted_; }
  double GetBalance() const { return balance_; }
  int GetSubscriptionMonths() const { return subscription_months_; }

  // Сеттери
  void SetBlacklisted(bool status) { is_blacklisted_ = status; }

  // Метод виведення інформації
  void DisplayInfo() const;

  // Оператори порівняння
  bool operator==(const Client& other) const;
  bool operator<(const Client& other) const;
};

#endif  // CLIENT_H