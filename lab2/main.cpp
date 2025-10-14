// Пункт 15: Демонстраційна програма
// Пункт 13: В коментарях вказано реалізацію кожного пункту завдання
#include <iostream>
#include <fstream>
#include "Publication.h"
#include "Client.h"

using namespace std;

// Функція для демонстрації роботи з файлами (Пункт 5)
void DemonstrateFileSaveLoad() {
  cout << "\n========== Пункт 5: Робота з файлами ==========" << endl;

  // Створюємо об'єкти
  Publication pub(1, "Комп'ютерний світ", "IT журнал", 150.0, "Технології", 80);
  Client client(1, "Іван", "Петренко", "ivan@example.com", "+380671234567", 1000.0);

  // Записуємо у файли
  ofstream pub_file("publications.dat");
  pub.SaveToFile(pub_file);
  pub_file.close();

  ofstream client_file("clients.dat");
  client.SaveToFile(client_file);
  client_file.close();

  cout << "Дані збережено у файли" << endl;

  // Читаємо з файлів
  Publication loaded_pub;
  ifstream pub_in("publications.dat");
  loaded_pub.LoadFromFile(pub_in);
  pub_in.close();

  Client loaded_client;
  ifstream client_in("clients.dat");
  loaded_client.LoadFromFile(client_in);
  client_in.close();

  cout << "Дані завантажено з файлів:" << endl;
  loaded_pub.DisplayInfo();
  loaded_client.DisplayInfo();
}

// Пункт 10: Демонстрація взаємодії об'єктів
void DemonstrateInteraction() {
  cout << "\n========== Пункт 10: Взаємодія об'єктів ==========" << endl;

  Publication magazine(2, "Наука і техніка", "Науковий журнал",
                       120.0, "Наука", 64);
  Client customer(2, "Марія", "Коваленко", "maria@example.com",
                  "+380672345678", 800.0);

  cout << "До покупки:" << endl;
  customer.DisplayInfo();

  // Клієнт купує підписку (взаємодія двох об'єктів)
  customer.PurchaseSubscription(magazine, 6);

  cout << "\nПісля покупки:" << endl;
  customer.DisplayInfo();
}

// Пункт 11: Демонстрація роботи з покажчиками
void DemonstratePointers() {
  cout << "\n========== Пункт 11: Робота з покажчиками ==========" << endl;

  // Створюємо об'єкт через покажчик
  Publication* pub_ptr = new Publication(3, "Автосвіт",
                                         "Журнал для автолюбителів",
                                         180.0, "Автомобілі", 96);

  cout << "Робота через покажчик:" << endl;
  pub_ptr->DisplayInfo();
  pub_ptr->AddRating(4.5);
  pub_ptr->AddRating(5.0);

  cout << "\nПісля додавання рейтингів:" << endl;
  pub_ptr->DisplayInfo();

  // Звільняємо пам'ять
  delete pub_ptr;
  cout << "Пам'ять звільнено" << endl;
}

// Пункт 12: Демонстрація методу з динамічною пам'яттю та сортуванням
void DemonstrateDynamicMemory() {
  cout << "\n========== Пункт 12: Динамічна пам'ять та сортування ==========" << endl;

  Publication pub(4, "Здоров'я", "Медичний журнал", 100.0, "Медицина", 72);

  int size;
  int* ratings = pub.GenerateAndSortRatings(size);

  cout << "Згенеровано та відсортовано " << size
       << " випадкових рейтингів:" << endl;
  for (int i = 0; i < size; i++) {
    cout << ratings[i] << " ";
  }
  cout << endl;

  // Звільняємо динамічну пам'ять
  delete[] ratings;

  // Те саме для Client
  Client client(3, "Олексій", "Сидоренко", "oleksiy@example.com",
                "+380673456789", 1500.0);

  int* months = client.GenerateAndSortMonths(size);
  cout << "\nЗгенеровано та відсортовано " << size
       << " випадкових термінів підписки:" << endl;
  for (int i = 0; i < size; i++) {
    cout << months[i] << " ";
  }
  cout << endl;

  delete[] months;
}

// Пункт 7-8: Демонстрація роботи з масивами об'єктів
void DemonstrateArrays() {
  cout << "\n========== Пункт 7-8: Масиви об'єктів ==========" << endl;

  // Пункт 7: Перший масив Publication
  Publication publications[3];
  publications[0] = Publication(5, "Кулінарія", "Рецепти", 90.0, "Кулінарія", 48);
  publications[1] = Publication(6, "Мода", "Стиль життя", 110.0, "Мода", 56);
  publications[2] = Publication(7, "Спорт", "Спортивні новини", 130.0, "Спорт", 64);

  cout << "Масив видань:" << endl;
  for (int i = 0; i < 3; i++) {
    publications[i].DisplayInfo();
  }

  // Пункт 7: Другий масив Client
  Client clients[3];
  clients[0] = Client(4, "Андрій", "Мельник", "andriy@example.com",
                     "+380674567890", 2000.0);
  clients[1] = Client(5, "Ольга", "Шевченко", "olga@example.com",
                     "+380675678901", 1800.0);
  clients[2] = Client(6, "Дмитро", "Бондаренко", "dmytro@example.com",
                     "+380676789012", 1500.0);

  cout << "\nМасив клієнтів:" << endl;
  for (int i = 0; i < 3; i++) {
    clients[i].DisplayInfo();
  }

  // Пункт 8: Робота з об'єктами в масиві
  cout << "\nКлієнти оформлюють підписки:" << endl;
  for (int i = 0; i < 3; i++) {
    clients[i].PurchaseSubscription(publications[i], 3);
  }
}

// Пункт 4: Демонстрація перевантажених методів
void DemonstrateOverloadedMethods() {
  cout << "\n========== Пункт 4: Перевантажені методи ==========" << endl;

  Publication pub(8, "Бізнес", "Економічний журнал", 200.0, "Бізнес", 88);

  // Перевантажений метод SetPrice
  cout << "Встановлення ціни без знижки:" << endl;
  pub.SetPrice(200.0);
  pub.DisplayInfo();

  cout << "\nВстановлення ціни зі знижкою 20%:" << endl;
  pub.SetPrice(200.0, 20.0);
  pub.DisplayInfo();

  // Перевантажений метод AddRating
  cout << "\nДодавання одиночного рейтингу:" << endl;
  pub.AddRating(4.5);
  pub.DisplayInfo();

  cout << "\nДодавання групового рейтингу:" << endl;
  pub.AddRating(5, 3);  // 3 відгуки з оцінкою 5
  pub.DisplayInfo();

  // Для Client
  Client client(7, "Наталія", "Коваль", "natalia@example.com",
                "+380677890123", 500.0);

  cout << "\nПоповнення балансу без бонусу:" << endl;
  client.AddBalance(200.0);
  client.DisplayInfo();

  cout << "\nПоповнення балансу з бонусом 50 грн:" << endl;
  client.AddBalance(300.0, 50.0);
  client.DisplayInfo();
}

// Пункт 4: Демонстрація методів, що приймають та повертають об'єкти
void DemonstrateObjectMethods() {
  cout << "\n========== Пункт 4: Методи з об'єктами ==========" << endl;

  Publication pub1(9, "Подорожі", "Туристичний журнал", 140.0, "Туризм", 76);
  Publication pub2(10, "Географія", "Науковий журнал", 140.0, "Туризм", 80);

  // Метод, що приймає об'єкт класу
  double discount = pub1.CalculateDiscount(pub2);
  cout << "Знижка при купівлі двох видань: " << discount << "%" << endl;

  // Метод, що повертає об'єкт класу
  Publication copy = pub1.CreateCopy();
  cout << "\nСтворена копія видання:" << endl;
  copy.DisplayInfo();

  // Для Client
  Client client(8, "Сергій", "Ткаченко", "sergiy@example.com",
                "+380678901234", 1000.0);
  client.Subscribe(pub1, 6);

  Publication subscribed = client.GetSubscribedPublication();
  cout << "\nПідписка клієнта:" << endl;
  subscribed.DisplayInfo();
}

int main() {
  cout << "========================================" << endl;
  cout << "  ДЕМОНСТРАЦІЯ РОБОТИ КЛАСІВ" << endl;
  cout << "  Лабораторна робота №2" << endl;
  cout << "========================================" << endl;

  // Пункт 6: 5 об'єктів у статичній пам'яті
  cout << "\n========== Пункт 6: Об'єкти у статичній пам'яті ==========" << endl;
  Publication static_pub1(11, "Література", "Літературний журнал",
                          100.0, "Культура", 60);
  Publication static_pub2(12, "Історія", "Історичний журнал",
                          110.0, "Історія", 68);
  Client static_client1(9, "Валерій", "Лисенко", "valeriy@example.com",
                        "+380679012345", 1200.0);
  Client static_client2(10, "Тетяна", "Гончаренко", "tetiana@example.com",
                        "+380670123456", 1400.0);
  Client static_client3(11, "Михайло", "Ковальчук", "mykhailo@example.com",
                        "+380671234567", 1600.0);

  cout << "Створено 5 об'єктів у статичній пам'яті" << endl;

  // Пункт 6: 5 об'єктів у динамічній пам'яті
  cout << "\n========== Пункт 6: Об'єкти у динамічній пам'яті ==========" << endl;
  Publication* dyn_pub1 = new Publication(13, "Психологія", "Журнал про психологію",
                                          130.0, "Психологія", 72);
  Publication* dyn_pub2 = new Publication(14, "Філософія", "Філософський журнал",
                                          140.0, "Філософія", 84);
  Publication* dyn_pub3 = new Publication(15, "Архітектура", "Архітектурний журнал",
                                          160.0, "Архітектура", 92);
  Client* dyn_client1 = new Client(12, "Анна", "Савченко", "anna@example.com",
                                   "+380672345678", 1800.0);
  Client* dyn_client2 = new Client(13, "Віктор", "Павленко", "viktor@example.com",
                                   "+380673456789", 2000.0);

  cout << "Створено 5 об'єктів у динамічній пам'яті" << endl;

  // Пункт 9: Демонстрація роботи всіх методів
  cout << "\n========== Пункт 9: Демонстрація всіх методів ==========" << endl;

  DemonstrateOverloadedMethods();
  DemonstrateObjectMethods();
  DemonstrateFileSaveLoad();
  DemonstrateArrays();
  DemonstrateInteraction();
  DemonstratePointers();
  DemonstrateDynamicMemory();

  // Очищення динамічної пам'яті
  cout << "\nОчищення динамічної пам'яті..." << endl;
  delete dyn_pub1;
  delete dyn_pub2;
  delete dyn_pub3;
  delete dyn_client1;
  delete dyn_client2;
  cout << "Пам'ять звільнено" << endl;

  cout << "\n========================================" << endl;
  cout << "  ДЕМОНСТРАЦІЮ ЗАВЕРШЕНО" << endl;
  cout << "========================================" << endl;

  return 0;
}