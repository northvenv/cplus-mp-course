#include <iostream>
#include <clocale>
#include <string>


void task1();
void task2();
std::string insertCommasBeforeAnd(const std::string& inputStr);
int countPalindromWords(const std::string& inputStr);
bool isPalindrom(const std::string& word);


int main() {
    setlocale(LC_ALL, "Russian");
    std::cout << "Лабороторная работа №5." << "\n" << std::endl;
    while (true) {
        std::cout << "Выбор задания для выполнения:\n"
			<< "0 - Выход\n"
			<< "1 - Задание 1. Вариант 14\n"
			<< "2 - Задание 2. Вариант 1\n"
			<< std::endl;

        int choice;
		std::cin >> choice;
        if (choice < 0 || choice > 2) {
            std::cout << "Ошибка: " << choice << " - неверный выбор!\n" << std::endl;
            continue;  
        }
        switch (choice)
		{
			case 0: return 0;
			case 1: task1(); break;
			case 2: task2(); break;
            default: return 0;
		}
    }
    return 0;
}

void task1() {
    std::cout << "Задача 1. Решение С-строками" << std::endl;
    std::cout << "Введите строку: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    const int INPUT_MAX_SIZE = 1000;
    char inputStr[INPUT_MAX_SIZE];
    std::cin.getline(inputStr, INPUT_MAX_SIZE);

    const int RESULT_MAX_SIZE = 1000;
    char result[RESULT_MAX_SIZE];
    char* index = std::strtok(inputStr, " ");
    bool firstWord = true;
    
    while (index != nullptr) {
        if (!firstWord) {
            if (std::strcmp(index, "а") == 0 || std::strcmp(index, "но") == 0) {
                std::strcat(result, ", ");
            } else {
                std::strcat(result, " ");
            }
        }
        std::strcat(result, index);
        firstWord = false;
        index = std::strtok(nullptr, " ");
    }
    
    std::cout << "\n" << "Результат: " << result << "\n" << std::endl;
}

void task2() {
    std::cout << "Задача 2. Решение С++ строками" << std::endl;
    std::string inputStr;
    std::cout << "Введите строку: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    std::getline(std::cin, inputStr);

    std::cout << "\n" << "Результат: " << insertCommasBeforeAnd(inputStr) << "\n" << std::endl;
    std::cout << "Количество симметричных слов: " << countPalindromWords(inputStr) << "\n" << std::endl;
}

bool isPalindrom(const std::string& word) {
    if (word.empty()) return false;

    size_t left = 0;
    size_t right = word.length() - 1;

    while (left < right) {
        if (word[left] != word[right]) {
            return false;
        }
        left ++;
        right --;
    }
    return true;
}

int countPalindromWords(const std::string& inputStr) {
    int count = 0;
    size_t start = 0;
    size_t end = inputStr.find(' ', start);

    while (end != std::string::npos) {
        std::string word = inputStr.substr(start, end - start);

        if (isPalindrom(word)) {
            count ++;
        }
        start = end + 1;
        end = inputStr.find(' ', start);
    }

    std::string lastWord = inputStr.substr(start);
    if (isPalindrom(lastWord)) {
        count++;
    }
    return count;
}

std::string insertCommasBeforeAnd(const std::string& inputStr) {
    std::string result;
    size_t start = 0;
    size_t end = inputStr.find(' ');

    while (end != std::string::npos) {
        std::string word = inputStr.substr(start, end - start);

        if (word == "and") {
            result += ", and"; 
        } else {
            if (!result.empty()) {
                result += " ";
            }
            result += word;
        }
        start = end + 1;
        end = inputStr.find(' ', start);
    }
    
    std::string lastWord = inputStr.substr(start);
    if (lastWord == "and") {
        result += ", and";
    } else {
        if (!result.empty()) {
            result += " ";
        }
        result += lastWord;
    }
    return result;
}