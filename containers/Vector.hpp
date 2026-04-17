/*
*  Vector Documentation
*
*  The Vector class is a dynamic array implementation with automatic resizing.
*  Supports bounds-checked iterators and basic STL-like container operations.
*
*  Key Features:
*    - Dynamic memory expansion/shrinking.
*    - Bounds checking for element access
*    - Support for random-access iterators.
*    - Capacity and size management.
*
*  Notes:
*    - Iterators throw std::out_of_range on out-of-bounds access.
*    - Existing iterators are invalidated when capacity changes.
*    - Not thread-safe.
*/

/*
*  type T must have :
*   - copy constructor
*   - operator = (copy)
*   - move semantic
*/
#pragma once
#include <stdexcept>
#include <type_traits>
#include <initializer_list>
#include <cstddef>


template <typename T>
class Vector {
private:
    size_t _capacity;
    size_t _size;
    T* _data;

    static constexpr bool is_trivial_T = std::is_trivially_destructible_v<T>;

public:
    //Constructor and destructor
    Vector() : _capacity(10), _size(0) {
        _data = new T[_capacity];
    }

    Vector(const Vector<T>& vec) : _size(vec._size), _capacity(vec._capacity) {
        _data = new T[_capacity];
        for (size_t i = 0; i < _size; ++i) {
            _data[i] = vec._data[i];
        }
    }

    Vector(Vector<T>&& vec) noexcept
        : _data(vec._data), _capacity(vec._capacity), _size(vec._size) {
        vec._data = nullptr;
        vec._capacity = 0;
        vec._size = 0;
    }

    Vector(std::initializer_list<T> init)
        : _size(init.size()),
        _capacity(init.size() > 10 ? init.size() * 2: 10),
        _data(new T[_capacity])
    {
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

    ~Vector() {
        delete[] _data; 
    }

    //--------------------------------- I T E R A T O R -----------------------------------
    class Iterator {
    private:
        Vector<T>& _container;  // Reference to the parent container
        T* _ptr;                // Current position pointer

        // Check for out-of-bounds access
        void _check_bounds(size_t pos) const {
            if (pos >= _container._size) {
                throw std::out_of_range("Iterator out of bounds");
            }
        }

    public:
        // Types for STL compatibility
        using iterator_category = std::random_access_iterator_tag;
        using value_type = T;
        //difference_type is a safe and generic way to work with distances between iterators,
        //supporting all possible scenarios, including negative values.
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        Iterator(Vector<T>& container, T* ptr)
            : _container(container), _ptr(ptr) {}

        ~Iterator() = default;

        // Basic operations ---------------------------------------------------
        reference operator*() const {
            _check_bounds(_ptr - _container._data);  // _container._data points to the start of the array
            return *_ptr;
        }

        // Increment/Decrement ------------------------------------------------
        Iterator& operator++() {
            //If iterator points to the last element(end() - 1), after increment it will become end() - this is valid
            //If iterator is already end(), increment is invalid - check must be before change
            _check_bounds(_ptr - _container._data);
            ++_ptr;
            return *this;
        }

        Iterator operator++(int) {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        Iterator& operator--() {
            //If iterator is end(), decrement will move it to the last element - this is valid
            //If iterator is begin(), decrement is invalid - check before change
            _check_bounds(_ptr - _container._data);
            --_ptr;
            return *this;
        }

        Iterator operator--(int) {
            Iterator tmp = *this;
            --(*this);
            return tmp;
        }

        // Arithmetic operations --------------------------------------------
        Iterator operator+(difference_type n) const {
            Iterator tmp = *this;
            tmp += n;
            return tmp;
        }

        Iterator operator-(difference_type n) const {
            Iterator tmp = *this;
            tmp -= n;
            return tmp;
        }

        difference_type operator-(const Iterator& other) const {
            return _ptr - other._ptr;
        }

        Iterator& operator+=(difference_type n) {
            _ptr += n;
            _check_bounds(_ptr - _container._data);
            return *this;
        }

        Iterator& operator-=(difference_type n) {
            _ptr -= n;
            _check_bounds(_ptr - _container._data);
            return *this;
        }

        // Comparison ---------------------------------------------------------
        bool operator==(const Iterator& other) const {
            return _ptr == other._ptr;
        }

        bool operator!=(const Iterator& other) const {
            return !(*this == other);
        }

        bool operator<(const Iterator& other) const {
            return _ptr < other._ptr;
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

    const T& at(size_t index) const {
        if (index >= _size) { throw std::out_of_range("Index out of range"); }
        return _data[index];
    }

    const T& back() const {
        if (empty()) { throw std::out_of_range("Vector is empty"); }
        return _data[_size - 1];
    }

    Iterator begin() {
        return Iterator(*this, _data);
    }

    size_t capacity() const {
        return _capacity;
    }

    void clear() {
        if (!is_trivial_T) { //if T not trivial
            for (size_t i = 0; i < _size;++i) {
                _data[i].~T();
            }
        }
        _size = 0;
    }

    T* data() {
        return _data;
    }

    const T* data() const {
        return _data;
    }

    void emplace_back(const T& element) {
        if (_size + 1 > _capacity) {
            reserve(_capacity == 0 ? 10 : _capacity * 2);
        }

        _data[_size] = element;
        ++_size;
    }

    bool empty() const {
        return _size == 0;
    }

    Iterator end() {
        return Iterator(*this, _data + _size);
    }

    void erase(const Iterator& first,const Iterator& last) {
        if (first < begin() || first >= end() || first > last) { //end points out of bounds array
            throw std::out_of_range("Iterator out of bounds");
        }

        if constexpr (!is_trivial_T) {
            for (auto it = first; it != last; ++it) {
                it.~T();
            }
        }

        size_t difference = last - first;
        for (auto it = last; it != end(); ++it) {
            *(it - difference) =  std::move(*it);
        }

        _size -= difference;
    }

    void erase(const Iterator& position) {
        if (position < begin() || position >= end()) {
            throw std::out_of_range("Iterator out of bounds");
        }

        size_t index = position - begin();

        //delete current object
        if (!is_trivial_T) {
            _data[index].~T();
        }

        for (size_t i = index; i < _size - 1; ++i) {
            _data[i] = std::move(_data[i + 1]);
        }
        --_size;
    }

    T& front() {
        if (empty()) { throw std::out_of_range("Vector is empty"); }
        return _data[0];
    }

    const T& front() const {
        if (empty()) { throw std::out_of_range("Vector is empty"); }
        return _data[0];
    }

    void insert(const T& element, const Iterator position) {
        if (position < begin() || position > end()) {
            throw std::out_of_range("Iterator out of bounds");
        }

        if (_size + 1 >= _capacity) {
            reserve(_size == 0 ? 10: _capacity * 2);
        }

        size_t pos_index = position - begin();
        for (size_t i = _size; i > pos_index; --i) {
            _data[i] = std::move(_data[i - 1]);
        }

        _data[pos_index] = element;
        ++_size;
    }

    void pop_back() {
        if (!empty()) {
            if (!is_trivial_T) {
                _data[_size - 1].~T();
            }
            --_size;
        }
    }

    void push_back(const T& element) {
        emplace_back(element);
    }

    void reserve(size_t new_capacity) {
        if (new_capacity <= _capacity) { return; }

        T* new_data = new T[new_capacity];

        for (size_t i = 0; i < _size; ++i) {
            new_data[i] = std::move(_data[i]);
        }

        delete[] _data;
        _data = new_data;
        _capacity = new_capacity;
    }

    void resize(size_t new_size, const T& default_value = T()) {
        if (new_size < _size) {
            if (!is_trivial_T) {
                for (size_t i = new_size; i < _size; ++i) {
                    _data[i].~T();
                }
            }
            _size = new_size;
            return;
        }

        if (new_size > _capacity) {
            reserve(new_size + 1);
        }
        for (size_t i = _size; i < new_size; ++i) {
            _data[i] = default_value;
        }
        _size = new_size;
    }

    void shrink_to_fit() {
        if (_capacity == _size) { return; }

        T* new_data = new T[_size];
        for (size_t i = 0; i < _size; ++i) {
            new_data[i] = std::move(_data[i]);
        }

        delete[] _data;
        _data = new_data;
        _capacity = _size;
    }

    size_t size() const {
        return _size;
    }

    void swap(Vector& other) noexcept {
        std::swap(_data, other._data);
        std::swap(_size, other._size);
        std::swap(_capacity, other._capacity);
    }

    //------------------------------- O P E R A T O R S -------------------------------------------------

    const T& operator[](size_t index) const {
        if (index >= _size) {
            throw std::out_of_range("Index out of bounds");
        }
        return _data[index];
    }

    T& operator[](size_t index) {
        if (index >= _size) {
            throw std::out_of_range("Index out of bounds");
        }
        return _data[index];
    }

    Vector& operator=(const Vector& other) {
        if (this != &other) {
            Vector temp(other);
            swap(temp);
        }
        return *this;
    }

    Vector& operator=(Vector&& right) {
        if (this != &right) {
            delete[] _data;

            _data = right._data;
            _size = right._size;
            _capacity = right._capacity;

            right._data = nullptr;
            right._size = 0;
            right._capacity = 0;
        }

        return *this;
    }

};
