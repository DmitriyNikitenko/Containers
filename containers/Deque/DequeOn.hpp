/*
*  Deque Documentation
*
*  The Deque class is a double-ended queue implementation using a dynamic circular buffer.
*  Supports efficient insertion and deletion at both ends and provides random-access iterators.
*
*  Key Features:
*    - Dynamic memory expansion/shrinking for efficient storage.
*    - Bounds-checked element access via at() and operator[].
*    - Support for random-access iterators with bounds checking.
*    - Constant time insertion and deletion at both ends (amortized).
*    - Capacity and size management (reserve, resize, shrink_to_fit).
*    - Full RAII compliance with proper copy/move semantics.
*
*  Notes:
*    - Iterators throw std::out_of_range on out-of-bounds access.
*    - Existing iterators are invalidated when capacity changes (reallocation occurs).
*    - Not thread-safe for concurrent modifications.
*    - The underlying storage is a contiguous array (circular buffer).
*    - When reallocation occurs, elements are rearranged to start at index 0.
*/
#include <stdexcept>
#include <initializer_list>
#include <cstring>
#include <cstddef>


template<typename T>
class Deque {
private:
	size_t _size;
	size_t _capacity;

	size_t front_index;
	size_t back_index;

	T* _data;
public:
	Deque() : _size(0), _capacity(10), front_index(0), back_index(0), _data(new T[_capacity]) {}
	Deque(size_t capacity) : _size(0), _capacity(capacity), front_index(0), back_index(0), _data(new T[_capacity]) {}
	Deque(const Deque& other) : _size(other._size), _capacity(other._capacity),
		front_index(other.front_index), back_index(other.back_index), _data(new T[_capacity]) {
		for (size_t i = front_index; i < _size;++i) {
			_data[i] = other._data[i];
		}
	}
	Deque(Deque&& other) noexcept : _size(other._size), _capacity(other._capacity),
		front_index(other.front_index), back_index(other.back_index), _data(other._data) {
		other._size = 0;
		other._capacity = 10;
		other.front_index = 0;
		other.back_index = 0;
		other._data = nullptr;
	}
	Deque(std::initializer_list<T> init) : _size(init.size()), _capacity(init.size() > 10 ? init.size() * 2 : 10),
		front_index(0), back_index(init.size() - 1), _data(new T[_capacity]) {

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
	~Deque() {
		delete[] _data;
	}


	//--------------------------------- I T E R A T O R -----------------------------------
	class Iterator {
	private:
		Deque* _container;
		T* _ptr;

		size_t _get_logical_pos() const {
			size_t current_index = _ptr - _container->_data;
			if (current_index >= _container->front_index) {
				return current_index - _container->front_index;
			}
			else {
				return current_index + _container->_capacity - _container->front_index;
			}
		}

		void _check_dereference() const {
			size_t logical_pos = _get_logical_pos();
			if (logical_pos >= _container->_size) {
				throw std::out_of_range("Dereferencing invalid iterator");
			}
		}

		void _check_arithmetic(size_t new_logical_pos) const {
			if (new_logical_pos > _container->_size) {
				throw std::out_of_range("Iterator out of range");
			}
		}

	public:
		Iterator(T* ptr, Deque* container) : _ptr(ptr), _container(container) {}

		T& operator*() {
			if (!_ptr || _ptr < _container->_data || _ptr >= _container->_data + _container->_capacity) {
				size_t current_index = _ptr - _container->_data;
				if (current_index >= _container->_capacity) {
					throw std::out_of_range("Dereferencing invalid iterator");
				}
				return *_ptr;
			}
			return *_ptr;
		}

		T* operator->() {
			_check_dereference();
			return _ptr; 
		}

		const T& operator*() const {
			if (!_ptr || _ptr < _container->_data || _ptr >= _container->_data + _container->_capacity) {
				size_t current_index = _ptr - _container->_data;
				if (current_index >= _container->_capacity) {
					throw std::out_of_range("Dereferencing invalid iterator");
				}
				return *_ptr;
			}
			return *_ptr;
		}

		const T* operator->() const {
			_check_dereference();
			return _ptr;  // Исправлено: было &_ptr
		}

		//Increment/decrement --------------------------------------------------
		Iterator& operator++() {
			*this += 1;
			return *this;
		}

		Iterator& operator--() {
			*this -= 1;
			return *this;
		}

		Iterator operator++(int) {
			Iterator tmp = *this;
			++(*this);
			return tmp;
		}

		Iterator operator--(int) {
			Iterator tmp = *this;
			--(*this);
			return tmp;
		}

		//Arithmetic operations -----------------------------------------------
		Iterator& operator+=(size_t n) {
			size_t logical_pos = _get_logical_pos();
			size_t new_logical_pos = logical_pos + n;
			_check_arithmetic(new_logical_pos);

			size_t new_physical_index = (new_logical_pos + _container->front_index) % _container->_capacity;
			_ptr = _container->_data + new_physical_index;
			return *this;
		}

		Iterator& operator-=(size_t n) {
			size_t logical_pos = _get_logical_pos();
			if (n > logical_pos) {
				_ptr = nullptr;
				return *this;
			}
			size_t new_logical_pos = logical_pos - n;

			size_t new_physical_index = (new_logical_pos + _container->front_index) % _container->_capacity;
			_ptr = _container->_data + new_physical_index;
			return *this;
		}

		Iterator operator+(size_t n) const {
			Iterator tmp = *this;
			tmp += n;
			return tmp;
		}

		Iterator operator-(size_t n) const {
			Iterator tmp = *this;
			tmp -= n;
			return tmp;
		}

		//Iterator difference
		ptrdiff_t operator-(const Iterator& other) const {
			if (_container != other._container) {
				throw std::invalid_argument("Iterators from different containers");
			}
			return static_cast<ptrdiff_t>(_get_logical_pos()) -
				static_cast<ptrdiff_t>(other._get_logical_pos());
		}

		// Comparison ------------------------------------------------------------
		Iterator& operator=(const Iterator& other) {
			_ptr = other._ptr;
			_container = other._container;
			return *this;
		}

		bool operator==(const Iterator& other) const {
			return _ptr == other._ptr;
		}

		bool operator!=(const Iterator& other) const {
			return !(*this == other);
		}

		bool operator<(const Iterator& other) const {
			return _get_logical_pos() < other._get_logical_pos();
		}

		bool operator>(const Iterator& other) const {
			return other < *this;
		}

		bool operator<=(const Iterator& other) const {
			return !(other < *this);
		}

		bool operator>=(const Iterator& other) const {
			return !(*this < other);
		}
	};
	//-------------------------------------------------------------------------------------


	//Adding elements :
	void push_back(const T& value) {
		if (_size >= _capacity) {
			reserve(_capacity < 10 ? 10 : _capacity * 2);
		}

		if (empty()) {
			front_index = 0;
			back_index = 0;
			_data[back_index] = value;
		}
		else {
			size_t new_index = (back_index + 1) % _capacity;
			_data[new_index] = value;
			back_index = new_index;
		}

		++_size;
	}

	void push_front(const T& value) {
		if (_size >= _capacity) {
			reserve(_capacity < 10 ? 10 : _capacity * 2);
		}

		if (empty()) {
			front_index = 0;
			back_index = 0;
			_data[front_index] = value;
		}
		else {
			size_t new_index = (front_index - 1 + _capacity) % _capacity;
			_data[new_index] = value;
			front_index = new_index;
		}
		++_size;
	}

	void insert(const Iterator& pos, const T& value) {
		size_t logical_pos = pos - begin();

		if (_size >= _capacity) {
			reserve(_capacity ? _capacity * 2 : 10);
		}

		for (size_t i = _size; i > logical_pos; --i) {
			size_t curr_phys = (front_index + i) % _capacity;
			size_t prev_phys = (front_index + i - 1) % _capacity;
			_data[curr_phys] = std::move(_data[prev_phys]);
		}

		size_t insert_phys = (front_index + logical_pos) % _capacity;
		new (&_data[insert_phys]) T(value);

		++_size;
		back_index = (front_index + _size) % _capacity;
	}

	void insert(const Iterator& pos, size_t count, const T& value) {
		if (count == 0) return;

		const size_t logical_pos = pos - begin();

		if (_size + count > _capacity) {
			size_t new_capacity = std::max(_capacity * 2, _size + count);
			reserve(new_capacity);
		}

		size_t elements_after = _size - logical_pos;

		for (size_t i = 0; i < elements_after; ++i) {
			size_t src_idx = _size - 1 - i;
			size_t dst_idx = _size - 1 - i + count;
			size_t src_physical = (front_index + src_idx) % _capacity;
			size_t dst_physical = (front_index + dst_idx) % _capacity;
			_data[dst_physical] = std::move(_data[src_physical]);
		}

		for (size_t i = 0; i < count; ++i) {
			size_t physical_idx = (front_index + logical_pos + i) % _capacity;
			new (&_data[physical_idx]) T(value);
		}

		_size += count;
		back_index = (front_index + _size) % _capacity;
	}


	//Access to elements:

	T& front() {
		if (empty()) {
			throw std::out_of_range("Deque is empty");
		}
		return _data[front_index];
	}

	const T& front() const {
		if (empty()) {
			throw std::out_of_range("Deque is empty");
		}
		return _data[front_index];
	}

	T& back() {
		if (empty()) {
			throw std::out_of_range("Deque is empty");
		}
		return _data[back_index];
	}

	const T& back() const {
		if (empty()) {
			throw std::out_of_range("Deque is empty");
		}
		return _data[back_index];
	}

	Iterator begin() {
		return empty() ? end() : Iterator(&_data[front_index], this);
	}

	Iterator end() {
		if (empty()) {
			return Iterator(_data, this);
		}
		return Iterator(&_data[back_index + 1], this);
	}

	const Iterator begin() const {
		return empty() ? end() : Iterator(&_data[front_index], this);
	}

	const Iterator end() const {
		if (empty()) {
			return Iterator(_data, this);
		}
		return Iterator(&_data[back_index + 1], this);
	}

	T& at(size_t pos) {
		if (pos > _capacity) {
			throw std::out_of_range("Iterator out of bounds");
		}
		return _data[pos];
	}

	const T& at(size_t pos) const {
		if (pos > _capacity) {
			throw std::out_of_range("Iterator out of bounds");
		}
		return _data[pos];
	}


	//Removing items:

	void pop_back() {
		if (empty()) {
			throw std::out_of_range("pop_back on empty deque");
		}

		_data[back_index].~T();
		--_size;

		if (empty()) {
			front_index = 0;
			back_index = 0;
		}
		else {
			back_index = (back_index + _capacity - 1) % _capacity;
		}
	}

	void pop_front() {
		if (empty()) {
			throw std::out_of_range("popfront_index on empty deque");
		}

		_data[front_index].~T();
		--_size;

		if (empty()) {
			front_index = 0;
			back_index = 0;
		}
		else {
			front_index = (front_index + 1) % _capacity;
		}

	}

	void erase(const Iterator& pos) {
		size_t logical_pos = pos - begin(); 

		size_t physical_pos = (front_index + logical_pos) % _capacity;
		_data[physical_pos].~T();

		for (size_t i = logical_pos; i < _size - 1; ++i) {
			size_t curr_phys = (front_index + i) % _capacity;
			size_t next_phys = (front_index + i + 1) % _capacity;
			_data[curr_phys] = std::move(_data[next_phys]);
		}

		--_size;
		back_index = (front_index + _size) % _capacity;
	}

	void erase(const Iterator first, const Iterator last) {
		if (last < first) {
			throw std::out_of_range("Invalid iterator range");
		}
		if (first == last) {
			return;
		}

		const size_t first_logical = first - begin();
		const size_t last_logical = last - begin();
		const size_t count = last_logical - first_logical;

		// Уничтожение элементов в диапазоне
		for (size_t i = 0; i < count; ++i) {
			size_t physical_idx = (front_index + first_logical + i) % _capacity;
			_data[physical_idx].~T();
		}

		// Сдвиг оставшихся элементов (двумя частями для кольцевого буфера)
		size_t elements_after = _size - last_logical;

		// Часть 1: Сдвигаем элементы после удаляемого диапазона влево
		for (size_t i = 0; i < elements_after; ++i) {
			size_t src_physical = (front_index + last_logical + i) % _capacity;
			size_t dst_physical = (front_index + first_logical + i) % _capacity;
			_data[dst_physical] = std::move(_data[src_physical]);
		}

		_size -= count;
		back_index = (front_index + _size) % _capacity;
	}


	//Other methods :

	bool empty() const {
		return _size == 0;
	}

	size_t size() const {
		return _size;
	}

	size_t max_size() const {
		return _capacity;
	}

	void reserve(size_t new_capacity) {
		if (new_capacity <= _capacity) { return; }

		T* new_data = new T[new_capacity]();
		size_t new_index = 0;

		if (!empty()) {
			size_t current = front_index;
			for (size_t i = 0; i < _size; ++i) {
				new_data[new_index++] = _data[current];
				current = (current + 1) % _capacity;
			}
		}

		delete[] _data;
		_data = new_data;
		_capacity = new_capacity;
		front_index = 0;
		back_index = (_size == 0) ? 0 : _size - 1;
	}

	void resize(size_t count, const T& value = T()) {
		if (count == _size) { return; }

		if (count > _size) {
			if (_size + count >= _capacity) {
				reserve(_capacity < 10 ? 10 : _size + count + 10);
			}

			size_t count_add = count - _size;
			for (size_t i = 0; i < count_add; ++i) {
				push_back(value);
			}
		}
		else {
			size_t count_remove = _size - count;
			for (size_t i = 0; i < count_remove; ++i) {
				pop_back();
			}
		}
	}

	void clear() {
		if (_data) {
			delete[] _data;
		}
		_capacity = 10;
		_size = 0;
		front_index = 0;
		back_index = 0;
		_data = new T[_capacity];
	}

	//----------------------------------------- O P E R A T O R S ------------------------------------------------
	Deque& operator=(const Deque& other) {
		if (this != &other) {
			delete[] _data;

			_size = other._size;
			_capacity = other._capacity;
			front_index = other.front_index;
			back_index = other.back_index;

			_data = new T[_capacity];
			if (other._data) {
				memcpy(_data, other._data, _capacity * sizeof(T));
			}
		}
		return *this;
	}

	Deque& operator=(Deque&& other) noexcept {
		if (this != &other) {
			delete[] _data;

			_data = other._data;
			_size = other._size;
			_capacity = other._capacity;
			front_index = other.front_index;
			back_index = other.back_index;

			other._data = nullptr;
			other._size = 0;
			other._capacity = 10;
			other.front_index = 0;
			other.back_index = 0;
		}
		return *this;
	}

	T& operator[](size_t index) {
		if (index >= _size) throw std::out_of_range("Index out of range");
		size_t physical_idx = (front_index + index) % _capacity;
		return _data[physical_idx];
	}

	const T& operator[](size_t index) const {
		if (index >= _size) throw std::out_of_range("Index out of range");
		size_t physical_idx = (front_index + index) % _capacity;
		return _data[physical_idx];
	}

};
