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

auto loadTest(const int N);

auto loadTest_std(const int N);

void  time_test();
