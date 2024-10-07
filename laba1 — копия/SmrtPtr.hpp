#pragma once
#include <utility> // ��� std::move
#include <iostream>


    // ������ ������ ���������
    template <typename T>
    class SmrtPtr {
    private:
        T* ptr;          // ����� ���������
        bool isArray;    // ��������� �� ������ ��� ��������� ������

    public:
        // ����������� ��� ���������� �������
        explicit SmrtPtr(T* p = nullptr) : ptr(p), isArray(false) {}

        // ����������� ��� �������
        explicit SmrtPtr(T* p, bool arrayFlag) : ptr(p), isArray(arrayFlag) {}

        // ��������� �����������
        SmrtPtr(const SmrtPtr&) = delete;

        // �������� ����������� (��������� �����������)
        SmrtPtr(SmrtPtr&& other) noexcept : ptr(other.ptr), isArray(other.isArray) {
            other.ptr = nullptr; // �������� �������� ����������
        }

        // �������� ����������� (��� ������������)
        SmrtPtr& operator=(SmrtPtr&& other) noexcept {
            if (this != &other) {
                if (ptr) {
                    if (isArray) {
                        delete[] ptr; // ����������� ������ ��� �������
                    }
                    else {
                        delete ptr;   // ����������� ������ ��� �������
                    }
                }
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
                    delete ptr;   // ����������� ��������� ������
                }
            }
        }
    };


 // SMRT_PTR_HPP
