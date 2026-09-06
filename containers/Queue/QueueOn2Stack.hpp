/*
*  QueueOn2Stack Documentation
*
*  The QueueOn2Stack class implements a First-In-First-Out (FIFO) container
*  using two internal stacks to simulate queue behavior.
*
*  Key Features:
*    - Amortized O(1) enqueue (`push`) and dequeue (`pop`)
*    - Separation of input and output stacks to minimize element movement
*    - Strong exception safety for core operations, assuming `Stack<T>` provides it
*    - Copy and move semantics for safe value and resource transfer
*
*  Requirements for Type T:
*    - Copy constructor
*    - Copy assignment operator
*    - Destructor (implicitly used)
*
*  Implementation Notes:
*    - New elements are pushed onto the input stack
*    - When the output stack is empty and a `pop` is requested, all elements
*      are transferred from input to output, reversing their order so that
*      the oldest element is on top of the output stack
*
*  Limitations:
*    - No iterator support
*    - Access to the front element relies on the state of the output stack
*/
#pragma once
#include <stdexcept>
#include <initializer_list>
#include <cstring>
#include <cstddef>
#include "../Stack/Stack.hpp"

template<typename T>
class QueueOn2Stack {
private:
    size_t _size;
    size_t _capacity;
    Stack<T> _stack_input;
    Stack<T> _stack_output;

    void move_input_to_output() {
        if (_stack_output.empty()) {
            while (!_stack_input.empty()) {
                _stack_output.push(_stack_input.top());
                _stack_input.pop();
            }
        }
    }
public:
    QueueOn2Stack() : _size(0), _capacity(10), _stack_input(), _stack_output() {}
    QueueOn2Stack(size_t capacity) : _size(0), _capacity(capacity > 10 ? capacity : 10), _stack_input(capacity > 10 ? capacity : 10), _stack_output(capacity > 10 ? capacity : 10) {}
    QueueOn2Stack(const QueueOn2Stack& other) : _size(other._size), _capacity(other._capacity), _stack_input(other._stack_input), _stack_output(other._stack_output) {}
    QueueOn2Stack(QueueOn2Stack&& other) noexcept : _size(other._size), _capacity(other._capacity),  _stack_input(std::move(other._stack_input)), _stack_output(std::move(other._stack_output)) {
        other._size = 0;
        other._capacity = 10;
        other._stack_input.clear();
        other._stack_output.clear();
    }
    ~QueueOn2Stack() {
        _stack_input.clear();
        _stack_output.clear();
    }

    //Main functions
    size_t capacity() const {
        return _capacity;
    }
    void clear() {
        _stack_input.clear();
        _stack_output.clear();
        _size = 0;
    }
    void push(const T& value) {
        _stack_input.push(value);
        ++_size;
    }
    void pop() {
        if (_size == 0) {
            return;
        }

        move_input_to_output();
        _stack_output.pop();
        --_size;
    }
    const T& front() const {
        if (_size == 0) {
            throw std::out_of_range("Queue is empty");
        }

        move_input_to_output();
        return _stack_output.top();
    }
    T& front() {
        if (_size == 0) {
            throw std::out_of_range("Queue is empty");
        }

        move_input_to_output();
        return _stack_output.top();
    }
    size_t size() const {
        return _size;
    }
    bool empty() const {
        return _size == 0;
    }
    void swap(QueueOn2Stack& other) {
        std::swap(_size, other._size);
        std::swap(_capacity, other._capacity);
        std::swap(_stack_input, other._stack_input);
        std::swap(_stack_output, other._stack_output);
    }


    //Operators
    QueueOn2Stack& operator=(const QueueOn2Stack& other) {
        if (this != &other) {
            _size = other._size;
            _capacity = other._capacity;
            _stack_input = other._stack_input;
            _stack_output = other._stack_output;
        }
        return *this;
    }  
    QueueOn2Stack& operator=(QueueOn2Stack&& other) noexcept {
        if (this != &other) {
            _size = other._size;
            _capacity = other._capacity;

            _stack_input = std::move(other._stack_input);
            _stack_output = std::move(other._stack_output);

            other._size = 0;
            other._capacity = 10;
        }

        return *this;
    }
    bool operator==(const QueueOn2Stack& other) const {
        return _size == other._size && _capacity == other._capacity && _stack_input == other._stack_input && _stack_output == other._stack_output;
    }
    bool operator!=(const QueueOn2Stack& other) const {
        return !(*this == other);
    }

        
};
