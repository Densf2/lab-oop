#include "Publication.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cstdlib>
#include <ctime>

// Конструктор за замовчуванням
// Пункт 2: Ініціалізація всіх 8 приватних полів
Publication::Publication()
    : id_(0), title_(""), description_(""), price_(0.0),
      category_(""), rating_(0.0), review_count_(0), pages_(0) {}

// Конструктор з параметрами
// Пункт 2: Використання всіх полів даних
Publication::Publication(int id, const std::string& title,
                         const std::string& description, double price,
                         const std::string& category, int pages)
    : id_(id), title_(title), description_(description),
      price_(price), category_(category), rating_(0.0),
      review_count_(0), pages_(pages) {}

// Деструктор
Publication::~Publication() {
  // Очищення ресурсів якщо потрібно
}

// Пункт 4: Метод 1 - Перевантажений метод SetPrice
// Пункт 2: Використання приватного поля price_
void Publication::SetPrice(double price) {
  if (price >= 0) {
    price_ = price;
  }
}

// Пункт 4: Перевантажений метод SetPrice зі знижкою
void Publication::SetPrice(double price, double discount) {
  if (price >= 0 && discount >= 0 && discount <= 100) {
    price_ = price * (1.0 - discount / 100.0);
  }
}

// Пункт 4: Метод 2 - Перевантажений метод AddRating
// Пункт 2: Використання полів rating_ та review_count_
void Publication::AddRating(double rating) {
  if (rating >= 1.0 && rating <= 5.0) {
    rating_ = (rating_ * review_count_ + rating) / (review_count_ + 1);
    review_count_++;
  }
}

// Пункт 4: Перевантажений метод AddRating
void Publication::AddRating(int rating, int count) {
  if (rating >= 1 && rating <= 5 && count > 0) {
    rating_ = (rating_ * review_count_ + rating * count) /
              (review_count_ + count);
    review_count_ += count;
  }
}

// Пункт 4: Метод 3 - Приймає об'єкт класу як параметр
// Пункт 2: Використання полів price_ та pages_
double Publication::CalculateDiscount(const Publication& other) const {
  // Розрахунок знижки при купівлі двох видань
  if (this->category_ == other.category_) {
    return 15.0;  // 15% знижки для однієї категорії
  }
  return 10.0;  // 10% стандартна знижка
}

// Пункт 4: Метод 4 - Повертає об'єкт класу
Publication Publication::CreateCopy() const {
  Publication copy;
  copy.id_ = this->id_;
  copy.title_ = this->title_;
  copy.description_ = this->description_;
  copy.price_ = this->price_;
  copy.category_ = this->category_;
  copy.rating_ = this->rating_;
  copy.review_count_ = this->review_count_;
  copy.pages_ = this->pages_;
  return copy;
}

// Пункт 4: Метод 5 - Розрахунок загальної вартості
// Пункт 2: Використання поля price_
double Publication::CalculateTotalPrice(int months) const {
  double total = price_ * months;
  // Знижка за довгострокову підписку
  if (months >= 12) {
    total *= 0.85;  // 15% знижки
  } else if (months >= 6) {
    total *= 0.90;  // 10% знижки
  }
  return total;
}

// Пункт 4: Метод 6 - Перевірка доступності
// Пункт 2: Використання полів rating_ та pages_
bool Publication::IsAvailable() const {
  return (rating_ > 0 || review_count_ == 0) && pages_ > 0;
}

// Пункт 5: Метод запису у файл
// Пункт 2: Використання всіх 8 полів
void Publication::SaveToFile(std::ofstream& file) const {
  file << id_ << "\n"
       << title_ << "\n"
       << description_ << "\n"
       << price_ << "\n"
       << category_ << "\n"
       << rating_ << "\n"
       << review_count_ << "\n"
       << pages_ << "\n";
}

// Пункт 5: Метод читання з файлу
void Publication::LoadFromFile(std::ifstream& file) {
  file >> id_;
  file.ignore();
  std::getline(file, title_);
  std::getline(file, description_);
  file >> price_;
  file.ignore();
  std::getline(file, category_);
  file >> rating_ >> review_count_ >> pages_;
  file.ignore();
}

// Пункт 12: Метод з динамічною пам'яттю та сортуванням
// Генерує випадкові рейтинги та сортує їх
int* Publication::GenerateAndSortRatings(int& size) const {
  // Випадковий розмір масиву від 5 до 20
  srand(static_cast<unsigned>(time(0)));
  size = 5 + rand() % 16;

  // Виділення динамічної пам'яті
  int* ratings = new int[size];

  // Заповнення випадковими значеннями (1-5)
  for (int i = 0; i < size; i++) {
    ratings[i] = 1 + rand() % 5;
  }

  // Сортування методом бульбашки
  for (int i = 0; i < size - 1; i++) {
    for (int j = 0; j < size - i - 1; j++) {
      if (ratings[j] > ratings[j + 1]) {
        int temp = ratings[j];
        ratings[j] = ratings[j + 1];
        ratings[j + 1] = temp;
      }
    }
  }

  return ratings;  // Повертаємо покажчик на динамічну пам'ять
}

// Виведення інформації про видання
// Пункт 2: Використання всіх полів класу
void Publication::DisplayInfo() const {
  std::cout << "\n=== Інформація про видання ===" << std::endl;
  std::cout << "ID: " << id_ << std::endl;
  std::cout << "Назва: " << title_ << std::endl;
  std::cout << "Опис: " << description_ << std::endl;
  std::cout << "Категорія: " << category_ << std::endl;
  std::cout << "Ціна: " << std::fixed << std::setprecision(2)
            << price_ << " грн/міс" << std::endl;
  std::cout << "Кількість сторінок: " << pages_ << std::endl;

  if (review_count_ > 0) {
    std::cout << "Рейтинг: " << std::fixed << std::setprecision(1)
              << rating_ << "/5.0 (" << review_count_ << " відгуків)"
              << std::endl;
  } else {
    std::cout << "Рейтинг: Немає відгуків" << std::endl;
  }
  std::cout << "================================" << std::endl;
}

// Оператор порівняння для сортування
bool Publication::operator<(const Publication& other) const {
  return title_ < other.title_;
}

// Оператор рівності
bool Publication::operator==(const Publication& other) const {
  return id_ == other.id_;
}