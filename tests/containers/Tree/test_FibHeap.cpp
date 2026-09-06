#include "../../../containers/Tree/FibHeap.hpp"
#include "../containersTests.hpp"
#include <limits>


void test_FibHeap(int& glob_counter) {
    std::cout << "\n=== FibHeap Class Test ===\n";
    int test_counter = 0;

    // FibHeap<int>: Basic Operations
    {
        FibHeap<int> heap;

        assert(heap.empty());
        ++test_counter;

        assert(heap.insert(10) != nullptr);
        assert(!heap.empty());
        assert(heap.minimum() == 10);
        test_counter += 2;

        assert(heap.insert(20) != nullptr);
        assert(heap.minimum() == 10);
        ++test_counter;

        assert(heap.insert(5) != nullptr);
        assert(heap.minimum() == 5);
        ++test_counter;

        assert(heap.insert(15) != nullptr);
        assert(heap.minimum() == 5);
        ++test_counter;

        assert(heap.extract_min() == 5);
        assert(heap.minimum() == 10);
        test_counter += 2;

        assert(heap.extract_min() == 10);
        assert(heap.minimum() == 15);
        test_counter += 2;

        assert(heap.extract_min() == 15);
        assert(heap.minimum() == 20);
        test_counter += 2;

        assert(heap.extract_min() == 20);
        assert(heap.empty());
        test_counter += 2;
    }

    // FibHeap<int>: Minimum & Empty Heap
    {
        FibHeap<int> heap;

        bool caught = false;

        try {
            heap.minimum();
        }
        catch (...) {
            caught = true;
        }

        assert(caught);
        ++test_counter;

        assert(heap.extract_min() == std::numeric_limits<int>::max());
        ++test_counter;

        assert(heap.empty());
        ++test_counter;
    }

    // FibHeap<int>: Find Node By Value
    {
        FibHeap<int> heap;

        FibHeap<int>::Pointer n1 = heap.insert(100);
        FibHeap<int>::Pointer n2 = heap.insert(50);
        FibHeap<int>::Pointer n3 = heap.insert(200);

        assert(n1 != nullptr);
        assert(n2 != nullptr);
        assert(n3 != nullptr);
        test_counter += 3;

        assert(heap.findNodeByValue(100) == n1);
        assert(heap.findNodeByValue(50) == n2);
        assert(heap.findNodeByValue(200) == n3);
        test_counter += 3;

        assert(heap.findNodeByValue(999) == nullptr);
        ++test_counter;
    }

    // FibHeap<int>: Decrease Key
    {
        FibHeap<int> heap;

        FibHeap<int>::Pointer node1 = heap.insert(50);
        FibHeap<int>::Pointer node2 = heap.insert(30);
        FibHeap<int>::Pointer node3 = heap.insert(40);

        assert(heap.minimum() == 30);
        ++test_counter;

        heap.decrease_key(node1, 10);

        assert(heap.minimum() == 10);
        ++test_counter;

        assert(node1 != nullptr);
        ++test_counter;

        heap.decrease_key(node3, 5);

        assert(heap.minimum() == 5);
        ++test_counter;

        // Decreasing a key to the same value should be valid
        heap.decrease_key(node2, 30);
        assert(heap.minimum() == 5);
        ++test_counter;
    }

    // FibHeap<int>: Invalid Decrease Key
    {
        FibHeap<int> heap;

        FibHeap<int>::Pointer node = heap.insert(100);

        bool caught = false;

        try {
            heap.decrease_key(node, 200);
        }
        catch (...) {
            caught = true;
        }

        assert(caught);
        ++test_counter;

        // Null node should throw
        caught = false;

        try {
            heap.decrease_key(nullptr, 0);
        }
        catch (...) {
            caught = true;
        }

        assert(caught);
        ++test_counter;
    }

    // FibHeap<int>: Delete Node
    {
        FibHeap<int> heap;

        FibHeap<int>::Pointer n1 = heap.insert(10);
        FibHeap<int>::Pointer n2 = heap.insert(20);
        FibHeap<int>::Pointer n3 = heap.insert(30);

        assert(heap.minimum() == 10);
        ++test_counter;

        heap.delete_node(n2);

        assert(heap.findNodeByValue(20) == nullptr);
        assert(heap.minimum() == 10);
        test_counter += 2;

        heap.delete_node(n1);

        assert(heap.findNodeByValue(10) == nullptr);
        assert(heap.minimum() == 30);
        test_counter += 2;

        assert(heap.extract_min() == 30);
        assert(heap.empty());
        test_counter += 2;
    }

    // FibHeap<int>: Extraction & Consolidation
    {
        FibHeap<int> heap;

        const int values[] = {
            42, 17, 8, 99, 23, 4, 56, 12,
            3, 75, 31, 1, 64, 18, 27
        };

        for (int value : values) {
            heap.insert(value);
        }

        assert(heap.minimum() == 1);
        ++test_counter;

        int previous = std::numeric_limits<int>::lowest();

        while (!heap.empty()) {
            int current = heap.extract_min();

            assert(current >= previous);
            previous = current;

            ++test_counter;
        }

        assert(heap.empty());
        ++test_counter;
    }

    // FibHeap<int>: Union
    {
        FibHeap<int> heap1;
        FibHeap<int> heap2;

        heap1.insert(10);
        heap1.insert(30);
        heap1.insert(50);

        heap2.insert(5);
        heap2.insert(20);
        heap2.insert(40);

        assert(heap1.minimum() == 10);
        assert(heap2.minimum() == 5);
        test_counter += 2;

        heap1.union_with(std::move(heap2));

        assert(heap1.minimum() == 5);
        test_counter++;

        // The moved heap must become empty
        assert(heap2.empty());
        ++test_counter;

        assert(heap1.extract_min() == 5);
        assert(heap1.extract_min() == 10);
        assert(heap1.extract_min() == 20);
        assert(heap1.extract_min() == 30);
        assert(heap1.extract_min() == 40);
        assert(heap1.extract_min() == 50);
        test_counter += 6;

        assert(heap1.empty());
        ++test_counter;
    }

    // FibHeap<int>: Union With Empty Heap
    {
        FibHeap<int> heap1;
        FibHeap<int> heap2;

        heap1.insert(10);
        heap1.insert(20);

        heap1.union_with(std::move(heap2));

        assert(heap2.get_size() == 0);
        assert(heap1.get_size() == 2);
    }

    // FibHeap<int>: Move Constructor
    {
        FibHeap<int> heap1;

        heap1.insert(100);
        heap1.insert(50);
        heap1.insert(200);

        FibHeap<int> heap2(std::move(heap1));

        assert(heap2.minimum() == 50);
        ++test_counter;

        assert(heap1.empty());
        assert(heap1.extract_min() == std::numeric_limits<int>::max());
        test_counter += 2;

        assert(heap2.extract_min() == 50);
        assert(heap2.extract_min() == 100);
        assert(heap2.extract_min() == 200);
        test_counter += 3;
    }

    // FibHeap<int>: Move Assignment
    {
        FibHeap<int> heap1;
        FibHeap<int> heap2;

        heap1.insert(15);
        heap1.insert(5);
        heap1.insert(25);

        heap2.insert(100);

        heap2 = std::move(heap1);

        assert(heap2.minimum() == 5);
        ++test_counter;

        assert(heap1.empty());
        ++test_counter;

        assert(heap2.extract_min() == 5);
        assert(heap2.extract_min() == 15);
        assert(heap2.extract_min() == 25);
        test_counter += 3;
    }

    // FibHeap<int>: Clear
    {
        FibHeap<int> heap;

        heap.insert(1);
        heap.insert(2);
        heap.insert(3);
        heap.insert(4);
        heap.insert(5);

        assert(!heap.empty());
        ++test_counter;

        heap.clear();

        assert(heap.empty());
        ++test_counter;

        assert(heap.extract_min() == std::numeric_limits<int>::max());
        ++test_counter;

        bool caught = false;

        try {
            heap.minimum();
        }
        catch (...) {
            caught = true;
        }

        assert(caught);
        ++test_counter;
    }

    // FibHeap<std::string>: Basic Operations
    {
        FibHeap<std::string> heap;

        heap.insert("Delta");
        heap.insert("Alpha");
        heap.insert("Charlie");
        heap.insert("Bravo");

        assert(heap.minimum() == "Alpha");
        ++test_counter;

        assert(heap.extract_min() == "Alpha");
        assert(heap.extract_min() == "Bravo");
        assert(heap.extract_min() == "Charlie");
        assert(heap.extract_min() == "Delta");
        test_counter += 4;

        assert(heap.empty());
        ++test_counter;
    }

    // FibHeap<int>: Large Number of Elements
    {
        FibHeap<int> heap;

        constexpr int count = 1000;

        for (int i = count; i >= 1; --i) {
            heap.insert(i);
        }

        assert(heap.minimum() == 1);
        ++test_counter;

        for (int i = 1; i <= count; ++i) {
            assert(heap.extract_min() == i);
        }

        test_counter += count;

        assert(heap.empty());
        ++test_counter;
    }

    std::cout << "=== All " << test_counter
              << " FibHeap tests passed! ===\n";

    glob_counter += test_counter;
}