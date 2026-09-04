/*
*  QueueOnList Documentation
*
*
*/
#pragma once
#include <stdexcept>
#include <initializer_list>
#include "../List/ListD.hpp"


template<typename T>
class QueueOnList {
private:
	size_t _size;
	size_t _capacity;
	ListD<T> _list;
public:
	//Constructor and destructor
	QueueOnList() : _size(0), _capacity(10), _list() {}
	QueueOnList(size_t capacity) : _size(0), _capacity(capacity > 10 ? capacity : 10), _list() {}
	QueueOnList(const QueueOnList& other) : _size(other._size), _capacity(other._capacity), _list(other._list) {}
	QueueOnList(QueueOnList&& other) noexcept : _size(other._size), _capacity(other._capacity), _list(std::move(other._list)) {
		other._size = 0;
		other._capacity = 10;
		other._list = ListD<T>();
	}
	QueueOnList(std::initializer_list<T> init) : _size(init.size()), _capacity(init.size() > 10 ? init.size() * 2 : 10), \
		_list(init) {
	}
	~QueueOnList() {
		_list.~ListD();
	}

	//Main functions
	void push(const T& value) {
        _list.push_back(value);
	}

	void pop() {
        _list.pop_front();
	}

	T& front() {
		if (empty()) { throw std::out_of_range("QueueOn is empty"); }
		return _list.front();
	}

	const T& front() const {
		if (empty()) { throw std::out_of_range("QueueOn is empty"); }
		return _list.front();
	}

	T& back() {
		if (empty()) { throw std::out_of_range("QueueOn is empty"); }
		return _list.back();
	}

	const T& back() const {
		if (empty()) { throw std::out_of_range("QueueOn is empty"); }
		return _list.back();
	}

	bool empty() const {
		return _list.empty();
	}

	size_t size() const {
		return _list.size();
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
