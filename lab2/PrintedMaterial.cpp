#include "PrintedMaterial.h"
#include <iostream>
#include <iomanip>

// Пункт 7: Конструктор базового класу
PrintedMaterial::PrintedMaterial(int id, const std::string& title,
                                 const std::string& publisher, double price,
                                 int pages, const std::string& isbn,
                                 int circulation, const std::string& language)
    : material_id_(id), title_(title), publisher_(publisher),
      price_(price), pages_(pages), isbn_(isbn),
      circulation_(circulation), language_(language) {
  std::cout << "[Конструктор PrintedMaterial] ID: " << material_id_ 
            << ", Назва: " << title_ << std::endl;
  ValidatePrice();
  ValidatePages();
}

// Конструктор без параметрів
PrintedMaterial::PrintedMaterial()
    : material_id_(0), title_(""), publisher_(""),
      price_(0.0), pages_(0), isbn_(""),
      circulation_(0), language_("") {
  std::cout << "[Конструктор PrintedMaterial] Без параметрів" << std::endl;
}

// Пункт 7: Деструктор базового класу
PrintedMaterial::~PrintedMaterial() {
  std::cout << "[Деструктор PrintedMaterial] ID: " << material_id_ 
            << ", Назва: " << title_ << std::endl;
}

// Пункт 2: Public метод - доступний всім
void PrintedMaterial::DisplayInfo() const {
  std::cout << "\n=== Друкований матеріал ===" << std::endl;
  std::cout << "ID: " << material_id_ << std::endl;
  std::cout << "Назва: " << title_ << std::endl;
  std::cout << "Видавництво: " << publisher_ << std::endl;
  std::cout << "ISBN: " << isbn_ << std::endl;
  std::cout << "Ціна: " << std::fixed << std::setprecision(2) 
            << price_ << " грн" << std::endl;
  std::cout << "Сторінок: " << pages_ << std::endl;
  std::cout << "Тираж: " << circulation_ << " екз." << std::endl;
  std::cout << "Мова: " << language_ << std::endl;
}

// Пункт 2: Public метод
void PrintedMaterial::UpdatePrice(double new_price) {
  std::cout << "[UpdatePrice] Зміна ціни з " << price_ 
            << " на " << new_price << std::endl;
  price_ = new_price;
  ValidatePrice();
}

// Пункт 2: Public метод
std::string PrintedMaterial::GetISBN() const {
  return isbn_;
}

// Пункт 2: Protected методи - доступні похідним класам
void PrintedMaterial::SetPages(int pages) {
  pages_ = pages;
  ValidatePages();
}

double PrintedMaterial::GetPrice() const {
  return price_;
}

int PrintedMaterial::GetPages() const {
  return pages_;
}

// Пункт 2: Private методи - тільки внутрішнє використання
void PrintedMaterial::ValidatePrice() {
  if (price_ < 0) {
    std::cout << "[ValidatePrice] Помилка: ціна не може бути від'ємною" << std::endl;
    price_ = 0;
  }
}

void PrintedMaterial::ValidatePages() {
  if (pages_ < 0) {
    std::cout << "[ValidatePages] Помилка: кількість сторінок не може бути від'ємною" << std::endl;
    pages_ = 0;
  }
}
