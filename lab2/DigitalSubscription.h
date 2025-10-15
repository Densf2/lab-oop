// Пункт 4: Клас з множинним наслідуванням (успадковує 2 і більше базових класів)
// Електронна підписка на видання (наслідує DigitalContent та Subscription)
#ifndef DIGITAL_SUBSCRIPTION_H
#define DIGITAL_SUBSCRIPTION_H

#include "DigitalContent.h"
#include "Subscription.h"
#include <string>

// Пункт 4: Множинне наслідування - наслідує два базові класи
class DigitalSubscription : public DigitalContent, public Subscription {
 private:
  std::string subscription_id_;
  std::string device_limit_;
  bool offline_access_;
  int simultaneous_devices_;
  std::string content_library_;
  bool premium_content_;
  std::string notification_type_;
  double discount_percentage_;

 public:
  // Пункт 5: Конструктор з параметрами (передає не менше 5 параметрів в базовий клас)
  // Пункт 7: Вивід повідомлень для демонстрації порядку виклику конструкторів
  DigitalSubscription(
      // Параметри для DigitalContent
      const std::string& format, double size, const std::string& url,
      int access_level, const std::string& platform,
      // Параметри для Subscription
      const std::string& subscriber_name, const std::string& sub_type,
      double sub_price, int months, const std::string& start_date,
      // Власні параметри
      const std::string& sub_id, int device_limit, bool offline);

  DigitalSubscription();

  // Пункт 7: Віртуальний деструктор для демонстрації порядку виклику деструкторів
  virtual ~DigitalSubscription();

  // Пункт 6: Використання оператора розв'язання області видимості
  // Метод для відображення повної інформації про цифрову підписку
  void DisplayFullInfo() const;
  
  // Метод для обробки цифрової підписки
  void ProcessDigitalSubscription();
  
  // Методи для роботи з додатковими полями
  void SetDeviceLimit(int limit);
  void EnablePremiumContent();
  double CalculateFinalPrice() const;  // З урахуванням знижки
};

#endif  // DIGITAL_SUBSCRIPTION_H
