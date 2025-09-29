#include "Review.h"
#include <iostream>
#include <ctime>

// Конструктор за замовчуванням
Review::Review() : reviewId(0), clientId(0), publicationId(0), rating(0), 
                  comment(""), isModerated(false) {
    reviewDate = std::chrono::system_clock::now();
}

// Конструктор з параметрами
Review::Review(int reviewId, int clientId, int publicationId, int rating, const std::string& comment)
    : reviewId(reviewId), clientId(clientId), publicationId(publicationId), 
      rating(rating), comment(comment), isModerated(false) {
    reviewDate = std::chrono::system_clock::now();
}

// Деструктор
Review::~Review() {}

// Геттери
int Review::getReviewId() const { 
    return reviewId; 
}

int Review::getClientId() const { 
    return clientId; 
}

int Review::getPublicationId() const { 
    return publicationId; 
}

int Review::getRating() const { 
    return rating; 
}

std::string Review::getComment() const { 
    return comment; 
}

std::string Review::getReviewDate() const {
    std::time_t time = std::chrono::system_clock::to_time_t(reviewDate);
    std::string timeStr = std::ctime(&time);
    if (!timeStr.empty() && timeStr.back() == '\n') {
        timeStr.pop_back();
    }
    return timeStr;
}

bool Review::getModerationStatus() const { 
    return isModerated; 
}

// Сеттери
void Review::setRating(int rating) {
    if (isValidRating(rating)) {
        this->rating = rating;
    }
}

void Review::setComment(const std::string& comment) {
    this->comment = comment;
}

void Review::setModerationStatus(bool status) {
    isModerated = status;
}

// Виведення інформації про відгук
void Review::displayInfo() const {
    std::cout << "\n=== Відгук ===" << std::endl;
    std::cout << "ID відгуку: " << reviewId << std::endl;
    std::cout << "ID клієнта: " << clientId << std::endl;
    std::cout << "ID видання: " << publicationId << std::endl;
    std::cout << "Оцінка: " << rating << "/5" << std::endl;
    std::cout << "Коментар: " << comment << std::endl;
    std::cout << "Дата: " << getReviewDate() << std::endl;
    std::cout << "Модерація: " << (isModerated ? "Пройдено" : "Очікує") << std::endl;
    std::cout << "===============" << std::endl;
}

// Перевірка валідності рейтингу
bool Review::isValidRating(int rating) const {
    return rating >= 1 && rating <= 5;
}

// Редагування відгуку
void Review::editReview(int newRating, const std::string& newComment) {
    if (isValidRating(newRating)) {
        rating = newRating;
        comment = newComment;
        isModerated = false; // Потребує повторної модерації
    }
}

// Оператори порівняння
bool Review::operator==(const Review& other) const {
    return reviewId == other.reviewId;
}

bool Review::operator<(const Review& other) const {
    return reviewDate < other.reviewDate;
}