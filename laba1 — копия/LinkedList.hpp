#pragma once

#include "SmrtPtr.hpp" // Подключаем SmrtPtr
#include <iostream>
#include <utility>

namespace SmartPointer {
    // Шаблон структуры узла
    template <typename T>
    struct Node {
        T data;
        SmrtPtr<Node<T>> next; // Умный указатель на следующий узел

        Node(T value) : data(value), next(nullptr) {}
    };

    // Шаблон класса односвязного списка
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
            if (head) {
                head = std::move(head->next); // Умный указатель автоматически удаляет старую голову
            }
            else {
                std::cout << "List is empty, nothing to pop." << std::endl;
            }
        }

        // Вывод списка
        void print() const {
            Node<T>* current = head.get(); // Используем get() для доступа к сырым указателям
            while (current) {
                std::cout << current->data << " ";
                current = current->next.get();
            }
            std::cout << std::endl;
        }
        

        // Деструктор
        ~LinkedList() {
            while (head) {
                head = std::move(head->next); // Автоматически удаляет узлы
            }
        }
    };
}

 // LINKED_LIST_HPP
