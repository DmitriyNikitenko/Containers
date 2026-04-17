/*
*  Array Documentation
*
*  The Array class is a fixed-capacity container designed to store a predefined number of elements.
*  It provides element access, basic manipulation methods, and a custom iterator for traversal.
*
*  Key Features:
*    - Fixed-size buffer defined at compile time (no dynamic allocation)
*    - Bounds-checked element access (`operator[]`, `front()`, `back()`)
*    - Custom iterator class supporting arithmetic and dereferencing
*    - Copy and move constructors/assignment operators implemented
*    - `push_back`, `fill`, and conversion to custom String
*    - `to_string()` method converting contents to a string
*
*  Notes:
*    - Maximum capacity defined by template parameter `N`
*    - `push_back()` will throw if called beyond capacity
*    - Iterator class supports forward and backward movement
*    - Not thread-safe for concurrent use
*    - There is no support for constant objects
*/

#pragma once
#include <stdexcept>
#include <initializer_list>
#include "String.hpp"

template <typename T,const size_t N>
class Array {
private:
    T data_[N];
    size_t size_ = 0;
    const size_t capacity_ = N;
public:
    //Constructors and destructor
    Array() = default;
    Array(size_t size, const T& value) {
        if (size > N) {
            throw std::runtime_error("Out of bounds");
        }
        for (size_t i = 0; i < size; ++i) {
            data_[i] = value;
        }
        size_ += size;
    }
    Array(const Array& other) : size_(other.size_) {
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    }
    Array(Array&& other) noexcept : size_(other.size_) {
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
        other.size_ = 0;
    }
    Array(std::initializer_list<T> init) {
        if (init.size() > capacity_) {
            throw std::runtime_error("Out of bounds");
        }
        size_ = init.size();
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = init[i];
        }
    }
    ~Array() = default;
    
    //--------------------------------- I T E R A T O R -----------------------------------
    class Iterator {
    private:
        T* current;
        Array* parent_array;

    public:
        Iterator() = delete;
        Iterator(T* _current, Array* _parent_array) : current(_current), parent_array(_parent_array) {}
        Iterator(const Iterator& other) : current(other.current), parent_array(other.parent_array) {}

        void is_valid() {
            Iterator end = parent_array->end();
            Iterator begin = parent_array->begin();
            if (!current || current >= end.current || current < begin.current) {
                throw std::runtime_error("Iterator not valid");
            }
        }

        bool is_null() const {
            return current == nullptr;
        }

        T& operator*() {
            is_valid();
            return *current;
        }

        T* operator->() {
            is_valid();
            return current;
        }

        const T& operator*() const {
            is_valid();
            return *current;
        }

        const T* operator->() const {
            is_valid();
            return current;
        }


        // Increment/Decrement ------------------------------------------------
        Iterator& operator++() {
            is_valid();
            ++current;
            return *this;
        }

        Iterator operator++(int) {
            Iterator tmp(*this);
            ++(*this);
            return tmp;
        }

        Iterator& operator--() {
            if (!is_null()) {
                --current;
            }
            is_valid();
            return *this;
        }

        Iterator operator--(int) {
            Iterator tmp(*this);
            --(*this);
            return tmp;
        }


        // Arithmetic operations --------------------------------------------
        Iterator& operator+=(size_t n) {
            is_valid();
            current += n;
            return *this;
        }

        Iterator& operator-=(size_t n) {
            if (!is_null()) {
                current -= n;
            }
            is_valid();
            return *this;
        }

        Iterator operator+(size_t n) const {
            Iterator tmp(*this);
            tmp += n;
            return tmp;
        }

        Iterator operator-(size_t n) const {
            Iterator tmp(*this);
            tmp -= n;
            return tmp;
        }


        // Comparison ---------------------------------------------------------
        bool operator==(const Iterator& other) const {
            return current == other.current;
        }

        bool operator!=(const Iterator& other) const {
            return !(current == other.current);
        }

        bool operator<(const Iterator& other) const {
            return current < other.current;
        }

        bool operator>(const Iterator& other) const {
            return current > other.current;
        }

        bool operator<=(const Iterator& other) const {
            return (current < other.current) || (current == other.current);
        }

        bool operator>=(const Iterator& other) const {
            return (current > other.current) || (current == other.current);
        }

    };
    //-------------------------------------------------------------------------------------

    T& front() {
        if (size_ < 1 || size_ > capacity_) {
            throw std::runtime_error("Outof bounds");
        }
        return data_[0];
    }

    T& back() {
        if (size_ < 1 || size_ > capacity_) {
            throw std::runtime_error("Out of bounds");
        }
        return data_[size_ - 1];
    }

    const T& front() const {
        if (size_ < 1 || size_ > capacity_) {
            throw std::runtime_error("Outof bounds");
        }
        return data_[0];
    }

    const T& back() const {
        if (size_ < 1 || size_ > capacity_) {
            throw std::runtime_error("Outof bounds");
        }
        return data_[size_ - 1];
    }

    void fill(const T& value) {
        for (size_t i = 0; i < capacity_; ++i) {
            data_[i] = value;
        }
        size_ = capacity_;
    }

    void push_back(const T& value) {
        if (size_ >= capacity_) {
            throw std::runtime_error("Out of bounds");
        }
        data_[size_++] = value;
    }

    Iterator begin() {
        return Iterator(data_, this);
    }

    Iterator end() {
        return Iterator(data_ + size_, this);
    }

    String toString() const {
        String str;
        for (size_t i = 0; i < size_; ++i) {
            str += std::to_string(data_[i]);
        }
        return str;
    }

    bool empty() const {
        return size_ == 0;
    }

    //Getters
    size_t size() const {
        return size_;
    }

    size_t capacity() const {
        return capacity_;
    }

    T* data() {
        return data_;
    }

    const T* data() const {
        return data_;
    }

    //--------------------------------- O P E A T O R S -------------------------------------
    Array& operator=(const Array& other) {
        if (this != &other) {
            size_ = other.size_;
            for (size_t i = 0; i < size_; ++i) {
                data_[i] = other.data_[i];
            }
        }
        return *this;
    }

    Array& operator=(Array&& other) noexcept {
        if (this != &other) {
            size_ = other.size_;
            for (size_t i = 0; i < size_; ++i) {
                data_[i] = other.data_[i];
            }
            other.size_ = 0;
        }
        return *this;
    }

    //Accessing elements
    T& operator[](size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data_[index];
    }

    const T& operator[](size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data_[index];
    }
};
