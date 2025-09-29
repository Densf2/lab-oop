#include "Publication.h"
#include <iostream>
#include <iomanip>

// Конструктор за замовчуванням
Publication::Publication() : id(0), title(""), description(""), price(0.0), 
                            category(""), rating(0.0), reviewCount(0) {}

// Конструктор з параметрами
Publication::Publication(int id, const std::string& title, const std::string& description, 
                        double price, const std::string& category) 
    : id(id), title(title), description(description), price(price), 
      category(category), rating(0.0), reviewCount(0) {}

// Деструктор
Publication::~Publication() {}

// Геттери
int Publication::getId() const { 
    return id; 
}

std::string Publication::getTitle() const { 
    return title; 
}

std::string Publication::getDescription() const { 
    return description; 
}

double Publication::getPrice() const { 
    return price; 
}

std::string Publication::getCategory() const { 
    return category; 
}

double Publication::getRating() const { 
    return rating; 
}

int Publication::getReviewCount() const { 
    return reviewCount; 
}

// Сеттери
void Publication::setTitle(const std::string& title) {
    this->title = title;
}

void Publication::setDescription(const std::string& description) {
    this->description = description;
}

void Publication::setPrice(double price) {
    if (price >= 0) {
        this->price = price;
    }
}

void Publication::setCategory(const std::string& category) {
    this->category = category;
}

// Додавання одиночного рейтингу
void Publication::addRating(double rating) {
    if (rating >= 1.0 && rating <= 5.0) {
        // Перерахунок середнього рейтингу
        this->rating = (this->rating * reviewCount + rating) / (reviewCount + 1);
        reviewCount++;
    }
}

// Розрахунок рейтингу на основі вектора оцінок
void Publication::calculateRating(const std::vector<double>& ratings) {
    if (ratings.empty()) {
        rating = 0.0;
        reviewCount = 0;
        return;
    }
    
    double sum = 0.0;
    for (double r : ratings) {
        if (r >= 1.0 && r <= 5.0) {
            sum += r;
        }
    }
    
    rating = sum / ratings.size();
    reviewCount = ratings.size();
}

// Виведення інформації про видання
void Publication::displayInfo() const {
    std::cout << "\n=== Інформація про видання ===" << std::endl;
    std::cout << "ID: " << id << std::endl;
    std::cout << "Назва: " << title << std::endl;
    std::cout << "Опис: " << description << std::endl;
    std::cout << "Категорія: " << category << std::endl;
    std::cout << "Ціна: " << std::fixed << std::setprecision(2) << price << " грн/міс" << std::endl;
    
    if (reviewCount > 0) {
        std::cout << "Рейтинг: " << std::fixed << std::setprecision(1) << rating 
                  << "/5.0 (" << reviewCount << " відгуків)" << std::endl;
    } else {
        std::cout << "Рейтинг: Немає відгуків" << std::endl;
    }
    std::cout << "===============================" << std::endl;
}

// Оператор порівняння для сортування за назвою
bool Publication::operator<(const Publication& other) const {
    return title < other.title;
}

// Оператор рівності
bool Publication::operator==(const Publication& other) const {
    return id == other.id;
}