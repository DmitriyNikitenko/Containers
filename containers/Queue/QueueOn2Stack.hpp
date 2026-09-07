/*
 * QueueOn2Stack
 *
 * FIFO queue implemented using two stacks.
 * Input elements are transferred to the output stack when needed.
 *
 * Time complexity:
 *   Push:    O(1)
 *   Pop:     O(1) amortized
 *   Front:   O(1) amortized
 *   Clear:   O(n)
 *
 * Key properties:
 *   - Uses separate input and output stacks
 *   - FIFO behavior through stack reversal
 *   - Copy and move semantics
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
