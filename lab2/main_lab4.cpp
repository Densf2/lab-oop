// Лабораторна робота №4: Наслідування
// Демонстрація всіх типів наслідування та множинного наслідування

#include <iostream>
#include <string>
#include "PrintedMaterial.h"
#include "Magazine.h"
#include "Newspaper.h"
#include "Book.h"
#include "DigitalContent.h"
#include "Subscription.h"
#include "DigitalSubscription.h"

void PrintSeparator(const std::string& title) {
  std::cout << "\n" << std::string(60, '=') << std::endl;
  std::cout << title << std::endl;
  std::cout << std::string(60, '=') << std::endl;
}

// Пункт 8: Демонстраційний сценарій використання ієрархії класів
int main() {
  std::cout << "\n╔══════════════════════════════════════════════════════════╗" << std::endl;
  std::cout << "║     ЛАБОРАТОРНА РОБОТА №4: НАСЛІДУВАННЯ В C++           ║" << std::endl;
  std::cout << "╚══════════════════════════════════════════════════════════╝" << std::endl;

  // ============================================================
  // Пункт 1: Базовий клас PrintedMaterial з 8+ полями
  // ============================================================
  PrintSeparator("БАЗОВИЙ КЛАС: PrintedMaterial");
  PrintedMaterial material(1, "Основи програмування", "Академвидав",
                          450.0, 320, "978-966-580-123-4", 5000, "Українська");
  material.DisplayInfo();

  // ============================================================
  // Пункт 4: Public наслідування (Magazine від PrintedMaterial)
  // ============================================================
  PrintSeparator("PUBLIC НАСЛІДУВАННЯ: Magazine");
  std::cout << "\nПункт 7: Порядок виклику конструкторів (Base -> Derived):" << std::endl;
  Magazine magazine(100, "National Geographic", "NatGeo",
                   199.0, 120, "978-966-111-222-3", 50000, "Англійська",
                   245, "Червень", "John Smith", "Наука", 12);
  
  std::cout << "\nВикористання методів через public наслідування:" << std::endl;
  magazine.DisplayInfo();
  magazine.UpdatePrice(219.0);  // Доступ до public методу базового класу

  // ============================================================
  // Пункт 4: Private наслідування (Newspaper від PrintedMaterial)
  // Пункт 3: Using-оголошення для надання доступу
  // ============================================================
  PrintSeparator("PRIVATE НАСЛІДУВАННЯ: Newspaper");
  std::cout << "\nПункт 7: Порядок виклику конструкторів:" << std::endl;
  Newspaper newspaper(200, "Київські вісті", "Медіа Група",
                     25.0, 16, "978-966-333-444-5", 100000, "Українська",
                     "2024-06-15", "Політика", 12, true, "Київ");
  
  std::cout << "\nВикористання методів через private наслідування:" << std::endl;
  std::cout << "ISBN (через using): " << newspaper.GetISBN() << std::endl;
  std::cout << "Наклад (через using): " << newspaper.circulation_ << std::endl;
  newspaper.ProcessNewspaper();

  // ============================================================
  // Пункт 4: Protected наслідування (Book від PrintedMaterial)
  // ============================================================
  PrintSeparator("PROTECTED НАСЛІДУВАННЯ: Book");
  std::cout << "\nПункт 7: Порядок виклику конструкторів:" << std::endl;
  Book book(300, "Майстер і Маргарита", "Фоліо",
           380.0, 480, "978-966-03-5432-1", 10000, "Українська",
           "Михайло Булгаков", "Роман", 32);
  
  std::cout << "\nВикористання методів через protected наслідування:" << std::endl;
  book.DisplayBookInfo();
  book.UpdatePrice(420.0);  // Доступний через using-оголошення
  book.ProcessBook();

  // ============================================================
  // Пункт 4: МНОЖИННЕ НАСЛІДУВАННЯ (DigitalSubscription)
  // Наслідує від DigitalContent та Subscription
  // ============================================================
  PrintSeparator("МНОЖИННЕ НАСЛІДУВАННЯ: DigitalSubscription");
  std::cout << "\nПункт 7: Порядок виклику конструкторів (обидва базові + похідний):" << std::endl;
  DigitalSubscription digitalSub(
      // DigitalContent параметри
      "PDF", 125.5, "https://example.com/download", 2, "iOS/Android",
      // Subscription параметри
      "Іван Петренко", "Premium Annual", 1200.0, 12, "2024-01-15",
      // DigitalSubscription параметри
      "DSUB12345", 5, true);
  
  std::cout << "\nПункт 6: Використання методів з обох базових класів:" << std::endl;
  digitalSub.DisplayFullInfo();
  
  std::cout << "\nРобота з множинним наслідуванням:" << std::endl;
  digitalSub.ProcessDigitalSubscription();
  digitalSub.EnablePremiumContent();
  digitalSub.SetDeviceLimit(10);

  // ============================================================
  // Пункт 6: Демонстрація оператора розв'язання області видимості (::)
  // ============================================================
  PrintSeparator("ОПЕРАТОР РОЗВ'ЯЗАННЯ ОБЛАСТІ ВИДИМОСТІ (::)");
  std::cout << "\nПряме звернення до методів базових класів:" << std::endl;
  
  // Виклик методів через Magazine (public наслідування)
  magazine.UpdatePrice(229.0);  // Через public наслідування
  std::cout << "Ціна журналу оновлена" << std::endl;
  
  // Виклик методів через DigitalSubscription (множинне наслідування)
  digitalSub.ShowDigitalInfo();  // З DigitalContent
  digitalSub.ShowSubscriptionInfo();  // З Subscription

  // ============================================================
  // Пункт 7: Демонстрація порядку виклику деструкторів
  // ============================================================
  PrintSeparator("ПОРЯДОК ВИКЛИКУ ДЕСТРУКТОРІВ");
  std::cout << "\nСтворення та знищення об'єкта з множинним наслідуванням:" << std::endl;
  {
    DigitalSubscription tempSub(
        "EPUB", 45.2, "https://temp.com", 1, "Web",
        "Тест Користувач", "Monthly", 99.0, 1, "2024-06-01",
        "TEMP001", 3, false);
    std::cout << "\n[Вихід з блоку - виклик деструкторів]" << std::endl;
  }
  std::cout << "[Деструктори викликані в зворотному порядку: Derived -> Base2 -> Base1]" << std::endl;

  // ============================================================
  // Пункт 2: Демонстрація рівнів доступу (public/protected/private)
  // ============================================================
  PrintSeparator("РІВНІ ДОСТУПУ");
  std::cout << "\nPublic методи (доступні всім):" << std::endl;
  material.UpdatePrice(500.0);
  std::cout << "ISBN: " << material.GetISBN() << std::endl;
  
  std::cout << "\nProtected методи (доступні лише в похідних класах):" << std::endl;
  std::cout << "Book використовує protected методи базового класу" << std::endl;
  book.ProcessBook();  // Всередині використовує GetPages(), SetPages()
  
  std::cout << "\nPrivate методи (доступні лише в самому класі):" << std::endl;
  std::cout << "ValidatePrice/ValidatePages викликаються всередині класу" << std::endl;

  // ============================================================
  // Пункт 5: Демонстрація передачі параметрів у базовий клас
  // ============================================================
  PrintSeparator("ПЕРЕДАЧА ПАРАМЕТРІВ У БАЗОВИЙ КЛАС");
  std::cout << "\nСтворення Magazine з 8 параметрами для базового класу:" << std::endl;
  Magazine newMag(999, "Science Today", "SciPress",
                 299.0, 150, "978-123-456-789-0", 30000, "Англійська",
                 123, "Липень", "Dr. Smith", "Технології", 4);
  std::cout << "Конструктор Magazine передав 8 параметрів у PrintedMaterial" << std::endl;

  // ============================================================
  // ЗАВЕРШЕННЯ ПРОГРАМИ
  // ============================================================
  PrintSeparator("ЗАВЕРШЕННЯ ПРОГРАМИ");
  std::cout << "\nПункт 7: При завершенні main() деструктори викликаються для всіх об'єктів" << std::endl;
  std::cout << "Порядок: зворотний до створення (LIFO - Last In First Out)" << std::endl;
  std::cout << "\nПрограма завершена успішно!" << std::endl;

  return 0;
}
