#pragma once

#include "LinkedList.hpp" 
#include "SmrtPtr.hpp" 
#include "std_LinkedList.hpp"
#include <cassert>

using namespace std;

void create_move_test();

void create_change_value_test();

void test_smart_pointer_reference_impl(SmrtPtr<int>& ptr);

void test_smart_pointer_reference();

double loadTest(const int N);

double loadTest_std(const int N);

void  time_test();

void all_tests();

void create_copy();