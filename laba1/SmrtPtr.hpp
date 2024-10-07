#pragma once
#include <utility> // Для std::move
#include <iostream>

#ifndef SMRT_PTR_HPP
#define SMRT_PTR_HPP

// Шаблон умного указателя

template <typename T>
class SmrtPtr {
private:
    T* ptr;

public:
    // Конструктор для одиночного объекта
    explicit SmrtPtr(T* p = nullptr)
        : ptr(p) {}

    // Конструктор копирования
    SmrtPtr(const SmrtPtr& other)
        : ptr(other.ptr ? new T(*other.ptr) : nullptr) {}

    // Оператор копирующего присваивания
    SmrtPtr& operator=(const SmrtPtr& other) {
        if (this != &other) {
            // Освобождаем старый объект, если есть
            delete ptr;

            // Копируем объект, если указатель не null
            ptr = other.ptr ? new T(*other.ptr) : nullptr;
        }
        return *this;
    }

    // Оператор перемещения
    SmrtPtr(SmrtPtr&& other) noexcept
        : ptr(other.ptr) {
        other.ptr = nullptr; // Забираем владение указателем
    }

    // Оператор перемещения для присваивания
    SmrtPtr& operator=(SmrtPtr&& other) noexcept {
        if (this != &other) {
            delete ptr; // Освобождаем старый объект

            ptr = other.ptr; // Забираем владение указателем
            other.ptr = nullptr; // Обнуляем указатель другого объекта
        }
        return *this;
    }

    // Деструктор
    ~SmrtPtr() {
        delete ptr; // Освобождаем объект
    }

    // Операторы разыменования и доступа
     T& operator*() const { return *ptr; }
     T* operator->() const { return ptr; }
     T* get() const { return ptr; }

   // T* get()  { return ptr; }
   // T* operator->() { return ptr; }
   // T& operator*()  { return *ptr; }
};



#endif  // SMRT_PTR_HPP