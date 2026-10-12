#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

void task1();
void task2();
int random_num(int min, int max);

constexpr int NUMS = 100;

int main() {
    setlocale(LC_ALL, "Russian");
    std::srand(std::time(nullptr));
    
    std::cout << "Лабораторная работа 6. Работа с файлами\n" << std::endl;
    
    while (true) {
        std::cout << "Меню заданий:\n"
                  << "0 - Выход\n"
                  << "1 - Текстовый файл\n"
                  << "2 - Двоичный файл\n"
                  << "Выберите задание: ";
        
        int choice;
        std::cin >> choice;
        
        if (choice < 0 || choice > 2) {
            std::cout << "Неверный выбор, попробуйте снова\n" << std::endl;
            continue;  
        }
        
        switch (choice) {
            case 0: 
                std::cout << "Выход из программы" << std::endl;
                return 0;
            case 1: 
                task1(); 
                break;
            case 2: 
                task2(); 
                break;
        }
    }
    return 0;
}

void task1() {
    const std::string FILE_NAME = "random_numbers.txt";
    
    std::cout << "\nРабота с текстовым файлом" << std::endl;
    std::cout << "Генерация случайных чисел..." << std::endl;
    
    std::ofstream output_file(FILE_NAME);
    
    if (!output_file.is_open()) {
        std::cerr << "Ошибка при создании файла" << std::endl;
        return;
    }
    
    for (int i = 0; i < NUMS; i++) {
        if (i > 0)
            output_file << ' ';
        output_file << random_num(1, 100);
    }
    
    std::cout << "Создан файл: " << FILE_NAME << std::endl;
    output_file.close();
    
    std::ifstream input_file(FILE_NAME);
    
    if (!input_file.is_open()) {
        std::cerr << "Не удалось открыть файл" << std::endl;
        return;
    }
    
    int count = 0;
    int num;
    int total = 0;
    
    std::cout << "Поиск чисел, кратных трем..." << std::endl;
    
    while (input_file >> num) {
        total++;
        if (num % 3 == 0) 
            count++;
    }
    
    std::cout << "\nРезультат:" << std::endl;
    std::cout << "Всего чисел: " << total << std::endl;
    std::cout << "Кратных трем: " << count << std::endl;
    std::cout << "Процент: " << (count * 100.0 / total) << "%" << std::endl;
    
    input_file.close();
}

void task2() {
    const std::string RANDOM_NUMS_FILE_NAME = "random-numbers.bin";
    const std::string FILTERED_NUMS_FILE_NAME = "filtered-numbers.bin";
    
    std::cout << "\nРабота с двоичным файлом" << std::endl;
    
    std::ofstream random_nums_of(RANDOM_NUMS_FILE_NAME, std::ios::binary);
    
    if (!random_nums_of.is_open()) {
        std::cerr << "Ошибка при создании файла" << std::endl;
        return;
    }
    
    std::cout << "Запись чисел в двоичный файл..." << std::endl;
    
    for (int i = 0; i < NUMS; i++) {
        int num = random_num(1, 100);
        random_nums_of.write(reinterpret_cast<char*>(&num), sizeof(int));
    }
    
    std::cout << "Файл создан: " << RANDOM_NUMS_FILE_NAME << std::endl;
    random_nums_of.close();
    
    int cmp_num;
    std::cout << "\nВведите число для фильтрации (будут выбраны числа больше этого): ";
    std::cin >> cmp_num;
    
    std::ifstream random_nums_if(RANDOM_NUMS_FILE_NAME, std::ios::binary);
    std::ofstream filtered_nums_of(FILTERED_NUMS_FILE_NAME, std::ios::binary);
    
    if (!random_nums_if.is_open()) {
        std::cerr << "Не удалось открыть файл" << std::endl;
        return;
    }
    
    if (!filtered_nums_of.is_open()) {
        std::cerr << "Ошибка при создании файла" << std::endl;
        return;
    }
    
    int num;
    int filtered_count = 0;
    int total_read = 0;
    
    std::cout << "Фильтрация чисел..." << std::endl;
    
    while (random_nums_if.read(reinterpret_cast<char*>(&num), sizeof(int))) {
        total_read++;
        if (num > cmp_num) {
            filtered_nums_of.write(reinterpret_cast<char*>(&num), sizeof(int));
            filtered_count++;
        }
    }
    
    std::cout << "\nРезультат фильтрации:" << std::endl;
    std::cout << "Прочитано чисел: " << total_read << std::endl;
    std::cout << "Число для сравнения: " << cmp_num << std::endl;
    std::cout << "Отфильтровано чисел: " << filtered_count << std::endl;
    std::cout << "Результат записан в: " << FILTERED_NUMS_FILE_NAME << std::endl;
    
    random_nums_if.close();
    filtered_nums_of.close();
}

int random_num(int min, int max) {
    return (std::rand() % (max - min + 1)) + min;
}