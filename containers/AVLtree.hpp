/*
*  AVLtree Documentation
*
*  The AVLtree class is a self-balancing binary search tree implementation (AVL Tree).
*  It maintains O(log n) time complexity for insertions, deletions, and lookups by ensuring
*  that the tree remains balanced using AVL rotations.
*
*  Key Features:
*    - Automatic balancing via single and double rotations (left/right)
*    - Support for insert, remove, and search operations
*    - Iterator with element access
*    - Height tracking and parent-pointer support for efficient upward traversal
*    - Full support for deep copy and move semantics
*    - Memory-safe node management using recursive destruction
*
*  Implementation Notes:
*    - Node structure includes parent pointer and subtree height
*    - Balancing is handled bottom-up after insertions and deletions
*    - Rotations correctly update all parent/child relationships and height
*    - Iterator supports basic arithmetic, dereferencing, and comparison
*    - Tree uses recursive functions for destruction and copying
*    - T must support default constructor, comparisons, and move semantics
*
*  Limitations:
*    - Iterators become invalid after structural modifications (insert/remove)
*    - Not thread-safe for concurrent modification or access
*    - No support for custom allocators or memory pooling
*    - There is no support for constant objects
*
*  Usage Recommendations:
*    - Suitable for ordered data where fast insertion/deletion and lookup is needed
*    - Avoid modifying the tree while iterating unless iterators are updated
*    - Ensure type T fulfills required operations (see template assumptions)
*/
#pragma once 
#include <stdexcept>

template<typename T, typename Compare = std::less<T>>
class AVLtree {
private:
	struct Node {
		T data;
		Node* left;
		Node* right;
		Node* parent;
		int height = 1;

		Node() : left(nullptr), right(nullptr), parent(nullptr), height(1) {}
		Node(const T& _data, Node* _left = nullptr, Node* _right = nullptr, Node* _parent = nullptr, int _height = 1) :
			data(_data), left(_left), right(_right), parent(_parent), height(_height) {}
		Node(const Node& node) :
			data(node.data), left(node.left), right(node.right), parent(node.parent), height(node.height) {}
		~Node() = default;

		//Calculates the balance factor of the current node, that is, the difference between the height of the right and left subtree.
		int balance() const {
			return ((right) ? right->height : 0) - ((left) ? left->height : 0);
		}

		//Updates the height field of the current node based on the heights of its children.
		void updateHeight() {
			height = std::max(((right) ? right->height : 0), ((left) ? left->height : 0)) + 1;
		}

		Node* minNode() {
			Node* current = this;
			while (current->left) {
				current = current->left;
			}
			return current;
		}

		Node* maxNode() {
			Node* current = this;
			while (current->right) {
				current = current->right;
			}
			return current;
		}

		bool isLeaf() const {
			return (!left) && (!right);
		}

		Node* next() const {
			if (right) {
				return right->minNode();
			}
			Node* current = this;
			Node* p = parent;
			while (p) {
				if (current == p->left) {
					break;
				}
				current = p;
				p = current->parent;
			}
			return p;
		}

	};

	Node* root = nullptr;
	size_t count = 0;
	Compare comp;

	//Rotation functions
	Node* rightRotate(Node* b) {
		if (!b || !b->left) { return b; }
		Node* a = b->left;
		Node* b_parent = b->parent;

		if (root == b) {
			root = a;
		}
		else {
			if (b == b_parent->left) {
				b_parent->left = a;
			}
			else {
				b_parent->right = a;
			}
		}

		b->parent = a;
		b->left = a->right;
		if (a->right) {
			a->right->parent = b;
		}
		a->right = b;
		a->parent = b_parent;
		b->updateHeight();
		a->updateHeight();
		return a;
	}
	Node* leftRotate(Node* b) {
		if (!b || !b->right) { return b; }
		Node* a = b->right;
		Node* b_parent = b->parent;

		if (root == b) {
			root = a;
		}
		else {
			if (b == b_parent->left) {
				b_parent->left = a;
			}
			else {
				b_parent->right = a;
			}
		}

		b->right = a->left;
		if (a->left) {
			a->left->parent = b;
		}
		a->left = b;
		b->parent = a;
		a->parent = b_parent;
		b->updateHeight();
		a->updateHeight();
		return a;
	}
	Node* doubleRightRotate(Node* b) {
		if (!b || !b->left || !b->left->right) {
			return b;
		}

		Node* a = b->left;
		Node* c = a->right;
		Node* b_parent = b->parent;

		if (root == b) {
			root = c;
		}
		else {
			if (b == b_parent->left) {
				b_parent->left = c;
			}
			else {
				b_parent->right = c;
			}
		}

		a->right = c->left;
		if (c->left) {
			c->left->parent = a;
		}
		b->left = c->right;
		if (c->right) {
			c->right->parent = b;
		}

		c->left = a;
		a->parent = c;
		c->right = b;
		b->parent = c;
		c->parent = b_parent;

		a->updateHeight();
		b->updateHeight();
		c->updateHeight();
		return c;
	}
	Node* doubleLeftRotate(Node* b) {
		if (!b || !b->right || !b->right->left) { return b; }

		Node* a = b->right;
		Node* c = a->left;
		Node* b_parent = b->parent;

		if (root == b) {
			root = c;
		}
		else {
			if (b == b_parent->left) {
				b_parent->left = c;
			}
			else {
				b_parent->right = c;
			}
		}

		a->left = c->right;
		if (c->right) {
			c->right->parent = a;
		}

		b->right = c->left;
		if (c->left) {
			c->left->parent = b;
		}

		c->left = b;
		c->right = a;
		c->parent = b_parent;
		a->parent = c;
		b->parent = c;

		a->updateHeight();
		b->updateHeight();
		c->updateHeight();
		return c;
	}

	//Function for copy constructor and copy =
	Node* copyThree(Node* node) {
		if (!node) {
			return nullptr;
		}
		Node* newNode = new Node(*node);
		newNode->left = copyThree(node->left);
		newNode->right = copyThree(node->right);
		return newNode;
	}
	
	//Function for balancing a tree
	void balancing(Node* current) {
		while (current) {
			current->updateHeight();
			if (current->balance() == -2) {
				if (current->left && current->left->balance() == 1) {
					current = doubleRightRotate(current);
				}
				else {
					current = rightRotate(current);
				}
			}
			else if (current->balance() == 2) {
				if (current->right && current->right->balance() == -1) {
					current = doubleLeftRotate(current);
				}
				else {
					current = leftRotate(current);
				}
			}
			current = current->parent;
		}
	}

	//The remove_uc (uncountable) function does not take count into account because additional recursion is called
	void remove_uc(Node* node) {
		if (!node) {
			return;
		}

		Node* node_parent = node->parent;
		if (!node->left && !node->right) {
			if (node->parent) {
				if (node->parent->right == node) {
					node->parent->right = nullptr;
				}
				else {
					node->parent->left = nullptr;
				}
			}
			else {
				root = nullptr;
			}
			delete node;
		}
		else if (node->left && node->right) {
			Node* min = findMin(node->right);
			node->data = min->data;
			remove_uc(min);
		}
		else {
			if (node->parent) {
				if (node->parent->right == node) {
					if (node->right) {
						node->right->parent = node->parent;
						node->parent->right = node->right;
					}
					else {
						node->left->parent = node->parent;
						node->parent->right = node->left;
					}
				}
				else {
					if (node->right) {
						node->right->parent = node->parent;
						node->parent->left = node->right;
					}
					else {
						node->left->parent = node->parent;
						node->parent->left = node->left;
					}
				}
			}
			else
			{
				if (node->right) {
					root = node->right;
					node->right->parent = nullptr;
				}
				else {
					root = node->left;
					node->left->parent = nullptr;
				}
			}
			delete node;
		}

		if (!node_parent) {
			balancing(root);
		}
		else {
			balancing(node_parent);
		}
	}

	//Function for destructor
	void clear(Node* node) {
		if (!node) { return; }
		clear(node->left);
		clear(node->right);
		node->left = nullptr;
		node->right = nullptr;
		delete node;
	}

public:
	//Constructor and destructor
	AVLtree() : root(nullptr), count(0) {}
	AVLtree(size_t _count, const T& value) {
		while (count < _count) {
			insert(value);
		}
	}
	AVLtree(size_t count) : AVLtree(count, T()) {}
	AVLtree(const AVLtree& other) {
		root = copyThree(other.root);
		count = other.count;
	}
	AVLtree(AVLtree&& other) {
		root = other.root;
		count = other.count;
		other.root = nullptr;
		other.count = 0;
	}
	~AVLtree() {
		clear();
	}

	//--------------------------------- I T E R A T O R -----------------------------------
	class Iterator {
	private:
		Node* current;
		AVLtree* parent_three;

	public:
		Iterator() = delete;
		Iterator(Node* _current, AVLtree* _parent_three) : current(_current), parent_three(_parent_three) {}
		Iterator(const Iterator& other) : current(other.current), parent_three(other.parent_three) {}

		void is_valid() {
			if (!current) {
				throw std::runtime_error("Iterator equal nullptr");
			}
		}

		T& operator*() {
			is_valid();
			return (current->data);
		}

		T* operator->() {
			is_valid();
			return &(current->data);
		}

		const T& operator*() const {
			is_valid();
			return (current->data);
		}

		const T* operator->() const {
			is_valid();
			return &(current->data);
		}


		// Increment/Decrement ------------------------------------------------
		Iterator& operator++() {
			is_valid();
			if (current->right) {
				current = current->right;
				while (current->left) {
					current = current->left;
				}
			}
			else {
				Node* prev;
				do {
					prev = current;
					current = current->parent;
				} while (current && prev != current->left);
			}
			return *this;
		}

		Iterator operator++(int) {
			Iterator tmp(*this);
			++(*this);
			return tmp;
		}

		Iterator& operator--() {
			is_valid();
			if (current->left) {
				current = current->left;
				while (current->right) {
					current = current->right;
				}
			}
			else {
				Node* prev;
				do {
					prev = current;
					current = current->parent;
				} while (current && prev != current->right);
			}
			return *this;
		}

		Iterator operator--(int) {
			Iterator tmp(*this);
			--(*this);
			return tmp;
		}


		// Arithmetic operations --------------------------------------------
		Iterator& operator+=(size_t n) {
			for (size_t i = 0; i < n; ++i) {
				++(*this);
			}
		}

		Iterator& operator-=(size_t n) {
			for (size_t i = 0; i < n; ++i) {
				--(*this);
			}
		}

		Iterator operator+(size_t n) const {
			Iterator tmp(*this);
			tmp += n;
			return tmp;
		}

		Iterator operator-(size_t n) const {
			Iterator tmp(*this);
			tmp -= n;
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

	void remove(Node* node) {
		remove_uc(node);
		--count;
	}

	void insert(const T& value) {
		if (!root) {
			root = new Node(value);
			++count;
			return;
		}

		Node* current = root;
		while (current) {
			if (!comp(value , current->data)) {
				if (!current->right) { 
					current->right = new Node(value, nullptr, nullptr, current);
					current = current->right;
					break;
				}
				current = current->right;
			}
			else {
				if (!current->left) { 
					current->left = new Node(value,nullptr,nullptr,current);
					current = current->left;
					break; 
				}
				current = current->left;
			}
		}
		++count;
		balancing(current);
	}

	bool contains(const T& value) const {
		Node* current = root;
		while (current) {
			if (!comp(value, current->data) && !comp(current->data, value)) {
				return true;
			}
			if (comp(current->data, value)) {
				if (!current->right) {
					return false;
				}
				current = current->right;
			}
			else {
				if (!current->left) {
					return false;
				}
				current = current->left;
			}
		}
		return false;
	}

	Node* find(const T& value) const {
		Node* current = root;
		while (current) {
			if (comp(value, current->data)) {
				current = current->left;
			}
			else if (comp(current->data, value)) {
				current = current->right;
			}
			else {
				return current;
			}
		}
		return nullptr;
	}

	Node* findMin(Node* node) const {
		if (!node->left) {
			return node;
		}
		Node* current = node;
		while (current->left) {
			current = current->left;
		}
		return current;
	}

	Node* findMax(Node* node) const {
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

	size_t height(Node* node) const {
		if (!node) {
			return 0;
		}

		return std::max(height(node->left), height(node->right)) + 1;
	}

	Iterator begin() {
		if (!root) {
			return end();
		}
		return Iterator(root->minNode(), this);
	}

	Iterator end() {
		return Iterator(nullptr, this);
	}

	const Iterator begin() const {
		if (!root) {
			return end();
		}
		return Iterator(root->minNode(), this);
	}

	const Iterator end() const {
		return Iterator(nullptr, this);
	}

	//getter
	Node* get_root() const {
		return root;
	}

	//--------------------------------- O P E A T O R S -------------------------------------

	AVLtree& operator=(const AVLtree& other) {
		clear();
		root = copyThree(other.root);
		count = other.count;
	}

	AVLtree& operator=(AVLtree&& other) {
		clear();
		root = other.root;
		count = other.count;
		other.root = nullptr;
		other.count = 0;
	}

};


