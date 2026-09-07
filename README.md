# MyContainers and algorithms for working with them

**MyContainers** is a collection of C++ data structure implementations designed for educational purposes.  

---

## Key Features

- **Comprehensive Documentation**: Each container includes comments explaining key algorithms.
- **Tests and Examples**: Ready-to-use examples and unit tests for correctness verification.


---


## Project Structure

```text
Containers/

├── algorithms/
│   └─ sorting/                  # Sorting algorithm implementations
│      ├─ bubbleSort.hpp         # Bubble sort
│      ├─ gnomeSort.hpp          # Gnome sort
│      ├─ mergeSort.hpp          # Merge sort
│      ├─ quickSort.hpp          # Quick sort
│      ├─ selectionSort.hpp      # Selection sort
│      └─ shakerSort.hpp         # Shaker (cocktail) sort
│
├── containers/
│   ├── Hash/
│   │    └─ HashSet.hpp           # Hash table based set
│   │
│   ├── List/
│   │    └─ ListD.hpp             # Doubly linked list
│   │
│   ├── Queue/
│   │    ├─ QueueCircBuf.hpp      # Queue based on a circular buffer
│   │    ├─ QueueOn2Stack.hpp     # Queue implemented using two stacks
│   │    └─ QueueOnList.hpp       # Queue implemented using a linked list
│   │
│   ├── Stack/
│   │    └─ Stack.hpp
│   │
│   ├── String/
│   │    └─ String.hpp            # String implementation
│   │
│   ├── Tree/
│   │    ├─ AAtree.hpp             # AA tree
│   │    ├─ AVLtree.hpp            # AVL self-balancing tree
│   │    └─ FibHeap.hpp            # Fibonacci heap
│   │
│   └── Vector/
│        ├─ Array.hpp              # Fixed-size dynamic array
│        └─ Vector.hpp             # Dynamic array with resizable capacity
│
├─ tests/                          # Unit tests for containers and algorithms
├─ Makefile                        # Build and test automation
└─ Readme.md                       # Project documentation
```


---

## Algorithms List

| Sorting algorithm | Description | Time Complexity |
|-------------------|-------------|-----------------|
| **`bubbleSort`** | Repeatedly swaps adjacent elements if they are in the wrong order. | `O(n²)` |
| **`gnomeSort`** | Swaps adjacent elements and moves backwards when an inversion is found. | `O(n²)` |
| **`mergeSort`** | Divides the sequence and merges sorted parts. | `O(n log n)` |
| **`quickSort`** | Partitions the sequence around a pivot and sorts the parts. | Average `O(n log n)`, Worst `O(n²)` |
| **`selectionSort`** | Selects the minimum element and places it at the beginning of the unsorted part. | `O(n²)` |
| **`shakerSort`** | Bubble sort variant that processes the sequence in both directions. | `O(n²)` |



## Container List

| Container | Description |
|-----------|-------------|
| **`HashSet`** | Hash-based set for storing unique elements. |
| **`ListD`** | Doubly linked list. |
| **`QueueCircBuf`** | FIFO queue based on a circular buffer. |
| **`QueueOn2Stack`** | FIFO queue implemented using two stacks. |
| **`QueueOnList`** | FIFO queue based on a linked list. |
| **`Stack`** | LIFO stack. |
| **`String`** | Custom dynamic string class. |
| **`AAtree`** | Self-balancing AA tree. |
| **`AVLtree`** | Self-balancing AVL tree. |
| **`FibHeap`** | Fibonacci heap. |
| **`Array`** | Fixed-capacity dynamic array. |
| **`Vector`** | Resizable dynamic array. |


---

## Educational Approach

The project explores different approaches to implementing C++ containers, including data structures, memory management, and object lifetime.

## Requirements
- C++17 compiler (GCC, Clang)


## License
Distributed under the MIT License.  
**Created for educational purposes**.
