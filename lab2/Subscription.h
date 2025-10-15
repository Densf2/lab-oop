// Пункт 4: Другий базовий клас для множинного наслідування
// Клас для роботи з підписками на видання
#ifndef SUBSCRIPTION_H
#define SUBSCRIPTION_H

#include <string>

class Subscription {
 protected:
  // Пункт 1: Поля класу (щонайменше 8)
  std::string subscriber_name_;
  std::string subscription_type_;  // monthly, annual, digital-only
  double subscription_price_;
  int months_remaining_;
  std::string start_date_;
  std::string end_date_;
  bool auto_renewal_;
  std::string payment_method_;

 public:
  // Пункт 5: Конструктор з параметрами (не менше 5)
  // Пункт 7: Вивід повідомлень у конструкторі
  Subscription(const std::string& name, const std::string& type,
               double price, int months, const std::string& start);
  
  Subscription();
  
  // Пункт 7: Віртуальний деструктор з виводом повідомлень
  virtual ~Subscription();

  // Пункт 2: Відкриті методи
  void ShowSubscriptionInfo() const;
  void RenewSubscription(int additional_months);
  bool IsActive() const;
  
  // Пункт 2: Захищені методи для похідних класів
 protected:
  void SetAutoRenewal(bool renewal);
  double GetSubscriptionPrice() const;
  int GetMonthsRemaining() const;
};

#endif  // SUBSCRIPTION_H
