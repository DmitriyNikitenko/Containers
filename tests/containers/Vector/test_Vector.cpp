#include "../../../containers/Vector/Vector.hpp"
#include "../../../containers/String/String.hpp"
#include "../containersTests.hpp"


void test_Vector(int& glob_counter) {
    std::cout << "\n=== Vector Class Test ===\n";
    int test_counter = 0;

    // Constructors and Basic Operations
    {
        Vector<int> v1;
        assert(v1.empty() && v1.capacity() == 10 && v1.size() == 0);
        ++test_counter;

        Vector<String> v2;
        assert(v2.empty() && v2.capacity() == 10);
        ++test_counter;
    }

    // Push/Pop Operations
    {
        Vector<int> v;
        v.push_back(10);
        assert(v.size() == 1 && v[0] == 10);
        ++test_counter;

        v.pop_back();
        assert(v.empty());
        ++test_counter;

        Vector<String> vs;
        vs.emplace_back("Test");
        assert(vs.back() == "Test");
        ++test_counter;
    }

    // Iterator Functionality
    {
        Vector<int> v{ 1, 2, 3 };
        auto it = v.begin();
        assert(*it == 1);
        ++test_counter;

        ++it;
        assert(*it == 2);
        ++test_counter;

        auto end = v.end();
        assert(it != end);
        ++test_counter;

        bool caught = false;
        try { v.end()++; }
        catch (...) { caught = true; }
        assert(caught);
        ++test_counter;
    }

    // Element Access and Modifiers
    {
        Vector<String> v{ "A", "B", "C" };
        assert(v.front() == "A" && v.back() == "C");
        ++test_counter;

        v[1] = "X";
        assert(v[1] == "X");
        ++test_counter;

        bool caught = false;
        try { v.at(5); }
        catch (...) { caught = true; }
        assert(caught);
        ++test_counter;
    }

    // Memory Management
    {
        Vector<int> v;
        v.reserve(100);
        assert(v.capacity() == 100 && v.empty());
        ++test_counter;

        v.resize(5, 10);
        assert(v.size() == 5 && v[4] == 10);
        ++test_counter;

        v.shrink_to_fit();
        assert(v.capacity() == 5);
        ++test_counter;
    }

    // Copy/Move Semantics
    {
        Vector<int> v1{ 1,2,3 };
        Vector<int> v2 = v1;
        assert(v2.size() == 3 && v2[2] == 3);
        ++test_counter;

        Vector<int> v3 = std::move(v1);
        assert(v3.size() == 3 && v1.empty());
        ++test_counter;
    }

    // Complex Operations
    {
        Vector<int> v{ 1,2,3,4,5 };

        // Erase elements
        auto first = v.begin() + 1;
        auto last = v.begin() + 3;
        v.erase(first, last);
        assert(v.size() == 3 && v[1] == 4);
        ++test_counter;

        // Insert element
        v.insert(10, v.begin() + 1);
        assert(v.size() == 4 && v[1] == 10);
        ++test_counter;

        // Clear vector
        v.clear();
        assert(v.empty());
        ++test_counter;
    }

    std::cout << "=== All " << test_counter << " vector tests passed! ===\n";
    glob_counter += test_counter;
}