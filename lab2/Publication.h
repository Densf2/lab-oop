#ifndef PUBLICATION_H
#define PUBLICATION_H

#include <string>
#include <fstream>

// Пункт 1: Клас Publication з не менше 8 полів
class Publication {
 private:  // Пункт 2: 5 приватних елементів
  int id_;
  std::string title_;
  std::string description_;
  double price_;
  std::string category_;
  double rating_;
  int review_count_;
  int pages_;

  // Лаб 3, Пункт 3: Статичне поле даних для спільного використання
  static int total_publications_count_;

 public:  // Пункт 2: 3 загальні елементи (конструктор, деструктор, displayInfo)
  // Лаб 3, Пункт 1: Конструктори
  Publication();  // Конструктор без параметрів
  Publication(int id, const std::string& title, const std::string& description,
              double price, const std::string& category, int pages);  // З параметрами
  Publication(const Publication& other);  // Конструктор копіювання

  // Лаб 3, Пункт 2: Конструктор зі списком ініціалізації (для констант і посилань)
  Publication(int id, const std::string& title, double price);

  // Деструктор
  ~Publication();

  // Пункт 4: 6 методів (2 перевантажені)
  // Метод 1: Перевантажений метод встановлення ціни
  void SetPrice(double price);
  void SetPrice(double price, double discount);  // Перевантажений

  // Метод 2: Перевантажений метод додавання рейтингу
  void AddRating(double rating);
  void AddRating(int rating, int count);  // Перевантажений

  // Метод 3: Приймає об'єкт класу як параметр (буде в Client)
  double CalculateDiscount(const Publication& other) const;

  // Метод 4: Повертає об'єкт класу
  Publication CreateCopy() const;

  // Метод 5: Розрахунок загальної вартості
  double CalculateTotalPrice(int months) const;

  // Метод 6: Перевірка доступності
  bool IsAvailable() const;

  // Пункт 5: Методи для роботи з файлами
  void SaveToFile(std::ofstream& file) const;
  void LoadFromFile(std::ifstream& file);

  // Пункт 12: Метод з динамічною пам'яттю та сортуванням
  int* GenerateAndSortRatings(int& size) const;

  // Лаб 3, Пункт 3: Статичний метод для роботи зі статичним полем
  static int GetTotalPublicationsCount();
  static void ResetPublicationsCount();

  // Геттери для доступу до приватних полів
  int GetId() const { return id_; }
  std::string GetTitle() const { return title_; }
  std::string GetDescription() const { return description_; }
  double GetPrice() const { return price_; }
  std::string GetCategory() const { return category_; }
  double GetRating() const { return rating_; }
  int GetReviewCount() const { return review_count_; }
  int GetPages() const { return pages_; }

  // Метод виведення інформації
  void DisplayInfo() const;

  // Оператори порівняння
  bool operator<(const Publication& other) const;
  bool operator==(const Publication& other) const;
};

#endif  // PUBLICATION_H