#pragma once
#include <utility> // ��� std::move
#include <iostream>

#ifndef SMRT_PTR_HPP
#define SMRT_PTR_HPP

// ������ ������ ���������

template <typename T>
class SmrtPtr {
private:
    T* ptr;

public:
    // ����������� ��� ���������� �������
    explicit SmrtPtr(T* p = nullptr)
        : ptr(p) {}

    // ����������� �����������
    SmrtPtr(const SmrtPtr& other)
        : ptr(other.ptr ? new T(*other.ptr) : nullptr) {}

    // �������� ����������� ������������
    SmrtPtr& operator=(const SmrtPtr& other) {
        if (this != &other) {
            // ����������� ������ ������, ���� ����
            delete ptr;

            // �������� ������, ���� ��������� �� null
            ptr = other.ptr ? new T(*other.ptr) : nullptr;
        }
        return *this;
    }

    // �������� �����������
    SmrtPtr(SmrtPtr&& other) noexcept
        : ptr(other.ptr) {
        other.ptr = nullptr; // �������� �������� ����������
    }

    // �������� ����������� ��� ������������
    SmrtPtr& operator=(SmrtPtr&& other) noexcept {
        if (this != &other) {
            delete ptr; // ����������� ������ ������

            ptr = other.ptr; // �������� �������� ����������
            other.ptr = nullptr; // �������� ��������� ������� �������
        }
        return *this;
    }

    // ����������
    ~SmrtPtr() {
        delete ptr; // ����������� ������
    }

    // ��������� ������������� � �������
     T& operator*() const { return *ptr; }
     T* operator->() const { return ptr; }
     T* get() const { return ptr; }

   // T* get()  { return ptr; }
   // T* operator->() { return ptr; }
   // T& operator*()  { return *ptr; }
};



#endif  // SMRT_PTR_HPP