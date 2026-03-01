/*
 *  Queue Documentation
 *
 *  The Queue class implements a First-In-First-Out (FIFO) container
 *  using a dynamically allocated circular buffer.
 *
 *  The container provides O(1) amortized push and pop operations
 *  by maintaining head and tail indices instead of shifting elements.
 *
 *  Key Features:
 *    - Circular buffer (ring buffer) implementation
 *    - O(1) push and pop operations
 *    - Dynamic capacity growth (doubling strategy)
 *    - Copy and move semantics
 *    - Initializer list construction
 *    - Bounds-checked element access (front / back)
 *
 *  Memory Model:
 *    - Storage is allocated using `new T[capacity]`
 *    - All elements are constructed eagerly at allocation time
 *    - pop() and clear() perform logical removal only
 *    - Element destructors are invoked only when the buffer is destroyed
 *      or reallocated
 *
 *  Requirements for Type T:
 *    - Copy constructible
 *    - Copy assignable
 *    - Destructible
 *
 *  Exception Safety:
 *    - Strong exception safety for constructors
 *    - Basic exception safety for copy assignment
 *    - reserve() provides strong exception safety
 *
 *  Limitations:
 *    - No iterator support
 *    - No allocator or placement-new based lifetime management
 *    - Destructors of elements are not called on pop()
 *
 *  This implementation prioritizes simplicity and performance
 *  over full STL-level memory management semantics.
 */
#pragma once
#include <stdexcept>
#include <initializer_list>

template<typename T>
class Queue {
private:
    size_t _size;
    size_t _capacity;
    T* _data;
    size_t _start;
    size_t _finish;
public:
	//Constructors
    Queue() : _size(0), _capacity(10), _data(new T[_capacity]), _start(0), _finish(0) {}
	Queue(size_t new_capacity, const T& default_val)
		: _size(0),
		_capacity(new_capacity),
		_data(new T[new_capacity]),
		_start(0),
		_finish(0) {

		for (size_t i = 0; i < _capacity; ++i) {
			_data[i] = default_val;
		}
	}
	Queue(std::initializer_list<T> init) : _size(init.size()), _capacity((_size == 0) ? 10 : _size * 2), _data(new T[_capacity]), _start(0), _finish(init.size()) {
        size_t i = 0;
        try {
            for (const auto& item : init) {
                _data[i] = item;
                ++i;
            }
        }
        catch (...) {
            delete[] _data;
            throw;
        }
    }
    Queue(const Queue& other) : _size(other._size), _capacity(other._capacity) , _data(new T[_capacity]), _start(other._start), _finish(other._finish) {
		size_t i = _start;
		size_t j = other._start;
		size_t counter = 0;
		while (counter < _size) {
			_data[i++] = other._data[j++];
			i %= _capacity;
			j %= other._capacity;
			++counter;
		}
    }
    Queue(Queue&& other) noexcept : _size(other._size), _capacity(other._capacity), _start(other._start), _finish(other._finish) {
        _data = other._data;

		other._data = nullptr;
		other._size = 0;
		other._capacity = 0;
		other._start = 0;
		other._finish = 0;
    }
    ~Queue() {
        delete[] _data;
    }

	//Main functions
	void push(const T& value) {
		if (_size == _capacity) {
			reserve(_capacity == 0 ? 1 : _capacity * 2);
		}
		_data[_finish++] = value;
		++_size;
		_finish %= _capacity;
	}
	void pop() {
		if (_size == 0) { return; }
		++_start;
		_start %= _capacity;
		--_size;
	}
	T& front() {
		if (empty()) { 
			throw std::out_of_range("Queue is empty");
		}
		return _data[_start];
	}
	const T& front() const {
		if (empty()) {
			throw std::out_of_range("Queue is empty");
		}
		return _data[_start];
	}
	T& back() {
		if (empty()) { 
			throw std::out_of_range("Queue is empty");
		}
		if (_finish == 0) {
			return _data[_capacity - 1];
		}
		return _data[_finish - 1];
	}
	const T& back() const {
		if (empty()) { 
			throw std::out_of_range("Queue is empty");
		}
		if (_finish == 0) {
			return _data[_capacity - 1];
		}
		return _data[_finish - 1];
	}
	bool empty() const {
		return _size == 0;
	}
	size_t size() const {
		return _size;
	}
	size_t capacity() const {
		return _capacity;
	}
	void clear() {
		_size = 0;
		_start = 0;
		_finish = 0;
	}
	void reserve(size_t new_capacity) {
		if (new_capacity <= _capacity) { return; }

		T* new_data = new T[new_capacity];
		try {
			size_t i = 0;
			size_t j = _start;
			size_t counter = 0;
			while (counter < _size) {
				new_data[i++] = _data[j++];
				j %= _capacity;
				++counter;
			}
		}
		catch (const std::exception& e) {
			delete[] new_data;
			throw ;
		}
		_start = 0;
		_finish = _size;
		delete[] _data;
		_data = new_data;
		_capacity = new_capacity;
	}

	//Operators
	Queue& operator=(const Queue& other) {
		if (this != &other) {
			_size = other._size;
			_capacity = other._capacity;
			_start = other._start;
			_finish = other._finish;

			delete[] _data;
			_data = new T[_capacity];
			size_t i = _start;
			size_t j = other._start;
			size_t counter = 0;
			while (counter < _size) {
				_data[i++] = other._data[j++];
				i %= _capacity;
				j %= other._capacity;
				++counter;
			}
		}
		return *this;
	}
	Queue& operator=(Queue&& other) noexcept {
		if (this != &other) {
			delete[] _data;
			_data = other._data;
			_size = other._size;
			_capacity = other._capacity;
			_start = other._start;
			_finish = other._finish;

			other._data = nullptr;
			other._size = 0;
			other._capacity = 0;
			other._start = 0;
			other._finish = 0;
		}
		return *this;
	}
	bool operator==(const Queue& other) const {
		if (_size != other._size) { return false; }

		size_t i = _start;
		size_t j = other._start;
		size_t counter = 0;
		while (counter < _size) {
			if (_data[i++] != other._data[j++]) {
				return false;
			}
			i %= _capacity;
			j %= other._capacity;
			++counter;
		}
		return true;
	}
	bool operator!=(const Queue& other) const {
		return !(*this == other);
	}
};
