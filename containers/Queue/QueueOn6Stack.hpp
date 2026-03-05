/*
*
*
*
*/
#pragma once
#include <stdexcept>
#include <initializer_list>
#include "../Stack/Stack.hpp"

template<typename T>
class QueueOn6Stack {
private:
    size_t _size;
    size_t _capacity;
    Stack<T> _stack_push_1;
    Stack<T> _stack_push_2;
    Stack<T> _stack_intermediate;
    Stack<T> _stack_intermediate_copy;
    Stack<T> _stack;
    Stack<T> _stack_pop_1;
    Stack<T> _stack_pop_2;
public:



};