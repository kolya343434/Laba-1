//#include <iostream>
//#include <utility> // ��� std::move
#pragma once

//#include "SmrtPtr.h"

// ������ ������ ���������
template <typename T>
class SmrtPtr {
private:
    T* ptr; // ����� ���������
    bool isArray; // ��������� �� ������ ��� ��������� ������

public:
    // ����������� ��� ���������� �������
    explicit SmrtPtr(T* p = nullptr) : ptr(p), isArray(false) {}

    // ����������� ��� �������
    explicit SmrtPtr(T* p, bool arrayFlag) : ptr(p), isArray(arrayFlag) {}

    // ��������� �����������, ��� ��� ����� ������� ��������� �������
    SmrtPtr(const SmrtPtr&) = delete;

    // �������� ����������� (��������� �����������)
    SmrtPtr(SmrtPtr&& other) noexcept : ptr(other.ptr), isArray(other.isArray) {
        other.ptr = nullptr; // �������� �������� ����������
    }

    // �������� ����������� (��� ������������)
    SmrtPtr& operator=(SmrtPtr&& other) noexcept {
        if (this != &other) {
            // ����������� ������� �������� �������
            if (ptr) {
                if (isArray) {
                    delete[] ptr; // ����������� ������ ��� �������
                }
                else {
                    delete ptr; // ����������� ������ ��� �������
                }
            }
            // �������� ������� � ������� �������
            ptr = other.ptr;
            isArray = other.isArray;
            other.ptr = nullptr;
        }
        return *this;
    }

    // �������� �������������
    T& operator*() const {
        return *ptr;
    }

    // �������� ������� � ������
    T* operator->() const {
        return ptr;
    }

    // �������� ������� � ��������� �������
    T& operator[](std::size_t index) const {
        return ptr[index];
    }

    // ����������
    ~SmrtPtr() {
        if (ptr) {
            if (isArray) {
                delete[] ptr; // ����������� ������
            }
            else {
                delete ptr; // ����������� ��������� ������
            }
        }
    }
};
/*
int main() {
    // ������ ������������� ��� ���������� �������
    SmrtPtr<int> smartPtr1(new int(42));
    std::cout << "Smart pointer value (object): " << *smartPtr1 << std::endl;

    // ������ ������������� ��� �������
    SmrtPtr<int> smartPtr2(new int[5] {1, 2, 3, 4, 5}, true);
    std::cout << "Smart pointer value (array): " << smartPtr2[2] << std::endl;

    // ������ �����������
    SmrtPtr<int> smartPtr3 = std::move(smartPtr1);
    if (!smartPtr1.operator->()) {
        std::cout << "Smart pointer 1 was moved." << std::endl;
    }
    std::cout << "Smart pointer 3 value (object): " << *smartPtr3 << std::endl;

    return 0;
}*/
