
#pragma once 
#include <cstddef>
#include <stdexcept>
#include "../Stack/Stack.hpp"

template<typename T>
class AAtree{
private:
    struct Node{
        T value;
        int level;
        Node* left;
        Node* right;

        Node() : level(1), left(nullptr), right(nullptr) {}
        Node(const T& _value, Node* _left = nullptr, Node* _right = nullptr) :
			value(_value), left(_left), right(_right), level(1) {}
        Node(const Node& node) :
			value(node.value), left(node.left), right(node.right), level(node.level) {}
		~Node() = default;

        bool isLeaf() const {
			return (!left) && (!right);
		}


    };

    Node* root = nullptr;
	size_t count = 0;

    // Eliminating a left link at one level
    Node* skew(Node* node){
        if(!node || !node->left) { return node; }

        if(node->left->level == node->level){
            Node* left = node->left;

            node->left = left->right;
            left->right = node;
            return left;
        }
        return node;
    }
    // Elimination of two right connections at the same level
    Node* split(Node* node){
        if(!node || !node->right || !node->right->right) { return node; }

        if(node->right->right->level == node->level){
            Node* right = node->right;

            node->right = right->left;
            right->left = node;
            ++right->level;
            return right;
        }

        return node;
    }

    Node* insert(Node* node, const T& value) {
        if (!node) {
            ++count;
            return new Node(value, nullptr, nullptr);
        }
    
        if (value < node->value) {
            node->left = insert(node->left, value);
        } 
        else if (value > node->value) {
            node->right = insert(node->right, value);
        } 
        else {
            return node; // no duplicates (set behavior)
        }
    
        node = skew(node);
        node = split(node);
    
        return node;
    }

    Node* erase(Node* node, const T& value){
        if(!node){ return nullptr; }
        
        if(value > node->value){
            node->right = erase(node->right, value);
        }else if(value < node->value){
            node->left = erase(node->left, value);
        }else{
            // Found node
            if(!node->left || !node->right){
                Node* child = node->left ? node->left : node->right;
                delete node;
                --count;
                return child;
            }else{
                // Replace with successor
                Node* successor = findMin(node->right);
                node->value = successor->value;
                node->right = erase(node->right, successor->value);
            }
        }

        // Rebalance
        int leftLevel = node->left ? node->left->level : 0;
        int rightLevel = node->right ? node->right->level : 0;
        
        int expectedLevel = std::min(leftLevel, rightLevel) + 1;
        if (expectedLevel < node->level) {
            node->level = expectedLevel;
        
            if (node->right && node->right->level > node->level) {
                node->right->level = node->level;
            }
        }
        
        node = skew(node);
        if (node->right) {
            node->right = skew(node->right);
        }
        if (node->right && node->right->right) {
            node->right->right = skew(node->right->right);
        }
        
        node = split(node);
        if (node->right) {
            node->right = split(node->right);
        }

        return node;

    }

    Node* copyTree(Node* node){
        if(!node){
            return nullptr;
        }
        Node* new_node = new Node(*node);
        new_node->left = copyTree(node->left);
        new_node->right = copyTree(node->right);
        return new_node;
    }

    void clear(Node* node){
        if(!node){ return; }
        clear(node->left);
        clear(node->right);
        node->left = nullptr;
        node->right = nullptr;
        delete node;
    }

public:
    //Constructor and destructor
    AAtree();
    AAtree(size_t _count, const T& value);
    AAtree(size_t count);
    AAtree(const AAtree& other);
    AAtree(AAtree&& other);
    ~AAtree(){
        clear(root);
    }

    //--------------------------------- I T E R A T O R -----------------------------------
    class Iterator {
        private:
                Node* current;
                AAtree* parent_tree;
                Stack<Node*> stack;

                void pushLeft(Node* node) {
                    Node* left = node;
                    while (left) {
                        stack.push(left);
                        left = left->left;
                    }
                }

        public:
                Iterator() : current(nullptr), parent_tree(nullptr) {} 
                Iterator(AAtree* _parent_tree) : parent_tree(_parent_tree) {
                    if (parent_tree && parent_tree->root) {
                        pushLeft(parent_tree->root);
                        current = stack.top();
                        stack.pop();
                    }else{
                        current = nullptr;
                    }
                }
                Iterator(const Iterator& other) : current(other.current), parent_tree(other.parent_tree), stack(other.stack) {}
        
                void is_valid() const {
                    if (!current) {
                        throw std::runtime_error("Iterator equal nullptr");
                    }
                }
        
                T& operator*() {
                    is_valid();
                    return (current->value);
                }
        
                T* operator->() {
                    is_valid();
                    return &(current->value);
                }
        
                const T& operator*() const {
                    is_valid();
                    return (current->value);
                }
        
                const T* operator->() const {
                    is_valid();
                    return &(current->value);
                }
        
        
                // Increment/Decrement ------------------------------------------------
                Iterator& operator++() {
                    if (stack.empty()) {
                        current = nullptr;
                        return *this;
                    }
            
                    Node* node = stack.top();
                    stack.pop();

                    if (node->right) {
                        pushLeft(node->right);
                    }
            
                    current = stack.empty() ? nullptr : stack.top();
                    return *this;
                }
        
                Iterator operator++(int) {
                    Iterator tmp(*this);
                    ++(*this);
                    return tmp;
                }
        
                // Arithmetic operations --------------------------------------------
                Iterator& operator+=(size_t n) {
                    for (size_t i = 0; i < n; ++i) {
                        ++(*this);
                    }
                    return *this;
                }
        
                Iterator operator+(size_t n) const {
                    Iterator tmp(*this);
                    tmp += n;
                    return tmp;
                }
        
                // Comparison ---------------------------------------------------------
                bool operator==(const Iterator& other) const {
                    return current == other.current;
                }
        
                bool operator!=(const Iterator& other) const {
                    return !(current == other.current);
                }
        
    };
        //-------------------------------------------------------------------------------------

    void insert(const T& value) {
        root = insert(root, value); 
    }

    void erase(const T& value) {
        root = erase(root, value);
    }

	bool contains(const T& value) const{
        return !(find(value) == nullptr);
    }

    Node* find(const T& value) const {
        Node* node = root;
    
        while (node) {
            if (value < node->value){
                node = node->left;
            }
            else if (value > node->value){
                node = node->right;
            }
            else{
                return node;
            }
        }
    
        return nullptr;
    }
    
	Node* findMin(Node* node) const{
        if (!node){ return nullptr; }
		if (!node->left) {
			return node;
		}
		Node* current = node;
		while (current->left) {
			current = current->left;
		}
		return current;
    }

	Node* findMax(Node* node) const{
        if (!node){ return nullptr; }
        if (!node->right) {
			return node;
		}
		Node* current = node;
		while (current->right) {
			current = current->right;
		}
		return current;
    }

	void clear() {
		clear(root);
		root = nullptr;
		count = 0;
	}

	bool empty() const {
		return count == 0;
	}

	size_t size() const {
		return count;
	}

    size_t level(Node* node) const {
        return node ? node->level : 0;
    }

	Iterator begin(){
        return Iterator(this);
    }

	Iterator end(){
        return Iterator();
    }

	Node* get_root() const {
		return root;
	}

	//--------------------------------- O P E A T O R S -------------------------------------
	AAtree& operator=(const AAtree& other){
        if (this != &other) {
            clear();
            root = copyTree(other.get_root());
            count = other.size();
        }
        return *this;
    }
	AAtree& operator=(AAtree&& other){
        if (this != &other) {
			clear();
			root = other.root;
			count = other.count;
			other.root = nullptr;
			other.count = 0;
		}
		return *this;
    }

};