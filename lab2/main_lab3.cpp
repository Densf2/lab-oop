// Лабораторна робота №3: Конструктори, деструктори, статичні елементи, дружні функції
// Пункт 8: В коментарях вказано реалізацію кожного пункту завдання
// Пункт 11: Демонстраційна програма (cpp-файл)

#include <iostream>
#include <fstream>
#include "Publication.h"
#include "Client.h"

using namespace std;

// Лаб 3, Пункт 4: Функція поза межами класу
// Приймає об'єкт класу як параметр, обчислює дані та виводить результат
void CalculatePublicationStatistics(const Publication& pub) {
  cout << "\n=== Статистика видання ===" << endl;
  cout << "Назва: " << pub.GetTitle() << endl;
  
  // Обчислення річної вартості
  double yearly_cost = pub.GetPrice() * 12;
  cout << "Річна вартість: " << yearly_cost << " грн" << endl;
  
  // Обчислення вартості за сторінку
  if (pub.GetPages() > 0) {
    double price_per_page = pub.GetPrice() / pub.GetPages();
    cout << "Ціна за сторінку: " << price_per_page << " грн" << endl;
  }
  
  // Обчислення середнього рейтингу
  if (pub.GetReviewCount() > 0) {
    cout << "Середній рейтинг: " << pub.GetRating() << "/5.0" << endl;
    cout << "Кількість відгуків: " << pub.GetReviewCount() << endl;
  }
  
  cout << "=========================" << endl;
}

// Лаб 3, Пункт 4: Ще одна функція поза класом для роботи з Client
void CalculateClientExpenses(const Client& client) {
  cout << "\n=== Витрати клієнта ===" << endl;
  cout << "Клієнт: " << client.GetFullName() << endl;
  cout << "Поточний баланс: " << client.GetBalance() << " грн" << endl;
  
  if (client.GetSubscriptionMonths() > 0) {
    cout << "Місяців підписки: " << client.GetSubscriptionMonths() << endl;
    // Якщо є підписка, показуємо інформацію
    Publication sub = client.GetSubscribedPublication();
    double monthly = sub.GetPrice();
    double total = monthly * client.GetSubscriptionMonths();
    cout << "Щомісячна оплата: " << monthly << " грн" << endl;
    cout << "Загальна вартість підписки: " << total << " грн" << endl;
  } else {
    cout << "Немає активної підписки" << endl;
  }
  
  cout << "=========================" << endl;
}

// Лаб 3, Пункт 5: Функція типу класу, яка повертає об'єкт
// Оперує з методами класу
Publication CreateDiscountedPublication(const Publication& original, double discount_percent) {
  cout << "\n[Функція CreateDiscountedPublication]" << endl;
  cout << "Створюємо видання зі знижкою " << discount_percent << "%" << endl;
  
  // Створюємо копію за допомогою конструктора копіювання
  Publication discounted = original;
  
  // Застосовуємо знижку через метод класу
  discounted.SetPrice(original.GetPrice(), discount_percent);
  
  cout << "Оригінальна ціна: " << original.GetPrice() << " грн" << endl;
  cout << "Ціна зі знижкою: " << discounted.GetPrice() << " грн" << endl;
  
  return discounted;  // Повертаємо об'єкт класу
}

// Лаб 3, Пункт 5: Ще одна функція, що повертає об'єкт Client
Client CreateVIPClient(const Client& regular_client, double bonus_balance) {
  cout << "\n[Функція CreateVIPClient]" << endl;
  cout << "Створюємо VIP-клієнта на базі звичайного" << endl;
  
  // Використовуємо конструктор копіювання
  Client vip_client = regular_client;
  
  // Додаємо бонус через метод класу (перевантажений)
  vip_client.AddBalance(0, bonus_balance);
  
  cout << "Баланс звичайного клієнта: " << regular_client.GetBalance() << " грн" << endl;
  cout << "Баланс VIP-клієнта: " << vip_client.GetBalance() << " грн" << endl;
  
  return vip_client;  // Повертаємо об'єкт класу
}

// Лаб 3, Пункт 7: Демонстрація всіх конструкторів
void DemonstrateConstructors() {
  cout << "\n========================================" << endl;
  cout << "ПУНКТ 1 і 7: Демонстрація конструкторів" << endl;
  cout << "========================================" << endl;
  
  // 1. Конструктор без параметрів
  cout << "\n--- Конструктор без параметрів ---" << endl;
  Publication pub1;
  Client client1;
  
  // 2. Конструктор з параметрами
  cout << "\n--- Конструктор з параметрами ---" << endl;
  Publication pub2(1, "Журнал програміста", "Про IT", 200.0, "IT", 100);
  Client client2(1, "Марія", "Коваленко", "maria@mail.com", "+380501234567", 1500.0);
  
  // 3. Конструктор копіювання
  cout << "\n--- Конструктор копіювання ---" << endl;
  Publication pub3 = pub2;  // Виклик конструктора копіювання
  Client client3 = client2;  // Виклик конструктора копіювання
  
  // 4. Конструктор зі списком ініціалізації
  cout << "\n--- Конструктор зі списком ініціалізації ---" << endl;
  Publication pub4(2, "Швидке видання", 150.0);
  Client client4(2, "Олександр", "Сидоренко");
  
  cout << "\nІнформація про створені об'єкти:" << endl;
  pub2.DisplayInfo();
  client2.DisplayInfo();
}

// Лаб 3, Пункт 3: Демонстрація статичних елементів
void DemonstrateStaticMembers() {
  cout << "\n========================================" << endl;
  cout << "ПУНКТ 3: Статичні поля та методи" << endl;
  cout << "========================================" << endl;
  
  // Виклик статичного методу без створення об'єктів
  cout << "\n--- Виклик статичних методів до створення об'єктів ---" << endl;
  cout << "Кількість видань (через статичний метод): " 
       << Publication::GetTotalPublicationsCount() << endl;
  cout << "Кількість клієнтів (через статичний метод): " 
       << Client::GetTotalClientsCount() << endl;
  
  // Створюємо об'єкти - лічильники автоматично збільшуються
  cout << "\n--- Створюємо 3 об'єкти Publication ---" << endl;
  Publication* pub1 = new Publication(10, "Видання 1", "Опис 1", 100, "Категорія", 50);
  Publication* pub2 = new Publication(11, "Видання 2", "Опис 2", 120, "Категорія", 60);
  Publication* pub3 = new Publication(12, "Видання 3", "Опис 3", 140, "Категорія", 70);
  
  cout << "\n--- Створюємо 2 об'єкти Client ---" << endl;
  Client* client1 = new Client(100, "Іван", "Іванов", "ivan@test.com", "+380111111111", 2000);
  Client* client2 = new Client(101, "Петро", "Петров", "petro@test.com", "+380222222222", 2500);
  
  // Перевіряємо лічильники через статичні методи
  cout << "\n--- Перевірка статичних полів через методи ---" << endl;
  cout << "Всього створено видань: " << Publication::GetTotalPublicationsCount() << endl;
  cout << "Всього створено клієнтів: " << Client::GetTotalClientsCount() << endl;
  
  // Видаляємо один об'єкт - лічильник зменшується
  cout << "\n--- Видаляємо один об'єкт Publication ---" << endl;
  delete pub1;
  cout << "Залишилось видань: " << Publication::GetTotalPublicationsCount() << endl;
  
  // Видаляємо решту
  cout << "\n--- Видаляємо решту об'єктів ---" << endl;
  delete pub2;
  delete pub3;
  delete client1;
  delete client2;
  
  cout << "\nФінальні значення лічильників:" << endl;
  cout << "Видань: " << Publication::GetTotalPublicationsCount() << endl;
  cout << "Клієнтів: " << Client::GetTotalClientsCount() << endl;
}

// Лаб 3, Пункт 4: Демонстрація функцій поза класом
void DemonstrateFunctionsOutsideClass() {
  cout << "\n========================================" << endl;
  cout << "ПУНКТ 4: Функції поза класом" << endl;
  cout << "========================================" << endl;
  
  // Створюємо об'єкти
  Publication pub(20, "Наукова думка", "Журнал про науку", 180.0, "Наука", 80);
  pub.AddRating(4.5);
  pub.AddRating(5.0);
  pub.AddRating(4.0);
  
  Client client(200, "Оксана", "Мельник", "oksana@mail.com", "+380333333333", 3000.0);
  client.Subscribe(pub, 6);
  
  // Викликаємо функції поза класом
  CalculatePublicationStatistics(pub);
  CalculateClientExpenses(client);
}

// Лаб 3, Пункт 5: Демонстрація функцій, що повертають об'єкти
void DemonstrateFunctionsReturningObjects() {
  cout << "\n========================================" << endl;
  cout << "ПУНКТ 5: Функції, що повертають об'єкти" << endl;
  cout << "========================================" << endl;
  
  // Створюємо базові об'єкти
  Publication original_pub(30, "Базовий журнал", "Опис", 300.0, "Преміум", 120);
  Client original_client(300, "Андрій", "Шевченко", "andrii@mail.com", "+380444444444", 5000.0);
  
  // Викликаємо функцію, що повертає об'єкт Publication
  Publication discounted_pub = CreateDiscountedPublication(original_pub, 20);
  discounted_pub.DisplayInfo();
  
  // Викликаємо функцію, що повертає об'єкт Client
  Client vip = CreateVIPClient(original_client, 10000.0);
  vip.DisplayInfo();
}

// Лаб 3, Пункт 6: Демонстрація покажчиків та масивів
void DemonstratePointersAndArrays() {
  cout << "\n========================================" << endl;
  cout << "ПУНКТ 6: Покажчики та масиви об'єктів" << endl;
  cout << "========================================" << endl;
  
  // Статичні об'єкти
  cout << "\n--- Статичні об'єкти ---" << endl;
  Publication static_pub(40, "Статичне видання", "Опис", 150, "Загальна", 50);
  Client static_client(400, "Статичний", "Клієнт", "static@mail.com", "+380555555555", 1000);
  
  // Динамічні об'єкти через покажчики
  cout << "\n--- Динамічні об'єкти (через new) ---" << endl;
  Publication* dyn_pub = new Publication(41, "Динамічне видання", "Опис", 200, "Преміум", 80);
  Client* dyn_client = new Client(401, "Динамічний", "Клієнт", "dynamic@mail.com", "+380666666666", 2000);
  
  // Робота через покажчик
  cout << "\n--- Робота через покажчик ---" << endl;
  cout << "Ціна через покажчик: " << dyn_pub->GetPrice() << " грн" << endl;
  dyn_pub->SetPrice(250);
  cout << "Нова ціна: " << dyn_pub->GetPrice() << " грн" << endl;
  
  cout << "Баланс через покажчик: " << dyn_client->GetBalance() << " грн" << endl;
  dyn_client->AddBalance(500);
  cout << "Новий баланс: " << dyn_client->GetBalance() << " грн" << endl;
  
  // Масиви об'єктів
  cout << "\n--- Масиви об'єктів ---" << endl;
  Publication pub_array[3] = {
    Publication(50, "Журнал 1", "Опис 1", 100, "Кат1", 40),
    Publication(51, "Журнал 2", "Опис 2", 120, "Кат2", 50),
    Publication(52, "Журнал 3", "Опис 3", 140, "Кат3", 60)
  };
  
  Client client_array[2] = {
    Client(500, "Клієнт1", "Прізвище1", "client1@mail.com", "+380777777777", 1000),
    Client(501, "Клієнт2", "Прізвище2", "client2@mail.com", "+380888888888", 1500)
  };
  
  cout << "Масив з " << 3 << " видань створено" << endl;
  cout << "Масив з " << 2 << " клієнтів створено" << endl;
  
  // Виведення через масив
  cout << "\nВиведення через масив (перше видання):" << endl;
  pub_array[0].DisplayInfo();
  
  // Видалення динамічних об'єктів
  cout << "\n--- Видалення динамічних об'єктів ---" << endl;
  delete dyn_pub;
  delete dyn_client;
}

// Головна функція
int main() {
  // Встановлюємо українську локаль для коректного виводу
  setlocale(LC_ALL, "Ukrainian");
  
  cout << "===============================================" << endl;
  cout << "  Лабораторна робота №3" << endl;
  cout << "  Конструктори, деструктори, статичні елементи" << endl;
  cout << "===============================================" << endl;
  
  // Демонстрація всіх пунктів завдання
  
  // Пункт 1 і 7: Конструктори
  DemonstrateConstructors();
  
  // Пункт 3: Статичні поля та методи
  DemonstrateStaticMembers();
  
  // Пункт 4: Функції поза класом
  DemonstrateFunctionsOutsideClass();
  
  // Пункт 5: Функції, що повертають об'єкти
  DemonstrateFunctionsReturningObjects();
  
  // Пункт 6: Покажчики та масиви
  DemonstratePointersAndArrays();
  
  cout << "\n===============================================" << endl;
  cout << "  Програма завершила роботу" << endl;
  cout << "  Всі пункти завдання продемонстровано" << endl;
  cout << "===============================================" << endl;
  
  return 0;
}
