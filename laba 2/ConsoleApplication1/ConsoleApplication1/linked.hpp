#pragma once

#include "smrt.hpp"
#include <iostream>
#include <utility>



    template <typename T>
    class Node {
    public:
        T data;
        SmrtPtr<Node<T>> next;

        Node(T value) : data(value), next(nullptr) {}
    };

    // Êëàññ LinkedList (îäíîñâÿçíûé ñïèñîê)
    template <typename T>
    class LinkedList {
    private:
        SmrtPtr<Node<T>> head;

    public:
        LinkedList() : head(nullptr) {}

        // Äîáàâëåíèå ýëåìåíòà â íà÷àëî ñïèñêà
        void push_front(T value) {
            SmrtPtr<Node<T>> newNode(new Node<T>(value));
            newNode->next = head;
            head = newNode;
        }

        // Âûâîä ýëåìåíòîâ ñïèñêà
        void print() const {
            SmrtPtr<Node<T>> current = head;
            while (current.get() != nullptr) {
                std::cout << current->data << " -> ";
                current = current->next;
            }
            std::cout << "nullptr" << std::endl;
        }

        // Óäàëåíèå ïåðâîãî ýëåìåíòà ñïèñêà
        void pop_front() {
            if (head.get() != nullptr) {
                SmrtPtr<Node<T>> temp = head;
                head = head->next;
            }
        }

        // Ïîèñê ýëåìåíòà â ñïèñêå
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

        size_t size() const {
            size_t count = 0;
            SmrtPtr<Node<T>> current = head;
            while (current.get() != nullptr) {
                count++;
                current = current->next;
            }
            return count;
        }

        // Методы begin() и end() для получения итераторов
        LinkedListIterator<T> begin() const {
            return LinkedListIterator<T>(head);
        }

        LinkedListIterator<T> end() const {
            return LinkedListIterator<T>(nullptr);
        }


    };



