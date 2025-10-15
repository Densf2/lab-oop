#include "Book.h"
#include <iostream>
#include <iomanip>

// Пункт 5: Конструктор з параметрами, який викликає конструктор базового класу
// Пункт 7: Вивід повідомлень для відстеження порядку виклику конструкторів
Book::Book(int id, const std::string& title,
           const std::string& publisher, double price, int pages,
           const std::string& isbn, int circulation, const std::string& lang,
           const std::string& author, const std::string& genre, int chapters)
    // Виклик конструктора базового класу з 8 параметрами
    : PrintedMaterial(id, title, publisher, price, pages, isbn, circulation, lang),
      author_(author), genre_(genre), chapter_count_(chapters),
      binding_type_("м'яка"), hardcover_(false), series_name_(""),
      edition_number_(1), translator_("") {
  std::cout << "[Конструктор Book] Автор: " << author_ 
            << ", Жанр: " << genre_ << std::endl;
}

Book::Book()
    : PrintedMaterial(), author_(""), genre_(""), chapter_count_(0),
      binding_type_(""), hardcover_(false), series_name_(""),
      edition_number_(0), translator_("") {
  std::cout << "[Конструктор Book] Без параметрів" << std::endl;
}

// Пункт 7: Деструктор для відстеження порядку виклику деструкторів
Book::~Book() {
  std::cout << "[Деструктор Book] Автор: " << author_ << std::endl;
}

void Book::DisplayBookInfo() const {
  std::cout << "\n========== ІНФОРМАЦІЯ ПРО КНИГУ ==========" << std::endl;
  
  // Пункт 6: При protected наслідуванні можемо використовувати public методи базового класу
  // всередині похідного класу, але вони стають protected для зовнішнього світу
  std::cout << "ISBN: " << GetISBN() << std::endl;
  std::cout << "Наклад: " << circulation_ << std::endl;
  
  // Доступ до protected методів базового класу
  std::cout << "Кількість сторінок: " << GetPages() << std::endl;
  std::cout << "Ціна: " << std::fixed << std::setprecision(2) 
            << GetPrice() << " грн" << std::endl;
  
  std::cout << "\n--- Інформація про автора та жанр ---" << std::endl;
  std::cout << "Автор: " << author_ << std::endl;
  std::cout << "Жанр: " << genre_ << std::endl;
  std::cout << "Кількість розділів: " << chapter_count_ << std::endl;
  std::cout << "Тип палітурки: " << binding_type_ << std::endl;
  std::cout << "Тверда обкладинка: " << (hardcover_ ? "Так" : "Ні") << std::endl;
  
  if (!series_name_.empty()) {
    std::cout << "Серія: " << series_name_ << std::endl;
  }
  if (edition_number_ > 1) {
    std::cout << "Видання: " << edition_number_ << std::endl;
  }
  if (!translator_.empty()) {
    std::cout << "Перекладач: " << translator_ << std::endl;
  }
  std::cout << "==========================================\n" << std::endl;
}

// Пункт 6: Використання захищених методів базового класу через protected наслідування
void Book::ProcessBook() {
  std::cout << "[Book] Обробка книги..." << std::endl;
  
  // Можемо використовувати protected методи базового класу
  int current_pages = GetPages();
  double current_price = GetPrice();
  
  std::cout << "[Book] Сторінок: " << current_pages 
            << ", Ціна: " << current_price << " грн" << std::endl;
  
  // Виклик захищеного методу похідного класу
  UpdateBookDetails();
}

void Book::SetAuthor(const std::string& author) {
  author_ = author;
  std::cout << "[Book] Автора встановлено: " << author_ << std::endl;
}

std::string Book::GetAuthor() const {
  return author_;
}

void Book::SetGenre(const std::string& genre) {
  genre_ = genre;
  std::cout << "[Book] Жанр встановлено: " << genre_ << std::endl;
}

int Book::GetChapterCount() const {
  return chapter_count_;
}

// Захищений метод, який використовує захищені методи базового класу
void Book::UpdateBookDetails() {
  std::cout << "[Book::UpdateBookDetails] Оновлення деталей книги..." << std::endl;
  
  // Використання захищених методів базового класу
  // SetPages є protected методом у PrintedMaterial
  if (chapter_count_ > 20) {
    SetPages(GetPages() + 50);  // Додаємо сторінки для великих книг
    std::cout << "[Book] Велика книга, додано сторінок" << std::endl;
  }
}
