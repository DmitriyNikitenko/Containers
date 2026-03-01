/*
*  Queue Documentation
*
*  The Queue class implements a First-In-First-Out (FIFO) container using a dynamic array.
*  Supports core queue operations with automatic resizing and exception-safe resource management.
*
*  Key Features:
*    - Dynamic memory expansion (doubling strategy)
*    - Deep-copy and move semantics
*    - Initializer list construction
*    - Bounds-checked element access
*    - Strong exception safety for core operations
*
*  Requirements for Type T:
*    - Copy constructor
*    - Copy assignment operator
*    - Destructor (implicitly used)
*
*  Implementation Notes:
*    - Uses contiguous storage with O(1) amortized push, O(n) pop
*    - Explicit destructor calls during pop operations
*    - Self-assignment safe operators
*    - Move operations leave source in valid empty state
*
*  Limitations:
*    - No iterator support
*    - pop() requires element shifting (linear time)
*    - Capacity always grows (never shrinks)
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
public:
	//Constructor and destructor
	Queue() : _size(0), _capacity(10), _data(new T[_capacity]) {}
	Queue(size_t capacity) : _size(0), _capacity(capacity > 10 ? capacity : 10), _data(new T[_capacity]) {}
	Queue(const Queue& other) : _size(other._size), _capacity(other._capacity), _data(new T[_capacity]) {
		for (size_t i = 0; i < _size;++i) {
			_data[i] = other._data[i];
		}
	}
	Queue(Queue&& other) noexcept : _size(other._size), _capacity(other._capacity), _data(other._data) {
		other._size = 0;
		other._capacity = 10;
		other._data = nullptr;
	}
	Queue(std::initializer_list<T> init) : _size(init.size()), _capacity(init.size() > 10 ? init.size() * 2 : 10), \
		_data(new T[_capacity]) {

		size_t i = 0;
		try {
			for (const auto& it : init) {
				_data[i] = it;
				++i;
			}
		}
		catch (...) {
			delete[] _data;
			throw;
		}
	}
	~Queue() {
		delete[] _data;
	}

	//Main functions
	void push(const T& value) {
		if (_size + 1 >= _capacity) {
			reserve((_size + 1) * 2);
		}

		_data[_size] = value;
		++_size;
	}

	void pop() {
		if (empty()) { throw std::out_of_range("Queue is empty"); }
		
		for (size_t i = 0; i < _size - 1; ++i) {
			_data[i] = _data[i + 1];
		}
		--_size;
	}

	T& front() {
		if (empty()) { throw std::out_of_range("Queue is empty"); }
		return _data[0];
	}

	const T& front() const {
		if (empty()) { throw std::out_of_range("Queue is empty"); }
		return _data[0];
	}

	T& back() {
		if (empty()) { throw std::out_of_range("Queue is empty"); }
		return _data[_size - 1];
	}

	const T& back() const {
		if (empty()) { throw std::out_of_range("Queue is empty"); }
		return _data[_size - 1];
	}

	bool empty() const {
		return _size == 0;
	}

	size_t size() const {
		return _size;
	}

	void reserve(size_t new_capacity) {
		if (new_capacity <= _capacity) { return; }

		T* new_data = new T[new_capacity];

		for (size_t i = 0; i < _size; ++i) {
			new_data[i] = _data[i];
		}

		delete[] _data;
		_data = new_data;
		_capacity = new_capacity;
	}

	//Operators
	Queue& operator=(const Queue& other) {
		if (this != &other) {
			_size = other._size;
			_capacity = other._capacity;

			delete[] _data;
			_data = new T[_capacity];
			for (size_t i = 0; i < _size; ++i) {
				_data[i] = other._data[i];
			}
		}
		return *this;
	}

	Queue& operator=(Queue&& other) {
		if (this != &other) {
			delete[] _data;

			_data = other._data;
			_size = other._size;
			_capacity = other._capacity;

			other._data = nullptr;
			other._size = 0;
			other._capacity = 0;
		}
		return *this;
	}

	bool operator==(const Queue& other) {
		if (_size != other._size) { return false; }

		for (size_t i = 0; i < _size; ++i) {
			if (_data[i] != other._data[i]) {
				return false;
			}
		}
		return true;
	}

	bool operator!=(const Queue& other) {
		return !(*this == other);
	}
};
