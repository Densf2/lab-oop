# Makefile для лабораторної роботи №2
# Пункт 15: Три файли - .h, .cpp реалізації, .cpp демонстрація

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2
TARGET = lab2_demo
SOURCES = main.cpp publications.cpp clients.cpp
OBJECTS = $(SOURCES:.cpp=.o)

# Головна ціль
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# Компіляція окремих файлів
main.o: main.cpp Publication.h Client.h
	$(CXX) $(CXXFLAGS) -c main.cpp

publications.o: publications.cpp Publication.h
	$(CXX) $(CXXFLAGS) -c publications.cpp

clients.o: clients.cpp Client.h Publication.h
	$(CXX) $(CXXFLAGS) -c clients.cpp

# Запуск програми
run: $(TARGET)
	./$(TARGET)

# Компіляція в режимі налагодження
debug: CXXFLAGS += -g -DDEBUG
debug: clean $(TARGET)

# Очищення
clean:
	rm -f $(OBJECTS) $(TARGET) *.dat

# Перевірка code style
style:
	@echo "Перевірка стилю коду згідно Google C++ Style Guide"
	@which cpplint > /dev/null && cpplint --filter=-legal/copyright *.cpp *.h || echo "cpplint не встановлено"

.PHONY: run debug clean style