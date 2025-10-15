### Основні файли для Лаб 3:

- ✅ `Publication.h` - заголовний файл класу Publication
- ✅ `publications.cpp` - реалізація методів класу Publication
- ✅ `Client.h` - заголовний файл класу Client
- ✅ `clients.cpp` - реалізація методів класу Client
- ✅ `main_lab3.cpp` - демонстраційна програма
- ✅ `Makefile` - файл для компіляції
- ✅ `README_LAB3.md` - повна документація
- ✅ `REPORT_LAB3.md` - звіт про виконання

### ПУНКТ 1: Конструктори

Створив **3 типи конструкторів** для кожного класу (Publication та Client).

1. **Конструктор без параметрів**

   - **Оголошення:** `Publication.h`, рядок 22
   - **Реалізація:** `publications.cpp`, рядки 10-18
   - **Що робить:** Ініціалізує всі 8 полів нульовими/порожніми значеннями, збільшує статичний лічильник

   ```cpp
   Publication::Publication()
       : id_(0), title_(""), description_(""), price_(0.0),
         category_(""), rating_(0.0), review_count_(0), pages_(0) {
     total_publications_count_++;
   }
   ```

2. **Конструктор з параметрами**

   - **Оголошення:** `Publication.h`, рядки 23-24
   - **Реалізація:** `publications.cpp`, рядки 20-35
   - **Що робить:** Ініціалізує поля переданими значеннями

   ```cpp
   Publication::Publication(int id, const std::string& title, ...)
       : id_(id), title_(title), description_(description), ...
   ```

3. **Конструктор копіювання**
   - **Оголошення:** `Publication.h`, рядок 25
   - **Реалізація:** `publications.cpp`, рядки 37-47
   - **Що робить:** Створює точну копію об'єкта
   ```cpp
   Publication::Publication(const Publication& other)
       : id_(other.id_), title_(other.title_), ...
   ```

**Client:**

1. **Конструктор без параметрів** - `Client.h` рядок 19, `clients.cpp` рядки 10-18
2. **Конструктор з параметрами** - `Client.h` рядки 20-21, `clients.cpp` рядки 20-35
3. **Конструктор копіювання** - `Client.h` рядок 22, `clients.cpp` рядки 37-57

**Файл:** `main_lab3.cpp`, функція `DemonstrateConstructors()` (рядки 103-146)

- Рядки 113-114: виклик конструкторів без параметрів
- Рядки 118-119: виклик конструкторів з параметрами
- Рядки 123-124: виклик конструкторів копіювання

---

### ПУНКТ 2: Списки ініціалізації для констант і посилань

Створив **спеціальні конструктори**, які демонструють використання списків ініціалізації для задання початкових значень.

**Publication:**

- **Оголошення:** `Publication.h`, рядки 27-28
- **Реалізація:** `publications.cpp`, рядки 49-66
  ```cpp
  Publication::Publication(int id, const std::string& title, double price)
      : id_(id),                    // Параметр
        title_(title),              // Параметр (посилання)
        description_("Без опису"),  // Константне початкове значення
        price_(price),
        category_("Загальна"),      // Константне початкове значення
        rating_(0.0),               // Початкове значення
        review_count_(0),
        pages_(0)
  ```
  - **Посилання:** параметри `const std::string& title`, `const std::string& description`
  - **Константи:** "Без опису", "Загальна" - задаються безпосередньо в списку

**Client:**

- **Оголошення:** `Client.h`, рядки 24-25
- **Реалізація:** `clients.cpp`, рядки 59-75
- **Що демонструє:**
  ```cpp
  Client::Client(int id, const std::string& first_name, const std::string& last_name)
      : client_id_(id),
        first_name_(first_name),       // Посилання
        last_name_(last_name),         // Посилання
        email_("no-email@example.com"), // Константа
        phone_("+380000000000"),       // Константа
        balance_(0.0),
        subscription_months_(0),
        subscribed_publication_()      // Виклик конструктора Publication()
  ```

#### Демонстрація:

**Файл:** `main_lab3.cpp`, рядки 128-129

```cpp
Publication pub4(2, "Швидке видання", 150.0);
Client client4(2, "Олександр", "Сидоренко");
```

---

### ПУНКТ 3: Статичні поля та методи

Створив **статичні елементи** для спільного використання між усіма об'єктами класу.

**Статичні поля:**

**Publication:**

- **Оголошення в класі:** `Publication.h`, рядок 15
  ```cpp
  private:
    static int total_publications_count_;
  ```
- **Ініціалізація поза класом:** `publications.cpp`, рядок 9
  ```cpp
  int Publication::total_publications_count_ = 0;
  ```
- **Використання:** Збільшується в кожному конструкторі, зменшується в деструкторі
  - Конструктори: рядки 17, 33, 45, 64
  - Деструктор: рядки 65-70

**Client:**

- **Оголошення:** `Client.h`, рядок 16
- **Ініціалізація:** `clients.cpp`, рядок 9
- **Використання:** Аналогічно Publication

**Статичні методи:**

**Publication:**

- **Оголошення:** `Publication.h`, рядки 56-57
  ```cpp
  static int GetTotalPublicationsCount();
  static void ResetPublicationsCount();
  ```
- **Реалізація:** `publications.cpp`, рядки 243-252

  ```cpp
  int Publication::GetTotalPublicationsCount() {
    return total_publications_count_;
  }

  void Publication::ResetPublicationsCount() {
    total_publications_count_ = 0;
  }
  ```

**Client:**

- **Оголошення:** `Client.h`, рядки 59-60
- **Реалізація:** `clients.cpp`, рядки 288-297

**Файл:** `main_lab3.cpp`, функція `DemonstrateStaticMembers()` (рядки 148-196)

- **Рядки 157-160:** Виклик статичних методів БЕЗ створення об'єктів
  ```cpp
  cout << "Кількість видань: " << Publication::GetTotalPublicationsCount() << endl;
  cout << "Кількість клієнтів: " << Client::GetTotalClientsCount() << endl;
  ```
- **Рядки 163-171:** Створення об'єктів - лічильники автоматично збільшуються
- **Рядки 174-176:** Перевірка через статичні методи
- **Рядки 180-189:** Видалення об'єктів - лічильники зменшуються

---

### ПУНКТ 4: Функції поза класом

Створив **4 функції поза межами класів**, які приймають об'єкти як параметри, обчислюють дані та виводять результати.

**Функція 1: CalculatePublicationStatistics**

- **Файл:** `main_lab3.cpp`, рядки 15-39
- **Що робить:**
  ```cpp
  void CalculatePublicationStatistics(const Publication& pub) {
    // Приймає об'єкт Publication як параметр
    double yearly_cost = pub.GetPrice() * 12;           // Обчислення 1
    double price_per_page = pub.GetPrice() / pub.GetPages(); // Обчислення 2
    // Виводить результати на екран
  }
  ```
- **Обчислення:**
  - Річна вартість (ціна × 12)
  - Ціна за сторінку (ціна ÷ кількість сторінок)
  - Середній рейтинг

**Функція 2: CalculateClientExpenses**

- **Файл:** `main_lab3.cpp`, рядки 41-63
- **Що робить:**
  ```cpp
  void CalculateClientExpenses(const Client& client) {
    // Приймає об'єкт Client
    double monthly = sub.GetPrice();
    double total = monthly * client.GetSubscriptionMonths(); // Обчислення
    // Виводить результати
  }
  ```

**Функція 3: CreateDiscountedPublication**

- **Файл:** `main_lab3.cpp`, рядки 65-83
- Описана в Пункті 5 (повертає об'єкт)

**Функція 4: CreateVIPClient**

- **Файл:** `main_lab3.cpp`, рядки 85-101
- Описана в Пункті 5 (повертає об'єкт)

#### Демонстрація виклику:

**Файл:** `main_lab3.cpp`, функція `DemonstrateFunctionsOutsideClass()` (рядки 198-216)

- **Рядки 203-209:** Створення об'єктів
- **Рядки 212-213:** Виклик функцій поза класом
  ```cpp
  CalculatePublicationStatistics(pub);
  CalculateClientExpenses(client);
  ```

---

### ПУНКТ 5: Функції, що повертають об'єкти

Створив **2 функції**, які повертають об'єкти класів та оперують з методами цих класів.

**Функція 1: CreateDiscountedPublication**

- **Файл:** `main_lab3.cpp`, рядки 65-83
- **Що робить:**

  ```cpp
  Publication CreateDiscountedPublication(const Publication& original,
                                          double discount_percent) {
    // Створює копію через конструктор копіювання
    Publication discounted = original;  // Виклик конструктора копіювання!

    // Оперує з методами класу
    discounted.SetPrice(original.GetPrice(), discount_percent);

    // Повертає об'єкт класу
    return discounted;  // Повернення об'єкта
  }
  ```

- **Методи класу, що використовуються:**
  - `GetPrice()` - рядок 70 (отримання оригінальної ціни)
  - **`SetPrice(double, double)`** - перевантажений метод з двома параметрами, **рядок 68**
    ```cpp
    discounted.SetPrice(original.GetPrice(), discount_percent);
    // Перший параметр: ціна (200.0)
    // Другий параметр: знижка в відсотках (20.0)
    ```

**Функція 2: CreateVIPClient**

- **Файл:** `main_lab3.cpp`, рядки 77-91
- **Що робить:**

  ```cpp
  Client CreateVIPClient(const Client& regular_client, double bonus_balance) {
    // Використовує конструктор копіювання
    Client vip_client = regular_client;  // Копіювання

    // Оперує методами класу (перевантажений метод!)
    vip_client.AddBalance(0, bonus_balance);

    // Повертає об'єкт
    return vip_client;
  }
  ```

- **Методи класу:**
  - `GetBalance()` - рядки 94, 95
  - `AddBalance(double, double)` - перевантажений метод, рядок 93

#### Демонстрація:

**Файл:** `main_lab3.cpp`, функція `DemonstrateFunctionsReturningObjects()` (рядки 218-234)

- **Рядки 222-225:** Створення базових об'єктів
- **Рядок 228:** Виклик функції, отримання об'єкта Publication
  ```cpp
  Publication discounted_pub = CreateDiscountedPublication(original_pub, 20);
  ```
- **Рядок 232:** Виклик функції, отримання об'єкта Client
  ```cpp
  Client vip = CreateVIPClient(original_client, 10000.0);
  ```

---

### ПУНКТ 6: Покажчики, статична та динамічна пам'ять, масиви

Продемонстрував роботу з **покажчиками**, **статичними та динамічними об'єктами**, **масивами об'єктів**.

**Функція:** `main_lab3.cpp`, `DemonstratePointersAndArrays()` (рядки 236-306)

**1. Статичні об'єкти (рядки 245-246):**

```cpp
Publication static_pub(40, "Статичне видання", "Опис", 150, "Загальна", 50);
Client static_client(400, "Статичний", "Клієнт", ...);
```

- Створюються на стеку
- Автоматично знищуються при виході з функції

**2. Динамічні об'єкти через new (рядки 250-252):**

```cpp
Publication* dyn_pub = new Publication(41, "Динамічне видання", ...);
Client* dyn_client = new Client(401, "Динамічний", "Клієнт", ...);
```

- Створюються в купі (heap)
- Потребують явного звільнення через delete

**3. Робота через покажчик -> (рядки 256-262):**

```cpp
cout << dyn_pub->GetPrice() << endl;  // Доступ до методу через ->
dyn_pub->SetPrice(250);               // Виклик методу
dyn_client->AddBalance(500);          // Зміна через покажчик
```

**4. Масиви об'єктів (рядки 266-279):**

```cpp
// Масив з 3 об'єктів Publication
Publication pub_array[3] = {
  Publication(50, "Журнал 1", "Опис 1", 100, "Кат1", 40),
  Publication(51, "Журнал 2", "Опис 2", 120, "Кат2", 50),
  Publication(52, "Журнал 3", "Опис 3", 140, "Кат3", 60)
};

// Масив з 2 об'єктів Client
Client client_array[2] = {
  Client(500, "Клієнт1", "Прізвище1", ...),
  Client(501, "Клієнт2", "Прізвище2", ...)
};
```

**5. Доступ до елементів масиву (рядок 286):**

```cpp
pub_array[0].DisplayInfo();  // Виклик методу для першого елемента
```

**6. Звільнення динамічної пам'яті (рядки 301-302):**

```cpp
delete dyn_pub;     // Викликається деструктор ~Publication()
delete dyn_client;  // Викликається деструктор ~Client()
```

---

### ПУНКТ 7: Демонстрація роботи всіх конструкторів

Створив спеціальну функцію, яка викликає **всі типи конструкторів** та показує їх роботу.

**Файл:** `main_lab3.cpp`, функція `DemonstrateConstructors()` (рядки 103-146)

**Демонстрація кожного конструктора:**

1. **Конструктор без параметрів (рядки 113-114):**

   ```cpp
   Publication pub1;  // Виклик Publication()
   Client client1;    // Виклик Client()
   ```

   - Вивід: `[Конструктор без параметрів] Створено Publication #1`

2. **Конструктор з параметрами (рядки 118-119):**

   ```cpp
   Publication pub2(1, "Журнал програміста", "Про IT", 200.0, "IT", 100);
   Client client2(1, "Марія", "Коваленко", ...);
   ```

   - Вивід: `[Конструктор з параметрами] Створено: Журнал програміста`

3. **Конструктор копіювання (рядки 123-124):**

   ```cpp
   Publication pub3 = pub2;  // Виклик Publication(const Publication&)
   Client client3 = client2; // Виклик Client(const Client&)
   ```

   - Вивід: `[Конструктор копіювання] Скопійовано: Журнал програміста`

4. **Конструктор зі списком ініціалізації (рядки 128-129):**
   ```cpp
   Publication pub4(2, "Швидке видання", 150.0);
   Client client4(2, "Олександр", "Сидоренко");
   ```
   - Вивід: `[Конструктор зі списком ініціалізації] Створено: Швидке видання`

**Виведення інформації (рядки 132-134):**

```cpp
pub2.DisplayInfo();
client2.DisplayInfo();
```

**Автоматичне знищення (деструктори):**

- При виході з функції всі об'єкти автоматично знищуються
- Кожен деструктор виводить повідомлення
- Вивід: `[Деструктор] Знищено: Журнал програміста`

---

### ПУНКТ 8: Коментарі в коді

#### Що зробив:

Додав коментарі з вказівкою реалізації кожного пункту завдання.

#### Де знаходиться:

**Publication.h:**

- Рядок 12: `// Лаб 3, Пункт 3: Статичне поле даних для спільного використання`
- Рядок 17: `// Лаб 3, Пункт 1: Конструктори`
- Рядок 22: `Publication();  // Конструктор без параметрів`
- Рядок 25: `Publication(const Publication& other);  // Конструктор копіювання`
- Рядок 27: `// Лаб 3, Пункт 2: Конструктор зі списком ініціалізації`
- Рядок 56: `// Лаб 3, Пункт 3: Статичний метод`

**publications.cpp:**

- Рядок 9: `// Лаб 3, Пункт 3: Ініціалізація статичного поля даних поза класом`
- Рядок 10: `// Лаб 3, Пункт 1: Конструктор без параметрів`
- Рядок 20: `// Лаб 3, Пункт 1: Конструктор з параметрами`
- Рядок 37: `// Лаб 3, Пункт 1: Конструктор копіювання`
- Рядок 49: `// Лаб 3, Пункт 2: Конструктор зі списком ініціалізації`
- Рядок 243: `// Лаб 3, Пункт 3: Статичний метод для отримання кількості`

**Client.h та clients.cpp:**

- Аналогічні коментарі для класу Client

**main_lab3.cpp:**

- Рядок 15: `// Лаб 3, Пункт 4: Функція поза межами класу`
- Рядок 41: `// Лаб 3, Пункт 4: Ще одна функція поза класом`
- Рядок 65: `// Лаб 3, Пункт 5: Функція типу класу, яка повертає об'єкт`
- Рядок 85: `// Лаб 3, Пункт 5: Ще одна функція, що повертає об'єкт Client`
- Рядок 103: `// Лаб 3, Пункт 7: Демонстрація всіх конструкторів`
- Рядок 148: `// Лаб 3, Пункт 3: Демонстрація статичних елементів`
- Рядок 198: `// Лаб 3, Пункт 4: Демонстрація функцій поза класом`
- Рядок 218: `// Лаб 3, Пункт 5: Демонстрація функцій, що повертають об'єкти`
- Рядок 236: `// Лаб 3, Пункт 6: Покажчики та масиви`

---

### ПУНКТ 9: UML-діаграма класів

Створив графічну UML-діаграму, яка показує структуру класів.

**Файл:** `README_LAB3.md`, рядки 390-436

**Діаграма показує:**

- Назви класів: `Publication`, `Client`
- Всі поля (включаючи статичні): `- static total_publications_count_: int`
- Всі методи (включаючи статичні): `+ static GetTotalPublicationsCount(): int`
- Модифікатори доступу: `+` (public), `-` (private)
- Взаємозв'язки: стрілка від Client до Publication (композиція)

```
┌─────────────────────────────┐
│      Publication            │
├─────────────────────────────┤
│ - static total_publications_count_: int │
├─────────────────────────────┤
│ + Publication()             │
│ + static GetTotalPublicationsCount() │
└─────────────────────────────┘
                △
                │ uses (composition)
                │
┌─────────────────────────────┐
│         Client              │
├─────────────────────────────┤
│ - subscribed_publication_: Publication │
│ - static total_clients_count_: int     │
└─────────────────────────────┘
```

**Структура класів:**

```
┌─────────────────────────────┐
│      Publication            │
├─────────────────────────────┤
│ - id_: int                  │
│ - title_: string            │
│ - description_: string      │
│ - price_: double            │
│ - category_: string         │
│ - rating_: double           │
│ - review_count_: int        │
│ - pages_: int               │
│ - static total_publications_count_: int │
├─────────────────────────────┤
│ + Publication()             │
│ + Publication(params)       │
│ + Publication(const Publication&) │
│ + ~Publication()            │
│ + SetPrice(double)          │
│ + AddRating(double)         │
│ + DisplayInfo()             │
│ + static GetTotalPublicationsCount() │
│ + static ResetPublicationsCount()    │
└─────────────────────────────┘
                △
                │
                │ uses
                │
┌─────────────────────────────┐
│         Client              │
├─────────────────────────────┤
│ - client_id_: int           │
│ - first_name_: string       │
│ - last_name_: string        │
│ - email_: string            │
│ - phone_: string            │
│ - is_blacklisted_: bool     │
│ - balance_: double          │
│ - subscription_months_: int │
│ - subscribed_publication_: Publication │
│ - static total_clients_count_: int     │
├─────────────────────────────┤
│ + Client()                  │
│ + Client(params)            │
│ + Client(const Client&)     │
│ + ~Client()                 │
│ + AddBalance(double)        │
│ + Subscribe(Publication&)   │
│ + DisplayInfo()             │
│ + static GetTotalClientsCount()    │
│ + static ResetClientsCount()       │
└─────────────────────────────┘
```

---

### ПУНКТ 10: Google C++ Style Guide

Дотримався всіх правил Google C++ Style Guide.

**1. Імена класів (PascalCase):**

- `Publication`, `Client` (правильно)
- НЕ `publication`, `client` (неправильно)

**2. Імена методів (PascalCase):**

- `GetTitle()`, `AddBalance()`, `DisplayInfo()` (правильно)
- НЕ `get_title()`, `add_balance()` (неправильно)

**3. Приватні поля (trailing underscore):**

- `id_`, `title_`, `balance_`, `price_` (правильно)
- НЕ `id`, `title`, `m_balance` (неправильно)

**4. Include guards:**

```cpp
#ifndef PUBLICATION_H_  // Правильно
#define PUBLICATION_H_
...
#endif  // PUBLICATION_H_
```

**5. Відступи (2 пробіли):**

```cpp
class Publication {
  private:    // 2 пробіли від початку
    int id_;  // 4 пробіли (2+2)
};
```

**6. Const correctness:**

```cpp
double GetPrice() const;  // Метод не змінює об'єкт
void CalculateStatistics(const Publication& pub);  // Параметр не змінюється
```

**7. Списки ініціалізації:**

```cpp
Publication::Publication(int id)
    : id_(id),      // Список ініціалізації
      title_("") {  // З відступом 4 пробіли
}
```

---

### ПУНКТ 11: Структура файлів

Створив правильну структуру проекту з окремими файлами.

#### Структура:

**Заголовні файли (.h) - оголошення класів:**

1. `Publication.h` - клас Publication

   - Рядки 1-74: оголошення класу, полів, методів

2. `Client.h` - клас Client
   - Рядки 1-83: оголошення класу, полів, методів

**Файли реалізації (.cpp) - реалізація методів:** 3. `publications.cpp` - реалізація методів Publication

- Рядки 9-252: всі методи класу Publication

4. `clients.cpp` - реалізація методів Client
   - Рядки 9-297: всі методи класу Client

**Демонстраційна програма (.cpp):** 5. `main_lab3.cpp` - програма з main()

- Рядки 1-341: функції демонстрації, головна функція

**Компіляція (Makefile):** 6. `Makefile` - правила компіляції

- Компілює кожен .cpp в .o
- Лінкує в виконуваний файл lab3_demo

**Документація:** 7. `README_LAB3.md` & `DETAILED_DESCRIPTION.md` - повна документація
