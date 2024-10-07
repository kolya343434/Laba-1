// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include "cblock.h"
#include "shared_ptr.h"
#include "weak_ptr.h"
#include <iostream>
#include "unique_ptr.h"
/*
int main()
{
    std::cout << "Hello World!\n";
}*/
/*
template <class T>
struct Node {
    T data;
    shared_ptr<Node<T>> next;

    explicit Node(T value) : data(value), next(nullptr) {}
};

// Linked list
template <class T>
class linked_list {
public:
    linked_list() = default;

    // Add a new element to the end of the list
    void push_back(T value) {
        shared_ptr<Node<T>> new_node = shared_ptr<Node<T>>(new Node<T>(value));
        if (!head) {
            head = std::move(new_node);
        }
        else {
            Node<T>* current = head.get();
            while (current->next) {
                current = current->next.get();
            }
            current->next = std::move(new_node);
        }
    }

    // Remove the first element from the list
    void pop() {
        if (head) {
            head = std::move(head->next);
        }
    }

    // Print all elements in the list
    void print() const {
        Node<T>* current = head.get();
        while (current) {
            std::cout << current->data << " ";
            current = current->next.get();
        }
        std::cout << std::endl;
    }

    // Remove all elements from the list
    void clear() {
        head.reset();
    }

private:
    shared_ptr<Node<T>> head;
};

int main() {
    linked_list<char> list;
    list.push_back(3);
    list.push_back(4);
    list.push_back(400000000000000);
    list.print(); // Output: 1 2 3

   // list.pop();
   // list.pop();
    list.print(); // Output: 2 3

    // list.clear();
    list.print(); // Output: (empty line)

    return 0;
}*/
//#include <cstdlib>
//#include "LinkedList.h"
//using namespace std;

/*
 *
 */

    template <typename T>
    struct Node {
        T data; // Данные узла
        unique_ptr<Node> next; // Умный указатель на следующий узел

        // Конструктор
        Node(T value) : data(value), next(nullptr) {}
    };

    // Класс односвязного списка
    template <typename T>
    class SinglyLinkedList {
    private:
        unique_ptr<Node<T>> head; // Умный указатель на первый узел (голову списка)

    public:
        // Конструктор
        SinglyLinkedList() : head(nullptr) {}

        // Метод для вставки элемента в начало списка
        void push_front(T value) {
            // Создаём новый узел вручную с помощью оператора new
            Node<T>* new_node = new Node<T>(value); // Создание нового узла

            // Передаем текущую голову как следующий узел для нового узла
            new_node->next = std::move(head); // Перемещаем голову в новый узел

            // Новый узел становится новой головой списка
            head = std::move(new_node);
        }

        // Метод для удаления элемента с начала списка
        void pop_front() {
            if (head) {
                // Убираем голову списка, следующим узлом становится head->next
                head = std::move(head->next);
            }
        }

        // Метод для вывода элементов списка
        void print_list() const {
            Node<T>* current = head.get(); // Получаем сырой указатель для обхода списка
            while (current) {
                std::cout << current->data << " -> ";
                current = current->next.get(); // Переходим к следующему узлу
            }
            std::cout << "null" << std::endl;
        }

        // Метод для проверки, пуст ли список
        bool is_empty() const {
            return head == nullptr;
        }
    };

    int  main(){
        SinglyLinkedList<int> r;
        r.push_front(23);
        r.push_front(43);
        r.pop_front();
        r.print_list();
        return 0;
}