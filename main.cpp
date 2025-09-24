#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <iomanip>
#include <sstream>

using namespace std;

// Структура для зберігання інформації про студента
struct Student {
    char surname[50];
    char name[50];
    int day;
    int month;
    int year;
    
    // Конструктор за замовчуванням
    Student() : day(0), month(0), year(0) {
        surname[0] = '\0';
        name[0] = '\0';
    }
    
    // Конструктор з параметрами
    Student(const string& surn, const string& nm, int d, int m, int y) 
        : day(d), month(m), year(y) {
        strncpy(surname, surn.c_str(), sizeof(surname) - 1);
        surname[sizeof(surname) - 1] = '\0';
        strncpy(name, nm.c_str(), sizeof(name) - 1);
        name[sizeof(name) - 1] = '\0';
    }
};

class FileManager {
public:
    // Перевантажена функція запису в бінарний файл
    void RW(const string& filename, const vector<Student>& students);
    
    // Перевантажена функція запису в текстовий файл
    void RW(const string& filename, const vector<Student>& students, bool textMode);
    
    // Перевантажена функція читання з бінарного файлу
    vector<Student> RD(const string& filename);
    
    // Перевантажена функція читання з текстового файлу
    vector<Student> RD(const string& filename, bool textMode);
    
    // Функція для виведення інформації про студентів на екран
    void displayStudents(const vector<Student>& students);
    
    // Функція для знаходження студентів, народжених під знаком Рака
    vector<Student> findCancerStudents(const vector<Student>& students);
    
private:
    bool isCancer(int day, int month);
};

// Запис у бінарний файл INFO.DAT
void FileManager::RW(const string& filename, const vector<Student>& students) {
    ofstream file(filename, ios::binary);
    if (!file) {
        cerr << "Помилка відкриття файлу для запису: " << filename << endl;
        return;
    }
    
    size_t count = students.size();
    file.write(reinterpret_cast<const char*>(&count), sizeof(count));
    
    for (const auto& student : students) {
        file.write(reinterpret_cast<const char*>(&student), sizeof(Student));
    }
    
    file.close();
    cout << "Дані записано у бінарний файл " << filename << endl;
}

// Запис у текстовий файл INFO.TXT
void FileManager::RW(const string& filename, const vector<Student>& students, bool textMode) {
    ofstream file(filename);
    if (!file) {
        cerr << "Помилка відкриття файлу для запису: " << filename << endl;
        return;
    }
    
    file << "Кількість студентів: " << students.size() << endl;
    file << "=========================" << endl;
    
    for (const auto& student : students) {
        file << "Прізвище: " << student.surname << endl;
        file << "Ім'я: " << student.name << endl;
        file << "Дата народження: " << setfill('0') << setw(2) << student.day 
             << "." << setw(2) << student.month << "." << student.year << endl;
        file << "-------------------------" << endl;
    }
    
    file.close();
    cout << "Дані записано у текстовий файл " << filename << endl;
}

// Читання з бінарного файлу INFO.DAT
vector<Student> FileManager::RD(const string& filename) {
    vector<Student> students;
    ifstream file(filename, ios::binary);
    
    if (!file) {
        cerr << "Помилка відкриття файлу для читання: " << filename << endl;
        return students;
    }
    
    size_t count;
    file.read(reinterpret_cast<char*>(&count), sizeof(count));
    
    students.resize(count);
    for (size_t i = 0; i < count; ++i) {
        file.read(reinterpret_cast<char*>(&students[i]), sizeof(Student));
    }
    
    file.close();
    cout << "Дані прочитано з бінарного файлу " << filename << endl;
    return students;
}

// Читання з текстового файлу INFO.TXT
vector<Student> FileManager::RD(const string& filename, bool textMode) {
    vector<Student> students;
    ifstream file(filename);
    
    if (!file) {
        cerr << "Помилка відкриття файлу для читання: " << filename << endl;
        return students;
    }
    
    string line;
    while (getline(file, line)) {
        if (line.find("Прізвище:") != string::npos) {
            Student student;
            
            // Читаємо прізвище
            string surname = line.substr(line.find(":") + 2);
            strncpy(student.surname, surname.c_str(), sizeof(student.surname) - 1);
            student.surname[sizeof(student.surname) - 1] = '\0';
            
            // Читаємо ім'я
            if (getline(file, line) && line.find("Ім'я:") != string::npos) {
                string name = line.substr(line.find(":") + 2);
                strncpy(student.name, name.c_str(), sizeof(student.name) - 1);
                student.name[sizeof(student.name) - 1] = '\0';
            }
            
            // Читаємо дату народження
            if (getline(file, line) && line.find("Дата народження:") != string::npos) {
                string dateStr = line.substr(line.find(":") + 2);
                sscanf(dateStr.c_str(), "%d.%d.%d", &student.day, &student.month, &student.year);
            }
            
            students.push_back(student);
        }
    }
    
    file.close();
    cout << "Дані прочитано з текстового файлу " << filename << endl;
    return students;
}

// Виведення інформації про студентів на екран
void FileManager::displayStudents(const vector<Student>& students) {
    cout << "\n=== СПИСОК СТУДЕНТІВ ===" << endl;
    for (size_t i = 0; i < students.size(); ++i) {
        cout << (i + 1) << ". " << students[i].surname << " " << students[i].name;
        cout << " (дата народження: " << setfill('0') << setw(2) << students[i].day 
             << "." << setw(2) << students[i].month << "." << students[i].year << ")" << endl;
    }
    cout << "========================" << endl;
}

// Перевірка чи народився студент під знаком Рака
bool FileManager::isCancer(int day, int month) {
    return (month == 6 && day >= 22) || (month == 7 && day <= 21);
}

// Знаходження студентів, народжених під знаком Рака
vector<Student> FileManager::findCancerStudents(const vector<Student>& students) {
    vector<Student> cancerStudents;
    
    for (const auto& student : students) {
        if (isCancer(student.day, student.month)) {
            cancerStudents.push_back(student);
        }
    }
    
    return cancerStudents;
}

// Функція для введення даних про студентів
vector<Student> inputStudents() {
    vector<Student> students;
    int n;
    
    cout << "Введіть кількість студентів: ";
    cin >> n;
    cin.ignore(); // Очищуємо буфер після введення числа
    
    for (int i = 0; i < n; ++i) {
        cout << "\nВведення даних для студента " << (i + 1) << ":" << endl;
        
        string surname, name;
        int day, month, year;
        
        cout << "Прізвище: ";
        getline(cin, surname);
        
        cout << "Ім'я: ";
        getline(cin, name);
        
        cout << "День народження (1-31): ";
        cin >> day;
        
        cout << "Місяць народження (1-12): ";
        cin >> month;
        
        cout << "Рік народження: ";
        cin >> year;
        cin.ignore(); // Очищуємо буфер
        
        students.push_back(Student(surname, name, day, month, year));
    }
    
    return students;
}

// Головна функція
int main() {
    FileManager fileManager;
    vector<Student> students;
    
    cout << "=== ПРОГРАМА РОБОТИ З ФАЙЛАМИ СТУДЕНТІВ ===" << endl;
    
    int choice;
    do {
        cout << "\nВиберіть опцію:" << endl;
        cout << "1. Ввести дані про студентів" << endl;
        cout << "2. Записати дані у бінарний файл INFO.DAT" << endl;
        cout << "3. Прочитати дані з бінарного файлу INFO.DAT" << endl;
        cout << "4. Записати дані у текстовий файл INFO.TXT" << endl;
        cout << "5. Прочитати дані з текстового файлу INFO.TXT" << endl;
        cout << "6. Знайти студентів, народжених під знаком Рака" << endl;
        cout << "7. Показати всіх студентів" << endl;
        cout << "0. Вихід" << endl;
        cout << "Ваш вибір: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                students = inputStudents();
                break;
                
            case 2:
                if (!students.empty()) {
                    fileManager.RW("INFO.DAT", students);
                } else {
                    cout << "Спочатку введіть дані про студентів!" << endl;
                }
                break;
                
            case 3: {
                vector<Student> loadedStudents = fileManager.RD("INFO.DAT");
                if (!loadedStudents.empty()) {
                    students = loadedStudents;
                    fileManager.displayStudents(students);
                }
                break;
            }
            
            case 4:
                if (!students.empty()) {
                    fileManager.RW("INFO.TXT", students, true);
                } else {
                    cout << "Спочатку введіть дані про студентів!" << endl;
                }
                break;
                
            case 5: {
                vector<Student> loadedStudents = fileManager.RD("INFO.TXT", true);
                if (!loadedStudents.empty()) {
                    students = loadedStudents;
                    fileManager.displayStudents(students);
                }
                break;
            }
            
            case 6:
                if (!students.empty()) {
                    vector<Student> cancerStudents = fileManager.findCancerStudents(students);
                    if (!cancerStudents.empty()) {
                        cout << "\nСтуденти, народжені під знаком Рака (22.06 - 21.07):" << endl;
                        fileManager.displayStudents(cancerStudents);
                    } else {
                        cout << "Студентів, народжених під знаком Рака, не знайдено." << endl;
                    }
                } else {
                    cout << "Спочатку введіть дані про студентів!" << endl;
                }
                break;
                
            case 7:
                if (!students.empty()) {
                    fileManager.displayStudents(students);
                } else {
                    cout << "Дані про студентів відсутні!" << endl;
                }
                break;
                
            case 0:
                cout << "До побачення!" << endl;
                break;
                
            default:
                cout << "Невірний вибір! Спробуйте ще раз." << endl;
        }
    } while (choice != 0);
    
    return 0;
}