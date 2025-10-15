// Лаб 4, Пункт 3: Клас з приватним наслідуванням
#ifndef NEWSPAPER_H_
#define NEWSPAPER_H_

#include "PrintedMaterial.h"
#include <string>

// Пункт 3: Private наслідування - всі елементи базового класу стають private
class Newspaper : private PrintedMaterial {
 private:
  std::string publication_date_;
  std::string main_topic_;
  int article_count_;
  bool is_daily_;
  std::string region_;
  int delivery_time_;  // Час доставки в годинах
  double delivery_cost_;
  int editorial_staff_count_;
  
 public:
  // Пункт 5: Конструктор з передачею параметрів базовому класу
  Newspaper(int id, const std::string& title, const std::string& publisher,
            double price, int pages, const std::string& isbn,
            int circulation, const std::string& language,
            const std::string& date, const std::string& topic,
            int articles, bool daily, const std::string& region);
  
  Newspaper();
  ~Newspaper();
  
  // Пункт 3: Для доступу до private базового класу треба створити public методи
  void ShowInfo() const;  // Власний метод замість DisplayInfo()
  
  void SetArticleCount(int count);
  int GetArticleCount() const;
  std::string GetRegion() const;
  
  // Пункт 6: Using для надання доступу до конкретних методів базового класу
  using PrintedMaterial::GetISBN;  // Робимо public
  using PrintedMaterial::circulation_;  // Робимо public поле
  
  // Метод для демонстрації доступу до private базового класу
  void UpdateNewspaperPrice(double new_price);
  
  // Пункт 3: Метод, який працює з методами різних класів ієрархії
  void ProcessNewspaper();
};

#endif  // NEWSPAPER_H_
