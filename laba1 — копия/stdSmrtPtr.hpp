

#include <iostream>
#include <memory> // Для std::unique_ptr


    
    // Структура узла
template <typename T>
struct Node {
    T data; // Данные узла
    std::unique_ptr<Node> next; // Умный указатель на следующий узел

    // Конструктор
    Node(T value) : data(value), next(nullptr) {}
};

// Класс односвязного списка
template <typename T>
class SinglyLinkedList {
private:
    std::unique_ptr<Node<T>> head; // Умный указатель на первый узел (голову списка)

public:
    // Конструктор
    SinglyLinkedList() : head(nullptr) {}

    // Метод для вставки элемента в начало списка
    void push_front(T value) {
        // Создаём новый узел и передаём владение старой головой как "next"
        std::unique_ptr<Node<T>> new_node = std::make_unique<Node<T>>(value);
        new_node->next = std::move(head);
        head = std::move(new_node); // Теперь новый узел становится головой
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


/*
int main() {
    SinglyLinkedList<int> list;

    // Вставка элементов в начало списка
    list.push_front(3);
    list.push_front(2);
    list.push_front(1);

    // Вывод списка
    std::cout << "List after inserting 1, 2, 3:" << std::endl;
    list.print_list();

    // Удаление элементов с начала
    list.pop_front();
    std::cout << "List after popping front:" << std::endl;
    list.print_list();

    return 0;
}*/
