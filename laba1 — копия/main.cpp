#include "LinkedList.hpp" // Подключаем LinkedList, который сам подключает SmrtPtr
#include "SmrtPtr.hpp" // Подключаем SmrtPtr
#include "stdSmrtPtr.hpp"


#include <iostream>
#include <thread>
using namespace std;



int main() {

    ///linkedlist

    /*
    SmartPointer::LinkedList<int> list;
    list.push_front(10);
    list.push_front(20);
    list.push_front(30);

    list.print(); // Вывод: 30 20 10
   
    */
    ////stdsmrt

    
        
       /* list.push_front(0);
        list.push_front(1);
        list.push_front(2);
        std::cout << "List after inserting 1:" << std::endl;
        list.print_list();*/


    SmartPointer::LinkedList<int> list;

    ///////////////////////////////////////////////////////////
        //SinglyLinkedList<int> list;
        auto start = chrono::high_resolution_clock::now();

        for (int i = 0;i<100; i++) {
            list.push_front(i);
           
        }

        auto end = chrono::high_resolution_clock::now();

         chrono::duration<float> duration = end - start;

        cout << "Duration:1000 " << duration.count() << "s" << endl;
        

        for (int i = 0; i < 100; i++) {
            // list.push_front(i);
            list.pop_front();

        }
        
        ////////////////////////////////////////////////
        auto start1 = chrono::high_resolution_clock::now();

        for (int i = 0; i < 10000; i++) {
            list.push_front(i);
        }

        auto end1 = chrono::high_resolution_clock::now();

        chrono::duration<float> duration1 = end1 - start1;

        cout << "Duration:10000 " << duration1.count() << "s" << endl;

        for (int i = 0; i < 10000; i++) {
            list.pop_front();
        }
        ///////////////
        auto start2 = chrono::high_resolution_clock::now();

        for (int i = 0; i < 100000; i++) {
            list.push_front(i);
        }

        auto end2 = chrono::high_resolution_clock::now();

        chrono::duration<float> duration2 = end2 - start2;

        cout << "Duration:100000 " << duration2.count() << "s" << endl;
        //////////////////////////////////
        for (int i = 0; i < 100000; i++) {
            list.pop_front();
        }

        auto start3 = chrono::high_resolution_clock::now();

        for (int i = 0; i < 1000000; i++) {
            list.push_front(i);
        }

        auto end3 = chrono::high_resolution_clock::now();

        chrono::duration<float> duration3 = end3 - start3;

        cout << "Duration:1000000 " << duration3.count() << "s" << endl;

    /*
    // Вывод списка
    std::cout << "List after inserting 1:" << std::endl;
    list.print_list();

    // Удаление элементов с начала
    list.pop_front();
    std::cout << "List after popping front:" << std::endl;
    list.print_list();
    
    */

    /*
    SmrtPtr<int> smartPtr1(new int(42));
    std::cout << "Smart pointer value (object): " << *smartPtr1 << std::endl;

 
    
    // Пример использования для массива
    SmrtPtr<int> smartPtr2(new int[5] {1, 2, 3, 4, 5}, true);
    std::cout << "Smart pointer value (array): " << smartPtr2[2] << std::endl;
    
    
    // Пример перемещения
    SmrtPtr<int> smartPtr3 = std::move(smartPtr1);

    // Проверка, был ли указатель smartPtr1 перемещен
    if (!smartPtr1.operator->()) {
        std::cout << "Smart pointer 1 was moved." << std::endl;
    }

    std::cout << "Smart pointer 3 value (object): " << *smartPtr3 << std::endl;
    */
    return 0;
}
