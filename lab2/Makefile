# Makefile для лабораторних робіт №2 та №3
# Пункт 11: Компіляція проекту з окремих файлів

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2

# Цілі для Лаб 2
TARGET_LAB2 = lab2_demo
SOURCES_LAB2 = main.cpp publications.cpp clients.cpp
OBJECTS_LAB2 = $(SOURCES_LAB2:.cpp=.o)

# Цілі для Лаб 3
TARGET_LAB3 = lab3_demo
SOURCES_LAB3 = main_lab3.cpp publications.cpp clients.cpp
OBJECTS_LAB3 = main_lab3.o publications.o clients.o

# За замовчуванням компілюємо Лаб 3
all: $(TARGET_LAB3)

# Компіляція Лаб 3
$(TARGET_LAB3): $(OBJECTS_LAB3)
	$(CXX) $(CXXFLAGS) -o $(TARGET_LAB3) $(OBJECTS_LAB3)

# Компіляція Лаб 2
$(TARGET_LAB2): $(OBJECTS_LAB2)
	$(CXX) $(CXXFLAGS) -o $(TARGET_LAB2) $(OBJECTS_LAB2)

# Компіляція окремих файлів
main.o: main.cpp Publication.h Client.h
	$(CXX) $(CXXFLAGS) -c main.cpp

main_lab3.o: main_lab3.cpp Publication.h Client.h
	$(CXX) $(CXXFLAGS) -c main_lab3.cpp

publications.o: publications.cpp Publication.h
	$(CXX) $(CXXFLAGS) -c publications.cpp

clients.o: clients.cpp Client.h Publication.h
	$(CXX) $(CXXFLAGS) -c clients.cpp

# Запуск Лаб 3
run: $(TARGET_LAB3)
	./$(TARGET_LAB3)

# Запуск Лаб 2
run-lab2: $(TARGET_LAB2)
	./$(TARGET_LAB2)

# Компіляція обох лабораторних
both: $(TARGET_LAB2) $(TARGET_LAB3)

# Компіляція в режимі налагодження
debug: CXXFLAGS += -g -DDEBUG
debug: clean $(TARGET_LAB3)

# Очищення
clean:
	rm -f *.o $(TARGET_LAB2) $(TARGET_LAB3) *.dat

# Перевірка code style
style:
	@echo "Перевірка стилю коду згідно Google C++ Style Guide"
	@which cpplint > /dev/null && cpplint --filter=-legal/copyright *.cpp *.h || echo "cpplint не встановлено"

.PHONY: all run run-lab2 both debug clean style