#include "DigitalContent.h"
#include <iostream>
#include <iomanip>

// Пункт 7: Конструктор першого базового класу для множинного наслідування
DigitalContent::DigitalContent(const std::string& format, double size,
                               const std::string& url, int level,
                               const std::string& platform)
    : file_format_(format), file_size_mb_(size), download_url_(url),
      download_count_(0), is_encrypted_(false), encryption_type_(""),
      access_level_(level), platform_(platform) {
  std::cout << "[Конструктор DigitalContent] Формат: " << file_format_ 
            << ", Розмір: " << file_size_mb_ << " MB" << std::endl;
}

DigitalContent::DigitalContent()
    : file_format_(""), file_size_mb_(0.0), download_url_(""),
      download_count_(0), is_encrypted_(false), encryption_type_(""),
      access_level_(1), platform_("") {
  std::cout << "[Конструктор DigitalContent] Без параметрів" << std::endl;
}

// Пункт 7: Деструктор
DigitalContent::~DigitalContent() {
  std::cout << "[Деструктор DigitalContent] Формат: " << file_format_ << std::endl;
}

void DigitalContent::ShowDigitalInfo() const {
  std::cout << "--- Цифровий контент ---" << std::endl;
  std::cout << "Формат файлу: " << file_format_ << std::endl;
  std::cout << "Розмір: " << std::fixed << std::setprecision(2) 
            << file_size_mb_ << " MB" << std::endl;
  std::cout << "URL завантаження: " << download_url_ << std::endl;
  std::cout << "Кількість завантажень: " << download_count_ << std::endl;
  std::cout << "Рівень доступу: " << access_level_ << std::endl;
  std::cout << "Платформа: " << platform_ << std::endl;
  if (is_encrypted_) {
    std::cout << "Шифрування: " << encryption_type_ << std::endl;
  }
}

void DigitalContent::UpdateDownloadCount() {
  download_count_++;
  std::cout << "[DigitalContent] Завантажень: " << download_count_ << std::endl;
}

int DigitalContent::GetDownloadCount() const {
  return download_count_;
}

void DigitalContent::SetEncryption(bool encrypted, const std::string& type) {
  is_encrypted_ = encrypted;
  encryption_type_ = type;
  std::cout << "[DigitalContent] Шифрування: " 
            << (encrypted ? "Увімкнено (" + type + ")" : "Вимкнено") << std::endl;
}
