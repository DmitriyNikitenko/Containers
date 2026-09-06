#pragma once
#include <cmath>
#include <limits>
#include <stdexcept>
#include "../Vector/Vector.hpp"

template <typename T>
class FibHeap {
 private:
  struct Node {
    Node* parent;
    Node* child;
    Node* left;
    Node* right;
    size_t degree;
    bool mark;
    T value;

    Node()
        : parent(nullptr),
          child(nullptr),
          left(this),
          right(this),
          degree(0),
          mark(false),
          value() {}
    Node(const T& _value)
        : parent(nullptr),
          child(nullptr),
          left(this),
          right(this),
          degree(0),
          mark(false),
          value(_value) {}
    void setValue(const T& _value) { value = _value; }
  };

  Node* min;
  size_t size;

  Node* findByValueFromNode(Node* node, const T& value) {
    if (node == nullptr) {
      return nullptr;
    }
    Node* tmp = node;
    Node* loc_res = nullptr;
    do {
      if (tmp->value == value) {
        return tmp;
      }
      loc_res = findByValueFromNode(tmp->child, value);
      if (loc_res != nullptr) {
        return loc_res;
      }
      tmp = tmp->right;
    } while (tmp != node);
    return loc_res;
  }

  void clear(Node* node) {
    if (node != nullptr) {
      Node* start = node;
      Node* next;
      do {
        next = node->right;
        clear(node->child);
        delete node;
        node = next;
      } while (node != start);
    }
  }

  void consolidate() {
    if (min == nullptr || size < 2) {
      return;
    }

    Vector<Node*> roots;
    roots.reserve(size);

    Node* node = min;
    do {
      roots.push_back(node);
      node = node->right;
    } while (node != min);

    Vector<Node*> arr;
    arr.resize(roots.size() + 2, nullptr);

    for (size_t i = 0; i < roots.size(); ++i) {
      node = roots[i];

      if (node->parent != nullptr) {
        continue;
      }

      while (true) {
        if (node->degree >= arr.size()) {
          arr.resize(node->degree + 1, nullptr);
        }

        if (arr[node->degree] == nullptr) {
          arr[node->degree] = node;
          break;
        }

        Node* other = arr[node->degree];
        arr[node->degree] = nullptr;

        if (other->value < node->value) {
          Node* tmp = node;
          node = other;
          other = tmp;
        }

        other->left->right = other->right;
        other->right->left = other->left;

        other->parent = node;
        other->mark = false;

        if (node->child == nullptr) {
          node->child = other;
          other->left = other;
          other->right = other;
        } else {
          Node* child = node->child;
          Node* child_left = child->left;

          other->right = child;
          other->left = child_left;
          child_left->right = other;
          child->left = other;
        }

        ++node->degree;
      }
    }

    min = nullptr;

    for (size_t i = 0; i < arr.size(); ++i) {
      Node* x = arr[i];
      if (x == nullptr || x->parent != nullptr) {
        continue;
      }

      x->left = x;
      x->right = x;

      if (min == nullptr) {
        min = x;
      } else {
        Node* min_left = min->left;

        x->right = min;
        x->left = min_left;
        min_left->right = x;
        min->left = x;

        if (x->value < min->value) {
          min = x;
        }
      }
    }
  }

  void cut(Node* x, Node* y) {
    if (x != nullptr && y != nullptr && x->parent == y) {
      if (y->child == x) {
        if (x->right == x) {
          y->child = nullptr;
        } else {
          y->child = x->right;
        }
      }

      x->left->right = x->right;
      x->right->left = x->left;

      Node* min_left = min->left;
      x->right = min;
      min->left = x;

      min_left->right = x;
      x->left = min_left;

      x->parent = nullptr;
      x->mark = false;
      --y->degree;
    }
  }

  void cascading_cut(Node* y) {
    Node* par = y->parent;

    if (par == nullptr) {
      return;
    }

    if (!static_cast<bool>(y->mark)) {
      y->mark = true;
    } else {
      cut(y, par);
      cascading_cut(par);
    }
  }

 public:
  using Pointer = Node*;

  FibHeap() : min(nullptr), size(0) {}
  FibHeap(const FibHeap&) = delete;
  FibHeap(FibHeap&& other) noexcept {
    min = other.min;
    size = other.size;
    other.min = nullptr;
    other.size = 0;
  }
  ~FibHeap() { clear(); }

  bool empty() const { return size == 0; }
  size_t get_size() const { return size; }
  const T& minimum() const {
    if (size == 0) {
      throw std::runtime_error("The heap is empty");
    }
    return min->value;
  }
  Node* insert(const T& value) {
    Node* node = new Node(value);
    if (size == 0) {
      min = node;
      ++size;
      return node;
    }

    Node* tmp = min->left;
    min->left = node;
    node->right = min;
    node->left = tmp;
    tmp->right = node;

    if (value < min->value) {
      min = node;
    }
    ++size;
    return node;
  }
  Node* findNodeByValue(const T& value) {
    if (min == nullptr) {
      return nullptr;
    }
    return findByValueFromNode(min, value);
  }
  void union_with(FibHeap<T>&& other) {
    if (other.size == 0) {
      return;
    }
    if (size == 0) {
      min = other.min;
      size = other.size;
      other.min = nullptr;
      other.size = 0;
      return;
    }

    Node* this_left_tmp = min->left;
    Node* other_left_tmp = other.min->left;

    this_left_tmp->right = other.min;
    other.min->left = this_left_tmp;

    other_left_tmp->right = min;
    min->left = other_left_tmp;

    min = (min->value > other.min->value) ? other.min : min;
    size += other.size;
    other.min = nullptr;
    other.size = 0;
  }
  T extract_min() {
    if (size == 0) {
      return std::numeric_limits<T>::max();
    }

    Node* z = min;
    T res = z->value;

    if (size == 1) {
      delete z;
      min = nullptr;
      size = 0;
      return res;
    }

    if (z->child != nullptr) {
      Node* child = z->child;

      Node* tmp = child;

      do {
        tmp->parent = nullptr;
        tmp = tmp->right;
      } while (tmp != child);

      Node* min_left = min->left;
      Node* child_left = child->left;

      min_left->right = child;
      child->left = min_left;

      child_left->right = min;
      min->left = child_left;
    }

    z->left->right = z->right;
    z->right->left = z->left;

    min = z->right;

    delete z;
    --size;
    consolidate();
    return res;
  }
  void decrease_key(Node* x, const T& new_key) {
    if (x == nullptr) {
      throw std::runtime_error("Null node");
    }
    if (new_key > x->value) {
      throw std::runtime_error("The new key is bigger than the old one.");
    }

    x->value = new_key;
    Node* par = x->parent;

    if (par != nullptr && x->value < par->value) {
      cut(x, par);
      cascading_cut(par);
    }

    if (min == nullptr || x->value < min->value) {
      min = x;
    }
  }
  void delete_node(Node* x) {
    decrease_key(x, std::numeric_limits<T>::lowest());
    extract_min();
  }
  void clear() {
    clear(min);
    min = nullptr;
    size = 0;
  }

  FibHeap& operator=(const FibHeap&) = delete;
  FibHeap& operator=(FibHeap&& other) noexcept {
    if (this != &other) {
      clear();
      min = other.min;
      size = other.size;
      other.min = nullptr;
      other.size = 0;
    }
    return *this;
  }
};