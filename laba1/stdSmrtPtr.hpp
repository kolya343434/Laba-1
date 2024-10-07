
#pragma once
#include <iostream>
#include <memory> // ��� std::unique_ptr

namespace stdSmartPointer {

    // ��������� ����
    template <typename T>
    struct Node {
        T data; // ������ ����
        std::unique_ptr<Node> next; // ����� ��������� �� ��������� ����

        // �����������
        Node(T value) : data(value), next(nullptr) {}
    };

    // ����� ������������ ������
    template <typename T>
    class SinglyLinkedList {
    private:
        std::unique_ptr<Node<T>> head; // ����� ��������� �� ������ ���� (������ ������)

    public:
        // �����������
        SinglyLinkedList() : head(nullptr) {}

        // ����� ��� ������� �������� � ������ ������
        void push_front(T value) {
            // ������ ����� ���� � ������� �������� ������ ������� ��� "next"
            std::unique_ptr<Node<T>> new_node = std::make_unique<Node<T>>(value);
            new_node->next = std::move(head);
            head = std::move(new_node); // ������ ����� ���� ���������� �������
        }

        // ����� ��� �������� �������� � ������ ������
        void pop_front() {
            if (head) {
                // ������� ������ ������, ��������� ����� ���������� head->next
                head = std::move(head->next);
            }
        }

        // ����� ��� ������ ��������� ������
        void print_list() const {
            Node<T>* current = head.get(); // �������� ����� ��������� ��� ������ ������
            while (current) {
                std::cout << current->data << " -> ";
                current = current->next.get(); // ��������� � ���������� ����
            }
            std::cout << "null" << std::endl;
        }

        // ����� ��� ��������, ���� �� ������
        bool is_empty() const {
            return head == nullptr;
        }


        size_t getMemoryUsage() const {
            size_t totalMemory = 0;
            Node<T>* current = head.get(); // ���������� ����� ��������� ����� get()

            while (current) {
                totalMemory += sizeof(Node<T>);       // ������ ��� ����
                totalMemory += sizeof(current->data); // ������ ��� ������ ������ ����
                current = current->next.get();        // ��������� � ���������� ����
            }

            return totalMemory;
        }

    };


}