#pragma once
#include <utility> 
#include <iostream>

#ifndef SMRT_PTR_HPP
#define SMRT_PTR_HPP



#include <iostream>

template <typename T>
class SmrtPtr {
private:
    T* ptr;
    unsigned* count; // ��������� �� ������� ������

public:
    // ����������� ��� ���������� �������
    explicit SmrtPtr(T* p = nullptr)
        : ptr(p), count(new unsigned(1)) {}

    // ����������� �����������
    SmrtPtr(const SmrtPtr& other)
        : ptr(other.ptr), count(other.count) {
        ++(*count); 
    }

    // �������� ����������� ������������
    SmrtPtr& operator=(const SmrtPtr& other) {
        if (this != &other) {
            // ��������� ������� ������ �� ������ ������
            if (--(*count) == 0) {
                delete ptr;
                delete count;
            }

            // �������� ��������� � ������� ������
            ptr = other.ptr;
            count = other.count;
            ++(*count); 
        }
        return *this;
    }

    // �������� �����������
    SmrtPtr(SmrtPtr&& other) noexcept
        : ptr(other.ptr), count(other.count) {
        other.ptr = nullptr;
        other.count = nullptr;
    }

    // �������� ����������� ��� ������������
    SmrtPtr& operator=(SmrtPtr&& other) noexcept {
        if (this != &other) {
            // ��������� ������� ������ �� ������ ������
            if (--(*count) == 0) {
                delete ptr;
                delete count;
            }

            // ���������� ��������� � ������� ������
            ptr = other.ptr;
            count = other.count;
            other.ptr = nullptr;
            other.count = nullptr;
        }
        return *this;
    }

    // ����������
    ~SmrtPtr() {
        // ��������� ������� ������ � ����������� ������, ���� ��� ������ �� ������������
        if (ptr && --(*count) == 0) {
            delete ptr;
            delete count;
        }
    }

    // ��������� ������������� � �������
    T& operator*() const { return *ptr; }
    T* operator->() const { return ptr; }
    T* get() const { return ptr; }

    // ���������� ������� ������� ������
    unsigned use_count() const { return *count; }
};




#endif  