# Makefile для системи періодичних видань
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2
TARGET = publication_system
SOURCES = main.cpp Publication.cpp Client.cpp Order.cpp Review.cpp Notification.cpp PublicationSystem.cpp
OBJECTS = $(SOURCES:.cpp=.o)

# Головна ціль
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# Компіляція окремих файлів
main.o: main.cpp PublicationSystem.h
	$(CXX) $(CXXFLAGS) -c main.cpp

Publication.o: Publication.cpp Publication.h
	$(CXX) $(CXXFLAGS) -c Publication.cpp

Client.o: Client.cpp Client.h
	$(CXX) $(CXXFLAGS) -c Client.cpp

Order.o: Order.cpp Order.h Publication.h Client.h
	$(CXX) $(CXXFLAGS) -c Order.cpp

Review.o: Review.cpp Review.h
	$(CXX) $(CXXFLAGS) -c Review.cpp

Notification.o: Notification.cpp Notification.h
	$(CXX) $(CXXFLAGS) -c Notification.cpp

PublicationSystem.o: PublicationSystem.cpp PublicationSystem.h Publication.h Client.h Order.h Review.h Notification.h
	$(CXX) $(CXXFLAGS) -c PublicationSystem.cpp

# Запуск програми
run: $(TARGET)
	./$(TARGET)

# Компіляція в режимі налагодження
debug: CXXFLAGS += -g -DDEBUG
debug: $(TARGET)

# Очищення
clean:
	rm -f $(OBJECTS) $(TARGET) *.dat *.txt

# Перевірка стилю коду (якщо встановлено cppcheck)
check:
	@which cppcheck > /dev/null && cppcheck --enable=all --std=c++11 *.cpp *.h || echo "cppcheck не встановлено"

# Створення архіву
archive:
	tar -czf publication_system_$(shell date +%Y%m%d).tar.gz *.cpp *.h Makefile README.md

# Встановлення залежностей (для різних систем)
install-deps:
	@echo "Проект використовує стандартну бібліотеку C++, додаткові залежності не потрібні"

.PHONY: run debug clean check archive install-deps