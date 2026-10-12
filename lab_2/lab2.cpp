#include <iostream>
#include <algorithm>
#include <cmath>

int countDivisors(int n);
void task1();
void task2();
void task3();

int main() {
    setlocale(LC_ALL, "Russian");
    int choice = 0;
    while (true) {
        std::cout << "\nЧто вы хотите выполнить? \n"
            << "1. Задание 1 (Задача 24) \n"
            << "2. Задание 2 (Задача 20)\n"
            << "3. Задание 3 (Задача 1)\n"
            << "4. Выход\n\n";
            std::cin >> choice;
        if (choice < 0 || choice > 4) {
            std::cout << "Ошибка: " << choice << " - неверный выбор!\n" << std::endl;
            continue;  
        }
        switch (choice) {
            case 1: task1(); break;
            case 2: task2(); break;
            case 3: task3(); break;
            case 4: return 0;
            default: return 0;
        }

    }
}

int countDivisors(int n) {
    if (n == 0) return 0;
    
    int count = 0;
    int s = sqrt(abs(n));

    for (int i = 1; i <= s; i++) {
        if (n % i == 0) {
            if (n / i == i) {
                count++;
            } else {
                count += 2;
            }
        }
    }
    return count;
}

void task1() {
    std::cout << "Задача 24" << std::endl;
    float a1, b1, a2, b2, a3, b3;
    std::cout << "Введите числитель a1 и знаменатель b1 дроби a1/b1: ";
    std::cin >> a1 >> b1;
    std::cout << "Введите числитель a2 и знаменатель b2 дроби a2/b2: ";
    std::cin >> a2 >> b2;
    std::cout << "Введите числитель a3 и знаменатель b3 дроби a3/b3: ";
    std::cin >> a3 >> b3;
    
    std::cout << "\nВведенные дроби:" << std::endl;
    std::cout << "Дробь 1: " << a1 << "/" << b1 << std::endl;
    std::cout << "Дробь 2: " << a2 << "/" << b2 << std::endl;
    std::cout << "Дробь 3: " << a3 << "/" << b3 << std::endl;
    
    float value1 = a1 / b1;
    float value2 = a2 / b2;
    float value3 = a3 / b3;
    
    std::cout << "\nЗначения дробей:" << std::endl;
    std::cout << a1 << "/" << b1 << " = " << value1 << std::endl;
    std::cout << a2 << "/" << b2 << " = " << value2 << std::endl;
    std::cout << a3 << "/" << b3 << " = " << value3 << std::endl;
    
    float max_value = std::max({value1, value2, value3});

    std::cout << "\nНаибольшая дробь:" << std::endl;

    if (value1 == max_value) {
        std::cout << a1 << "/" << b1 << std::endl;
    }
    else if (value2 == max_value) {
        std::cout << a2 << "/" << b2 << std::endl;
    }
    else  {
        std::cout << a3 << "/" << b3 << std::endl;
    }
}


void task2() {
    std::cout << "\nЗадача 20" << std::endl;
    int c = 1;
    int k = 0;
    for (int i = 50; i >= 20; i--) {
        if (i % 5 != 0) {
            c *= i;
            k++;
        }
        if (k == 3) {
            break;
        }
    }
    std::cout << c << std::endl;
}

void task3() {
    std::cout << "\nЗадача 1" << std::endl;
    std::cout << "Введите последовательность целых чисел (0 - конец последовательности):" << std::endl;
    int number;

    while (true) {
        std::cin >> number;

        if (number == 0) {
            break;
        }
        int divisors = countDivisors(number);
        std::cout << "Число " << number << " имеет " << divisors << " делителей" << std::endl;
    }
}
