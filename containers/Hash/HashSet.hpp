/*
 * HashSet
 *
 * Hash-based set that stores unique elements using separate chaining.
 * Each bucket contains a linked list of elements with the same hash index.
 *
 * Time complexity:
 *   Insert:   O(1) average, O(n) worst
 *   Remove:   O(1) average, O(n) worst
 *   Contains: O(1) average, O(n) worst
 *   Rehash:   O(n)
 *
 * Key properties:
 *   - Stores unique elements
 *   - Separate chaining for collision handling
 *   - Automatic rehashing when the load factor exceeds 0.75
 */
#include <functional>
#include "../List/ListD.hpp"

template<typename T>
class HashSet{
private:
    ListD<T>* data;    
    size_t bucket_count;
    size_t element_count;

    void rehash(){
        size_t new_bucket_count = bucket_count * 2;
        ListD<T>* new_data = new ListD<T>[new_bucket_count];

        size_t new_index;
        for(size_t i = 0; i < bucket_count; ++i){
            for(size_t j = 0; j < data[i].size(); ++j){
                const T& value = data[i][j];

                new_index = std::hash<T>{}(value) % new_bucket_count;
                new_data[new_index].push_back(value);
            }
        }
        delete[] data;
        data = new_data;
        bucket_count = new_bucket_count;
    }

    size_t hash(const T& value) const {
        if(bucket_count == 0){
            return static_cast<size_t>(0);
        }
        return std::hash<T>{}(value) % bucket_count;
    }
public:
    // Constructors
    HashSet() : bucket_count(8), element_count(0) {
        data = new ListD<T>[bucket_count];
    }
    HashSet(size_t size) : data(new ListD<T>[size]), bucket_count((size == 0) ? 1 : size), element_count(0) {}
    HashSet(const HashSet<T>& other){
        bucket_count = other.bucket_count;
        element_count = other.element_count;
        data = new ListD<T>[bucket_count];
        for(size_t i = 0; i < bucket_count; ++i){
            data[i] = other.data[i];
        }
    }
    HashSet(HashSet<T>&& other) noexcept {
        data = other.data;
        bucket_count = other.bucket_count;
        element_count = other.element_count;
        other.data = nullptr;
        other.bucket_count = 0;
        other.element_count = 0;
    }
    ~HashSet(){
        clear();
        delete[] data;
    }

    // Main functions
    bool insert(const T& value){
        size_t idx = hash(value);
        if(data[idx].find(value) == static_cast<size_t>(-1)){
            data[idx].push_back(value);
            ++element_count;

            if (static_cast<double>(element_count) / bucket_count > 0.75) {
                rehash();
            }
            return true;
        }
        return false;
    }
    bool remove(const T& value){
        size_t idx = hash(value);
        size_t pos = data[idx].find(value);

        if(pos != static_cast<size_t>(-1)){
            data[idx].erase(pos);
            --element_count;
            return true;
        }
        return false;
    }
    void clear(){
        for(size_t i = 0; i < bucket_count; ++i){
            data[i].clear();
        }
        element_count = 0;
    }
    bool contains(const T& value) const {
        return data[hash(value)].find(value) != static_cast<size_t>(-1);
    }
    size_t get_bucket_count() const {
        return bucket_count;
    }
    size_t get_element_count() const {
        return element_count;
    }
    bool empty() const {
        return element_count == 0;
    }


    // ----------------------- O P E R A T O R S ------------------------------

    HashSet& operator=(const HashSet<T>& other){
        if(this != &other){
            clear();
            delete[] data;
            bucket_count = other.bucket_count;
            element_count = other.element_count;
            data = new ListD<T>[bucket_count];
            for(size_t i = 0; i < bucket_count; ++i){
                data[i] = other.data[i];
            }
        }
        return *this;
    }
    HashSet& operator=(HashSet<T>&& other) noexcept {
        if(this != &other){
            clear();
            delete[] data;
            data = other.data;
            bucket_count = other.bucket_count;
            element_count = other.element_count;
            other.data = nullptr;
            other.bucket_count = 0;
            other.element_count = 0;
        }
        return *this;
    }
};
