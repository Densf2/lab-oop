#include "Magazine.h"
#include <iostream>
#include <iomanip>

// Пункт 5: Конструктор похідного класу передає параметри базовому
// Пункт 7: Виклик конструктора базового класу
Magazine::Magazine(int id, const std::string& title, const std::string& publisher,
                   double price, int pages, const std::string& isbn,
                   int circulation, const std::string& language,
                   int issue_number, const std::string& month,
                   const std::string& editor, const std::string& category,
                   int frequency)
    : PrintedMaterial(id, title, publisher, price, pages, isbn, circulation, language),
      issue_number_(issue_number), month_(month), editor_(editor),
      category_(category), frequency_per_year_(frequency),
      has_subscription_(true), subscription_discount_(0.0), subscriber_count_(0) {
  std::cout << "[Конструктор Magazine] Номер випуску: " << issue_number_ 
            << ", Категорія: " << category_ << std::endl;
}

Magazine::Magazine()
    : PrintedMaterial(), issue_number_(0), month_(""),
      editor_(""), category_(""), frequency_per_year_(12),
      has_subscription_(false), subscription_discount_(0.0), subscriber_count_(0) {
  std::cout << "[Конструктор Magazine] Без параметрів" << std::endl;
}

// Пункт 7: Деструктор похідного класу
Magazine::~Magazine() {
  std::cout << "[Деструктор Magazine] Номер: " << issue_number_ 
            << ", Категорія: " << category_ << std::endl;
}

// Перевизначений метод
void Magazine::DisplayInfo() const {
  // Пункт 6: Виклик методу базового класу через ::
  PrintedMaterial::DisplayInfo();
  
  std::cout << "--- Інформація про журнал ---" << std::endl;
  std::cout << "Номер випуску: " << issue_number_ << std::endl;
  std::cout << "Місяць: " << month_ << std::endl;
  std::cout << "Редактор: " << editor_ << std::endl;
  std::cout << "Категорія: " << category_ << std::endl;
  std::cout << "Частота виходу: " << frequency_per_year_ << " разів/рік" << std::endl;
  std::cout << "Підписників: " << subscriber_count_ << std::endl;
  if (subscription_discount_ > 0) {
    std::cout << "Знижка на підписку: " << subscription_discount_ << "%" << std::endl;
  }
}

void Magazine::SetSubscriptionDiscount(double discount) {
  subscription_discount_ = discount;
  std::cout << "[Magazine] Встановлено знижку на підписку: " 
            << discount << "%" << std::endl;
}

void Magazine::AddSubscriber() {
  subscriber_count_++;
  std::cout << "[Magazine] Додано підписника. Всього: " 
            << subscriber_count_ << std::endl;
}

int Magazine::GetIssueNumber() const {
  return issue_number_;
}

std::string Magazine::GetCategory() const {
  return category_;
}

// Пункт 6: Використання protected методу базового класу
void Magazine::IncreasePages(int additional_pages) {
  std::cout << "[Magazine::IncreasePages] Додаємо " << additional_pages 
            << " сторінок" << std::endl;
  // Доступ до protected методу SetPages() базового класу
  SetPages(GetPages() + additional_pages);
}

// Пункт 6: Доступ до елементів базового класу через оператор ::
void Magazine::ShowBasePrice() {
  std::cout << "[Magazine::ShowBasePrice] Базова ціна (через protected метод): " 
            << GetPrice() << " грн" << std::endl;
  // Пункт 6: Доступ до public поля через базовий клас
  std::cout << "[Magazine::ShowBasePrice] Тираж (public поле): " 
            << PrintedMaterial::circulation_ << " екз." << std::endl;
}
