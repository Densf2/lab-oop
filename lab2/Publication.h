#ifndef PUBLICATION_H
#define PUBLICATION_H

#include <string>
#include <vector>

// Клас для представлення періодичного видання
class Publication {
private:
    int id;
    std::string title;
    std::string description;
    double price;
    std::string category;
    double rating;
    int reviewCount;

public:
    // Конструктори
    Publication();
    Publication(int id, const std::string& title, const std::string& description, 
               double price, const std::string& category);
    
    // Деструктор
    ~Publication();
    
    // Геттери
    int getId() const;
    std::string getTitle() const;
    std::string getDescription() const;
    double getPrice() const;
    std::string getCategory() const;
    double getRating() const;
    int getReviewCount() const;
    
    // Сеттери
    void setTitle(const std::string& title);
    void setDescription(const std::string& description);
    void setPrice(double price);
    void setCategory(const std::string& category);
    
    // Методи для роботи з рейтингом
    void addRating(double rating);
    void calculateRating(const std::vector<double>& ratings);
    
    // Метод виведення інформації
    void displayInfo() const;
    
    // Оператори порівняння для сортування
    bool operator<(const Publication& other) const;
    bool operator==(const Publication& other) const;
};

#endif // PUBLICATION_H