# MyContainers 🗃️

**MyContainers** is a collection of C++ data structure implementations designed for educational purposes.  
The project focuses on **code transparency**, **implementation details**, and **learning examples** to help developers understand the inner mechanics of popular containers.

---

## 🌟 Key Features

- **Simplicity and Readability**: Code is written with minimal optimizations to emphasize structural logic.
- **Comprehensive Documentation**: Each container includes comments explaining key algorithms.
- **Tests and Examples**: Ready-to-use examples and unit tests for correctness verification.
- **STL-like API**: Interfaces closely mimic the Standard Template Library for easy transition.

---

## 📦 Container List

| Container                | Description                                          | Status        |
|--------------------------|-----------------------------------------------------|---------------|
| **`Vector`**             | Dynamic array with automatic resizing               | ✅ Complete  |
| **`Array`**             | Array with specific size                            | ✅ Complete  |
| **`String`**             | `std::string`-like class with memory management     | ✅ Complete   |
| **`Stack`**              | LIFO stack                                          | ✅ Complete  |
| **`Deque`**              | Double-ended queue (deque)                          | ✅ Complete |
| **`Qeque`**              | FIFO data structure where elements are added to the rear and removed from the front. | ✅ Complete |
| **`List`**               | Doubly linked list                                   | ✅ Complete   |
| **`AVL Tree`**           | Self-balancing AVL Tree                             | ✅ Complete  |
| **`Unordered_map`**           |                             |   |

---

### Requirements
- C++17 compiler (GCC, Clang, MSVC)
- CMake build system (optional)

---

## Educational Approach

We implement **divergent memory management strategies** across containers to demonstrate different C++ techniques:

| Container | Memory Management Approach                          | Key Characteristics                             |
|-----------|----------------------------------------------------|------------------------------------------------|
| **`Stack`** | Low-level control:                                  | • Placement new for explicit construction<br>• Manual destructor calls<br>• Raw memory via `::operator new` |
| **`Vector`**  | Hybrid approach:                                    | • Default initialization + assignment<br>• Conditional destruction<br>• Optimized for trivial types |

### Why Different Approaches?
This intentional contrast helps students:
1. **Compare tradeoffs** between flexibility and simplicity
2. **Analyze constraints** of different implementation patterns
3. **Understand design decisions** behind standard library containers
4. **Appreciate why** there's no single "correct" solution in systems programming

### Key Learning Points:
- How object lifetime management affects container design
- Tradeoffs between type requirements and implementation complexity
- Performance implications for primitive vs. complex types
- Exception safety considerations in container development

---


## License
Distributed under the MIT License. See `LICENSE` for more information.  
**Created for educational purposes** •
