// Лаб 4, Пункт 4: Додатковий клас для множинного наслідування
#ifndef DIGITAL_CONTENT_H_
#define DIGITAL_CONTENT_H_

#include <string>
#include <iostream>

// Перший додатковий клас для множинного наслідування
class DigitalContent {
 protected:
  std::string file_format_;
  double file_size_mb_;
  std::string download_url_;
  
 private:
  int download_count_;
  bool is_encrypted_;
  std::string encryption_type_;
  
 public:
  int access_level_;  // 1-free, 2-paid, 3-subscription
  std::string platform_;
  
  // Пункт 5: Конструктор з параметрами
  DigitalContent(const std::string& format, double size, const std::string& url,
                 int level, const std::string& platform);
  
  DigitalContent();
  
  // Пункт 7: Віртуальний деструктор
  virtual ~DigitalContent();
  
  virtual void ShowDigitalInfo() const;
  void UpdateDownloadCount();
  int GetDownloadCount() const;
  void SetEncryption(bool encrypted, const std::string& type);
};

#endif  // DIGITAL_CONTENT_H_
