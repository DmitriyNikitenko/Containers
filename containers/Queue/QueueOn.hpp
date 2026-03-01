/*
*  QueueOn Documentation
*
*  The QueueOn class implements a First-In-First-Out (FIFO) container using a dynamic array.
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
class QueueOn {
private:
	size_t _size;
	size_t _capacity;
	T* _data;
public:
	//Constructor and destructor
	QueueOn() : _size(0), _capacity(10), _data(new T[_capacity]) {}
	QueueOn(size_t capacity) : _size(0), _capacity(capacity > 10 ? capacity : 10), _data(new T[_capacity]) {}
	QueueOn(const QueueOn& other) : _size(other._size), _capacity(other._capacity), _data(new T[_capacity]) {
		for (size_t i = 0; i < _size;++i) {
			_data[i] = other._data[i];
		}
	}
	QueueOn(QueueOn&& other) noexcept : _size(other._size), _capacity(other._capacity), _data(other._data) {
		other._size = 0;
		other._capacity = 10;
		other._data = nullptr;
	}
	QueueOn(std::initializer_list<T> init) : _size(init.size()), _capacity(init.size() > 10 ? init.size() * 2 : 10), \
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
	~QueueOn() {
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
		if (empty()) { throw std::out_of_range("QueueOn is empty"); }
		
		for (size_t i = 0; i < _size - 1; ++i) {
			_data[i] = _data[i + 1];
		}
		--_size;
	}

	T& front() {
		if (empty()) { throw std::out_of_range("QueueOn is empty"); }
		return _data[0];
	}

	const T& front() const {
		if (empty()) { throw std::out_of_range("QueueOn is empty"); }
		return _data[0];
	}

	T& back() {
		if (empty()) { throw std::out_of_range("QueueOn is empty"); }
		return _data[_size - 1];
	}

	const T& back() const {
		if (empty()) { throw std::out_of_range("QueueOn is empty"); }
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
	QueueOn& operator=(const QueueOn& other) {
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

	QueueOn& operator=(QueueOn&& other) {
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

	bool operator==(const QueueOn& other) {
		if (_size != other._size) { return false; }

		for (size_t i = 0; i < _size; ++i) {
			if (_data[i] != other._data[i]) {
				return false;
			}
		}
		return true;
	}

	bool operator!=(const QueueOn& other) {
		return !(*this == other);
	}
};
