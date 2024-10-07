#pragma once

#include "SmrtPtr.hpp" // ���������� SmrtPtr
#include <iostream>
#include <utility>

namespace SmartPointer {

    template <typename T>
    struct Node {
        T data; // ������ ������
        SmrtPtr<Node<T>> next; // ����� ��������� �� ��������� ����

        Node(T value) : data(value), next(nullptr) {}
    };

    template <typename T>
    class LinkedList {
    private:
        SmrtPtr<Node<T>> head; // ����� ��������� �� ������ ������

    public:
        LinkedList() : head(nullptr) {}

        // ���������� �������� � ������ ������
        void push_front(T value) {
            SmrtPtr<Node<T>> newNode(new Node<T>(value));
            newNode->next = std::move(head); // ����������� ������ ������ �� ��������� ����
            head = std::move(newNode);       // ������������� ����� ���� � �������� ������
        }

        // �������� �������� � ������ ������
        
        void pop_front() {
            if (head.get()) { // ���������, �� ���� �� ������
               // std::cout << "Popping node with value: " << head.get()->next << std::endl;
                std::cout << "Popping node with value: " << head.get()->data << std::endl; // ���������� ���������
                head = std::move(head.get()->next); // ���������� ��������� �� ��������� ����

            }
            else {
                std::cout << "List is empty, nothing to pop." << std::endl;
            }
        }


        // �������� ���� ��������� ������
        



        // ����� ������
        void print() const {
            Node<T>* current = head.get(); // ���������� get() ��� ������� � ����� ����������
            while (current) {
                std::cout << current->data << "->";
                current = current->next.get();
            }
            std::cout << std::endl;
        }
        
        
        /*
        // ����� ��� ��������� ������, ������� �������
        size_t getMemoryUsage() const {
            size_t totalMemory = 0;
            Node<T>* current = head.get(); // ���������� ����� ��������� ����� get()

            while (current) {
                totalMemory += sizeof(Node<T>);       // ������ ��� ����
                totalMemory += sizeof(current->data); // ������ ��� ������ ������ ����
                current = current->next.get();        // ��������� � ���������� ����
            }

            return totalMemory;
        } */ 
    };

}

 
