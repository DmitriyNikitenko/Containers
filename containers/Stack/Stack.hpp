/*
* Stack Documentation
*
* The Stack class implements a stack with dynamic memory management.
* Features:
*    - Low-level memory management via ::operator new() and ::operator delete().
*    - Use of placement new for explicit object construction.
*    - Manual destructor calls to control object lifetimes.
*
* Core Concepts:
* -------------------
* 1. Memory Management:
*    - Memory is allocated as "raw" (uninitialized) using ::operator new(), avoiding
*      default constructor calls for unused elements.
*    - Memory is deallocated via ::operator delete(), which does not invoke destructors
*      (they are called manually).
*
* 2. Placement New:
*    - Objects are constructed in pre-allocated memory using the syntax: new (address) T(args).
*    - Enables:
*      * Precise control over object initialization.
*      * Support for types without default constructors.
*      * Avoidance of unnecessary data copies.
*
* 3. Safety:
*    - Destructors are explicitly called for each object before memory deallocation.
*    - Constructors include exception handling to prevent leaks.
*
* Differences from Standard Containers:
* -----------------------------------
* - Does not use new[]/delete[], providing full control over object lifecycles.
* - Does not require T to have a default constructor.
* - Optimized for scenarios where the stack size changes frequently.

* Limitations:
* ------------
* - Not thread-safe.
* - Move semantics must be supported by type T for efficient object transfers.
*/
#pragma once
#include <stdexcept>
#include <initializer_list>
#include <cstring>

template<typename T>
class Stack{
private:
    //the fields are in this order because the initialization sequence is important
    //fields are initialized in the order they are declared in the class,
    // not in the order they are listed in the constructor's initialization list
	size_t _size;
	size_t _capacity;
    T* _data;
public:
    //Constructor and destructor
    Stack() : _size(0), _capacity(10), _data(static_cast<T*>(::operator new(_capacity * sizeof(T)))) {}
	Stack(size_t capacity) :
        _size(0), _capacity(capacity),
        _data(static_cast<T*>(::operator new(_capacity * sizeof(T)))) {}
    Stack(const Stack& other) 
        : _size(other._size), _capacity(other._capacity) {
        _data = static_cast<T*>(::operator new(_capacity * sizeof(T)));

        for (size_t i = 0; i < _size; ++i) {
            new (&_data[i]) T(other._data[i]);
        }
    }
    Stack(Stack&& other) noexcept {
        _data = other._data;
        _size = other._size;
        _capacity = other._capacity;

        other._data = nullptr;
        other._size = 0;
        other._capacity = 1;
    }
    Stack(std::initializer_list<T> init)
        : _size(init.size()), _capacity(init.size() > 10 ? init.size() * 2 : 10),
        _data(static_cast<T*>(::operator new(_capacity * sizeof(T))))  //creating raw memory
    {

        size_t i = 0;
        try {
            for (const auto& item : init) {
                new (&_data[i++]) T(item); 
            }
        }
        catch (...) {
            for (size_t j = 0; j < i; ++j) {
                _data[j].~T(); 
            }
            ::operator delete(_data);
            throw;
        }
    }
    ~Stack() {
        for (size_t i = 0; i < _size; ++i) {
            _data[i].~T();
        }
        ::operator delete(_data);
    }


    //Main functions
    size_t capacity() const {
        return _capacity;
    }

    void clear() {
        for (size_t i = 0; i < _size; ++i) {
            _data[i].~T();
        }
        _size = 0;
    }

    void push(const T& element) {
        if (_size + 1 >= _capacity) {
            reserve( (_size == 0) ? 10 : _size * 2 );
        }

        new (&_data[_size]) T(element);
        ++_size;
    }

    void pop() {
        if (empty()) { throw std::out_of_range("Stack is empty"); }
        _data[_size - 1].~T();
        --_size;
    }

    const T& top() const {
        if (empty()) { throw std::out_of_range("Stack is empty"); }
        return _data[_size - 1];
    }

    T& top() {
        if (empty()) { throw std::out_of_range("Stack is empty"); }
        return _data[_size - 1];
    }

    size_t size() const {
        return _size;
    }

    bool empty() const {
        return _size == 0;
    }

    void swap(Stack& other) {
        std::swap(_size, other._size);
        std::swap(_capacity, other._capacity);
	memcpy(_data, other._data, other.size() * sizeof(T));
        std::swap(_data, other._data);
    }
    
    void reserve(size_t new_capacity) {
        if (new_capacity <= _capacity) { return; }

        T* new_data = (static_cast<T*>(::operator new(new_capacity * sizeof(T))));
        for (size_t i = 0; i < _size; ++i) {
            new (&new_data[i]) T(_data[i]);
            _data[i].~T();
        }

        ::operator delete(_data);

        _data = new_data;
        _capacity = new_capacity;
    }

    //Operators

    Stack& operator=(const Stack& other) {
        if (this != &other) {
            Stack tmp(other);
            swap(tmp);
        }
        return *this;
    }

    Stack& operator=(Stack&& other) noexcept {
        if (this != &other) {
            if (_data) {
                for (size_t i = 0; i < _size; ++i) {
                    _data[i].~T();
                }
                ::operator delete(_data);
            }

            _data = other._data;
            _size = other._size;
            _capacity = other._capacity;

            other._data = nullptr;
            other._size = 0;
            other._capacity = 1;
        }
        return *this;
    }

    bool operator==(const Stack& other) const {
        if (_size != other._size) { return false; }

        for (size_t i = 0; i < _size; ++i) {
            if (_data[i] != other._data[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const Stack& other) const {
        return !(*this == other);
    }

};
