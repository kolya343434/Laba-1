#pragma once
#include "LinkedList.hpp" // Подключаем LinkedList, который сам подключает SmrtPtr
#include "SmrtPtr.hpp" // Подключаем SmrtPtr
#include "stdSmrtPtr.hpp"
#include <cassert>
#include <iostream>
#include <thread>
#include <iomanip>

using namespace std;


void create_move_test() {

    SmrtPtr<int> ptr1(new int(6));
    SmrtPtr<int> ptr2 = ptr1;  // Теперь это разрешено, и произойдёт глубокое копирование
    assert(*ptr2 == 6);        // Убедимся, что значение корректно скопировано
    ///проверим адреса
    assert(ptr2.operator->() != ptr1.operator->());
    cout << "everything okay with create_move_test" << endl;
}
void create_change_value_test() {
    SmrtPtr<int> ptr1(new int(6));
    *ptr1 = 7;
    assert(*ptr1 == 7);
    *ptr1 = 5;
    assert(*ptr1 == 5);
    cout << "everything okay create_change_value_test" << endl;

}
/*
auto time_work_LinkedList(int p, SmartPointer::LinkedList<int>& list) {
	// Замер начала времени
	auto start = std::chrono::high_resolution_clock::now();

	// Выполнение операции добавления элементов
	for (int i = 0; i < p; i++) {
		list.push_front(i);
	}

	// Замер конца времени
	auto end = std::chrono::high_resolution_clock::now();

	// Вычисление продолжительности
	std::chrono::duration<float> duration = end - start;

	// Возвращаем продолжительность в секундах
	return duration.count(); // Возвращаем время в секундах (float)
}

auto time_work_LinkedList_clear(int p, stdSmartPointer::SinglyLinkedList<int>& list) {
    for (int i = 0; i+1 < p; i++) {
        list.pop_front();
    }
}


auto time_work_LinkedList(int p, stdSmartPointer::SinglyLinkedList<int>& list) {
	// Замер начала времени
	auto start = std::chrono::high_resolution_clock::now();

	// Выполнение операции добавления элементов
	for (int i = 0; i < p; i++) {
		list.push_front(i);
	}

	// Замер конца времени
	auto end = std::chrono::high_resolution_clock::now();

	// Вычисление продолжительности
	std::chrono::duration<float> duration = end - start;

	// Возвращаем продолжительность в секундах
	return duration.count(); // Возвращаем время в секундах (float)
}
*/
template <typename T>
auto loadTest(const int N) {
    
    SmrtPtr<T>* buff = new SmrtPtr<T>[N]; // Динамический массив указателей
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < N; ++i) {
        if (i % 5 == 0) {
            buff[i] = SmrtPtr<T>(new T()); // Allocate a new T
        }
        else {
            buff[i] = buff[i % 5 * 5]; // Copy from existing
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    //std::cout <<  duration.count() << " s" << std::endl;


    delete[] buff; // Освобождаем динамический массив
    return duration.count();
}
template <typename T>
auto loadTest_std(const int N) {
    // Динамический массив уникальных указателей
    std::unique_ptr<std::unique_ptr<T>[]> buff(new std::unique_ptr<T>[N]);

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < N; ++i) {
        if (i % 5 == 0) {
            buff[i] = std::unique_ptr<T>(new T()); // Выделяем память под новый объект T
        }
        else {
            if (buff[i % (5 * 5)]) {
                buff[i] = std::unique_ptr<T>(new T(*buff[i % (5 * 5)])); // Копируем объект
            }
            else {
                buff[i] = std::unique_ptr<T>(new T()); // Если указатель не инициализирован, создаём новый объект
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
   // std::cout << "Load test completed in: " << duration.count() << " seconds." << std::endl;
    return duration.count();
}
void  time_test() {
   
    
    cout << setw(15) << " SmrtPtr "
        << setw(20) << " stdSmrtPtr " << endl;
   // loadTest<int>(100);

    cout << setw(5) <<  loadTest<int>(100) << "s " 
        << setw(20) << loadTest_std<int>(100) << "s " << endl;

    cout << setw(5) << loadTest<int>(1000) << "s "
        << setw(20) << loadTest_std<int>(1000) << "s " << endl;

    cout << setw(5) << loadTest<int>(10000) << "s "
        << setw(20) << loadTest_std<int>(10000) << "s " << endl;

    cout << setw(5) << loadTest<int>(100000) << "s "
        << setw(20) << loadTest_std<int>(100000) << "s " << endl;

    cout << setw(5) << loadTest<int>(1000000) << "s "
        << setw(20) << loadTest_std<int>(1000000) << "s " << endl;

    /*
    SmartPointer::LinkedList<int> list_linkedlist_with_SmrtPtrst_test;
    stdSmartPointer::SinglyLinkedList<int> list_linkedlist_with_std_SmrtPtrst_test;

   // cout << "SmrtPtr" << endl;
    cout << setw(15) << " SmrtPtr "
        << setw(20) << " stdSmrtPtr " << endl;

    int p = 1000;
    auto time_taken = time_work_LinkedList(p, list_linkedlist_with_SmrtPtrst_test);
    //cout << "Time taken: " << time_taken << "s" << endl;

    size_t total_memory1 = list_linkedlist_with_SmrtPtrst_test.getMemoryUsage();

   // time_work_LinkedList_clear(p, list_linkedlist_with_SmrtPtrst_test);

   //    time_work_LinkedList_clear(p, list_linkedlist_with_SmrtPtrst_test);

   //  cout <<"fdgddfgdfg" << list_linkedlist_with_SmrtPtrst_test.getMemoryUsage() << endl;

    p = 1000;
    auto time_taken1 = time_work_LinkedList(p, list_linkedlist_with_SmrtPtrst_test);
    //cout << "Time taken: " << time_taken1 << " seconds" << endl;
    size_t total_memory2 = list_linkedlist_with_SmrtPtrst_test.getMemoryUsage();


    p = 100000;
    auto time_taken2 = time_work_LinkedList(p, list_linkedlist_with_SmrtPtrst_test);
   // cout << "Time taken: " << time_taken2 << " seconds" << endl;
    size_t total_memory3 = list_linkedlist_with_SmrtPtrst_test.getMemoryUsage();


    p = 1000000;
    auto time_taken3 = time_work_LinkedList(p, list_linkedlist_with_SmrtPtrst_test);
    //cout << "Time taken: " << time_taken3 << " seconds" << endl;
    size_t total_memory4 = list_linkedlist_with_SmrtPtrst_test.getMemoryUsage();

  


//    cout << "stdSmrtPtr" << endl;

    p = 1000;
    auto time_taken11 = time_work_LinkedList(p, list_linkedlist_with_std_SmrtPtrst_test);
   // cout << "Time taken: " << time_taken11 << " seconds" << endl;
    //size_t total_memory11 = sizeof(list_linkedlist_with_std_SmrtPtrst_test) + sizeof(list_linkedlist_with_std_SmrtPtrst_test);

   // time_work_LinkedList_clear(p, list_linkedlist_with_std_SmrtPtrst_test);
    size_t total_memory11= list_linkedlist_with_std_SmrtPtrst_test.getMemoryUsage();
    p = 10000;
    auto time_taken22 = time_work_LinkedList(p, list_linkedlist_with_std_SmrtPtrst_test);
   // cout << "Time taken: " << time_taken22 << " seconds" << endl;
    //size_t total_memory22 = sizeof(list_linkedlist_with_std_SmrtPtrst_test) + sizeof(list_linkedlist_with_std_SmrtPtrst_test);
    size_t total_memory22 = list_linkedlist_with_std_SmrtPtrst_test.getMemoryUsage();

    p = 100000;
    auto time_taken33 = time_work_LinkedList(p, list_linkedlist_with_std_SmrtPtrst_test);
   // cout << "Time taken: " << time_taken33 << " seconds" << endl;
    size_t total_memory33 = list_linkedlist_with_std_SmrtPtrst_test.getMemoryUsage();

    p = 1000000;
    auto time_taken44 = time_work_LinkedList(p, list_linkedlist_with_std_SmrtPtrst_test);
    //cout << "Time taken: " << time_taken44 << " seconds" << endl;
    size_t total_memory44 = list_linkedlist_with_std_SmrtPtrst_test.getMemoryUsage();

    cout << setw(5) << " Time:" << time_taken << "s "
        << setw(7) << " Time:" << time_taken11 << "s " << endl;

    cout << setw(9) << " memory: " << total_memory1 <<" "
         << setw(15) << " memory: " << total_memory11 << "\n" << endl;

    

    cout << setw(5) << " Time:" << time_taken1 << "s "
        << setw(7) << " Time:" << time_taken22 << "s " << endl;

    cout << setw(9) << " memory: " << total_memory2 << " "
        << setw(15) << " memory: " << total_memory22 << "\n" << endl;

    ////
    cout << setw(5) << " Time:" << time_taken2 << "s "
        << setw(7) << " Time:" << time_taken33 << "s " << endl;

    cout << setw(9) << " memory: " << total_memory3 << " "
        << setw(15) << " memory: " << total_memory33 << "\n" << endl;



    cout << setw(5) << " Time:" << time_taken3 << "s "
        << setw(7) << " Time:" << time_taken44 << "s " << endl;

    cout << setw(9) << " memory: " << total_memory4 << " "
        << setw(15) << " memory: " << total_memory44 << "\n" << endl;


    //time_work_LinkedList_clear(p, list_linkedlist_with_std_SmrtPtrst_test);
   // time_work_LinkedList_clear(p, list_linkedlist_with_SmrtPtrst_test);

    */
}
