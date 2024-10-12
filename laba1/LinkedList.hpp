#pragma once

#include "SmrtPtr.hpp"
#include <iostream>
#include <utility>

namespace SmartPointer {

    template <typename T>
    class Node {
    public:
        T data;
        SmrtPtr<Node<T>> next;

        Node(T value) : data(value), next(nullptr) {}
    };

    // Класс LinkedList (односвязный список)
    template <typename T>
    class LinkedList {
    private:
        SmrtPtr<Node<T>> head;

    public:
        LinkedList() : head(nullptr) {}

        // Добавление элемента в начало списка
        void push_front(T value) {
            SmrtPtr<Node<T>> newNode(new Node<T>(value));
            newNode->next = head;
            head = newNode;
        }

        // Вывод элементов списка
        void print() const {
            SmrtPtr<Node<T>> current = head;
            while (current.get() != nullptr) {
                std::cout << current->data << " -> ";
                current = current->next;
            }
            std::cout << "nullptr" << std::endl;
        }

        void pop_front() {
            if (head.get() != nullptr) {
                SmrtPtr<Node<T>> temp = head; 
                head = head->next;           
                
            }
        }


        bool find(T value) const {
            SmrtPtr<Node<T>> current = head;
            while (current.get() != nullptr) {
                if (current->data == value) {
                    return true;
                }
                current = current->next;
            }
            return false;
        }

    };

}

 
