# Makefile для компіляції проекту
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2
TARGET = student_manager
SOURCE = main.cpp

# Компіляція програми
$(TARGET): $(SOURCE)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCE)

# Запуск програми
run: $(TARGET)
	./$(TARGET)

# Очищення
clean:
	rm -f $(TARGET) INFO.DAT INFO.TXT

# Перевірка наявності файлів
check:
	@echo "Перевіряємо наявність файлів:"
	@ls -la INFO.DAT INFO.TXT 2>/dev/null || echo "Файли ще не створені"

.PHONY: run clean check