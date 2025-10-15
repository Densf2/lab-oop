#include "Newspaper.h"
#include <iostream>

// Пункт 3, 5: Конструктор з приватним наслідуванням
// Пункт 7: Виклик конструктора базового класу
Newspaper::Newspaper(int id, const std::string& title, const std::string& publisher,
                     double price, int pages, const std::string& isbn,
                     int circulation, const std::string& language,
                     const std::string& date, const std::string& topic,
                     int articles, bool daily, const std::string& region)
    : PrintedMaterial(id, title, publisher, price, pages, isbn, circulation, language),
      publication_date_(date), main_topic_(topic), article_count_(articles),
      is_daily_(daily), region_(region), delivery_time_(2),
      delivery_cost_(15.0), editorial_staff_count_(50) {
  std::cout << "[Конструктор Newspaper] Дата: " << publication_date_ 
            << ", Регіон: " << region_ << std::endl;
}

Newspaper::Newspaper()
    : PrintedMaterial(), publication_date_(""), main_topic_(""),
      article_count_(0), is_daily_(false), region_(""),
      delivery_time_(0), delivery_cost_(0.0), editorial_staff_count_(0) {
  std::cout << "[Конструктор Newspaper] Без параметрів" << std::endl;
}

// Пункт 7: Деструктор
Newspaper::~Newspaper() {
  std::cout << "[Деструктор Newspaper] Регіон: " << region_ << std::endl;
}

// Пункт 3: Власний метод для виведення інформації (базовий DisplayInfo недоступний)
void Newspaper::ShowInfo() const {
  std::cout << "\n=== Газета ===" << std::endl;
  // Пункт 3, 6: Доступ до private базового класу через protected/public методи
  std::cout << "ISBN (через using): " << GetISBN() << std::endl;
  std::cout << "Тираж (через using): " << circulation_ << " екз." << std::endl;
  
  std::cout << "--- Інформація про газету ---" << std::endl;
  std::cout << "Дата публікації: " << publication_date_ << std::endl;
  std::cout << "Головна тема: " << main_topic_ << std::endl;
  std::cout << "Кількість статей: " << article_count_ << std::endl;
  std::cout << "Тип: " << (is_daily_ ? "Щоденна" : "Тижнева") << std::endl;
  std::cout << "Регіон: " << region_ << std::endl;
  std::cout << "Час доставки: " << delivery_time_ << " год" << std::endl;
  std::cout << "Вартість доставки: " << delivery_cost_ << " грн" << std::endl;
  std::cout << "Редакційний колектив: " << editorial_staff_count_ << " осіб" << std::endl;
}

void Newspaper::SetArticleCount(int count) {
  article_count_ = count;
  std::cout << "[Newspaper] Встановлено кількість статей: " << count << std::endl;
}

int Newspaper::GetArticleCount() const {
  return article_count_;
}

std::string Newspaper::GetRegion() const {
  return region_;
}

// Пункт 3: Доступ до private базового класу через публічний метод
void Newspaper::UpdateNewspaperPrice(double new_price) {
  std::cout << "[Newspaper::UpdateNewspaperPrice] Оновлення ціни газети" << std::endl;
  // Викликаємо protected/public метод базового класу
  UpdatePrice(new_price);
}

// Пункт 3: Метод, який демонструє роботу з різними класами ієрархії
void Newspaper::ProcessNewspaper() {
  std::cout << "\n[Newspaper::ProcessNewspaper] Обробка газети..." << std::endl;
  
  // Робота з власними полями
  std::cout << "1. Перевірка кількості статей: " << article_count_ << std::endl;
  
  // Пункт 6: Доступ до методів базового класу через оператор ::
  std::cout << "2. Доступ до ISBN через using: " << GetISBN() << std::endl;
  
  // Робота з public полем базового класу (через using)
  std::cout << "3. Перевірка тиражу: " << circulation_ << " екз." << std::endl;
  
  // Виклик методу базового класу
  std::cout << "4. Оновлення ціни через метод базового класу:" << std::endl;
  UpdateNewspaperPrice(25.0);
  
  std::cout << "[Newspaper::ProcessNewspaper] Обробка завершена" << std::endl;
}
