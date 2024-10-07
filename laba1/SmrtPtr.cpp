//#include <iostream>
//#include <utility> // Для std::move
#pragma once

//#include "SmrtPtr.h"

// Шаблон умного указателя
template <typename T>
class SmrtPtr {
private:
    T* ptr; // Сырой указатель
    bool isArray; // Указатель на массив или одиночный объект

public:
    // Конструктор для одиночного объекта
    explicit SmrtPtr(T* p = nullptr) : ptr(p), isArray(false) {}

    // Конструктор для массива
    explicit SmrtPtr(T* p, bool arrayFlag) : ptr(p), isArray(arrayFlag) {}

    // Запрещаем копирование, так как нужно вручную управлять памятью
    SmrtPtr(const SmrtPtr&) = delete;

    // Оператор перемещения (разрешаем перемещение)
    SmrtPtr(SmrtPtr&& other) noexcept : ptr(other.ptr), isArray(other.isArray) {
        other.ptr = nullptr; // Забираем владение указателем
    }

    // Оператор перемещения (для присваивания)
    SmrtPtr& operator=(SmrtPtr&& other) noexcept {
        if (this != &other) {
            // Освобождаем ресурсы текущего объекта
            if (ptr) {
                if (isArray) {
                    delete[] ptr; // Освобождаем память для массива
                }
                else {
                    delete ptr; // Освобождаем память для объекта
                }
            }
            // Забираем ресурсы у другого объекта
            ptr = other.ptr;
            isArray = other.isArray;
            other.ptr = nullptr;
        }
        return *this;
    }

    // Оператор разыменования
    T& operator*() const {
        return *ptr;
    }

    // Оператор доступа к членам
    T* operator->() const {
        return ptr;
    }

    // Оператор доступа к элементам массива
    T& operator[](std::size_t index) const {
        return ptr[index];
    }

    // Деструктор
    ~SmrtPtr() {
        if (ptr) {
            if (isArray) {
                delete[] ptr; // Освобождаем массив
            }
            else {
                delete ptr; // Освобождаем одиночный объект
            }
        }
    }
};
/*
int main() {
    // Пример использования для одиночного объекта
    SmrtPtr<int> smartPtr1(new int(42));
    std::cout << "Smart pointer value (object): " << *smartPtr1 << std::endl;

    // Пример использования для массива
    SmrtPtr<int> smartPtr2(new int[5] {1, 2, 3, 4, 5}, true);
    std::cout << "Smart pointer value (array): " << smartPtr2[2] << std::endl;

    // Пример перемещения
    SmrtPtr<int> smartPtr3 = std::move(smartPtr1);
    if (!smartPtr1.operator->()) {
        std::cout << "Smart pointer 1 was moved." << std::endl;
    }
    std::cout << "Smart pointer 3 value (object): " << *smartPtr3 << std::endl;

    return 0;
}*/
