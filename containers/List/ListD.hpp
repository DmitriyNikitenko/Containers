/*
*  ListD Documentation
*
*  The ListD class is a doubly linked list implementation providing efficient insertion/deletion operations.
*  Supports bidirectional iterators with bounds checking and common list operations.
*
*  Key Features:
*    - Dynamic memory management with O(1) insertion/deletion at head/tail
*    - Bidirectional iterators with element access operations
*    - Exception safety for core operations
*    - Custom operations: unique(), reverse()
*    - Support for initializer lists and move semantics
*    - Move semantic
*
*  Notes:
*    - Iterators become invalid after element deletion
*    - Not thread-safe for concurrent access
*    - Uses deep copying for copy operations
*/
#include <stdexcept>
#include <initializer_list>


template<typename T>
class ListD {
private:
	size_t _size;
	struct Node {
		T _data;
		Node* _next;
		Node* _prev;

		Node(const T& data_ = T(),Node* next_ = nullptr, Node* prev_ = nullptr) : _data(data_), _next(next_), _prev(prev_) {}
		Node(T&& data_, Node* next_ = nullptr, Node* prev_ = nullptr) : _data(std::move(data_)), _next(next_), _prev(prev_) {}

		void swap(Node& other) {
			std::swap(_data, other._data);
		}
	};
	Node* _head;
	Node* _tail;
public:
	//Constructor and destructor
	ListD() : _size(0), _head(nullptr), _tail(nullptr) {}
	ListD(size_t count, const T& value) : _size(0) {
		if (count > 0) {
			_head = new Node(value);
			Node* _current = _head;
			_size = 1;

			for (size_t i = 1; i < count; ++i) {
				_current->_next = new Node(value);
				_current = _current->_next;
				++_size;
			}
			_tail = _current;
		}
	}
	ListD(size_t count) : ListD(count,T()) {}
	ListD(const ListD& other) : _size(other._size), _head(nullptr), _tail(nullptr) {
		try {
			if (other._size > 0) {
				_head = new Node(other._head->_data);
				Node* _current = _head;
				Node* other_current = other._head;
				_size = 1;

				for (size_t i = 1; i < other._size; ++i) {
					if (!other_current) {
						throw std::runtime_error("Invalid source list");
					}

					_current->_next = new Node(other_current->_next->_data, nullptr, _current);
					_current = _current->_next;
					other_current = other_current->_next;
					++_size;
				}
				_tail = _current;

				if (other._size != _size) {
					throw std::runtime_error("Size mismatch in source list");
				}
			}
		}
		catch (...) {
			clear();
			throw;
		}
	}
	ListD(ListD&& other) noexcept : _size(other._size), _head(other._head), _tail(other._tail) {
		other._size = 0;
		other._head = nullptr;
		other._tail = nullptr;
	}
	ListD(std::initializer_list<T> init) : _size(0), _head(nullptr), _tail(nullptr) {
		try {
			if (init.size() > 0) {
				auto it = init.begin();
				_head = new Node(*it);
				Node* _current = _head;
				_size = 1;

				++it;
				for (; it != init.end(); ++it) {
					_current->_next = new Node(*it, nullptr, _current);
					_current = _current->_next;
					++_size;
				}
				_tail = _current;

			}
		}
		catch (...) {
			clear();
			throw;
		}
	}
	~ListD() {
		clear();
	}

    //--------------------------------- I T E R A T O R -----------------------------------

    class Iterator {
	private:
		Node* current;
		ListD* parent_list;

	public:
		Iterator(Node* node, ListD* parent) : current(node), parent_list(parent) {}

		friend class ListD;

		T& operator*() {
			if (!current) {
				throw std::runtime_error("Dereferencing null iterator");
			}
			return current->_data;
		}

		T* operator->() {
			if (!current) {
				throw std::runtime_error("Dereferencing null iterator");
			}
			return &(current->_data);
		}

		const T& operator*() const {
			if (!current) {
				throw std::runtime_error("Dereferencing null iterator");
			}
			return current->_data;
		}

		const T* operator->() const {
			if (!current) {
				throw std::runtime_error("Dereferencing null iterator");
			}
			return &(current->_data);
		}


		Iterator& operator++() {
			if (current) {
				current = current->_next;
			}
			return *this;
		}

		Iterator operator++(int) {
			Iterator tmp = *this;
			if (current) {
				++(*this);
			}
			return tmp;
		}

		Iterator& operator--() {
			if (!current) {
				current = parent_list->_tail;
			}
			else {
				current = current->_prev;
			}
			return *this;
		}

		Iterator operator--(int) {
			Iterator tmp = *this;
			--(*this); 
			return tmp;
		}

		Iterator& operator+=(size_t n) {
			while (n > 0) {
				if (!current) {
					break;
				}
				current = current->_next;
				--n;
			}
			return *this;
		}

		Iterator& operator-=(size_t n) {
			while (n > 0) {
				if (!current) {
					if (parent_list) {
						current = parent_list->_tail;
						--n;
						continue;
					}
					break;
				}
				current = current->_prev;
				--n;
			}
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


		bool operator==(const Iterator& other) const {
			return current == other.current;
		}

		bool operator!=(const Iterator& other) const {
			return !(current == other.current);
		}


		bool is_valid() const {
			return current != nullptr;
		}
		
    };

    //-------------------------------------------------------------------------------------


	T& front() {
		if (empty()) { throw std::out_of_range("ListD is empty"); }
		return _head->_data;
	}
	
	const T& front() const {
		if (empty()) { throw std::out_of_range("ListD is empty"); }
		return _head->_data;
	}

	T& back() {
		if (empty()) { throw std::out_of_range("ListD is empty"); }
		return _tail->_data;
	}

	const T& back() const {
		if (empty()) { throw std::out_of_range("ListD is empty"); }
		return _tail->_data;
	}

	//Adding elements:

	void push_back(const T& value) {
		if (empty()) {
			_head = new Node(value);
			_tail = _head;
		}
		else {
			_tail->_next = new Node(value,nullptr,_tail);
			_tail = _tail->_next;
		}
		++_size;
	}

	void push_back(T&& value) {
		if (empty()) {
			_head = new Node(std::move(value));
			_tail = _head;
		}
		else {
			_tail->_next = new Node(std::move(value), nullptr, _tail);
			_tail = _tail->_next;
		}
		++_size;
	}

	void push_front(const T& value) {
		if (empty()) {
			_head = new Node(value);
			_tail = _head;
		}
		else {
			_head->_prev = new Node(value, _head, nullptr);
			_head = _head->_prev;
		}
		++_size;
	}

	void push_front(T&& value) {
		if (empty()) {
			_head = new Node(std::move(value));
			_tail = _head;
		}
		else {
			_head->_prev = new Node(std::move(value), _head, nullptr);
			_head = _head->_prev;
		}
		++_size;
	}

	void insert(const Iterator& position,const T& value) {
		if (position == begin()) {
			push_front(value);
			return;
		}
		if (position == end()) {
			push_back(value);
			return;
		}

		Node* new_node = new Node(value, position.current, position.current->_prev);
		position.current->_prev->_next = new_node;
		position.current->_prev = new_node;
		++_size;
	}

	void insert(const Iterator& position,size_t n,const T& value) {
		if (n == 0) { return; }

		if (position == begin()) {
			while (n > 0) {
				push_front(value);
				--n;
			}
			_size += n;
			return;
		}
		if (position == end()) {
			while (n > 0) {
				push_back(value);
				--n;
			}
			_size += n;
			return;
		}
		Iterator cpy_position = position;
		_size += n;

		while (n > 0) {
			Node* new_node = new Node(value, cpy_position.current, cpy_position.current->_prev);
			cpy_position.current->_prev->_next = new_node;
			cpy_position.current->_prev = new_node;
			--cpy_position;
			--n;
		}
	}


	//Removing items:

	void pop_back() {
		if (empty()) {
			throw std::runtime_error("Remove item from empty list");
		}

		Node* remove_node = _tail;
		if (_size == 1) {
			_head = nullptr;
			_tail = nullptr;
		}
		else {
			_tail = _tail->_prev;
			_tail->_next = nullptr;
		}
		delete remove_node;
		--_size;
	}

	void pop_front() {
		if (empty()) {
			throw std::runtime_error("Remove item from empty list");
		}

		Node* remove_node = _head;
		if (_size == 1) {
			_head = nullptr;
			_tail = nullptr;
		}
		else {
			_head = _head->_next;
			_head->_prev = nullptr;
		}
		delete remove_node;
		--_size;
	}

	Iterator erase(const Iterator& position) {
		if (empty()) {
			throw std::runtime_error("Remove item from empty list");
		}

		if (position == begin()) {
			pop_front();
			return begin();
		}
		if (position == end()) {
			throw std::invalid_argument("Cannot erase element at end() iterator");
		}

		Node* remove_node = position.current;
		Node* next_node = position.current->_next;
		Node* prev_node = position.current->_prev;
		if(!next_node){
			pop_back();
			return Iterator(prev_node, this);
		}
		if(!prev_node){
			pop_front();
			return Iterator(next_node, this);
		}
		
		next_node->_prev = prev_node;
		prev_node->_next = next_node;
		delete remove_node;
		--_size;
		return Iterator(next_node, position.parent_list);
	}

	void erase(size_t position){
		if (empty()) {
			throw std::runtime_error("Remove item from empty list");
		}

		if(position >= _size){
			throw std::runtime_error("Out of bounds");
		}
		if(position == _size - 1){
			pop_back();
			return;
		}
		Node* remove_node = _head;
		for(size_t i = 0; i < position; ++i){
			if(remove_node->_next){
				remove_node = remove_node->_next;
			}
		}

		if(remove_node == nullptr){
			return;
		}

		Node* next_node = remove_node->_next;
		Node* prev_node = remove_node->_prev;
		if(!next_node){
			pop_back();
			return;
		}
		if(!prev_node){
			pop_front();
			return;
		}
		next_node->_prev = prev_node;
		prev_node->_next = next_node;
		delete remove_node;
		--_size;
	}

	void erase(const T& value){
		Node* remove_node = _head;
		for(size_t i = 0; i < _size; ++i){
			if(remove_node->_data == value){
				Node* next_node = remove_node->_next;
				Node* prev_node = remove_node->_prev;
				if(!next_node){
					pop_back();
					return;
				}
				if(!prev_node){
					pop_front();
					return;
				}
				next_node->_prev = prev_node;
				prev_node->_next = next_node;
				delete remove_node;
				--_size;
				return;
			}
			if(remove_node->_next != nullptr){
				remove_node = remove_node->_next;
			}
		}
	}

	void eraseAll(const T& value){
		Node* remove_node = _head;
		Node* next_node;
		Node* prev_node;
		for(size_t i = 0; i < _size; ++i){
			if(remove_node->_data == value){
				next_node = remove_node->_next;
				prev_node = remove_node->_prev;
				if(!next_node){
					pop_back();
					continue;
				}
				if(!prev_node){
					pop_front();
					continue;
				}
				next_node->_prev = prev_node;
				prev_node->_next = next_node;
				delete remove_node;
				--_size;
			}
			if(remove_node->_next != nullptr){
				remove_node = remove_node->_next;
			}
		}
	}

	void clear() {
		if (empty()) {
			return;
		}

		Node* current = _head;
		while (current != nullptr) {
			Node* next = current->_next;
			delete current;
			current = next;
		}

		_head = nullptr;
		_tail = nullptr;
		_size = 0;
	}


	//Finding and editing elements:

	Iterator begin() {
		return Iterator(_head,this);
	}

	Iterator end() {
		return Iterator(nullptr,this);
	}

	bool empty() const {
		return _size == 0;
	}

	size_t size() const {
		return _size;
	}


	//Other methods

	void unique() {
		if (empty()) {
			return;
		}

		Iterator _current = begin();
		while (_current != end()) {
			Iterator next = _current;
			++next;
			while (next != end()) {
				if (*_current == *next) {
					next = erase(next);
				}
				else {
					++next;
				}
			}
			++_current;
		}
	}

	void reverse() {
		if (empty()) {
			return;
		}

		Iterator position = begin();
		Iterator reverse_position = Iterator(_tail, this);
		size_t counter = 0;
		while (counter < _size / 2) {
			position.current->swap(*reverse_position.current);
			++position;
			--reverse_position;
			++counter;
		}
	}

	Iterator findIt(const T& value) {
		Iterator cur = begin();
		for(size_t i = 0; i < _size; ++i){
			if(cur.current->_data == value){
				return cur;
			}
			if(cur.current->_next != nullptr){
				++cur;
			}
		}
		return end();
	}

	size_t find(const T& value) const {
		Node* current = _head;
		for(size_t i = 0; i < _size; ++i){
			if(current->_data == value){
				return i;
			}
			if(current->_next != nullptr){
				current = current->_next;
			}
		}
		return static_cast<size_t>(-1);
	}

	//----------------------------------------- O P E R A T O R S ------------------------------------------------
	T& operator[](size_t n) {
		if (n >= _size) {
			throw std::runtime_error("Wrong index");
		}

		Node* current = _head;
		while (n > 0) {
			current = current->_next;
			--n;
		}
		return current->_data;
	}

	ListD& operator=(const ListD& other) {
		if (this != &other) {
			if (!empty()) {
				clear();
			}
			*this = ListD(other);
		}
		return *this;
	}

	ListD& operator=(ListD&& other) {
		if (this != &other) {
			if (!empty()) {
				clear();
			}
			_head = other._head;
			_tail = other._tail;
			_size = other._size;

			other._head = nullptr;
			other._tail = nullptr;
			other._size = 0;
		}
		return *this;
	}

};
