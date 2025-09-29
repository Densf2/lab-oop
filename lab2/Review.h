#ifndef REVIEW_H
#define REVIEW_H

#include <string>
#include <chrono>

// Клас для представлення відгуку на видання
class Review {
private:
    int reviewId;
    int clientId;
    int publicationId;
    int rating;          // Оцінка від 1 до 5
    std::string comment;
    std::chrono::system_clock::time_point reviewDate;
    bool isModerated;    // Чи пройшов модерацію

public:
    // Конструктори
    Review();
    Review(int reviewId, int clientId, int publicationId, int rating, const std::string& comment);
    
    // Деструктор
    ~Review();
    
    // Геттери
    int getReviewId() const;
    int getClientId() const;
    int getPublicationId() const;
    int getRating() const;
    std::string getComment() const;
    std::string getReviewDate() const;
    bool getModerationStatus() const;
    
    // Сеттери
    void setRating(int rating);
    void setComment(const std::string& comment);
    void setModerationStatus(bool status);
    
    // Методи для роботи з відгуком
    void displayInfo() const;
    bool isValidRating(int rating) const;
    void editReview(int newRating, const std::string& newComment);
    
    // Оператори порівняння
    bool operator==(const Review& other) const;
    bool operator<(const Review& other) const;
};

#endif // REVIEW_H