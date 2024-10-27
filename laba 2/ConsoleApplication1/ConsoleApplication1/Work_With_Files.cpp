#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <iostream>
#include <fstream>
#include <random>
#include <string>

#include "DynamicArray.h"
#include "LinkedList.h"
#include "Sequence.h"


void WriteRandomNumbersToFile(int quantity, const std::string& outputFileName)
{
    std::ofstream fileStream(outputFileName);

    if (!fileStream.is_open()) {
        std::cerr << "Unable to open file: " << outputFileName << std::endl;
        return;
    }

    // Используем более современный генератор случайных чисел
    std::random_device rd; // Источник энтропии
    std::mt19937 gen(rd()); // Mersenne Twister с сидом от random_device
    std::uniform_int_distribution<> dist(0, 4999); // Диапазон от 0 до 4999

    for (int index = 0; index < quantity; ++index) {
        int randomValue = dist(gen); // Генерация случайного числа
        fileStream << randomValue << "\n";
    }

    std::cout << "Generated " << quantity << " random numbers in file: " << outputFileName << std::endl;

    fileStream.close();
}

void ReadNumbersFromFile(const std::string& inputFileName) {
    std::ifstream fileStream(inputFileName); // Создаем объект для чтения из файла

    if (!fileStream.is_open()) { // Проверяем, открылся ли файл
        std::cerr << "Error opening file: " << inputFileName << std::endl;
        return; // Если файл не открылся, завершаем функцию
    }

    std::vector<int> numbers; // Вектор для хранения считанных чисел
    int number;

    // Читаем числа из файла
    while (fileStream >> number) {
        numbers.push_back(number); // Добавляем каждое число в вектор
    }

    fileStream.close(); // Закрываем файл

    // Выводим считанные числа
    std::cout << "Numbers read from file:\n";
    for (const int num : numbers) {
        std::cout << num << std::endl; // Печатаем каждое число
    }
}
