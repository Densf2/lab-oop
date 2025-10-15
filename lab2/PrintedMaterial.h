// Лаб 4: Базовий клас для ієрархії наслідування
// Пункт 1: Базовий клас PrintedMaterial з не менше 8 полів
#ifndef PRINTED_MATERIAL_H_
#define PRINTED_MATERIAL_H_

#include <string>
#include <iostream>

// Базовий клас - Друковані матеріали
class PrintedMaterial {
 protected:  // Пункт 2: Protected - доступні похідним класам
  int material_id_;
  std::string title_;
  std::string publisher_;
  
 private:  // Пункт 2: Private - доступні тільки через методи
  double price_;
  int pages_;
  std::string isbn_;
  
 public:  // Пункт 2: Public - доступні всім
  int circulation_;
  std::string language_;
  
  // Пункт 5: Конструктор з не менше 5 аргументів
  PrintedMaterial(int id, const std::string& title, const std::string& publisher,
                  double price, int pages, const std::string& isbn,
                  int circulation, const std::string& language);
  
  // Конструктор без параметрів
  PrintedMaterial();
  
  // Віртуальний деструктор для правильного знищення похідних об'єктів
  virtual ~PrintedMaterial();
  
  // Пункт 2: Public методи - доступні всім
  virtual void DisplayInfo() const;
  void UpdatePrice(double new_price);
  std::string GetISBN() const;
  
  // Protected методи - доступні похідним класам
 protected:
  void SetPages(int pages);
  double GetPrice() const;
  int GetPages() const;
  
  // Private методи - тільки для внутрішнього використання
 private:
  void ValidatePrice();
  void ValidatePages();
};

#endif  // PRINTED_MATERIAL_H_
