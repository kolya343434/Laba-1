#pragma once

#include "SmrtPtr.hpp" // Подключаем SmrtPtr
#include <iostream>
#include <utility>

namespace SmartPointer {

    template <typename T>
    struct Node {
        T data; // Храним данные
        SmrtPtr<Node<T>> next; // Умный указатель на следующий узел

        Node(T value) : data(value), next(nullptr) {}
    };

    template <typename T>
    class LinkedList {
    private:
        SmrtPtr<Node<T>> head; // Умный указатель на голову списка

    public:
        LinkedList() : head(nullptr) {}

        // Добавление элемента в начало списка
        void push_front(T value) {
            SmrtPtr<Node<T>> newNode(new Node<T>(value));
            newNode->next = std::move(head); // Перемещение старой головы на следующий узел
            head = std::move(newNode);       // Устанавливаем новый узел в качестве головы
        }

        // Удаление элемента с начала списка
        
        void pop_front() {
            if (head.get()) { // Проверяем, не пуст ли список
               // std::cout << "Popping node with value: " << head.get()->next << std::endl;
                std::cout << "Popping node with value: " << head.get()->data << std::endl; // Отладочное сообщение
                head = std::move(head.get()->next); // Перемещаем указатель на следующий узел

            }
            else {
                std::cout << "List is empty, nothing to pop." << std::endl;
            }
        }


        // Удаление всех элементов списка
        



        // Вывод списка
        void print() const {
            Node<T>* current = head.get(); // Используем get() для доступа к сырым указателям
            while (current) {
                std::cout << current->data << "->";
                current = current->next.get();
            }
            std::cout << std::endl;
        }
        
        
        /*
        // Метод для измерения памяти, занятой списком
        size_t getMemoryUsage() const {
            size_t totalMemory = 0;
            Node<T>* current = head.get(); // Используем сырые указатели через get()

            while (current) {
                totalMemory += sizeof(Node<T>);       // Память для узла
                totalMemory += sizeof(current->data); // Память для данных внутри узла
                current = current->next.get();        // Переходим к следующему узлу
            }

            return totalMemory;
        } */ 
    };

}

 
