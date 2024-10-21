#include <iostream>
#include <vector>
#include "linked.hpp"
using namespace std;

void countingSort(LinkedList<int>& arr) {
    // Поиск максимального элемента для определения диапазона
    int maxElement = *max_element(arr.begin(), arr.end());

    // Создание массива для хранения количества вхождений
    vector<int> count(maxElement + 1, 0);

    // Подсчёт количества вхождений каждого элемента
    for (int i = 0; i < arr.size(); i++) {
        count[arr[i]]++;
    }

    // Восстановление отсортированного массива
    int index = 0;
    for (int i = 0; i <= maxElement; i++) {
        while (count[i] > 0) {
            arr[index++] = i;
            count[i]--;
        }
    }
}

