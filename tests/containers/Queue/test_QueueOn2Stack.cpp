#include "../../../containers/Queue/QueueOn2Stack.hpp"
#include "../containersTests.hpp"


void test_QueueOn2Stack(int& glob_counter) {
    std::cout << "\n=== QueueOn2Stack Class Test ===\n";
    int test_counter = 0;

    // QueueOn2Stack<int>: Basic FIFO Operations
    {
        QueueOn2Stack<int> q;

        assert(q.empty());
        assert(q.size() == 0);
        assert(q.capacity() == 10);
        ++test_counter;

        q.push(10);

        assert(!q.empty());
        assert(q.size() == 1);
        assert(q.front() == 10);
        test_counter += 3;

        q.push(20);

        assert(q.size() == 2);
        assert(q.front() == 10);
        test_counter += 2;

        q.push(30);

        assert(q.size() == 3);
        assert(q.front() == 10);
        test_counter += 2;

        q.pop();

        assert(q.size() == 2);
        assert(q.front() == 20);
        test_counter += 2;

        q.pop();

        assert(q.size() == 1);
        assert(q.front() == 30);
        test_counter += 2;

        q.pop();

        assert(q.empty());
        assert(q.size() == 0);
        test_counter += 2;
    }

    // QueueOn2Stack<int>: FIFO Order
    {
        QueueOn2Stack<int> q;

        for (int i = 1; i <= 5; ++i) {
            q.push(i);
        }

        assert(q.size() == 5);
        assert(q.front() == 1);
        test_counter += 2;

        for (int i = 1; i <= 5; ++i) {
            assert(q.front() == i);
            q.pop();
            ++test_counter;
        }

        assert(q.empty());
        ++test_counter;
    }

    // QueueOn2Stack<int>: Input/Output Stack Transfer
    {
        QueueOn2Stack<int> q;

        q.push(10);
        q.push(20);
        q.push(30);

        // The first pop should transfer elements from input stack
        // to output stack and remove the oldest element.
        q.pop();

        assert(q.front() == 20);
        assert(q.size() == 2);
        test_counter += 2;

        q.push(40);
        q.push(50);

        assert(q.front() == 20);
        assert(q.size() == 4);
        test_counter += 2;

        q.pop();
        assert(q.front() == 30);

        q.pop();
        assert(q.front() == 40);

        q.pop();
        assert(q.front() == 50);

        test_counter += 3;
    }

    // QueueOn2Stack<int>: Empty Queue Operations
    {
        QueueOn2Stack<int> q;

        assert(q.empty());
        ++test_counter;

        bool caught = false;

        try {
            q.front();
        }
        catch (...) {
            caught = true;
        }

        assert(caught);
        ++test_counter;

        // pop() on an empty queue should not crash.
        bool pop_threw = false;

        try {
            q.pop();
        }
        catch (...) {
            pop_threw = true;
        }

        assert(!pop_threw);
        ++test_counter;

        assert(q.empty());
        ++test_counter;
    }

    // QueueOn2Stack<int>: Clear
    {
        QueueOn2Stack<int> q;

        q.push(10);
        q.push(20);
        q.push(30);

        assert(q.size() == 3);
        ++test_counter;

        q.clear();

        assert(q.empty());
        assert(q.size() == 0);
        test_counter += 2;

        q.push(100);

        assert(q.front() == 100);
        assert(q.size() == 1);
        test_counter += 2;
    }

    // QueueOn2Stack<int>: Custom Capacity
    {
        QueueOn2Stack<int> q1(5);
        QueueOn2Stack<int> q2(20);

        // Capacity must be at least 10.
        assert(q1.capacity() == 10);
        assert(q2.capacity() == 20);
        test_counter += 2;

        q1.push(1);
        q2.push(2);

        assert(q1.front() == 1);
        assert(q2.front() == 2);
        test_counter += 2;
    }

    // QueueOn2Stack<int>: Copy Constructor
    {
        QueueOn2Stack<int> q1;

        q1.push(10);
        q1.push(20);
        q1.push(30);

        QueueOn2Stack<int> q2(q1);

        assert(q2.size() == 3);
        assert(q2.front() == 10);
        test_counter += 2;

        q1.pop();

        assert(q1.front() == 20);
        assert(q2.front() == 10);
        test_counter += 2;

        q1.push(40);

        assert(q2.front() == 10);
        test_counter += 2;
    }

    // QueueOn2Stack<int>: Copy Assignment
    {
        QueueOn2Stack<int> q1;
        QueueOn2Stack<int> q2;

        q1.push(10);
        q1.push(20);
        q1.push(30);

        q2.push(100);

        q2 = q1;

        assert(q2.size() == 3);
        assert(q2.front() == 10);
        test_counter += 2;

        q1.pop();

        assert(q1.front() == 20);
        assert(q2.front() == 10);
        test_counter += 2;
    }

    // QueueOn2Stack<int>: Move Constructor
    {
        QueueOn2Stack<int> q1;

        q1.push(10);
        q1.push(20);
        q1.push(30);

        QueueOn2Stack<int> q2(std::move(q1));

        assert(q2.size() == 3);
        assert(q2.front() == 10);
        test_counter += 2;

        assert(q1.empty());
        assert(q1.size() == 0);
        test_counter += 2;
    }

    // QueueOn2Stack<int>: Move Assignment
    {
        QueueOn2Stack<int> q1;
        QueueOn2Stack<int> q2;

        q1.push(10);
        q1.push(20);
        q1.push(30);

        q2.push(100);
        q2.push(200);

        q2 = std::move(q1);

        assert(q2.size() == 3);
        assert(q2.front() == 10);
        test_counter += 2;

        assert(q1.empty());
        assert(q1.size() == 0);
        test_counter += 2;
    }

    // QueueOn2Stack<int>: Swap
    {
        QueueOn2Stack<int> q1;
        QueueOn2Stack<int> q2;

        q1.push(10);
        q1.push(20);

        q2.push(100);
        q2.push(200);
        q2.push(300);

        q1.swap(q2);

        assert(q1.size() == 3);
        assert(q1.front() == 100);

        assert(q2.size() == 2);
        assert(q2.front() == 10);

        test_counter += 4;
    }

    // QueueOn2Stack<int>: Equality
    {
        QueueOn2Stack<int> q1;
        QueueOn2Stack<int> q2;

        q1.push(1);
        q1.push(2);
        q1.push(3);

        q2.push(1);
        q2.push(2);
        q2.push(3);

        assert(q1 == q2);
        assert(!(q1 != q2));
        test_counter += 2;

        q2.pop();

        assert(q1 != q2);
        assert(!(q1 == q2));
        test_counter += 2;
    }

    // QueueOn2Stack<std::string>: Basic Operations
    {
        QueueOn2Stack<std::string> q;

        q.push("Hello");
        q.push("World");
        q.push("C++");

        assert(q.size() == 3);
        assert(q.front() == "Hello");
        test_counter += 2;

        q.pop();

        assert(q.front() == "World");
        assert(q.size() == 2);
        test_counter += 2;

        q.pop();

        assert(q.front() == "C++");
        ++test_counter;

        q.pop();

        assert(q.empty());
        ++test_counter;
    }

    // QueueOn2Stack<std::string>: Copy & Move
    {
        QueueOn2Stack<std::string> q1;

        q1.push("A");
        q1.push("B");
        q1.push("C");

        QueueOn2Stack<std::string> q2(q1);

        assert(q2.front() == "A");
        assert(q2.size() == 3);
        test_counter += 2;

        QueueOn2Stack<std::string> q3(std::move(q2));

        assert(q3.front() == "A");
        assert(q3.size() == 3);
        test_counter += 2;

        assert(q2.empty());
        ++test_counter;
    }

    // QueueOn2Stack<int>: Self Assignment
    {
        QueueOn2Stack<int> q;

        q.push(1);
        q.push(2);
        q.push(3);

        q = q;

        assert(q.size() == 3);
        assert(q.front() == 1);

        test_counter += 2;
    }

    // QueueOn2Stack<int>: Large Number of Elements
    {
        QueueOn2Stack<int> q;

        constexpr int count = 1000;

        for (int i = 1; i <= count; ++i) {
            q.push(i);
        }

        assert(q.size() == count);
        assert(q.front() == 1);
        test_counter += 2;

        for (int i = 1; i <= count; ++i) {
            assert(q.front() == i);
            q.pop();
            ++test_counter;
        }

        assert(q.empty());
        ++test_counter;
    }

    std::cout << "=== All " << test_counter
              << " QueueOn2Stack tests passed! ===\n";

    glob_counter += test_counter;
}