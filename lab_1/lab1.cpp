#include <iostream>
#include <bitset>
#include <limits>
#include <clocale>

#define type_info(type) std::cout << "min " << #type << " = " << std::numeric_limits<type>::min() << ", max " << #type << " = " << std::numeric_limits<type>::max() << ", size of " << #type << " = " << sizeof(type) << std::endl

int main()
{
	setlocale(LC_ALL, "Russian");
	std::cout << "1.\nУланов Сергей Алексеевич, 251-952\n" << std::endl;

	std::cout << "2.\n";
	type_info(int);
	type_info(unsigned int);
	type_info(short);
	type_info(unsigned short);
	type_info(long);
	type_info(long long);
	type_info(bool);
	std::cout << "min char = -128, max char = 127, size of char = " << sizeof(char) << std::endl;
	std::cout << "min unsigned char = 0, max unsigned char = 255, size of char = " << sizeof(unsigned char) << std::endl;

	std::cout << "\n3.\nВведите число: ";
	int num;
	std::cin >> num;
	std::cout << "В бинарном виде: " << std::bitset<16>(num) << std::endl;
	std::cout << "В шестнадцатиричном виде: " << std::hex << num << std::endl;
	std::cout << "int: " << std::dec << num << std::endl;
	std::cout << "short: " << static_cast<short>(num) << std::endl;
	std::cout << "double: " << static_cast<double>(num) << std::endl;
	std::cout << "char: " << static_cast<char>(num) << std::endl;
	std::cout << "bool: " << static_cast<bool>(num) << std::endl;

	std::cout << "\n4.\nВведите коэффициенты для ур-ия a * x = b: ";
	int a, b;
	std::cin >> a >> b;
	std::cout << a << " * x = " << b << std::endl;
	std::cout << "x = " << b << " / " << a << std::endl;
	std::cout << "x = " << static_cast<float>(b) / a << std::endl;
	std::cout << "Ответ: " << static_cast<float>(b) / a << std::endl;

	std::cout << "\n5.\nВведите координаты отрезка на прямой: ";
	int x, y;
	std::cin >> x >> y;
	std::cout << "Середина отрезка находится в точке с координатой: " << (x + y) / 2.0 << std::endl;
}
