#include "Subscription.h"
#include <iostream>
#include <iomanip>

// Пункт 7: Конструктор другого базового класу для множинного наслідування
Subscription::Subscription(const std::string& name, const std::string& type,
                           double price, int months, const std::string& start)
    : subscriber_name_(name), subscription_type_(type),
      subscription_price_(price), months_remaining_(months),
      start_date_(start), end_date_(""), auto_renewal_(false),
      payment_method_("") {
  std::cout << "[Конструктор Subscription] Підписник: " << subscriber_name_ 
            << ", Тип: " << subscription_type_ << std::endl;
}

Subscription::Subscription()
    : subscriber_name_(""), subscription_type_(""), subscription_price_(0.0),
      months_remaining_(0), start_date_(""), end_date_(""),
      auto_renewal_(false), payment_method_("") {
  std::cout << "[Конструктор Subscription] Без параметрів" << std::endl;
}

// Пункт 7: Деструктор
Subscription::~Subscription() {
  std::cout << "[Деструктор Subscription] Підписник: " << subscriber_name_ << std::endl;
}

void Subscription::ShowSubscriptionInfo() const {
  std::cout << "--- Інформація про підписку ---" << std::endl;
  std::cout << "Підписник: " << subscriber_name_ << std::endl;
  std::cout << "Тип підписки: " << subscription_type_ << std::endl;
  std::cout << "Ціна: " << std::fixed << std::setprecision(2) 
            << subscription_price_ << " грн" << std::endl;
  std::cout << "Залишилось місяців: " << months_remaining_ << std::endl;
  std::cout << "Дата початку: " << start_date_ << std::endl;
  std::cout << "Автопродовження: " << (auto_renewal_ ? "Так" : "Ні") << std::endl;
  if (!payment_method_.empty()) {
    std::cout << "Спосіб оплати: " << payment_method_ << std::endl;
  }
}

void Subscription::RenewSubscription(int additional_months) {
  months_remaining_ += additional_months;
  std::cout << "[Subscription] Підписку продовжено на " << additional_months 
            << " місяців. Залишилось: " << months_remaining_ << std::endl;
}

bool Subscription::IsActive() const {
  return months_remaining_ > 0;
}

void Subscription::SetAutoRenewal(bool renewal) {
  auto_renewal_ = renewal;
  std::cout << "[Subscription] Автопродовження: " 
            << (renewal ? "Увімкнено" : "Вимкнено") << std::endl;
}

double Subscription::GetSubscriptionPrice() const {
  return subscription_price_;
}

int Subscription::GetMonthsRemaining() const {
  return months_remaining_;
}
