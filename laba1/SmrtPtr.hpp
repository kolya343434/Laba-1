#ifndef SMRT_PTR_HPP
#define SMRT_PTR_HPP

template <typename T>
class SmrtPtr {
private:
    T* ptr;
    unsigned* count;
        
public:

    explicit SmrtPtr(T* p = nullptr)
        : ptr(p), count(new unsigned(1)) {}

    
    SmrtPtr(const SmrtPtr& other)
        : ptr(other.ptr), count(other.count) {
        ++(*count);
    }
  
    
    SmrtPtr& operator=(const SmrtPtr& other) {
        if (this != &other) {
       
            if (--(*count) == 0) {
                delete ptr;
                delete count;
            }
           
            
            ptr = other.ptr;
            count = other.count;
            ++(*count);
        }
        return *this;
    }   
    ~SmrtPtr() {

        if (count && --(*count) == 0) { 
            delete ptr;
            delete count;
            ptr = nullptr;
            count = nullptr;

        }
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