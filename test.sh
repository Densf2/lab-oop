#!/bin/bash

echo "=== АВТОМАТИЧНЕ ТЕСТУВАННЯ ПРОГРАМИ ==="

# Створення тестового файлу з вхідними даними
cat > test_input.txt << EOF
1
3
Іваненко
Петро
25
6
2001
Петренко 
Марія
15
7
2000
Сидоренко
Олег
10
3
2002
2
3
7
4
5
7
6
7
0
EOF

echo "Тестові дані створено. Запускаю програму..."
echo "Очікувані результати:"
echo "- Створення файлів INFO.DAT та INFO.TXT"
echo "- Знаходження 2 студентів під знаком Рака: Іваненко та Петренко"
echo ""

# Запуск програму з тестовими даними
./student_manager < test_input.txt

echo ""
echo "=== ПЕРЕВІРКА СТВОРЕНИХ ФАЙЛІВ ==="

if [ -f "INFO.DAT" ]; then
    echo "✓ Бінарний файл INFO.DAT створено"
    ls -la INFO.DAT
else
    echo "✗ Бінарний файл INFO.DAT НЕ створено"
fi

if [ -f "INFO.TXT" ]; then
    echo "✓ Текстовий файл INFO.TXT створено"
    ls -la INFO.TXT
    echo ""
    echo "Вміст текстового файлу:"
    cat INFO.TXT
else
    echo "✗ Текстовий файл INFO.TXT НЕ створено"
fi

# Очистка тестових файлів
rm -f test_input.txt

echo ""
echo "=== ТЕСТУВАННЯ ЗАВЕРШЕНО ==="