// Лаб 4, Пункт 1, 2: Похідний клас Magazine (публічне наслідування)
#ifndef MAGAZINE_H_
#define MAGAZINE_H_

#include "PrintedMaterial.h"
#include <string>

// Пункт 2: Public наслідування - всі public елементи базового класу залишаються public
class Magazine : public PrintedMaterial {
 private:
  int issue_number_;
  std::string month_;
  std::string editor_;
  std::string category_;
  int frequency_per_year_;  // Частота виходу на рік
  bool has_subscription_;
  double subscription_discount_;
  int subscriber_count_;
  
 public:
  // Пункт 5: Конструктор приймає параметри і передає частину базовому класу
  Magazine(int id, const std::string& title, const std::string& publisher,
           double price, int pages, const std::string& isbn,
           int circulation, const std::string& language,
           int issue_number, const std::string& month, const std::string& editor,
           const std::string& category, int frequency);
  
  Magazine();
  
  // Пункт 7: Деструктор
  ~Magazine() override;
  
  // Перевизначений метод базового класу
  void DisplayInfo() const override;
  
  // Власні методи похідного класу
  void SetSubscriptionDiscount(double discount);
  void AddSubscriber();
  int GetIssueNumber() const;
  std::string GetCategory() const;
  
  // Пункт 6: Використання protected методів базового класу
  void IncreasePages(int additional_pages);
  
  // Пункт 6: Доступ до елементів базового класу через оператор ::
  void ShowBasePrice();
};

#endif  // MAGAZINE_H_
