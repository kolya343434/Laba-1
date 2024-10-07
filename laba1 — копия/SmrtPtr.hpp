#pragma once
#include <utility> // Для std::move
#include <iostream>


    // Шаблон умного указателя
    template <typename T>
    class SmrtPtr {
    private:
        T* ptr;          // Сырой указатель
        bool isArray;    // Указатель на массив или одиночный объект

    public:
        // Конструктор для одиночного объекта
        explicit SmrtPtr(T* p = nullptr) : ptr(p), isArray(false) {}

        // Конструктор для массива
        explicit SmrtPtr(T* p, bool arrayFlag) : ptr(p), isArray(arrayFlag) {}

        // Запрещаем копирование
        SmrtPtr(const SmrtPtr&) = delete;

        // Оператор перемещения (разрешаем перемещение)
        SmrtPtr(SmrtPtr&& other) noexcept : ptr(other.ptr), isArray(other.isArray) {
            other.ptr = nullptr; // Забираем владение указателем
        }

        // Оператор перемещения (для присваивания)
        SmrtPtr& operator=(SmrtPtr&& other) noexcept {
            if (this != &other) {
                if (ptr) {
                    if (isArray) {
                        delete[] ptr; // Освобождаем память для массива
                    }
                    else {
                        delete ptr;   // Освобождаем память для объекта
                    }
                }
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
                    delete ptr;   // Освобождаем одиночный объект
                }
            }
        }
    };


 // SMRT_PTR_HPP
