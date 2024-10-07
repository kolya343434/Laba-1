

#include <iostream>
#include <memory> // ��� std::unique_ptr


    
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
};


/*
int main() {
    SinglyLinkedList<int> list;

    // ������� ��������� � ������ ������
    list.push_front(3);
    list.push_front(2);
    list.push_front(1);

    // ����� ������
    std::cout << "List after inserting 1, 2, 3:" << std::endl;
    list.print_list();

    // �������� ��������� � ������
    list.pop_front();
    std::cout << "List after popping front:" << std::endl;
    list.print_list();

    return 0;
}*/
