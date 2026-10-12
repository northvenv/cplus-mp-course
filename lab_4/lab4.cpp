#include <iostream>
#include <cmath>
#include <iomanip>
#include <clocale>


const int STATIC_MAX_SIZE = 100;
void staticSolution();
void dynamicSolution();
void printDynamicMatrix(int** matrix, int n);
void printStaticMatrix(int matrix[][STATIC_MAX_SIZE], int n);
bool isPrime(int num);
void countPrimesStatic(int matrix[][STATIC_MAX_SIZE], int n, int& primeCount, int& primeSum);
void countPrimesDynamic(int** matrix, int n, int& primeCount, int& primeSum);
void swapDiagonalsStatic(int matrix[][STATIC_MAX_SIZE], int n);
void swapDiagonalsDynamic(int** matrix, int n);


int main() {
    setlocale(LC_ALL, "Russian");
    std::cout << "Лабороторная работа №4. Задача 1" << "\n" << std::endl;
    while (true) {
        std::cout << "Выбор способа решения задачи:\n"
			<< "0 - Выход\n"
			<< "1 - Решение статическим массивом\n"
			<< "2 - Решение динамическим массивом\n"
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
			case 1: staticSolution(); break;
			case 2: dynamicSolution(); break;
		}
    }
    return 0;
}

void staticSolution() {
    int matrix[STATIC_MAX_SIZE][STATIC_MAX_SIZE];
    int n;
    
    std::cout << "\nРешение статическим массивом\n" << std::endl;
    std::cout << "Введите размер матрицы n (max 100): ";
    std::cin >> n;
    
    if (n <= 0 || n > STATIC_MAX_SIZE) {
        std::cout << "Ошибка: размер матрицы должен быть от 1 до " << STATIC_MAX_SIZE << std::endl;
        return;
    }
    
    std::cout << "Введите элементы матрицы:" << std::endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << "B[" << i << "][" << j << "] = ";
            std::cin >> matrix[i][j];
        }
    }
    
    std::cout << "\n----------- Матрица ДО преобразований -----------" << std::endl;
    printStaticMatrix(matrix, n);
    
    int primeCount = 0;
    int primeSum = 0;
    
    countPrimesStatic(matrix, n, primeCount, primeSum);
    
    std::cout << "Количество простых чисел вне диагоналей: " << primeCount << std::endl;
    std::cout << "Сумма простых чисел вне диагоналей: " << primeSum << std::endl;
    
    if (primeCount == 0) {
        swapDiagonalsStatic(matrix, n);
        
        std::cout << "\n----------- Матрица ПОСЛЕ преобразований -----------" << std::endl;
        printStaticMatrix(matrix, n);
    } else {
        std::cout << "\nПреобразования не требуются." << std::endl;
    }
}

void dynamicSolution() {
    int n;
    
    std::cout << "\nРешение динамическим массивом\n" << std::endl;
    std::cout << "Введите размер матрицы n: ";
    std::cin >> n;
    
    if (n <= 0) {
        std::cout << "Матрица должна состоять хотя бы из одного элемента" << std::endl;
        return;
    }
    
    int** matrix = new int*[n];
    for (int i = 0; i < n; i++) {
        matrix[i] = new int[n];
    }
    
    std::cout << "Введите элементы матрицы:" << std::endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << "B[" << i << "][" << j << "] = ";
            std::cin >> matrix[i][j];
        }
    }
    
    std::cout << "\n----------- Матрица ДО преобразований -----------" << std::endl;
    printDynamicMatrix(matrix, n);
    
    int primeCount = 0;
    int primeSum = 0;
    
    countPrimesDynamic(matrix, n, primeCount, primeSum);
    
    std::cout << "Количество простых чисел вне диагоналей: " << primeCount << std::endl;
    std::cout << "Сумма простых чисел вне диагоналей: " << primeSum << std::endl;

    if (primeCount == 0) {        
        swapDiagonalsDynamic(matrix, n);

        std::cout << "\n----------- Матрица ПОСЛЕ преобразований -----------" << std::endl;
        printDynamicMatrix(matrix, n);
    } else {
        std::cout << "\nПреобразования не требуются." << std::endl;
    }
    
    for (int i = 0; i < n; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

void printDynamicMatrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        std::cout << "[";
        for (int j = 0; j < n; j++) {
            std::cout << std::setw(6) << matrix[i][j] << " ";
        }
        std::cout << std::setw(6) << "]";
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void printStaticMatrix(int matrix[][STATIC_MAX_SIZE], int n) {
    for (int i = 0; i < n; i++) {
        std::cout << "[";
        for (int j = 0; j < n; j++) {
            std::cout << std::setw(6) << matrix[i][j] << " ";
        }
        std::cout << std::setw(6) << "]";
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

bool isPrime(int num) {
    if (num < 2) return false;
    if (num == 2) return true;
    if (num % 2 == 0) return false;
    
    for (int i = 3; i <= sqrt(num); i += 2) {
        if (num % i == 0) return false;
    }
    return true;
}

void countPrimesStatic(int matrix[][STATIC_MAX_SIZE], int n, int& primeCount, int& primeSum) {
    primeCount = 0;
    primeSum = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j && i + j != n - 1) {  
                if (isPrime(matrix[i][j])) {
                    primeCount++;
                    primeSum += matrix[i][j];
                }
            }
        }
    }
}

void countPrimesDynamic(int** matrix, int n, int& primeCount, int& primeSum) {
    primeCount = 0;
    primeSum = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j && i + j != n - 1) {  
                if (isPrime(matrix[i][j])) {
                    primeCount++;
                    primeSum += matrix[i][j];
                }
            }
        }
    }
}

void swapDiagonalsStatic(int matrix[][STATIC_MAX_SIZE], int n) {
    for (int i = 0; i < n; i++) {
        int temp = matrix[i][i];
        matrix[i][i] = matrix[i][n - 1 - i];
        matrix[i][n - 1 - i] = temp;
    }
}

void swapDiagonalsDynamic(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        int temp = matrix[i][i];
        matrix[i][i] = matrix[i][n - 1 - i];
        matrix[i][n - 1 - i] = temp;
    }
}
