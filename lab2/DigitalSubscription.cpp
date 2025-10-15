#include "DigitalSubscription.h"
#include <iostream>
#include <iomanip>

// Пункт 5: Конструктор похідного класу, який викликає конструктори обох базових класів
// Пункт 7: Вивід повідомлень для відстеження порядку виклику конструкторів
DigitalSubscription::DigitalSubscription(
    const std::string& format, double size, const std::string& url,
    int access_level, const std::string& platform,
    const std::string& subscriber_name, const std::string& sub_type,
    double sub_price, int months, const std::string& start_date,
    const std::string& sub_id, int device_limit, bool offline)
    // Пункт 4: Ініціалізація обох базових класів при множинному наслідуванні
    : DigitalContent(format, size, url, access_level, platform),
      Subscription(subscriber_name, sub_type, sub_price, months, start_date),
      subscription_id_(sub_id), device_limit_(std::to_string(device_limit)),
      offline_access_(offline), simultaneous_devices_(device_limit),
      content_library_("standard"), premium_content_(false),
      notification_type_("email"), discount_percentage_(0.0) {
  std::cout << "[Конструктор DigitalSubscription] ID підписки: " 
            << subscription_id_ << ", Ліміт пристроїв: " << device_limit_ << std::endl;
}

DigitalSubscription::DigitalSubscription()
    : DigitalContent(), Subscription(),
      subscription_id_(""), device_limit_("0"), offline_access_(false),
      simultaneous_devices_(0), content_library_(""), premium_content_(false),
      notification_type_(""), discount_percentage_(0.0) {
  std::cout << "[Конструктор DigitalSubscription] Без параметрів" << std::endl;
}

// Пункт 7: Деструктор для відстеження порядку виклику деструкторів
DigitalSubscription::~DigitalSubscription() {
  std::cout << "[Деструктор DigitalSubscription] ID: " << subscription_id_ << std::endl;
}

// Пункт 6: Використання оператора розв'язання області видимості для доступу до методів базових класів
void DigitalSubscription::DisplayFullInfo() const {
  std::cout << "\n========== ЦИФРОВА ПІДПИСКА ==========" << std::endl;
  std::cout << "ID підписки: " << subscription_id_ << std::endl;
  
  // Пункт 6: Виклик методів з різних базових класів за допомогою оператора ::
  std::cout << "\n--- Цифровий контент ---" << std::endl;
  DigitalContent::ShowDigitalInfo();
  
  std::cout << "\n--- Підписка ---" << std::endl;
  Subscription::ShowSubscriptionInfo();
  
  std::cout << "\n--- Додаткова інформація ---" << std::endl;
  std::cout << "Ліміт пристроїв: " << device_limit_ << std::endl;
  std::cout << "Одночасних пристроїв: " << simultaneous_devices_ << std::endl;
  std::cout << "Офлайн доступ: " << (offline_access_ ? "Так" : "Ні") << std::endl;
  std::cout << "Бібліотека контенту: " << content_library_ << std::endl;
  std::cout << "Преміум контент: " << (premium_content_ ? "Так" : "Ні") << std::endl;
  std::cout << "Тип сповіщень: " << notification_type_ << std::endl;
  if (discount_percentage_ > 0) {
    std::cout << "Знижка: " << discount_percentage_ << "%" << std::endl;
    std::cout << "Фінальна ціна: " << std::fixed << std::setprecision(2) 
              << CalculateFinalPrice() << " грн" << std::endl;
  }
  std::cout << "========================================\n" << std::endl;
}

// Пункт 6: Використання методів обох базових класів через оператор розв'язання області видимості
void DigitalSubscription::ProcessDigitalSubscription() {
  std::cout << "[DigitalSubscription] Обробка цифрової підписки..." << std::endl;
  
  // Використання методів з DigitalContent
  DigitalContent::UpdateDownloadCount();
  int downloads = DigitalContent::GetDownloadCount();
  
  // Використання захищених методів з Subscription
  int months = GetMonthsRemaining();
  double price = GetSubscriptionPrice();
  
  std::cout << "[DigitalSubscription] Завантажень: " << downloads 
            << ", Місяців: " << months << ", Ціна: " << price << " грн" << std::endl;
  
  // Перевірка активності підписки
  if (IsActive()) {
    std::cout << "[DigitalSubscription] Підписка активна" << std::endl;
  } else {
    std::cout << "[DigitalSubscription] Підписка неактивна" << std::endl;
  }
}

void DigitalSubscription::SetDeviceLimit(int limit) {
  simultaneous_devices_ = limit;
  device_limit_ = std::to_string(limit);
  std::cout << "[DigitalSubscription] Ліміт пристроїв встановлено: " << limit << std::endl;
}

void DigitalSubscription::EnablePremiumContent() {
  premium_content_ = true;
  content_library_ = "premium";
  discount_percentage_ = 15.0;
  std::cout << "[DigitalSubscription] Преміум контент увімкнено, знижка 15%" << std::endl;
}

double DigitalSubscription::CalculateFinalPrice() const {
  double base_price = GetSubscriptionPrice();
  return base_price * (1.0 - discount_percentage_ / 100.0);
}
