#include <iostream>
#include <cassert>
#include <ctime>     // Для функции time()
#include <chrono>
#include <locale>  
#include <clocale> // Äëÿ setlocale
#include "LinkedList.h"
#include "DynamicArray.h"
#include "Sequence.h"
#include "Sort.h"
#include "Work_With_Files.h"

using namespace std;

template <typename T>
class SmrtPtr {
private:
    T* ptr;
    unsigned* count;
    bool isArray;  // Флаг для отслеживания, является ли указатель массивом

public:
    // Конструктор для одного объекта
    explicit SmrtPtr(T* p = nullptr)
        : ptr(p), count(new unsigned(1)), isArray(false) {}

    // Конструктор для массива
    explicit SmrtPtr(T* p, bool arrayFlag)
        : ptr(p), count(new unsigned(1)), isArray(arrayFlag) {}

    // Копирующий конструктор
    SmrtPtr(const SmrtPtr& other)
        : ptr(other.ptr), count(other.count), isArray(other.isArray) {
        ++(*count);
    }
    // Оператор присваивания
    SmrtPtr& operator=(const SmrtPtr& other) {
        if (this != &other) {
            // Уменьшаем счетчик ссылок на текущий объект
            if (--(*count) == 0) {
                // Удаляем объект или массив
                if (isArray) {
                    delete[] ptr;
                }
                else {
                    delete ptr;
                }
                delete count;
            }

            // Присваиваем новые значения
            ptr = other.ptr;
            count = other.count;
            isArray = other.isArray;
            ++(*count);
        }
        return *this;
    }

    // Деструктор
    ~SmrtPtr() {
        if (count && --(*count) == 0) {
            // Удаляем объект или массив в зависимости от флага
            if (isArray) {
                delete[] ptr;
            }
            else {
                delete ptr;
            }
            delete count;
            count = nullptr;
            ptr = nullptr;

        }
    }

    // Операторы разыменования и доступа к членам
    T& operator*() const { return *ptr; }
    T* operator->() const { return ptr; }
    T* get() const { return ptr; }

    // Возвращаем количество ссылок
    unsigned use_count() const { return *count; }

    // Оператор сравнения ==
    bool operator==(const SmrtPtr& other) const {
        return ptr == other.ptr;
    }

    // Оператор сравнения !=
    bool operator!=(const SmrtPtr& other) const {
        return ptr != other.ptr;
    }

    // Оператор приведения к bool
    operator bool() const {
        return ptr != nullptr;
    }
    
};




// Пример функции сравнения для целых чисел
int Compare(int a, int b) {
    return a - b;  // Сравнение двух чисел
}


int main() {
    srand(static_cast<unsigned int>(time(0))); // Инициализация генератора случайных чисел

    // Создаем LinkedList и заполняем его случайными числами
    LinkedList<int> linkedList;
    std::setlocale(LC_ALL, "Russian");
    
   // linkedList.Prepend('b');
    //linkedList.Prepend('a');
    
   // for (int i = 0; i < 100; ++i) {
     //   linkedList.Append(rand()); // Добавляем случайные числа от 0 до 99
    //}
    

    WriteRandomNumbersToFile(15,"4545");
    ReadNumbersFromFile("4545");
    ReadData("4545", linkedList);
   
  
  

    // Печатаем элементы до сортировки
    //auto start = std::chrono::high_resolution_clock::now();
    
    // Создаем экземпляр Sorter и сортируем LinkedList

    Sort<int> sorter;  // Теперь это корректно, если реализованы все методы
    sorter.InsertionSort(&linkedList);

    linkedList.Print();
    /*
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    cout << duration.count();
   
    */
    return 0;
}
