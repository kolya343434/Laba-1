#include <iostream>
#include <memory> // для std::shared_ptr
#include <cassert>
using namespace std;

template <typename T>
class SmrtPtr {
private:
    T* ptr;
    unsigned* count;
    bool isArray;  // Флаг для отслеживания, является ли указатель массивом

public:
    // Конструктор для одного объекта
    explicit SmrtPtr(T* p = nullptr)
        : ptr(p), count(new unsigned(1)), isArray(false) {}

    // Конструктор для массива
    explicit SmrtPtr(T* p, bool arrayFlag)
        : ptr(p), count(new unsigned(1)), isArray(arrayFlag) {}

    // Копирующий конструктор
    SmrtPtr(const SmrtPtr& other)
        : ptr(other.ptr), count(other.count), isArray(other.isArray) {
        ++(*count);
    }

    

    // Оператор присваивания
    SmrtPtr& operator=(const SmrtPtr& other) {
        if (this != &other) {
            // Уменьшаем счетчик ссылок на текущий объект
            if (--(*count) == 0) {
                // Удаляем объект или массив
                if (isArray) {
                    delete[] ptr;
                }
                else {
                    delete ptr;
                }
                delete count;
            }

            // Присваиваем новые значения
            ptr = other.ptr;
            count = other.count;
            isArray = other.isArray;
            ++(*count);
        }
        return *this;
    }

    // Деструктор
    ~SmrtPtr() {
        if (count && --(*count) == 0) {
            // Удаляем объект или массив в зависимости от флага
            if (isArray) {
                delete[] ptr;
            }
            else {
                delete ptr;
            }
            delete count;
            count = nullptr;
            ptr = nullptr;

        }
    }

    // Операторы разыменования и доступа к членам
    T& operator*() const { return *ptr; }
    T* operator->() const { return ptr; }
    T* get() const { return ptr; }

    // Возвращаем количество ссылок
    unsigned use_count() const { return *count; }

    // Оператор сравнения ==
    bool operator==(const SmrtPtr& other) const {
        return ptr == other.ptr;
    }

    // Оператор сравнения !=
    bool operator!=(const SmrtPtr& other) const {
        return ptr != other.ptr;
    }

    // Оператор приведения к bool
    operator bool() const {
        return ptr != nullptr;
    }
    
};




template <typename T>
class Node {
public:
    T data;
    SmrtPtr<Node<T>> next;

    Node(T value) : data(value), next(nullptr) {}
};

// Итератор для связного списка
template <typename T>
class LinkedListIterator {
private:
    SmrtPtr<Node<T>> current;

public:
    LinkedListIterator(SmrtPtr<Node<T>> node) : current(node) {}

    T& operator*() {
        return current->data;
    }

    LinkedListIterator& operator++() { // префиксный инкремент
        if (current) {
            current = current->next;
        }
        return *this;
    }

    bool operator!=(const LinkedListIterator& other) const {
        return current != other.current;
    }
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
    /*
    void reverse() {
        SmrtPtr<Node<T>> prev = nullptr;       // Указатель на предыдущий узел
        SmrtPtr<Node<T>> current = head;       // Указатель на текущий узел
        SmrtPtr<Node<T>> next = nullptr;       // Указатель на следующий узел

        while (current != nullptr) {
            next = current->next;              // Сохраняем следующий узел
            current->next = prev;              // Переворачиваем ссылку
            prev = current;                    // Переходим к следующему узлу
            current = next;
        }

        head = prev;  // Устанавливаем новую голову списка
    }*/
    // Вывод элементов списка
    void print() const {
        SmrtPtr<Node<T>> current = head;
        while (current.get() != nullptr) {
            cout << current->data << " -> ";
            current = current->next;
        }
        cout << "nullptr" << endl;
    }
    T& operator[](size_t index) {
        SmrtPtr<Node<T>> current = head;
        size_t count = 0;

        while (current.get() != nullptr) {
            if (count == index) {
                return current->data;
            }
            current = current->next;
            count++;
        }

        throw std::out_of_range("Index out of range");
    }

    const T& operator[](size_t index) const {
        SmrtPtr<Node<T>> current = head;
        size_t count = 0;

        while (current.get() != nullptr) {
            if (count == index) {
                return current->data;
            }
            current = current->next;
            count++;
        }

        throw std::out_of_range("Index out of range");
    }

    // Метод size() для получения размера списка
    size_t size() const {
        size_t count = 0;
        SmrtPtr<Node<T>> current = head;
        while (current.get() != nullptr) {
            count++;
            current = current->next;
        }
        return count;
    }

    // Поиск максимального элемента в списке
    T findMax() const {
        T maxElement = head->data;
        SmrtPtr<Node<T>> current = head;
        while (current.get() != nullptr) {
            if (current->data > maxElement) {
                maxElement = current->data;
            }
            current = current->next;
        }
        return maxElement;
    }
    void pop_front() {
        if (head.get() != nullptr) {
            SmrtPtr<Node<T>> temp = head;
            head = head->next;
        }
    }

    // Методы begin() и end() для получения итераторов
    LinkedListIterator<T> begin() const {
        return LinkedListIterator<T>(head);
    }

    LinkedListIterator<T> end() const {
        return LinkedListIterator<T>(SmrtPtr<Node<T>>(nullptr)); // Исправлено
    }
};


template <typename T>
class ISorter {
public:
    virtual LinkedList<T> Sort(LinkedList<T> seq, int (*cmp)(T, T)) = 0;
    virtual ~ISorter() = default;
};

template <typename T>
class CountingSorter : public ISorter<T> {
public:
    LinkedList<T> Sort(LinkedList<T> seq, int (*cmp)(T, T)) override {
        static_assert(std::is_integral<T>::value, "Counting Sort is only applicable to integral types.");

        T maxElement = seq.findMax();
        SmrtPtr<int> count(new int[maxElement + 1](), true);  // Используем массив с умным указателем

        for (auto it = seq.begin(); it != seq.end(); ++it) {
            count.get()[*it]++;  // Обращаемся к массиву через get()
        }

        auto it = seq.begin();
        for (T i = 0; i <= maxElement; i++) {
            while (count.get()[i] > 0) {
                *it = i;
                ++it;
                count.get()[i]--;
            }
        }

        return seq;
    }
};


template <typename T>
class BubbleSorter : public ISorter<T> {
public:
    LinkedList<T> Sort(LinkedList<T> seq, int (*cmp)(T, T)) override {
        size_t n = seq.size();  // Получаем размер списка

        // Проходим по каждому элементу списка
        for (size_t i = 0; i < n - 1; i++) {
            bool swapped = false;

            // Проходим по списку и "всплываем" наибольший элемент вправо
            for (size_t j = 0; j < n - i - 1; j++) {
                // Сравниваем элементы при помощи переданной функции cmp
                if (cmp(seq[j], seq[j + 1]) > 0) {
                    // Меняем элементы местами
                    T temp = seq[j];
                    seq[j] = seq[j + 1];
                    seq[j + 1] = temp;
                    swapped = true;  // Отмечаем, что был обмен
                }
            }

            // Если обменов не было, выходим из цикла, т.к. список отсортирован
            if (!swapped) break;
        }

        return seq;  // Возвращаем отсортированный список
    }
};


// Функция сравнения для сортировки чисел
int IntCompare(int a, int b) {
    return a - b;  // Сравнение двух чисел
}
template <typename T>
class SelectionSorter : public ISorter<T> {
public:
    LinkedList<T> Sort(LinkedList<T> seq, int (*cmp)(T, T)) override {
        size_t n = seq.size(); // Получаем размер списка

        // Проходим по каждому элементу списка
        for (size_t i = 0; i < n - 1; i++) {
            size_t minIndex = i; // Индекс текущего минимального элемента

            // Ищем наименьший элемент в оставшейся части списка
            for (size_t j = i + 1; j < n; j++) {
                if (cmp(seq[j], seq[minIndex]) < 0) {  // Если текущий элемент меньше найденного минимума
                    minIndex = j; // Обновляем индекс минимального элемента
                }
            }

            // Если найден новый минимальный элемент, меняем его местами с текущим элементом
            if (minIndex != i) {
                T temp = seq[i];
                seq[i] = seq[minIndex];
                seq[minIndex] = temp;
            }
        }

        return seq;  // Возвращаем отсортированный список
    }
};
int main() {
    // Создаем список
    LinkedList<int> seq;
    seq.push_front(5);
    seq.push_front(2);
    seq.push_front(9);
    seq.push_front(454545);
    seq.push_front(7);
    
    // Выводим элементы списка до сортировки
    std::cout << "До сортировки: ";
    seq.print();  // Вывод элементов списка

    // Выбираем сортировщик (Bubble Sort)
    SmrtPtr<ISorter<int>> sorter(new BubbleSorter<int>());  // Исправление

    // Сортируем список
    LinkedList<int> sortedSeq = sorter->Sort(seq, IntCompare);

    // Выводим элементы списка после сортировки
    std::cout << "После сортировки: ";
    sortedSeq.print();  // Вывод отсортированных элементов

    return 0;
}

