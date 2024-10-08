#pragma once
#include <utility> 
#include <iostream>

#ifndef SMRT_PTR_HPP
#define SMRT_PTR_HPP



#include <iostream>

template <typename T>
class SmrtPtr {
private:
    T* ptr;
    unsigned* count; // Указатель на счётчик ссылок

public:
    // Конструктор для одиночного объекта
    explicit SmrtPtr(T* p = nullptr)
        : ptr(p), count(new unsigned(1)) {}

    // Конструктор копирования
    SmrtPtr(const SmrtPtr& other)
        : ptr(other.ptr), count(other.count) {
        ++(*count); 
    }

    // Оператор копирующего присваивания
    SmrtPtr& operator=(const SmrtPtr& other) {
        if (this != &other) {
            // Уменьшаем счётчик ссылок на старый объект
            if (--(*count) == 0) {
                delete ptr;
                delete count;
            }

            // Копируем указатель и счётчик ссылок
            ptr = other.ptr;
            count = other.count;
            ++(*count); 
        }
        return *this;
    }

    // Оператор перемещения
    SmrtPtr(SmrtPtr&& other) noexcept
        : ptr(other.ptr), count(other.count) {
        other.ptr = nullptr;
        other.count = nullptr;
    }

    // Оператор перемещения для присваивания
    SmrtPtr& operator=(SmrtPtr&& other) noexcept {
        if (this != &other) {
            // Уменьшаем счётчик ссылок на старый объект
            if (--(*count) == 0) {
                delete ptr;
                delete count;
            }

            // Перемещаем указатель и счётчик ссылок
            ptr = other.ptr;
            count = other.count;
            other.ptr = nullptr;
            other.count = nullptr;
        }
        return *this;
    }

    // Деструктор
    ~SmrtPtr() {
        // Уменьшаем счётчик ссылок и освобождаем память, если она больше не используется
        if (ptr && --(*count) == 0) {
            delete ptr;
            delete count;
        }
    }

    // Операторы разыменования и доступа
    T& operator*() const { return *ptr; }
    T* operator->() const { return ptr; }
    T* get() const { return ptr; }

    // Возвращает текущий счётчик ссылок
    unsigned use_count() const { return *count; }
};




#endif  