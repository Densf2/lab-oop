---

## ЛАБОРАТОРНА РОБОТА №4: НАСЛІДУВАННЯ

### Основні файли для Лаб 4:

- `PrintedMaterial.h` - базовий клас для ієрархії наслідування
- `PrintedMaterial.cpp` - реалізація базового класу
- `Magazine.h` - клас з public наслідуванням
- `Magazine.cpp` - реалізація Magazine
- `Newspaper.h` - клас з private наслідуванням
- `Newspaper.cpp` - реалізація Newspaper
- `Book.h` - клас з protected наслідуванням
- `Book.cpp` - реалізація Book
- `DigitalContent.h` - перший базовий клас для множинного наслідування
- `DigitalContent.cpp` - реалізація DigitalContent
- `Subscription.h` - другий базовий клас для множинного наслідування
- `Subscription.cpp` - реалізація Subscription
- `DigitalSubscription.h` - клас з множинним наслідуванням
- `DigitalSubscription.cpp` - реалізація DigitalSubscription
- `main_lab4.cpp` - демонстраційна програма

---

### ПУНКТ 1: Базовий клас з 8+ полями

Створив базовий клас **PrintedMaterial** з 8 полями для представлення друкованих матеріалів.

**Оголошення:** `PrintedMaterial.h`, рядки 6-42

```cpp
class PrintedMaterial {
 protected:
  std::string material_id_;      // 1. Унікальний ідентифікатор
  std::string title_;            // 2. Назва матеріалу
  std::string publisher_;        // 3. Видавництво

 public:
  double base_price_;            // 4. Базова ціна (public)
  std::string isbn_;             // 5. ISBN номер (public)

 protected:
  int page_count_;               // 6. Кількість сторінок
  int circulation_;              // 7. Наклад
  std::string language_;         // 8. Мова видання

 private:
  double price_with_discount_;   // Ціна зі знижкою (private)
  int publication_year_;         // Рік видання (private)
  bool in_stock_;                // Наявність на складі (private)
};
```

**Реалізація:** `PrintedMaterial.cpp`, рядки 4-90

---

### ПУНКТ 2: Різні рівні доступу (public/protected/private)

Базовий клас **PrintedMaterial** демонструє всі три рівні доступу.

**Оголошення:** `PrintedMaterial.h`, рядки 6-42

#### Public секція (доступна всім):

```cpp
public:
  // Публічні поля
  double base_price_;
  std::string isbn_;

  // Публічні методи
  void DisplayInfo() const;              // Відображення інформації
  void UpdatePrice(double new_price);    // Оновлення ціни
  std::string GetISBN() const;           // Отримання ISBN
```

#### Protected секція (доступна похідним класам):

```cpp
protected:
  // Захищені поля
  std::string material_id_;
  std::string title_;
  std::string publisher_;
  int page_count_;
  int circulation_;
  std::string language_;

  // Захищені методи
  void SetPages(int pages);              // Встановлення кількості сторінок
  double GetPrice() const;               // Отримання ціни
  int GetPages() const;                  // Отримання кількості сторінок
```

#### Private секція (доступна тільки в класі):

```cpp
private:
  // Приватні поля
  double price_with_discount_;
  int publication_year_;
  bool in_stock_;

  // Приватні методи
  bool ValidatePrice(double price) const;  // Валідація ціни
  bool ValidatePages(int pages) const;     // Валідація сторінок
```

**Демонстрація:** `main_lab4.cpp`, функція `main()`, секція "РІВНІ ДОСТУПУ" (рядки 146-157)

---

### ПУНКТ 3: Private наслідування з using-оголошеннями

Створив клас **Newspaper** з private наслідуванням від PrintedMaterial.

**Оголошення:** `Newspaper.h`, рядки 6-45

```cpp
// Private наслідування - всі public та protected члени базового класу стають private
class Newspaper : private PrintedMaterial {
 private:
  std::string publication_date_;
  std::string main_topic_;
  int article_count_;
  // ... інші поля

 public:
  // Using-оголошення для надання доступу до обраних членів базового класу
  using PrintedMaterial::GetISBN;        // Метод стає public
  using PrintedMaterial::circulation_;   // Поле стає public

  Newspaper(const std::string& id, ...);
  void ProcessNewspaper();
};
```

**Що робить using:**

- При private наслідуванні всі члени базового класу стають private
- Using-оголошення робить обрані члени знову доступними як public

**Реалізація:** `Newspaper.cpp`, рядки 4-96
**Демонстрація:** `main_lab4.cpp`, секція "PRIVATE НАСЛІДУВАННЯ" (рядки 50-60)

---

### ПУНКТ 4: Три типи наслідування та множинне наслідування

Реалізував всі чотири види наслідування:

#### 1. Public наслідування (Magazine від PrintedMaterial)

**Оголошення:** `Magazine.h`, рядок 8

```cpp
class Magazine : public PrintedMaterial {
  // При public наслідуванні:
  // - public члени базового класу залишаються public
  // - protected члени залишаються protected
};
```

**Особливості:**

- Усі public методи базового класу доступні через об'єкт Magazine
- Protected методи доступні всередині Magazine
- Найбільш поширений тип наслідування

**Файли:** `Magazine.h`, `Magazine.cpp`
**Демонстрація:** `main_lab4.cpp`, секція "PUBLIC НАСЛІДУВАННЯ" (рядки 38-47)

#### 2. Private наслідування (Newspaper від PrintedMaterial)

**Оголошення:** `Newspaper.h`, рядок 8

```cpp
class Newspaper : private PrintedMaterial {
  // При private наслідуванні:
  // - public члени базового класу стають private
  // - protected члени стають private
  // - потрібні using-оголошення для доступу
};
```

**Особливості:**

- Використовується для реалізації через наслідування (implementation inheritance)
- Using-оголошення для вибіркового надання доступу

**Файли:** `Newspaper.h`, `Newspaper.cpp`
**Демонстрація:** `main_lab4.cpp`, секція "PRIVATE НАСЛІДУВАННЯ" (рядки 50-60)

#### 3. Protected наслідування (Book від PrintedMaterial)

**Оголошення:** `Book.h`, рядок 10

```cpp
class Book : protected PrintedMaterial {
  // При protected наслідуванні:
  // - public члени базового класу стають protected
  // - protected члени залишаються protected
  // - можливе подальше наслідування з доступом
};
```

**Особливості:**

- Середній варіант між public та private
- Зберігає можливість подальшого наслідування
- Public методи базового класу стають protected

**Файли:** `Book.h`, `Book.cpp`
**Демонстрація:** `main_lab4.cpp`, секція "PROTECTED НАСЛІДУВАННЯ" (рядки 62-72)

#### 4. Множинне наслідування (DigitalSubscription)

**Оголошення:** `DigitalSubscription.h`, рядок 10

```cpp
// Наслідує одразу два базові класи
class DigitalSubscription : public DigitalContent, public Subscription {
 private:
  std::string subscription_id_;
  // ... інші поля

 public:
  DigitalSubscription(
      // Параметри для DigitalContent (5 параметрів)
      const std::string& format, double size, const std::string& url,
      int access_level, const std::string& platform,
      // Параметри для Subscription (5 параметрів)
      const std::string& subscriber_name, const std::string& sub_type,
      double sub_price, int months, const std::string& start_date,
      // Власні параметри
      const std::string& sub_id, int device_limit, bool offline);
};
```

**Базові класи для множинного наслідування:**

1. **DigitalContent** (`DigitalContent.h`, `DigitalContent.cpp`) - 8 полів:

   - file*format*, file*size_mb*, download*url*, download*count*
   - is*encrypted*, encryption*type*, access*level*, platform\_

2. **Subscription** (`Subscription.h`, `Subscription.cpp`) - 8 полів:
   - subscriber*name*, subscription*type*, subscription*price*
   - months*remaining*, start*date*, end*date*, auto*renewal*, payment*method*

**Реалізація:** `DigitalSubscription.cpp`, рядки 4-103
**Демонстрація:** `main_lab4.cpp`, секція "МНОЖИННЕ НАСЛІДУВАННЯ" (рядки 74-96)

---

### ПУНКТ 5: Конструктор з 8+ параметрами для базового класу

Кожен похідний клас передає не менше 8 параметрів у конструктор базового класу.

#### Magazine (public наслідування):

**Оголошення:** `Magazine.h`, рядки 19-23

```cpp
Magazine(const std::string& id, const std::string& title,
         const std::string& publisher, double price, int pages,
         const std::string& isbn, int circulation, const std::string& lang,
         int issue, const std::string& month, const std::string& editor,
         const std::string& category, const std::string& frequency);
```

**Реалізація:** `Magazine.cpp`, рядки 7-24

```cpp
Magazine::Magazine(const std::string& id, ...)
    // Передача 8 параметрів у базовий клас PrintedMaterial
    : PrintedMaterial(id, title, publisher, price, pages, isbn, circulation, lang),
      issue_number_(issue),
      publication_month_(month),
      // ... ініціалізація власних полів
```

#### DigitalSubscription (множинне наслідування):

**Реалізація:** `DigitalSubscription.cpp`, рядки 7-27

```cpp
DigitalSubscription::DigitalSubscription(...)
    // Передача 5 параметрів у DigitalContent
    : DigitalContent(format, size, url, access_level, platform),
      // Передача 5 параметрів у Subscription
      Subscription(subscriber_name, sub_type, sub_price, months, start_date),
      // Ініціалізація власних полів
      subscription_id_(sub_id), ...
```

**Демонстрація:** `main_lab4.cpp`, секція "ПЕРЕДАЧА ПАРАМЕТРІВ" (рядки 159-167)

---

### ПУНКТ 6: Оператор розв'язання області видимості (::) та using

Демонстрація використання оператора :: та using-оголошень.

#### 1. Оператор :: у Magazine:

**Файл:** `Magazine.cpp`, метод `DisplayMagazineInfo()`, рядки 40-67

```cpp
void Magazine::DisplayMagazineInfo() const {
  // Виклик методу базового класу через оператор ::
  PrintedMaterial::DisplayInfo();

  // Доступ до захищених методів базового класу
  int pages = GetPages();  // Без ::, бо protected
  double price = GetPrice();

  // Використання публічних полів базового класу
  std::cout << "ISBN: " << isbn_ << std::endl;
  std::cout << "Ціна: " << base_price_ << std::endl;
}
```

#### 2. Оператор :: у DigitalSubscription:

**Файл:** `DigitalSubscription.cpp`, метод `DisplayFullInfo()`, рядки 38-63

```cpp
void DigitalSubscription::DisplayFullInfo() const {
  // Виклик методів з різних базових класів через ::
  DigitalContent::ShowDigitalInfo();    // З першого базового
  Subscription::ShowSubscriptionInfo(); // З другого базового
}
```

**Файл:** `DigitalSubscription.cpp`, метод `ProcessDigitalSubscription()`, рядки 66-84

```cpp
void DigitalSubscription::ProcessDigitalSubscription() {
  // Явне вказання класу для методів
  DigitalContent::UpdateDownloadCount();
  int downloads = DigitalContent::GetDownloadCount();

  // Використання методів другого базового класу
  int months = GetMonthsRemaining();  // З Subscription
  bool active = IsActive();           // З Subscription
}
```

#### 3. Using-оголошення у Newspaper:

**Файл:** `Newspaper.h`, рядки 31-33

```cpp
class Newspaper : private PrintedMaterial {
 public:
  // Using робить private члени базового класу знову public
  using PrintedMaterial::GetISBN;      // Метод
  using PrintedMaterial::circulation_; // Поле
};
```

#### 4. Using-оголошення у Book:

**Файл:** `Book.h`, рядки 30-33

```cpp
class Book : protected PrintedMaterial {
 public:
  // Using робить protected члени знову public
  using PrintedMaterial::GetISBN;
  using PrintedMaterial::UpdatePrice;
  using PrintedMaterial::circulation_;
};
```

**Демонстрація:** `main_lab4.cpp`, секція "ОПЕРАТОР РОЗВ'ЯЗАННЯ" (рядки 98-111)

---

### ПУНКТ 7: Конструктори та деструктори з виводом повідомлень

Усі класи мають конструктори та деструктори з виводом для відстеження порядку виклику.

#### Базовий клас PrintedMaterial:

**Файл:** `PrintedMaterial.cpp`

**Конструктор з параметрами (рядки 5-20):**

```cpp
PrintedMaterial::PrintedMaterial(const std::string& id, ...)
    : material_id_(id), title_(title), ... {
  std::cout << "[Конструктор PrintedMaterial] ID: " << material_id_
            << ", Назва: " << title_ << std::endl;
}
```

**Конструктор без параметрів (рядки 22-29):**

```cpp
PrintedMaterial::PrintedMaterial()
    : material_id_(""), title_(""), ... {
  std::cout << "[Конструктор PrintedMaterial] Без параметрів" << std::endl;
}
```

**Деструктор (рядки 31-34):**

```cpp
PrintedMaterial::~PrintedMaterial() {
  std::cout << "[Деструктор PrintedMaterial] ID: " << material_id_ << std::endl;
}
```

#### Magazine (public наслідування):

**Файл:** `Magazine.cpp`

**Конструктор (рядки 7-24):**

```cpp
Magazine::Magazine(...)
    : PrintedMaterial(id, title, ...), // Спочатку базовий
      issue_number_(issue), ... {
  std::cout << "[Конструктор Magazine] Номер: " << issue_number_ << std::endl;
}
```

**Деструктор (рядки 32-35):**

```cpp
Magazine::~Magazine() {
  std::cout << "[Деструктор Magazine] Номер: " << issue_number_ << std::endl;
}
```

#### DigitalSubscription (множинне наслідування):

**Файл:** `DigitalSubscription.cpp`

**Конструктор (рядки 7-27):**

```cpp
DigitalSubscription::DigitalSubscription(...)
    : DigitalContent(...),    // Перший базовий
      Subscription(...),      // Другий базовий
      subscription_id_(...) { // Власні поля
  std::cout << "[Конструктор DigitalSubscription] ID: "
            << subscription_id_ << std::endl;
}
```

**Порядок виклику конструкторів при множинному наслідуванні:**

1. Конструктор DigitalContent (перший в списку наслідування)
2. Конструктор Subscription (другий в списку наслідування)
3. Конструктор DigitalSubscription (похідний клас)

**Порядок виклику деструкторів (зворотний):**

1. Деструктор DigitalSubscription
2. Деструктор Subscription
3. Деструктор DigitalContent

**Демонстрація:** `main_lab4.cpp`, секція "ПОРЯДОК ВИКЛИКУ ДЕСТРУКТОРІВ" (рядки 113-126)

```cpp
{
  DigitalSubscription tempSub(...);
  std::cout << "\n[Вихід з блоку - виклик деструкторів]" << std::endl;
}
// Виведе:
// [Конструктор DigitalContent] ...
// [Конструктор Subscription] ...
// [Конструктор DigitalSubscription] ...
// [Вихід з блоку - виклик деструкторів]
// [Деструктор DigitalSubscription] ...
// [Деструктор Subscription] ...
// [Деструктор DigitalContent] ...
```

---

### ПУНКТ 8: Демонстраційний сценарій

Створив повний демонстраційний сценарій у `main_lab4.cpp`.

**Файл:** `main_lab4.cpp`, функція `main()`, рядки 16-178

#### Структура демонстрації:

1. **Базовий клас (рядки 26-30):**

   - Створення об'єкта PrintedMaterial
   - Виклик методів базового класу

2. **Public наслідування (рядки 38-47):**

   - Створення Magazine
   - Демонстрація доступу до public методів базового класу
   - Виклик власних методів

3. **Private наслідування (рядки 50-60):**

   - Створення Newspaper
   - Демонстрація using-оголошень
   - Обмежений доступ до базового класу

4. **Protected наслідування (рядки 62-72):**

   - Створення Book
   - Демонстрація using-оголошень для protected членів
   - Доступ до захищених методів

5. **Множинне наслідування (рядки 74-96):**

   - Створення DigitalSubscription
   - Виклик методів з обох базових класів
   - Демонстрація складної ієрархії

6. **Оператор :: (рядки 98-111):**

   - Пряме звернення до методів базових класів
   - Розв'язання неоднозначності при множинному наслідуванні

7. **Порядок конструкторів/деструкторів (рядки 113-126):**

   - Створення та знищення об'єкта в блоці
   - Вивід повідомлень про порядок викликів

8. **Рівні доступу (рядки 146-157):**

   - Демонстрація public методів
   - Обмеження для protected та private

9. **Передача параметрів (рядки 159-167):**
   - Створення об'єкта з багатьма параметрами
   - Передача параметрів у базовий клас

#### Допоміжна функція:

**PrintSeparator()** (рядки 11-15):

```cpp
void PrintSeparator(const std::string& title) {
  std::cout << "\n" << std::string(60, '=') << std::endl;
  std::cout << title << std::endl;
  std::cout << std::string(60, '=') << std::endl;
}
```

**Призначення:** Форматований вивід заголовків секцій для кращої читабельності.

---

### ПУНКТ 9: Коментарі для кожної вимоги

Усі файли містять коментарі з номерами пунктів завдання.

#### Приклади коментарів:

**PrintedMaterial.h:**

```cpp
// Пункт 1: Базовий клас з 8+ полями
class PrintedMaterial {
 protected:
  // Пункт 1: Поля класу (щонайменше 8)
  std::string material_id_;
  std::string title_;
  // ...

 public:
  // Пункт 2: Публічні методи
  void DisplayInfo() const;

 protected:
  // Пункт 2: Захищені методи для похідних класів
  void SetPages(int pages);

 private:
  // Пункт 2: Приватні методи
  bool ValidatePrice(double price) const;
};
```

**Magazine.h:**

```cpp
// Пункт 4: Клас з public наслідуванням від базового класу
class Magazine : public PrintedMaterial {
  // Пункт 5: Конструктор з параметрами (не менше 5 для базового класу)
  Magazine(const std::string& id, ...);
};
```

**Newspaper.h:**

```cpp
// Пункт 4: Клас з private наслідуванням від базового класу
class Newspaper : private PrintedMaterial {
 public:
  // Пункт 3: Using-оголошення для надання доступу
  using PrintedMaterial::GetISBN;
};
```

**Book.h:**

```cpp
// Пункт 4: Клас з protected наслідуванням від базового класу
class Book : protected PrintedMaterial {
  // Пункт 3, 6: Using-оголошення для надання доступу
  using PrintedMaterial::GetISBN;
};
```

**DigitalSubscription.h:**

```cpp
// Пункт 4: Клас з множинним наслідуванням
class DigitalSubscription : public DigitalContent, public Subscription {
  // Пункт 7: Віртуальний деструктор для демонстрації порядку
  virtual ~DigitalSubscription();
};
```

**main_lab4.cpp:**

```cpp
// Пункт 8: Демонстраційний сценарій використання ієрархії класів
int main() {
  // ============================================================
  // Пункт 1: Базовий клас PrintedMaterial з 8+ полями
  // ============================================================
  PrintSeparator("БАЗОВИЙ КЛАС: PrintedMaterial");

  // ============================================================
  // Пункт 4: Public наслідування (Magazine від PrintedMaterial)
  // ============================================================
  PrintSeparator("PUBLIC НАСЛІДУВАННЯ: Magazine");
  std::cout << "\nПункт 7: Порядок виклику конструкторів" << std::endl;
}
```

---

### ПУНКТ 10: UML-діаграма

#### Ієрархія класів:

```
                    ┌─────────────────────┐
                    │  PrintedMaterial    │
                    │  (Базовий клас)     │
                    ├─────────────────────┤
                    │ - material_id_      │
                    │ - title_            │
                    │ - publisher_        │
                    │ + base_price_       │
                    │ + isbn_             │
                    │ # page_count_       │
                    │ # circulation_      │
                    │ # language_         │
                    │ - price_discount_   │
                    ├─────────────────────┤
                    │ + DisplayInfo()     │
                    │ + UpdatePrice()     │
                    │ + GetISBN()         │
                    │ # SetPages()        │
                    │ # GetPrice()        │
                    │ - ValidatePrice()   │
                    └──────────┬──────────┘
                               │
              ┌────────────────┼────────────────┐
              │                │                │
    ┌─────────▼──────┐ ┌──────▼──────┐ ┌───────▼────────┐
    │   Magazine      │ │  Newspaper   │ │     Book       │
    │  (public)       │ │  (private)   │ │  (protected)   │
    ├─────────────────┤ ├──────────────┤ ├────────────────┤
    │ - issue_number_ │ │ - date_      │ │ - author_      │
    │ - month_        │ │ - topic_     │ │ - genre_       │
    │ - editor_       │ │ - articles_  │ │ - chapters_    │
    │ ...             │ │ ...          │ │ ...            │
    ├─────────────────┤ ├──────────────┤ ├────────────────┤
    │ + DisplayInfo() │ │ + GetISBN()  │ │ + GetISBN()    │
    │ + UpdateIssue() │ │ + Process()  │ │ + DisplayInfo()│
    └─────────────────┘ └──────────────┘ └────────────────┘


                    Множинне наслідування:

    ┌───────────────────┐         ┌──────────────────┐
    │  DigitalContent   │         │   Subscription   │
    ├───────────────────┤         ├──────────────────┤
    │ - file_format_    │         │ - subscriber_    │
    │ - file_size_mb_   │         │ - sub_type_      │
    │ - download_url_   │         │ - sub_price_     │
    │ - download_count_ │         │ - months_        │
    │ ...               │         │ ...              │
    ├───────────────────┤         ├──────────────────┤
    │ + ShowInfo()      │         │ + ShowSubInfo()  │
    │ + UpdateCount()   │         │ + Renew()        │
    └─────────┬─────────┘         └────────┬─────────┘
              │                            │
              └──────────┬─────────────────┘
                         │
              ┌──────────▼───────────┐
              │ DigitalSubscription  │
              ├──────────────────────┤
              │ - subscription_id_   │
              │ - device_limit_      │
              │ - offline_access_    │
              │ ...                  │
              ├──────────────────────┤
              │ + DisplayFullInfo()  │
              │ + ProcessSub()       │
              └──────────────────────┘
```

**Легенда:**

- `+` public члени
- `#` protected члени
- `-` private члени
- `(public)` тип наслідування
- `▼` наслідування

---

### ПУНКТ 11: Google C++ Style Guide

Код написаний відповідно до Google C++ Style Guide.

#### 1. Назви файлів:

```
PrintedMaterial.h     // CapitalCase для класів
PrintedMaterial.cpp
Magazine.h
main_lab4.cpp        // lowercase з підкресленням для main
```

#### 2. Назви класів:

```cpp
class PrintedMaterial { };    // CapitalCase
class DigitalSubscription { };
```

#### 3. Назви змінних:

```cpp
std::string material_id_;     // snake_case з підкресленням в кінці
int page_count_;
double base_price_;
```

#### 4. Назви методів:

```cpp
void DisplayInfo();           // PascalCase
void UpdatePrice();
std::string GetISBN();
```

#### 5. Назви констант:

```cpp
const int kMaxPages = 1000;   // k префікс + PascalCase
```

#### 6. Відступи:

```cpp
class Example {
 public:              // 1 пробіл для модифікаторів доступу
  void Method() {     // 2 пробіли для методів
    int x = 0;        // 4 пробіли для коду всередині методів
  }
};
```

#### 7. Include guards:

```cpp
#ifndef PRINTED_MATERIAL_H
#define PRINTED_MATERIAL_H
// ...
#endif  // PRINTED_MATERIAL_H
```

#### 8. Порядок include:

```cpp
#include "PrintedMaterial.h"  // Спочатку власний заголовок
#include <iostream>           // Потім системні бібліотеки
#include <string>
```

#### 9. Const correctness:

```cpp
double GetPrice() const;  // Метод не змінює об'єкт
void ShowInfo() const;
```

#### 10. Списки ініціалізації:

```cpp
Magazine::Magazine(...)
    : PrintedMaterial(...),  // З відступом 4 пробіли
      issue_number_(0),
      month_("") {
}
```

---

### ПУНКТ 12: Структура файлів

Правильна структура проекту з окремими файлами для кожного класу.

#### Структура Lab 4:

**Базовий клас:**

1. `PrintedMaterial.h` (56 рядків) - оголошення базового класу
2. `PrintedMaterial.cpp` (90 рядків) - реалізація базового класу

**Public наслідування:** 3. `Magazine.h` (51 рядок) - оголошення класу з public наслідуванням 4. `Magazine.cpp` (94 рядки) - реалізація Magazine

**Private наслідування:** 5. `Newspaper.h` (45 рядків) - оголошення класу з private наслідуванням 6. `Newspaper.cpp` (96 рядків) - реалізація Newspaper

**Protected наслідування:** 7. `Book.h` (53 рядки) - оголошення класу з protected наслідуванням 8. `Book.cpp` (88 рядків) - реалізація Book

**Перший базовий клас для множинного наслідування:** 9. `DigitalContent.h` (40 рядків) - оголошення класу цифрового контенту 10. `DigitalContent.cpp` (50 рядків) - реалізація DigitalContent

**Другий базовий клас для множинного наслідування:** 11. `Subscription.h` (42 рядки) - оголошення класу підписки 12. `Subscription.cpp` (62 рядки) - реалізація Subscription

**Множинне наслідування:** 13. `DigitalSubscription.h` (48 рядків) - клас з множинним наслідуванням 14. `DigitalSubscription.cpp` (103 рядки) - реалізація DigitalSubscription

**Демонстраційна програма:** 15. `main_lab4.cpp` (178 рядків) - головна програма з демонстрацією всіх можливостей

**Усього:** 15 файлів, ~1000 рядків коду

#### Залежності між файлами:

```
main_lab4.cpp
    ├── PrintedMaterial.h
    ├── Magazine.h → PrintedMaterial.h
    ├── Newspaper.h → PrintedMaterial.h
    ├── Book.h → PrintedMaterial.h
    ├── DigitalContent.h
    ├── Subscription.h
    └── DigitalSubscription.h → DigitalContent.h, Subscription.h
```

---
