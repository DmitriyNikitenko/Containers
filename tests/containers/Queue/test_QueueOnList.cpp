#include "../../../containers/Queue/QueueOnList.hpp"
#include "../containersTests.hpp"


void test_QueueOnList(int& glob_counter) {
    std::cout << "\n=== QueueOnList Class Test ===\n";
    int test_counter = 0;

    // QueueOnList<int>: Basic Operations
    {
        QueueOnList<int> q;

        assert(q.empty());
        assert(q.size() == 0);
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

    // QueueOnList<int>: FIFO Order
    {
        QueueOnList<int> q;

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

    // QueueOnList<int>: Initializer List
    {
        QueueOnList<int> q = {1, 2, 3, 4, 5};

        assert(q.size() == 5);
        assert(q.front() == 1);
        assert(q.back() == 5);
        test_counter += 3;

        q.pop();

        assert(q.front() == 2);
        assert(q.back() == 5);
        assert(q.size() == 4);
        test_counter += 3;

        q.push(6);

        assert(q.front() == 2);
        assert(q.back() == 6);
        assert(q.size() == 5);
        test_counter += 3;
    }

    // QueueOnList<int>: Capacity Constructor
    {
        QueueOnList<int> q1;
        QueueOnList<int> q2(5);
        QueueOnList<int> q3(20);

        // Capacity must be at least 10
        assert(q1.size() == 0);
        assert(q2.size() == 0);
        assert(q3.size() == 0);
        test_counter += 3;

        // The queue should work regardless of the requested capacity
        q2.push(10);
        q3.push(20);

        assert(q2.front() == 10);
        assert(q3.front() == 20);
        test_counter += 2;
    }

    // QueueOnList<int>: Empty Queue Operations
    {
        QueueOnList<int> q;

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

    // QueueOnList<int>: Copy Constructor
    {
        QueueOnList<int> q1;

        q1.push(10);
        q1.push(20);
        q1.push(30);

        QueueOnList<int> q2(q1);

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

    // QueueOnList<int>: Copy Assignment
    {
        QueueOnList<int> q1;
        QueueOnList<int> q2;

        q1.push(10);
        q1.push(20);
        q1.push(30);

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

    // QueueOnList<int>: Move Constructor
    {
        QueueOnList<int> q1;

        q1.push(10);
        q1.push(20);
        q1.push(30);

        QueueOnList<int> q2(std::move(q1));

        assert(q2.size() == 3);
        assert(q2.front() == 10);
        assert(q2.back() == 30);
        test_counter += 3;

        assert(q1.empty());
        assert(q1.size() == 0);
        test_counter += 2;
    }

    // QueueOnList<int>: Move Assignment
    {
        QueueOnList<int> q1;
        QueueOnList<int> q2;

        q1.push(10);
        q1.push(20);
        q1.push(30);

        q2.push(100);
        q2.push(200);

        q2 = std::move(q1);

        assert(q2.size() == 3);
        assert(q2.front() == 10);
        assert(q2.back() == 30);
        test_counter += 3;

        assert(q1.empty());
        assert(q1.size() == 0);
        test_counter += 2;
    }

    // QueueOnList<std::string>: Basic Operations
    {
        QueueOnList<std::string> q;

        q.push("Hello");
        q.push("World");
        q.push("C++");

        assert(q.size() == 3);
        assert(q.front() == "Hello");
        assert(q.back() == "C++");
        test_counter += 3;

        q.pop();

        assert(q.front() == "World");
        assert(q.back() == "C++");
        test_counter += 2;

        q.pop();
        q.pop();

        assert(q.empty());
        ++test_counter;
    }

    // QueueOnList<std::string>: Copy & Move
    {
        QueueOnList<std::string> q1 = {"A", "B", "C"};

        QueueOnList<std::string> q2(q1);

        assert(q2.size() == 3);
        assert(q2.front() == "A");
        assert(q2.back() == "C");
        test_counter += 3;

        q1.pop();

        assert(q1.front() == "B");
        assert(q2.front() == "A");
        test_counter += 2;

        QueueOnList<std::string> q3(std::move(q2));

        assert(q3.size() == 3);
        assert(q3.front() == "A");
        assert(q3.back() == "C");
        test_counter += 3;

        assert(q2.empty());
        ++test_counter;
    }

    // QueueOnList<int>: Self Assignment
    {
        QueueOnList<int> q = {1, 2, 3};

        q = q;

        assert(q.size() == 3);
        assert(q.front() == 1);
        assert(q.back() == 3);
        test_counter += 3;
    }

    std::cout << "=== All " << test_counter
              << " QueueOnList tests passed! ===\n";

    glob_counter += test_counter;
}