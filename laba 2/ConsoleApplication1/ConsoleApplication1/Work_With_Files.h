#pragma once
#include <iostream>

#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>

#include "DynamicArray.h"
#include "LinkedList.h"
#include "Sequence.h"


void WriteRandomNumbersToFile(int quantity, const std::string& outputFileName);

void ReadNumbersFromFile(const std::string& inputFileName);

template <typename T>
void ReadData(const std::string& fileName, LinkedList<T>& list) {
    std::ifstream inFile(fileName); // Создаем объект для чтения из файла
    if (!inFile) {
        std::cerr << "Error opening the file: " << fileName << std::endl;
        return; // Если файл не открылся, выходим из функции
    }

    T value;
    // Читаем данные из файла
    while (inFile >> value) {
        list.Append(value); // Добавляем каждое считанное значение в список
    }

    inFile.close(); // Закрываем файл
}

template <typename T>
void ReadData(const std::string& fileName, DynamicArray<T>& array) {
    std::ifstream inFile(fileName); // Открываем файл для чтения
    if (!inFile) {
        std::cerr << "Error opening the file: " << fileName << std::endl;
        return; // Если файл не открылся, выходим из функции
    }

    T value;
    // Читаем данные из файла
    while (inFile >> value) {
        array.Append(value); // Добавляем каждое считанное значение в массив
    }

    inFile.close(); // Закрываем файл
}
