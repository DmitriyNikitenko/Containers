#include "../../../containers/Queue/QueueCircBuf.hpp"
#include "../containersTests.hpp"


void test_Queue(int& glob_counter) {
    std::cout << "\n=== QueueCirclBuf Class Test ===\n";
    int test_counter = 0;

    // Queue<int>: Basic FIFO Operations
    {
        Queue<int> q;

        assert(q.empty());
        assert(q.size() == 0);
        assert(q.capacity() == 10);
        ++test_counter;

        q.push(10);

        assert(!q.empty());
        assert(q.size() == 1);
        assert(q.front() == 10);
        assert(q.back() == 10);
        test_counter += 4;

        q.push(20);

        assert(q.size() == 2);
        assert(q.front() == 10);
        assert(q.back() == 20);
        test_counter += 3;

        q.pop();

        assert(q.size() == 1);
        assert(q.front() == 20);
        assert(q.back() == 20);
        test_counter += 3;

        q.pop();

        assert(q.empty());
        assert(q.size() == 0);
        ++test_counter;
    }

    // Queue<int>: FIFO Order
    {
        Queue<int> q;

        q.push(1);
        q.push(2);
        q.push(3);
        q.push(4);

        assert(q.front() == 1);
        assert(q.back() == 4);
        test_counter += 2;

        q.pop();
        assert(q.front() == 2);
        ++test_counter;

        q.pop();
        assert(q.front() == 3);
        ++test_counter;

        q.pop();
        assert(q.front() == 4);
        ++test_counter;

        q.pop();
        assert(q.empty());
        ++test_counter;
    }

    // Queue<int>: Initializer List
    {
        Queue<int> q = {1, 2, 3, 4, 5};

        assert(q.size() == 5);
        assert(q.front() == 1);
        assert(q.back() == 5);
        assert(q.capacity() == 10);
        test_counter += 4;

        q.pop();

        assert(q.front() == 2);
        assert(q.back() == 5);
        ++test_counter;

        q.push(6);

        assert(q.front() == 2);
        assert(q.back() == 6);
        assert(q.size() == 5);
        test_counter += 3;
    }

    // Queue<int>: Circular Buffer Behaviour
    {
        Queue<int> q;

        for (int i = 1; i <= 10; ++i) {
            q.push(i);
        }

        assert(q.size() == 10);
        assert(q.front() == 1);
        assert(q.back() == 10);
        test_counter += 3;

        // Move the start index forward
        for (int i = 0; i < 5; ++i) {
            q.pop();
        }

        assert(q.size() == 5);
        assert(q.front() == 6);
        assert(q.back() == 10);
        test_counter += 3;

        // Reuse the freed positions in the circular buffer
        q.push(11);
        q.push(12);
        q.push(13);

        assert(q.size() == 8);
        assert(q.front() == 6);
        assert(q.back() == 13);
        test_counter += 3;
    }

    // Queue<int>: Automatic Capacity Growth
    {
        Queue<int> q;

        size_t old_capacity = q.capacity();

        for (size_t i = 0; i < old_capacity + 1; ++i) {
            q.push(static_cast<int>(i));
        }

        assert(q.size() == old_capacity + 1);
        assert(q.capacity() == old_capacity * 2);
        assert(q.front() == 0);
        assert(q.back() == static_cast<int>(old_capacity));
        test_counter += 4;
    }

    // Queue<int>: Capacity Growth After Wrap-around
    {
        Queue<int> q(4, 0);

        q.push(1);
        q.push(2);
        q.push(3);
        q.push(4);

        q.pop();
        q.pop();

        q.push(5);
        q.push(6);

        assert(q.size() == 4);
        assert(q.front() == 3);
        assert(q.back() == 6);
        test_counter += 3;

        // This push should trigger reallocation
        q.push(7);

        assert(q.size() == 5);
        assert(q.front() == 3);
        assert(q.back() == 7);
        assert(q.capacity() == 8);
        test_counter += 4;
    }

    // Queue<int>: Custom Capacity Constructor
    {
        Queue<int> q(20, 42);

        assert(q.capacity() == 20);
        assert(q.size() == 0);
        assert(q.empty());
        test_counter += 3;

        q.push(10);

        assert(q.front() == 10);
        assert(q.back() == 10);
        assert(q.size() == 1);
        test_counter += 3;
    }

    // Queue<int>: Clear
    {
        Queue<int> q;

        q.push(10);
        q.push(20);
        q.push(30);

        assert(q.size() == 3);
        assert(!q.empty());
        test_counter += 2;

        q.clear();

        assert(q.empty());
        assert(q.size() == 0);
        assert(q.capacity() == 10);
        test_counter += 3;

        q.push(100);

        assert(q.front() == 100);
        assert(q.back() == 100);
        ++test_counter;
    }

    // Queue<int>: Empty Queue Operations
    {
        Queue<int> q;

        // pop() on an empty queue should do nothing
        q.pop();

        assert(q.empty());
        assert(q.size() == 0);
        test_counter += 2;

        bool caught = false;

        try {
            q.front();
        }
        catch (...) {
            caught = true;
        }

        assert(caught);
        ++test_counter;

        caught = false;

        try {
            q.back();
        }
        catch (...) {
            caught = true;
        }

        assert(caught);
        ++test_counter;
    }

    // Queue<int>: Reserve
    {
        Queue<int> q;

        q.push(10);
        q.push(20);
        q.push(30);

        size_t old_capacity = q.capacity();

        q.reserve(50);

        assert(q.capacity() == 50);
        assert(q.size() == 3);
        assert(q.front() == 10);
        assert(q.back() == 30);
        test_counter += 4;

        // reserve() with smaller capacity should do nothing
        q.reserve(10);

        assert(q.capacity() == 50);
        assert(q.size() == 3);
        test_counter += 2;
    }

    // Queue<int>: Reserve With Wrapped Data
    {
        Queue<int> q;

        for (int i = 1; i <= 7; ++i) {
            q.push(i);
        }

        for (int i = 0; i < 4; ++i) {
            q.pop();
        }

        q.push(8);
        q.push(9);

        assert(q.front() == 5);
        assert(q.back() == 9);
        ++test_counter;

        q.reserve(30);

        assert(q.capacity() == 30);
        assert(q.size() == 5);
        assert(q.front() == 5);
        assert(q.back() == 9);
        test_counter += 4;

        assert(q.front() == 5);
        q.pop();
        assert(q.front() == 6);
        q.pop();
        assert(q.front() == 7);
        q.pop();
        assert(q.front() == 8);
        q.pop();
        assert(q.front() == 9);
        test_counter += 5;
    }

    // Queue<int>: Copy Constructor
    {
        Queue<int> q1;

        q1.push(10);
        q1.push(20);
        q1.push(30);

        Queue<int> q2(q1);

        assert(q2.size() == 3);
        assert(q2.front() == 10);
        assert(q2.back() == 30);
        test_counter += 3;

        q1.pop();

        assert(q1.front() == 20);
        assert(q2.front() == 10);
        test_counter += 2;

        q1.push(40);

        assert(q1.back() == 40);
        assert(q2.back() == 30);
        test_counter += 2;
    }

    // Queue<int>: Copy Assignment
    {
        Queue<int> q1;

        q1.push(10);
        q1.push(20);
        q1.push(30);

        Queue<int> q2;

        q2.push(100);
        q2.push(200);

        q2 = q1;

        assert(q2.size() == 3);
        assert(q2.front() == 10);
        assert(q2.back() == 30);
        test_counter += 3;

        q1.pop();

        assert(q1.front() == 20);
        assert(q2.front() == 10);
        test_counter += 2;
    }

    // Queue<int>: Move Constructor
    {
        Queue<int> q1;

        q1.push(10);
        q1.push(20);
        q1.push(30);

        Queue<int> q2(std::move(q1));

        assert(q2.size() == 3);
        assert(q2.front() == 10);
        assert(q2.back() == 30);
        test_counter += 3;

        assert(q1.empty());
        assert(q1.size() == 0);
        assert(q1.capacity() == 0);
        test_counter += 3;
    }

    // Queue<int>: Move Assignment
    {
        Queue<int> q1;

        q1.push(10);
        q1.push(20);
        q1.push(30);

        Queue<int> q2;

        q2.push(100);
        q2.push(200);

        q2 = std::move(q1);

        assert(q2.size() == 3);
        assert(q2.front() == 10);
        assert(q2.back() == 30);
        test_counter += 3;

        assert(q1.empty());
        assert(q1.size() == 0);
        assert(q1.capacity() == 0);
        test_counter += 3;
    }

    // Queue<int>: Equality Operators
    {
        Queue<int> q1 = {1, 2, 3};
        Queue<int> q2 = {1, 2, 3};
        Queue<int> q3 = {1, 2, 4};

        assert(q1 == q2);
        assert(!(q1 != q2));
        test_counter += 2;

        assert(q1 != q3);
        assert(!(q1 == q3));
        test_counter += 2;

        q2.pop();

        assert(q1 != q2);
        ++test_counter;
    }

    // Queue<int>: Equality After Different Internal Layouts
    {
        Queue<int> q1;

        q1.push(1);
        q1.push(2);
        q1.push(3);
        q1.pop();
        q1.pop();
        q1.push(4);
        q1.push(5);

        Queue<int> q2 = {3, 4, 5};

        assert(q1 == q2);
        assert(!(q1 != q2));
        test_counter += 2;
    }

    // Queue<std::string>: Basic Operations
    {
        Queue<std::string> q;

        q.push("Hello");
        q.push("World");
        q.push("C++");

        assert(q.front() == "Hello");
        assert(q.back() == "C++");
        assert(q.size() == 3);
        test_counter += 3;

        q.pop();

        assert(q.front() == "World");
        assert(q.back() == "C++");
        test_counter += 2;

        q.clear();

        assert(q.empty());
        ++test_counter;
    }

    // Queue<std::string>: Initializer List & Copy
    {
        Queue<std::string> q1 = {"A", "B", "C"};

        Queue<std::string> q2(q1);

        assert(q2.size() == 3);
        assert(q2.front() == "A");
        assert(q2.back() == "C");
        test_counter += 3;

        q1.pop();

        assert(q1.front() == "B");
        assert(q2.front() == "A");
        test_counter += 2;
    }

    // Queue<std::string>: Move Semantics
    {
        Queue<std::string> q1 = {"One", "Two", "Three"};

        Queue<std::string> q2(std::move(q1));

        assert(q2.size() == 3);
        assert(q2.front() == "One");
        assert(q2.back() == "Three");
        test_counter += 3;

        assert(q1.empty());
        ++test_counter;
    }

    // Queue<int>: Self Assignment
    {
        Queue<int> q = {1, 2, 3};

        q = q;

        assert(q.size() == 3);
        assert(q.front() == 1);
        assert(q.back() == 3);
        test_counter += 3;
    }

    std::cout << "=== All " << test_counter
              << " queue tests passed! ===\n";

    glob_counter += test_counter;
}