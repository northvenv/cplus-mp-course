#include <iostream>
#include <cmath>
#include <clocale>

void staticSolution();
void dynamicSolution();
void copyEverySecondElement(int* arr1, int arr1Size, int* arr2, int& arr2size);
bool isPrime(int num);
int countPrimes(int* arr, int size);
double calculateAverage(int* arr, int size);
void printArray(int* arr, int size);


int main() {
    setlocale(LC_ALL, "Russian");
    std::cout << "Лабороторная работа №3. Задача 1" << "\n" << std::endl;
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
            default: return 0;
		}
    }
    return 0;
}

void staticSolution() {
    std::cout << "\nРешение статическим массивом\n" << std::endl;

    const int MAX_SIZE = 50;
    int arrX[MAX_SIZE], arrY[MAX_SIZE];
    int n, sizeArrY;

    std::cout << "Введите размер массива " << "(Массив должен состоять менее чем из 50 элементов): ";
    std::cin >> n;

    if (n < 1 || n > MAX_SIZE) {
        std::cout << "Массив должен состоять менее чем из 50 элементов и хотя бы из одного элемента" << std::endl;
        return;
    }

    for (int i = 0; i < n; i++) {
        std::cout << "X[" << i << "] = ";
        std::cin >> arrX[i];
    }
    copyEverySecondElement(arrX, n, arrY, sizeArrY);

    std::cout << "\nМассив X\n";
    printArray(arrX, n);

    std::cout << "\nМассив Y\n";
    printArray(arrY, sizeArrY);

    std::cout << "\nКоличество простых чисел в массиве X: " << countPrimes(arrX, n);
    std::cout << "\nКоличество простых чисел в массиве Y: " << countPrimes(arrY, sizeArrY);

    double avgX = calculateAverage(arrX, n);
    double avgY = calculateAverage(arrY, sizeArrY);

    std::cout << "\n\nСреднее арифметическое элементов массивов X и Y: " << (avgX + avgY) / 2 << "\n" << std::endl;
}

void dynamicSolution() {
    std::cout << "\nРешение динамическим массивом\n" << std::endl;

    int n, sizeArrY;

    std::cout << "Введите размер массива X: ";
    std::cin >> n;

    if (n < 1) {
        std::cout << "Массив должен состоять хотя бы из одного элемента" << std::endl;
        return;
    }

    int* arrX = new int[n];
    int* arrY = new int[n / 2 + 1];

    for (int i = 0; i < n; i++) {
        std::cout << "X[" << i << "] = ";
        std::cin >> arrX[i];
    }
    copyEverySecondElement(arrX, n, arrY, sizeArrY);

    std::cout << "\nМассив X\n";
    printArray(arrX, n);

    std::cout << "\nМассив Y\n";
    printArray(arrY, sizeArrY);

    std::cout << "\nКоличество простых чисел в массиве X: " << countPrimes(arrX, n);
    std::cout << "\nКоличество простых чисел в массиве Y: " << countPrimes(arrY, sizeArrY);

    double avgX = calculateAverage(arrX, n);
    double avgY = calculateAverage(arrY, sizeArrY);

    std::cout << "\n\nСреднее арифметическое элементов массивов X и Y: " << (avgX + avgY) / 2 << "\n" << std::endl;

    delete[] arrX;
    delete[] arrY;
}

void copyEverySecondElement(int* arr1, int arr1Size, int* arr2, int& arr2size) {
    arr2size = 0;
    for (int i = 1; i < arr1Size; i += 2) {
        arr2[arr2size] = arr1[i];
        arr2size++;
    }
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

int countPrimes(int* arr, int size) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (isPrime(arr[i])) {
            count ++;
        }
    }
    return count;
}

double calculateAverage(int* arr, int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum / size;
}

void printArray(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        std::cout << arr[i];
        if (i < size - 1) std::cout << ", ";
    }
    std::cout << "\n";
}