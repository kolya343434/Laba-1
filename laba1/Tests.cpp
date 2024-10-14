
#include <iostream>
#include <thread>
#include <iomanip>
#include "Tests.h"
#include <vector>


void create_move_test() {

    SmrtPtr<int> ptr1(new int(6));
    SmrtPtr<int> ptr2 = ptr1;

    assert(*ptr2 == 6);        // Убедимся, что значение корректно скопировано

    assert(ptr2.operator->() == ptr1.operator->()); //проверим адреса
   
}
void create_change_value_test() {
    SmrtPtr<int> ptr1(new int(6));
    *ptr1 = 7;
    assert(*ptr1 == 7);
    *ptr1 = 5;
    assert(*ptr1 == 5);
   

}
void create_copy() {

    SmrtPtr<int> ptr1(new int(6));

    assert(ptr1.use_count()==1);

    SmrtPtr<int> ptr2 = ptr1;

    assert(ptr1.use_count() == 2);
    assert(ptr2.use_count() == 2);

}
void test_smart_pointer_reference_impl(SmrtPtr<int>& ptr) {

    unsigned p = ptr.use_count();

    SmrtPtr<int> ptr1 = ptr;

    SmrtPtr<int> ptr2 = ptr;

  
    assert(ptr.use_count() - p == 2);
}

void test_smart_pointer_reference() {

    create_move_test();
    create_change_value_test();
    SmrtPtr<int> ptr;

    assert(ptr.use_count() == 1);

    test_smart_pointer_reference_impl(ptr);

    assert(ptr.use_count() == 1);
}

void all_tests() {

    create_move_test();

    create_change_value_test();

    create_copy();

    test_smart_pointer_reference();
}

double loadTest(const int N) {

    // Используем std::vector для управления массивом умных указателей SmrtPtr<int>
    std::vector<SmrtPtr<int>> buff(N);

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < N; ++i) {
        if (i % 5 == 0) {
            buff[i] = SmrtPtr<int>(new int());  // Создаем новый объект
        }
        else {
            buff[i] = buff[i % (5 * 5)];  
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    return duration.count();
}


double loadTest_std(const int N) {

    std::unique_ptr<std::unique_ptr<int>[]> buff(new std::unique_ptr<int>[N]);

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < N; ++i) {
        if (i % 5 == 0) {
            buff[i] = std::unique_ptr<int>(new int()); 
        }
        else {
            if (buff[i % (5 * 5)]) {
                buff[i] = std::unique_ptr<int>(new int(*buff[i % (5 * 5)])); 
            }
            else {
                buff[i] = std::unique_ptr<int>(new int()); 
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    return duration.count();
}

void  time_test() {

    
    cout << setw(15) << " SmrtPtr "
        << setw(20) << " stdSmrtPtr " << endl;


    cout << setw(5) << loadTest(100) << "s "
        << setw(20) << loadTest_std(100) << "s " << endl;

    cout << setw(5) << loadTest(1000) << "s "
        << setw(20) << loadTest_std(1000) << "s " << endl;

    cout << setw(5) << loadTest(10000) << "s "
        << setw(20) << loadTest_std(10000) << "s " << endl;

    cout << setw(5) << loadTest(100000) << "s "
        << setw(20) << loadTest_std(100000) << "s " << endl;

    cout << setw(5) << loadTest(1000000) << "s "
        << setw(20) << loadTest_std(1000000) << "s " << endl;

}
