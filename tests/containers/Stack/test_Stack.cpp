#include "../../../containers/Stack/Stack.hpp"
#include "../../../containers/String/String.hpp"
#include "../containersTests.hpp"


void test_Stack(int& glob_counter) {
    std::cout << "\n=== Stack Class Test ===\n";
    int test_counter = 0;

    // Stack<int>: Basic Operations
    {
        Stack<int> s;
        assert(s.empty() == true);
        ++test_counter;

        s.push(10);
        assert(!s.empty() && s.top() == 10);
        ++test_counter;

        s.push(20);
        assert(s.top() == 20);
        ++test_counter;

        s.pop();
        assert(s.top() == 10);
        ++test_counter;
    }

    // Stack<int>: Initializer List, Copy & Move
    {
        Stack<int> s1 = { 1, 2, 3 };
        assert(s1.top() == 3);
        ++test_counter;

        Stack<int> s2(s1); // Copy
        assert(s2.top() == 3);
        s1.pop();
        assert(s1.top() != s2.top());
        ++test_counter += 2;

        Stack<int> s3(std::move(s2)); // Move
        assert(s3.top() == 3);
        assert(s2.empty());
        test_counter += 2;
    }

    // Stack<int>: Assignment
    {
        Stack<int> s1 = { 100, 200 };
        Stack<int> s2;
        s2 = s1;

        assert(s2.top() == 200);
        s1.pop();
        assert(s1.top() != s2.top());
        test_counter += 2;

        Stack<int> s3;
        s3 = std::move(s2);
        assert(s3.top() == 200);
        assert(s2.empty());
        test_counter += 2;
    }

    // Stack<int>: Exceptions
    {
        Stack<int> s;
        bool caught = false;
        try { s.top(); }
        catch (...) { caught = true; }
        assert(caught);

        caught = false;
        try { s.pop(); }
        catch (...) { caught = true; }
        assert(caught);
        test_counter += 2;
    }

    // Stack<std::string>: Basic & Edge Cases
    {
        Stack<String> s;
        s.push("Hello");
        s.push("World");
        assert(s.top() == "World");
        ++test_counter;

        s.pop();
        assert(s.top() == "Hello");
        ++test_counter;

        Stack<String> s2 = { "A", "B", "C" };
        assert(s2.top() == "C");
        ++test_counter;

        Stack<String> s3(s2); // Copy
        s2.pop();
        assert(s3.top() == "C");
        ++test_counter;

        Stack<String> s4;
        s4 = std::move(s3);
        assert(s4.top() == "C");
        assert(s3.empty());
        test_counter += 2;

        s4.clear();
        assert(s4.empty());
        ++test_counter;

        bool caught = false;
        try { s4.top(); }
        catch (...) { caught = true; }
        assert(caught);
        ++test_counter;
    }

    std::cout << "=== All " << test_counter << " stack tests passed! ===\n";
    glob_counter += test_counter;
}