// Пункт 4: Клас з захищеним (protected) наслідуванням від PrintedMaterial
// Книга - демонструє третій тип наслідування
#ifndef BOOK_H
#define BOOK_H

#include "PrintedMaterial.h"
#include <string>

// Пункт 4: Захищене наслідування (protected inheritance)
// При захищеному наслідуванні: public члени базового класу стають protected у похідному
class Book : protected PrintedMaterial {
 private:
  std::string author_;
  std::string genre_;
  int chapter_count_;
  std::string binding_type_;
  bool hardcover_;
  std::string series_name_;
  int edition_number_;
  std::string translator_;

 public:
  // Пункт 5: Конструктор з параметрами (передає не менше 5 параметрів в базовий клас)
  // Пункт 7: Вивід повідомлень для демонстрації порядку виклику конструкторів
  Book(int id, const std::string& title,
       const std::string& publisher, double price, int pages,
       const std::string& isbn, int circulation, const std::string& lang,
       const std::string& author, const std::string& genre, int chapters);

  Book();

  // Пункт 7: Віртуальний деструктор для демонстрації порядку виклику деструкторів
  virtual ~Book();

  // Пункт 3, 6: Using-оголошення для надання доступу до певних членів базового класу
  // При protected наслідуванні public члени стають protected, тому робимо їх знову public
  using PrintedMaterial::GetISBN;
  using PrintedMaterial::UpdatePrice;
  using PrintedMaterial::circulation_;
  
  // Власні методи класу
  void DisplayBookInfo() const;
  void ProcessBook();
  
  // Методи для роботи з додатковими полями
  void SetAuthor(const std::string& author);
  std::string GetAuthor() const;
  void SetGenre(const std::string& genre);
  int GetChapterCount() const;

 protected:
  // Захищений метод, який використовує захищені методи базового класу
  void UpdateBookDetails();
};

#endif  // BOOK_H
