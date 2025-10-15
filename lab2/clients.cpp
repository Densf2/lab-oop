#include "Client.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cstdlib>
#include <ctime>

// Лаб 3, Пункт 3: Ініціалізація статичного поля даних поза класом
int Client::total_clients_count_ = 0;

// Лаб 3, Пункт 1: Конструктор без параметрів
// Пункт 2: Ініціалізація всіх 9 приватних полів (включаючи об'єкт Publication)
Client::Client()
    : client_id_(0), first_name_(""), last_name_(""), email_(""),
      phone_(""), is_blacklisted_(false), balance_(0.0),
      subscription_months_(0), subscribed_publication_() {
  // Лаб 3, Пункт 3: Збільшуємо лічильник клієнтів
  total_clients_count_++;
  std::cout << "[Конструктор без параметрів] Створено Client #" 
            << total_clients_count_ << std::endl;
}

// Лаб 3, Пункт 1: Конструктор з параметрами
Client::Client(int id, const std::string& first_name,
               const std::string& last_name, const std::string& email,
               const std::string& phone, double balance)
    : client_id_(id), first_name_(first_name), last_name_(last_name),
      email_(email), phone_(phone), is_blacklisted_(false),
      balance_(balance), subscription_months_(0), subscribed_publication_() {
  // Лаб 3, Пункт 3: Збільшуємо лічильник
  total_clients_count_++;
  std::cout << "[Конструктор з параметрами] Створено клієнта: " 
            << first_name_ << " " << last_name_ 
            << " (Всього: " << total_clients_count_ << ")" << std::endl;
}

// Лаб 3, Пункт 1: Конструктор копіювання
// Створює повну копію клієнта включаючи вкладений об'єкт Publication
Client::Client(const Client& other)
    : client_id_(other.client_id_), 
      first_name_(other.first_name_),
      last_name_(other.last_name_),
      email_(other.email_),
      phone_(other.phone_),
      is_blacklisted_(other.is_blacklisted_),
      balance_(other.balance_),
      subscription_months_(other.subscription_months_),
      subscribed_publication_(other.subscribed_publication_) {  // Копіюємо вкладений об'єкт
  // Лаб 3, Пункт 3: Збільшуємо лічильник
  total_clients_count_++;
  std::cout << "[Конструктор копіювання] Скопійовано клієнта: " 
            << first_name_ << " " << last_name_ 
            << " (Всього: " << total_clients_count_ << ")" << std::endl;
}

// Лаб 3, Пункт 2: Конструктор зі списком ініціалізації
// Демонструє задання початкових значень констант і посилань
Client::Client(int id, const std::string& first_name, const std::string& last_name)
    : client_id_(id),                // Ініціалізація через список
      first_name_(first_name),       // Ініціалізація через список
      last_name_(last_name),         // Ініціалізація через список
      email_("no-email@example.com"), // Константне значення
      phone_("+380000000000"),       // Константне значення
      is_blacklisted_(false),        // Початкове значення
      balance_(0.0),                 // Початкове значення
      subscription_months_(0),       // Початкове значення
      subscribed_publication_() {    // Викликається конструктор без параметрів Publication
  // Лаб 3, Пункт 3: Збільшуємо лічильник
  total_clients_count_++;
  std::cout << "[Конструктор зі списком ініціалізації] Створено: " 
            << first_name_ << " " << last_name_ 
            << " (Всього: " << total_clients_count_ << ")" << std::endl;
}

// Деструктор
Client::~Client() {
  // Лаб 3, Пункт 3: Зменшуємо лічильник при знищенні
  total_clients_count_--;
  std::cout << "[Деструктор] Знищено клієнта: " << first_name_ << " " << last_name_ 
            << " (Залишилось: " << total_clients_count_ << ")" << std::endl;
}

// Пункт 4: Метод 1 - Перевантажений метод AddBalance
// Пункт 2: Використання приватного поля balance_
void Client::AddBalance(double amount) {
  if (amount > 0) {
    balance_ += amount;
  }
}

// Пункт 4: Перевантажений метод AddBalance з бонусом
void Client::AddBalance(double amount, double bonus) {
  if (amount > 0 && bonus >= 0) {
    balance_ += amount + bonus;
  }
}

// Пункт 4: Метод 2 - Перевантажений метод Subscribe
// Пункт 3: Робота з об'єктом класу Publication
bool Client::Subscribe(const Publication& pub, int months) {
  double total_cost = pub.CalculateTotalPrice(months);

  if (balance_ >= total_cost && !is_blacklisted_) {
    balance_ -= total_cost;
    subscribed_publication_ = pub;
    subscription_months_ = months;
    return true;
  }
  return false;
}

// Пункт 4: Перевантажений метод Subscribe (1 місяць за замовчуванням)
bool Client::Subscribe(const Publication& pub) {
  return Subscribe(pub, 1);
}

// Пункт 10: Метод 3 - Сценарій взаємодії (клієнт купує підписку)
// Пункт 4: Приймає об'єкт класу як параметр
bool Client::PurchaseSubscription(const Publication& publication, int months) {
  std::cout << "\n=== Процес покупки підписки ===" << std::endl;
  std::cout << "Клієнт: " << GetFullName() << std::endl;
  std::cout << "Видання: " << publication.GetTitle() << std::endl;
  std::cout << "Період: " << months << " міс." << std::endl;

  double total_cost = publication.CalculateTotalPrice(months);
  std::cout << "Вартість: " << std::fixed << std::setprecision(2)
            << total_cost << " грн" << std::endl;
  std::cout << "Баланс до покупки: " << balance_ << " грн" << std::endl;

  if (is_blacklisted_) {
    std::cout << "ВІДМОВА: Клієнт у чорному списку!" << std::endl;
    return false;
  }

  if (balance_ < total_cost) {
    std::cout << "ВІДМОВА: Недостатньо коштів!" << std::endl;
    std::cout << "Не вистачає: " << (total_cost - balance_) << " грн"
              << std::endl;
    return false;
  }

  balance_ -= total_cost;
  subscribed_publication_ = publication;
  subscription_months_ = months;

  std::cout << "УСПІХ: Підписку оформлено!" << std::endl;
  std::cout << "Баланс після покупки: " << balance_ << " грн" << std::endl;
  std::cout << "===============================" << std::endl;

  return true;
}

// Пункт 4: Метод 4 - Повертає об'єкт класу
Publication Client::GetSubscribedPublication() const {
  return subscribed_publication_;
}

// Пункт 4: Метод 5 - Розрахунок знижки
// Пункт 2: Використання поля subscription_months_
double Client::CalculateDiscount(int months) const {
  if (months >= 12) {
    return 15.0;  // 15% для річної підписки
  } else if (months >= 6) {
    return 10.0;  // 10% для піврічної
  } else if (months >= 3) {
    return 5.0;   // 5% для квартальної
  }
  return 0.0;
}

// Пункт 4: Метод 6 - Перевірка можливості покупки
bool Client::CanAfford(const Publication& pub, int months) const {
  double total_cost = pub.CalculateTotalPrice(months);
  return balance_ >= total_cost && !is_blacklisted_;
}

// Пункт 5: Метод запису у файл
// Пункт 2: Використання всіх полів
void Client::SaveToFile(std::ofstream& file) const {
  file << client_id_ << "\n"
       << first_name_ << "\n"
       << last_name_ << "\n"
       << email_ << "\n"
       << phone_ << "\n"
       << is_blacklisted_ << "\n"
       << balance_ << "\n"
       << subscription_months_ << "\n";

  // Зберігаємо підписане видання
  subscribed_publication_.SaveToFile(file);
}

// Пункт 5: Метод читання з файлу
void Client::LoadFromFile(std::ifstream& file) {
  file >> client_id_;
  file.ignore();
  std::getline(file, first_name_);
  std::getline(file, last_name_);
  std::getline(file, email_);
  std::getline(file, phone_);
  file >> is_blacklisted_ >> balance_ >> subscription_months_;
  file.ignore();

  // Завантажуємо підписане видання
  subscribed_publication_.LoadFromFile(file);
}

// Пункт 12: Метод з динамічною пам'яттю та сортуванням
int* Client::GenerateAndSortMonths(int& size) const {
  // Випадковий розмір від 5 до 15
  srand(static_cast<unsigned>(time(0)) + client_id_);
  size = 5 + rand() % 11;

  // Виділення динамічної пам'яті
  int* months_array = new int[size];

  // Заповнення випадковими значеннями (1-24 місяців)
  for (int i = 0; i < size; i++) {
    months_array[i] = 1 + rand() % 24;
  }

  // Сортування методом вставки
  for (int i = 1; i < size; i++) {
    int key = months_array[i];
    int j = i - 1;

    while (j >= 0 && months_array[j] > key) {
      months_array[j + 1] = months_array[j];
      j = j - 1;
    }
    months_array[j + 1] = key;
  }

  return months_array;
}

// Геттер для повного імені
std::string Client::GetFullName() const {
  return first_name_ + " " + last_name_;
}

// Виведення інформації про клієнта
// Пункт 2: Використання всіх полів класу
void Client::DisplayInfo() const {
  std::cout << "\n=== Інформація про клієнта ===" << std::endl;
  std::cout << "ID: " << client_id_ << std::endl;
  std::cout << "Ім'я: " << GetFullName() << std::endl;
  std::cout << "Email: " << email_ << std::endl;
  std::cout << "Телефон: " << phone_ << std::endl;
  std::cout << "Баланс: " << std::fixed << std::setprecision(2)
            << balance_ << " грн" << std::endl;
  std::cout << "Статус: "
            << (is_blacklisted_ ? "В чорному списку" : "Активний")
            << std::endl;

  if (subscription_months_ > 0) {
    std::cout << "Підписка: " << subscribed_publication_.GetTitle()
              << " на " << subscription_months_ << " міс." << std::endl;
  } else {
    std::cout << "Підписка: Немає активної підписки" << std::endl;
  }
  std::cout << "===============================" << std::endl;
}

// Оператор рівності
bool Client::operator==(const Client& other) const {
  return client_id_ == other.client_id_;
}

// Оператор порівняння для сортування
bool Client::operator<(const Client& other) const {
  if (last_name_ != other.last_name_) {
    return last_name_ < other.last_name_;
  }
  return first_name_ < other.first_name_;
}

// Лаб 3, Пункт 3: Статичний метод для отримання кількості клієнтів
// Може бути викликаний без створення об'єкта класу
int Client::GetTotalClientsCount() {
  return total_clients_count_;
}

// Лаб 3, Пункт 3: Статичний метод для скидання лічильника
void Client::ResetClientsCount() {
  total_clients_count_ = 0;
  std::cout << "[Статичний метод] Лічильник клієнтів скинуто до 0" << std::endl;
}