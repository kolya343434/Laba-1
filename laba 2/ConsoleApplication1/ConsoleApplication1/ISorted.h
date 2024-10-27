#pragma once

template <class T>
class ISorted {
public:
    virtual void InsertionSort(Sequence<T>* sequence) = 0;
    virtual void QuickSort(Sequence<T>* sequence) = 0;
    virtual void BubbleSorter(Sequence<T>* sequence) = 0;
    virtual ~ISorted() {}
};

