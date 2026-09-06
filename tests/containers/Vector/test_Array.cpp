#include "../../../containers/Vector/Array.hpp"
#include "../containersTests.hpp"


void test_Array(int& glob_counter){
    std::cout << "\n=== Array Class Test ===\n";
    int test_counter = 0;

    // Constructors and Basic Properties
    {
        Array<int, 5> a1;
        assert(a1.size() == 0 && a1.capacity() == 5);
        ++test_counter;

        Array<int, 4> a2(2, 99);
        assert(a2.size() == 2 && a2[0] == 99 && a2[1] == 99);
        ++test_counter;

        bool caught = false;
        try { Array<int, 2> a3(5, 1); }
        catch (...) { caught = true; }
        assert(caught);
        ++test_counter;
    }

    // Push Back and Element Access
    {
        Array<int, 3> a;
        a.push_back(10);
        a.push_back(20);
        assert(a.size() == 2 && a[1] == 20);
        ++test_counter;

        a[0] = 99;
        assert(a[0] == 99);
        ++test_counter;

        bool caught = false;
        try { a[5]; }
        catch (...) { caught = true; }
        assert(caught);
        ++test_counter;

        caught = false;
        try { a.push_back(30); a.push_back(40); }
        catch (...) { caught = true; }
        assert(caught);
        ++test_counter;
    }

    // Front and Back
    {
        Array<int, 3> a;
        a.push_back(5);
        a.push_back(7);
        assert(a.front() == 5 && a.back() == 7);
        ++test_counter;

        a.push_back(9);
        assert(a.back() == 9);
        ++test_counter;

        bool caught = false;
        try {
            Array<int, 2> b;
            b.front();
        }
        catch (...) { caught = true; }
        assert(caught);
        ++test_counter;
    }

    // Fill and Empty
    {
        Array<int, 4> a;
        a.push_back(1);
        a.push_back(2);
        a.fill(8);
        assert(a[0] == 8 && a.size() == 4);
        ++test_counter;

        Array<int, 3> b;
        assert(b.empty());
        ++test_counter;

        b.push_back(1);
        assert(!b.empty());
        ++test_counter;
    }

    // Iterators Basic
    {
        Array<int, 3> a;
        a.push_back(1);
        a.push_back(2);
        a.push_back(3);

        auto it = a.begin();
        assert(*it == 1);
        ++test_counter;

        ++it;
        assert(*it == 2);
        ++test_counter;

        it++;
        assert(*it == 3);
        ++test_counter;
    }

    // Iterator Arithmetic and Comparison
    {
        Array<int, 4> a;
        for (int i = 0; i < 4; ++i) {
            a.push_back(i + 1);
        }

        auto it = a.begin();
        it += 2;
        assert(*it == 3);
        ++test_counter;

        it -= 1;
        assert(*it == 2);
        ++test_counter;

        assert((it + 1) == (a.begin() + 2));
        ++test_counter;

        assert((it + 1) != (it));
        ++test_counter;
    }

    // Copy Constructor and Assignment
    {
        Array<int, 5> a;
        a.push_back(10);
        a.push_back(20);

        Array<int, 5> b = a;
        assert(b.size() == 2 && b[1] == 20);
        ++test_counter;

        Array<int, 5> c;
        c = a;
        assert(c[0] == 10 && c.size() == 2);
        ++test_counter;
    }

    // Move Constructor and Assignment
    {
        Array<int, 5> a;
        a.push_back(1);
        a.push_back(2);

        Array<int, 5> b = std::move(a);
        assert(b.size() == 2 && b[1] == 2);
        ++test_counter;

        Array<int, 5> c;
        c = std::move(b);
        assert(c.size() == 2 && c[0] == 1);
        ++test_counter;
    }

    // Erase and Modify
    {
        Array<int, 4> a;
        a.push_back(10);
        a.push_back(20);
        a.push_back(30);

        a[1] = 99;
        assert(a[1] == 99);
        ++test_counter;

        a.fill(7);
        assert(a[2] == 7);
        ++test_counter;
    }

    // toString Method
    {
        Array<int, 3> a;
        a.push_back(1);
        a.push_back(2);
        a.push_back(3);
        String s = a.toString();
        assert(s == "123");
        ++test_counter;
    }

    // Iterator Dereferencing and Arrow Operator
    {
        struct Point { int x; };
        Array<Point, 2> arr;
        arr.push_back({ 10 });
        auto it = arr.begin();
        assert(it->x == 10);
        ++test_counter;

        assert((*it).x == 10);
        ++test_counter;
    }


    // End Iterator Position
    {
        Array<int, 3> a;
        a.push_back(1);
        a.push_back(2);
        a.push_back(3);

        auto it = a.begin();
        int sum = 0;
        while (it != a.end()) {
            sum += *it;
            ++it;
        }
        assert(sum == 6);
        ++test_counter;
    }


    // Iterator Decrement and Comparison
    {
        Array<int, 3> a;
        a.push_back(3);
        a.push_back(2);
        a.push_back(1);

        auto it = a.begin() + 2;
        assert(*it == 1);
        ++test_counter;

        --it;
        assert(*it == 2);
        ++test_counter;
    }


    // Capacity & Size Invariants

    {
        Array<char, 10> a;
        for (int i = 0; i < 10; ++i) {
            a.push_back('a');
        }
        assert(a.capacity() == 10 && a.size() == 10);
        ++test_counter;

        bool caught = false;
        try { a.push_back('x'); }
        catch (...) { caught = true; }
        assert(caught);
        ++test_counter;
    }

    // Data Pointer Access
    {
        Array<int, 2> a;
        a.push_back(1);
        a.push_back(2);
        int* ptr = a.data();
        assert(ptr[0] == 1 && ptr[1] == 2);
        ++test_counter;
    }

    // Iterator Validity Checking
    {
        Array<int, 1> a;
        a.push_back(5);

        auto it = a.end();
        bool caught = false;
        try { *it; }
        catch (...) { caught = true; }
        assert(caught);
        ++test_counter;
    }

    // Iterator Comparison Operators
    {
        Array<int, 3> a;
        a.push_back(10);
        a.push_back(20);
        a.push_back(30);

        auto it1 = a.begin();
        auto it2 = a.begin() + 1;
        assert(it1 != it2);
        ++test_counter;

        ++it1;
        assert(it1 == it2);
        ++test_counter;
    }

    // Push/Pop Logic Testing
    {
        Array<int, 3> a;
        a.push_back(42);
        a.push_back(24);
        assert(a.back() == 24);
        ++test_counter;

        a[1] = 100;
        assert(a[1] == 100);
        ++test_counter;
    }

    {
        Array<int, 3> a;
        a.push_back(42);
        a.push_back(100);

        auto it = a.end() - 1;
        assert(*it == 100);
        ++test_counter;
    }


    std::cout << "=== All " << test_counter << " Array tests passed! ===\n";
    glob_counter += test_counter;
}