#ifndef SMRT_PTR_HPP
#define SMRT_PTR_HPP

template <typename T>
class SmrtPtr {
private:

    T* ptr;
    unsigned* count;

    void free() {
        if (count) {
            --(*count); 
            if (*count == 0) { 
                delete ptr;
                delete count;
            }
        }

    }

public:

    explicit SmrtPtr(T* p = nullptr)
        : ptr(p), count(new unsigned(1)) {}

    
    SmrtPtr(const SmrtPtr& other)
        : ptr(other.ptr), count(other.count) {
        ++(*count);
    }
    
    SmrtPtr& operator=(const SmrtPtr& other) {
        if (this != &other) {
       
            free();

            ptr = other.ptr;
            count = other.count;
            ++(*count);
        }
        return *this;
    }   

    ~SmrtPtr() {

        free();
    
    }

    // Оператор сравнения 
    bool operator==(const SmrtPtr& other) const {
        return ptr == other.ptr;
    }

    // Оператор сравнения 
    bool operator!=(const SmrtPtr& other) const {
        return ptr != other.ptr;
    }

    // Оператор приведения к bool
    operator bool() const {
        return ptr != nullptr;
    }

    
    T&  operator*() const { return *ptr; }
    T*  operator->() const { return ptr; }
    T*  get() const { return ptr; }
    T& operator*()  { return *ptr; }
    T* operator->()  { return ptr; }
    T* get()  { return ptr; }
  
    unsigned use_count() const { return *count; }
};


#endif  