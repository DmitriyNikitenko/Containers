#include "containers/Vector.hpp"
#include "containers/Array.hpp"
#include "containers/String.hpp"
#include "containers/Stack.hpp"
#include "containers/Deque.hpp"
#include "containers/Queue.hpp"
#include "containers/List.hpp"
#include "containers/AVLtree.hpp"
#include <cassert>
#include <iostream>
#include <string>


int glob_counter = 0;

void test_vector_class() {
    std::cout << "\n=== Vector Class Test ===\n";
    int test_counter = 0;

    // ======================================================
    // 1. Constructors and Basic Operations
    // ======================================================
    {
        Vector<int> v1;
        assert(v1.empty() && v1.capacity() == 10 && v1.size() == 0); // Test 1
        ++test_counter;

        Vector<String> v2;
        assert(v2.empty() && v2.capacity() == 10); // Test 2
        ++test_counter;
    }

    // ======================================================
    // 2. Push/Pop Operations
    // ======================================================
    {
        Vector<int> v;
        v.push_back(10);
        assert(v.size() == 1 && v[0] == 10); // Test 3
        ++test_counter;

        v.pop_back();
        assert(v.empty()); // Test 4
        ++test_counter;

        Vector<String> vs;
        vs.emplace_back("Test");
        assert(vs.back() == "Test"); // Test 5
        ++test_counter;
    }

    // ======================================================
    // 3. Iterator Functionality
    // ======================================================
    {
        Vector<int> v{ 1, 2, 3 };
        auto it = v.begin();
        assert(*it == 1); // Test 6
        ++test_counter;

        ++it;
        assert(*it == 2); // Test 7
        ++test_counter;

        auto end = v.end();
        assert(it != end); // Test 8
        ++test_counter;

        bool caught = false;
        try { v.end()++; }
        catch (...) { caught = true; }
        assert(caught); // Test 9
        ++test_counter;
    }

    // ======================================================
    // 4. Element Access and Modifiers
    // ======================================================
    {
        Vector<String> v{ "A", "B", "C" };
        assert(v.front() == "A" && v.back() == "C"); // Test 10
        ++test_counter;

        v[1] = "X";
        assert(v[1] == "X"); // Test 11
        ++test_counter;

        bool caught = false;
        try { v.at(5); }
        catch (...) { caught = true; }
        assert(caught); // Test 12
        ++test_counter;
    }

    // ======================================================
    // 5. Memory Management
    // ======================================================
    {
        Vector<int> v;
        v.reserve(100);
        assert(v.capacity() == 100 && v.empty()); // Test 13
        ++test_counter;

        v.resize(5, 10);
        assert(v.size() == 5 && v[4] == 10); // Test 14
        ++test_counter;

        v.shrink_to_fit();
        assert(v.capacity() == 5); // Test 15
        ++test_counter;
    }

    // ======================================================
    // 6. Copy/Move Semantics
    // ======================================================
    {
        Vector<int> v1{ 1,2,3 };
        Vector<int> v2 = v1;
        assert(v2.size() == 3 && v2[2] == 3); // Test 16
        ++test_counter;

        Vector<int> v3 = std::move(v1);
        assert(v3.size() == 3 && v1.empty()); // Test 17
        ++test_counter;
    }

    // ======================================================
    // 7. Complex Operations
    // ======================================================
    {
        Vector<int> v{ 1,2,3,4,5 };

        // Erase elements
        auto first = v.begin() + 1;
        auto last = v.begin() + 3;
        v.erase(first, last);
        assert(v.size() == 3 && v[1] == 4); // Test 18
        ++test_counter;

        // Insert element
        v.insert(10, v.begin() + 1);
        assert(v.size() == 4 && v[1] == 10); // Test 19
        ++test_counter;

        // Clear vector
        v.clear();
        assert(v.empty()); // Test 20
        ++test_counter;
    }

    std::cout << "=== All " << test_counter << " vector tests passed! ===\n";
    glob_counter += test_counter;
}


void test_array_class() {
    std::cout << "\n=== Array Class Test ===\n";
    int test_counter = 0;

    // ======================================================
    // 1. Constructors and Basic Properties
    // ======================================================
    {
        Array<int, 5> a1;
        assert(a1.size() == 0 && a1.capacity() == 5); // Test 1
        ++test_counter;

        Array<int, 4> a2(2, 99);
        assert(a2.size() == 2 && a2[0] == 99 && a2[1] == 99); // Test 2
        ++test_counter;

        bool caught = false;
        try { Array<int, 2> a3(5, 1); }
        catch (...) { caught = true; }
        assert(caught); // Test 3
        ++test_counter;
    }

    // ======================================================
    // 2. Push Back and Element Access
    // ======================================================
    {
        Array<int, 3> a;
        a.push_back(10);
        a.push_back(20);
        assert(a.size() == 2 && a[1] == 20); // Test 4
        ++test_counter;

        a[0] = 99;
        assert(a[0] == 99); // Test 5
        ++test_counter;

        bool caught = false;
        try { a[5]; }
        catch (...) { caught = true; }
        assert(caught); // Test 6
        ++test_counter;

        caught = false;
        try { a.push_back(30); a.push_back(40); }
        catch (...) { caught = true; }
        assert(caught); // Test 7
        ++test_counter;
    }

    // ======================================================
    // 3. Front and Back
    // ======================================================
    {
        Array<int, 3> a;
        a.push_back(5);
        a.push_back(7);
        assert(a.front() == 5 && a.back() == 7); // Test 8
        ++test_counter;

        a.push_back(9);
        assert(a.back() == 9); // Test 9
        ++test_counter;

        bool caught = false;
        try {
            Array<int, 2> b;
            b.front();
        }
        catch (...) { caught = true; }
        assert(caught); // Test 10
        ++test_counter;
    }

    // ======================================================
    // 4. Fill and Empty
    // ======================================================
    {
        Array<int, 4> a;
        a.push_back(1);
        a.push_back(2);
        a.fill(8);
        assert(a[0] == 8 && a.size() == 4); // Test 11
        ++test_counter;

        Array<int, 3> b;
        assert(b.empty()); // Test 12
        ++test_counter;

        b.push_back(1);
        assert(!b.empty()); // Test 13
        ++test_counter;
    }

    // ======================================================
    // 5. Iterators Basic
    // ======================================================
    {
        Array<int, 3> a;
        a.push_back(1);
        a.push_back(2);
        a.push_back(3);

        auto it = a.begin();
        assert(*it == 1); // Test 14
        ++test_counter;

        ++it;
        assert(*it == 2); // Test 15
        ++test_counter;

        it++;
        assert(*it == 3); // Test 16
        ++test_counter;
    }

    // ======================================================
    // 6. Iterator Arithmetic and Comparison
    // ======================================================
    {
        Array<int, 4> a;
        for (int i = 0; i < 4; ++i) {
            a.push_back(i + 1);
        }

        auto it = a.begin();
        it += 2;
        assert(*it == 3); // Test 17
        ++test_counter;

        it -= 1;
        assert(*it == 2); // Test 18
        ++test_counter;

        assert((it + 1) == (a.begin() + 2)); // Test 19
        ++test_counter;

        assert((it + 1) != (it)); // Test 20
        ++test_counter;
    }

    // ======================================================
    // 7. Copy Constructor and Assignment
    // ======================================================
    {
        Array<int, 5> a;
        a.push_back(10);
        a.push_back(20);

        Array<int, 5> b = a;
        assert(b.size() == 2 && b[1] == 20); // Test 21
        ++test_counter;

        Array<int, 5> c;
        c = a;
        assert(c[0] == 10 && c.size() == 2); // Test 22
        ++test_counter;
    }

    // ======================================================
    // 8. Move Constructor and Assignment
    // ======================================================
    {
        Array<int, 5> a;
        a.push_back(1);
        a.push_back(2);

        Array<int, 5> b = std::move(a);
        assert(b.size() == 2 && b[1] == 2); // Test 23
        ++test_counter;

        Array<int, 5> c;
        c = std::move(b);
        assert(c.size() == 2 && c[0] == 1); // Test 24
        ++test_counter;
    }

    // ======================================================
    // 9. Erase and Modify
    // ======================================================
    {
        Array<int, 4> a;
        a.push_back(10);
        a.push_back(20);
        a.push_back(30);

        a[1] = 99;
        assert(a[1] == 99); // Test 25
        ++test_counter;

        a.fill(7);
        assert(a[2] == 7); // Test 26
        ++test_counter;
    }

    // ======================================================
    // 10. toString Method
    // ======================================================
    {
        Array<int, 3> a;
        a.push_back(1);
        a.push_back(2);
        a.push_back(3);
        String s = a.toString();
        assert(s == "123"); // Test 27
        ++test_counter;
    }

    // ======================================================
    // 11. Iterator Dereferencing and Arrow Operator
    // ======================================================
    {
        struct Point { int x; };
        Array<Point, 2> arr;
        arr.push_back({ 10 });
        auto it = arr.begin();
        assert(it->x == 10); // Test 28
        ++test_counter;

        assert((*it).x == 10); // Test 29
        ++test_counter;
    }

    // ======================================================
    // 12. End Iterator Position
    // ======================================================
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
        assert(sum == 6); // Test 30
        ++test_counter;
    }

    // ======================================================
    // 13. Iterator Decrement and Comparison
    // ======================================================
    {
        Array<int, 3> a;
        a.push_back(3);
        a.push_back(2);
        a.push_back(1);

        auto it = a.begin() + 2;
        assert(*it == 1); // Test 31
        ++test_counter;

        --it;
        assert(*it == 2); // Test 32
        ++test_counter;
    }

    // ======================================================
    // 14. Capacity & Size Invariants
    // ======================================================
    {
        Array<char, 10> a;
        for (int i = 0; i < 10; ++i) {
            a.push_back('a');
        }
        assert(a.capacity() == 10 && a.size() == 10); // Test 33
        ++test_counter;

        bool caught = false;
        try { a.push_back('x'); }
        catch (...) { caught = true; }
        assert(caught); // Test 34
        ++test_counter;
    }

    // ======================================================
    // 15. Data Pointer Access
    // ======================================================
    {
        Array<int, 2> a;
        a.push_back(1);
        a.push_back(2);
        int* ptr = a.data();
        assert(ptr[0] == 1 && ptr[1] == 2); // Test 35
        ++test_counter;
    }

    // ======================================================
    // 16. Iterator Validity Checking
    // ======================================================
    {
        Array<int, 1> a;
        a.push_back(5);

        auto it = a.end();
        bool caught = false;
        try { *it; }
        catch (...) { caught = true; }
        assert(caught); // Test 36
        ++test_counter;
    }

    // ======================================================
    // 17. Iterator Comparison Operators
    // ======================================================
    {
        Array<int, 3> a;
        a.push_back(10);
        a.push_back(20);
        a.push_back(30);

        auto it1 = a.begin();
        auto it2 = a.begin() + 1;
        assert(it1 != it2); // Test 37
        ++test_counter;

        ++it1;
        assert(it1 == it2); // Test 38
        ++test_counter;
    }

    // ======================================================
    // 18. Push/Pop Logic Testing
    // ======================================================
    {
        Array<int, 3> a;
        a.push_back(42);
        a.push_back(24);
        assert(a.back() == 24); // Test 39
        ++test_counter;

        a[1] = 100;
        assert(a[1] == 100); // Test 40
        ++test_counter;
    }

    // ======================================================
    // 19. Iterator end() - 1 Dereferencing
    // ======================================================
    {
        Array<int, 3> a;
        a.push_back(42);
        a.push_back(100);

        auto it = a.end() - 1;
        assert(*it == 100); // Test 41
        ++test_counter;
    }


    std::cout << "=== All " << test_counter << " Array tests passed! ===\n";
    glob_counter += test_counter;
}


void test_string_class() {
    std::cout << "\n=== String Class Test ===\n";
    int test_counter = 0;

    // ======================================================
    // 1. Constructors and Basic Operations
    // ======================================================
    {
        String s1;
        assert(s1.is_empty() && s1.capacity() == 1); // Test 1
        ++test_counter;

        String s2("Hello");
        assert(s2.size() == 5 && s2[4] == 'o'); // Test 2
        ++test_counter;

        String s3("");
        assert(s3.is_empty() && s3.capacity() == 1); // Test 3
        ++test_counter;

        bool exception = false;
        try { String s4(nullptr); }
        catch (const std::invalid_argument&) { exception = true; }
        assert(exception); // Test 4
        ++test_counter;
    }

    // ======================================================
    // 2. Element Access (at, operator[])
    // ======================================================
    {
        String s("ABCD");
        assert(s.at(0) == 'A' && s[3] == 'D'); // Test 5
        ++test_counter;

        bool exception1 = false;
        try { s.at(5); }
        catch (const std::out_of_range&) { exception1 = true; }
        assert(exception1); // Test 6
        ++test_counter;

        s[1] = 'X';
        assert(s == "AXCD"); // Test 7
        ++test_counter;

        const String& cs = s;
        assert(cs[2] == 'C'); // Test 8
        ++test_counter;
    }

    // ======================================================
    // 3. Modifiers (push_back, pop_back, clear)
    // ======================================================
    {
        String s;
        s.push_back('A');
        assert(s == "A" && s.size() == 1); // Test 9
        ++test_counter;

        for (char c : {'B', 'C', 'D'}) {
            s.push_back(c);
        }
        assert(s == "ABCD"); // Test 10
        ++test_counter;

        s.pop_back();
        assert(s == "ABC"); // Test 11
        ++test_counter;

        s.clear();
        assert(s.is_empty()); // Test 12
        ++test_counter;

        bool exception = false;
        try { s.pop_back(); }
        catch (const std::out_of_range&) { exception = true; }
        assert(exception); // Test 13
        ++test_counter;
    }

    // ======================================================
    // 4. Insert Method
    // ======================================================
    {
        String s("Hello");
        s.insert(5, " World");
        assert(s == "Hello World"); // Test 14
        ++test_counter;

        s.insert(0, "Start: ");
        assert(s == "Start: Hello World"); // Test 15
        ++test_counter;

        s.insert(7, "Inserted ");
        assert(s == "Start: Inserted Hello World"); // Test 16
        ++test_counter;

        String empty;
        empty.insert(0, "Test");
        assert(empty == "Test"); // Test 17
        ++test_counter;

        bool exception = false;
        try { s.insert(100, "Fail"); }
        catch (const std::out_of_range&) { exception = true; }
        assert(exception); // Test 18
        ++test_counter;
    }

    // ======================================================
    // 5. Erase Method
    // ======================================================
    {
        String s1("ABCDEF");
        s1.erase(0, 2);
        assert(s1 == "DEF" && s1.size() == 3); // Test 19
        ++test_counter;

        s1.erase(1, 2);
        assert(s1 == "D" && s1.size() == 1); // Test 20
        ++test_counter;

        s1.erase(0, 0);
        assert(s1 == "" && s1.is_empty()); // Test 21
        ++test_counter;

        bool exception = false;
        try { s1.erase(0, 0); }
        catch (const std::out_of_range&) { exception = true; }
        assert(exception); // Test 22
        ++test_counter;

        String s2("Complete");
        s2.erase(2, 5);
        assert(s2 == "Cote"); // Test 23
        ++test_counter;
    }

    // ======================================================
    // 6. Replace Method
    // ======================================================
    {
        String s("ABCDEF");

        s.replace(0, 2, "XY");
        assert(s == "XYDEF" && s.size() == 5); // Test 24
        ++test_counter;

        s.replace(4, 4, "Z");
        assert(s == "XYDEZ" && s.size() == 5); // Test 25
        ++test_counter;

        s.replace(0, 4, "Hello");
        assert(s == "Hello" && s.size() == 5); // Test 26
        ++test_counter;

        s.replace(0, 3, "");
        assert(s == "o" && s.size() == 1); // Test 27
        ++test_counter;

        bool exception = false;
        try { s.replace(2, 1, "X"); }
        catch (const std::out_of_range&) { exception = true; }
        assert(exception); // Test 28
        ++test_counter;
    }

    // ======================================================
    // 7. Combined Operations
    // ======================================================
    {
        String s("Start");
        s.erase(0, 1);
        assert(s == "art" && s.size() == 3); // Test 29
        ++test_counter;

        s.replace(1, 1, "eplace");
        assert(s == "aeplacet" && s.size() == 8); // Test 30
        ++test_counter;

        s.erase(3, 7);
        assert(s == "aep" && s.size() == 3); // Test 31
        ++test_counter;

        s.insert(3, "END");
        assert(s == "aepEND"); // Test 32
        ++test_counter;
    }

    // ======================================================
    // 8. Capacity Management
    // ======================================================
    {
        String s;
        s.reserve(100);
        assert(s.capacity() >= 100 && s.is_empty()); // Test 33
        ++test_counter;

        s = "Hello";
        s.shrink_to_fit();
        assert(s.capacity() == 6 && s == "Hello"); // Test 34
        ++test_counter;

        s.resize(10, 'X');
        assert(s.size() == 10 && s[9] == 'X'); // Test 35
        ++test_counter;

        s.resize(3, 'Y');
        assert(s.size() == 3 && s == "Hel"); // Test 36
        ++test_counter;
    }

    // ======================================================
    // 9. Move Semantics
    // ======================================================
    {
        String source("MoveMe");
        String dest(std::move(source));
        assert(dest == "MoveMe" && dest.capacity() == 7); // Test 37
        assert(source.is_empty() && source.capacity() == 0); // Test 38
        test_counter += 2;

        String dest2;
        dest2 = std::move(dest);
        assert(dest2 == "MoveMe"); // Test 39
        assert(dest.is_empty()); // Test 40
        test_counter += 2;
    }

    // ======================================================
    // 10. Operators (+, +=, ==, !=)
    // ======================================================
    {
        String s1("Hello");
        s1 += " ";
        assert(s1 == "Hello "); // Test 41
        ++test_counter;

        String s2("World");
        s1 += s2;
        assert(s1 == "Hello World"); // Test 42
        ++test_counter;

        String s3 = s1 + "!";
        assert(s3 == "Hello World!"); // Test 43
        ++test_counter;

        assert(String("A") + "B" == "AB"); // Test 44
        ++test_counter;

        assert(s1 != s3 && String("A") != String("B")); // Test 45
        ++test_counter;

        s1 = "Test";
        s2 = "Test";
        assert(s1 == s2); // Test 46
        ++test_counter;
    }

    // ======================================================
    // 11. Copy Semantics
    // ======================================================
    {
        String orig("Original");
        String copy(orig);
        assert(copy == orig); // Test 47
        assert(copy.capacity() == orig.capacity()); // Test 48
        ++test_counter;

        copy[0] = 'X';
        assert(orig == "Original" && copy == "Xriginal"); // Test 49
        ++test_counter;

        String copy2;
        copy2 = orig;
        assert(copy2 == orig); // Test 50
        ++test_counter;
    }

    // ======================================================
    // 12. Edge Cases & Exceptions
    // ======================================================
    {
        String s;
        s.reserve(0); // Should be no-op
        assert(s.capacity() == 1); // Test 51
        ++test_counter;

        s = "A";
        s.shrink_to_fit();
        assert(s.capacity() == 2); // Test 52
        ++test_counter;

        String empty1, empty2;
        empty1 += empty2;
        assert(empty1.is_empty()); // Test 53
        ++test_counter;

        String s2("AB");
        s2.replace(0, 1, s2); // Self-replacement
        assert(s2 == "AB"); // Test 54
        ++test_counter;
    }

    // ======================================================
   // 13. Iterator Tests
   // ======================================================
    {
        // Basic iteration
        String s("Hello");
        size_t count = 0;
        for (String::Iterator it = s.begin(); it != s.end(); ++it) {
            ++count;
        }
        assert(count == s.size()); // Test 55
        ++test_counter;

        // Dereference and modification
        String::Iterator it = s.begin();
        *it = 'J';
        assert(s == "Jello"); // Test 56
        ++test_counter;

        // Value access
        it = s.begin() + 1;
        assert(*it == 'e'); // Test 57
        ++test_counter;

        // Increment/Decrement
        ++it;
        assert(*it == 'l'); // Test 58
        ++test_counter;
        it--;
        assert(*it == 'e'); // Test 59
        ++test_counter;

        // Arithmetic operations
        String::Iterator it2 = s.begin() + 3;
        assert(*(it2) == 'l'); // Test 60
        ++test_counter;
        assert(*(it2 + 1) == 'o'); // Test 61
        ++test_counter;

        // Comparison
        assert(it < it2); // Test 62
        ++test_counter;
        assert(!(it >= it2)); // Test 63
        ++test_counter;

        // Bounds checking
        bool exception = false;
        try {
            String::Iterator end_it = s.end();
            *end_it;
        }
        catch (const std::out_of_range&) {
            exception = true;
        }
        assert(exception); // Test 64
        ++test_counter;

        // Empty string iteration
        String empty;
        assert(empty.begin() == empty.end()); // Test 65
        ++test_counter;

        // Reverse iteration
        String rev;
        for (String::Iterator rit = s.end() - 1; rit >= s.begin(); --rit) {
            rev.push_back(*rit);
        }
        assert(rev == "olleJ"); // Test 66
        ++test_counter;

        // Partial range
        String part;
        for (String::Iterator pit = s.begin() + 1; pit < s.end() - 1; ++pit) {
            part.push_back(*pit);
        }
        assert(part == "ell"); // Test 67
        ++test_counter;

        // Iterator with replace/insert
        it = s.begin() + 4;
        s.replace(4, 4, "y!");
        it = s.end() - 1;
        assert(*it == '!'); // Test 68 (проверка валидности после изменения)
        ++test_counter;
    }

    std::cout << "=== All " << test_counter << " string tests passed! ===\n";
    glob_counter += test_counter;
}


void test_stack_class() {
    std::cout << "\n=== Stack Class Test ===\n";
    int test_counter = 0;

    // ======================================================
    // 1. Stack<int>: Basic Operations
    // ======================================================
    {
        Stack<int> s;
        assert(s.empty() == true);                     // Test 1
        ++test_counter;

        s.push(10);
        assert(!s.empty() && s.top() == 10);   // Test 2
        ++test_counter;

        s.push(20);
        assert(s.top() == 20);                    // Test 3
        ++test_counter;

        s.pop();
        assert(s.top() == 10);                    // Test 4
        ++test_counter;
    }

    // ======================================================
    // 2. Stack<int>: Initializer List, Copy & Move
    // ======================================================
    {
        Stack<int> s1 = { 1, 2, 3 };
        assert(s1.top() == 3);                    // Test 5
        ++test_counter;

        Stack<int> s2(s1); // Copy
        assert(s2.top() == 3);                    // Test 6
        s1.pop();
        assert(s1.top() != s2.top());             // Test 7
        ++test_counter += 2;

        Stack<int> s3(std::move(s2)); // Move
        assert(s3.top() == 3);                    // Test 8
        assert(s2.empty());                    // Test 9
        test_counter += 2;
    }

    // ======================================================
    // 3. Stack<int>: Assignment
    // ======================================================
    {
        Stack<int> s1 = { 100, 200 };
        Stack<int> s2;
        s2 = s1;

        assert(s2.top() == 200);                  // Test 10
        s1.pop();
        assert(s1.top() != s2.top());             // Test 11
        test_counter += 2;

        Stack<int> s3;
        s3 = std::move(s2);
        assert(s3.top() == 200);                  // Test 12
        assert(s2.empty());                    // Test 13
        test_counter += 2;
    }

    // ======================================================
    // 4. Stack<int>: Exceptions
    // ======================================================
    {
        Stack<int> s;
        bool caught = false;
        try { s.top(); }
        catch (...) { caught = true; }
        assert(caught);                           // Test 14

        caught = false;
        try { s.pop(); }
        catch (...) { caught = true; }
        assert(caught);                           // Test 15
        test_counter += 2;
    }

    // ======================================================
    // 5. Stack<std::string>: Basic & Edge Cases
    // ======================================================
    {
        Stack<String> s;
        s.push("Hello");
        s.push("World");
        assert(s.top() == "World");               // Test 16
        ++test_counter;

        s.pop();
        assert(s.top() == "Hello");               // Test 17
        ++test_counter;

        Stack<String> s2 = { "A", "B", "C" };
        assert(s2.top() == "C");                  // Test 18
        ++test_counter;

        Stack<String> s3(s2); // Copy
        s2.pop();
        assert(s3.top() == "C");                  // Test 19
        ++test_counter;

        Stack<String> s4;
        s4 = std::move(s3);
        assert(s4.top() == "C");                  // Test 20
        assert(s3.empty());                    // Test 21
        test_counter += 2;

        s4.clear();
        assert(s4.empty());                    // Test 22
        ++test_counter;

        bool caught = false;
        try { s4.top(); }
        catch (...) { caught = true; }
        assert(caught);                           // Test 23
        ++test_counter;
    }

    std::cout << "=== All " << test_counter << " stack tests passed! ===\n";
    glob_counter += test_counter;
}


void test_deque_class() {
    std::cout << "\n=== Deque Class Test ===\n";
    int test_counter = 0;

    // ====================== CONSTRUCTORS & BASIC OPERATIONS ======================
    {
        //Default constructor
        Deque<String> d1;
        assert(d1.empty());
        assert(d1.size() == 0);
        assert(d1.max_size() >= 1);
        test_counter += 3;

        //Initial capacity
        Deque<std::string> d2(15);
        assert(d2.empty());
        assert(d2.max_size() == 15);
        test_counter += 2;

        //Initializer list constructor
        Deque<std::string> d3 = { "A", "B", "C" };
        assert(d3.size() == 3);
        assert(d3.front() == "A");
        assert(d3.back() == "C");
        test_counter += 3;

        //Push back/front
        Deque<std::string> d4;
        d4.push_back("X");
        d4.push_front("Y");
        assert(d4.size() == 2);
        assert(d4.front() == "Y");
        assert(d4.back() == "X");
        test_counter += 3;

        //Pop back/front
        d4.pop_back();
        assert(d4.size() == 1);
        assert(d4.back() == "Y");
        d4.pop_front();
        assert(d4.empty());
        test_counter += 3;
    }

    // ====================== RING BUFFER BEHAVIOR ======================
    {
        //Wrap-around behavior
        Deque<int> d(3);
        d.push_back(1);
        d.push_back(2);
        d.push_back(3);
        assert(d.max_size() == 3);
        assert(d.size() == 3);

        d.pop_front();
        d.push_back(4);

        assert(d.size() == 3);
        assert(d.front() == 2);
        assert(d.back() == 4);
        test_counter += 5;

        //Front wrap-around
        d.push_front(5);
        assert(d.front() == 5);
        assert(d.back() == 4);
        assert(d.size() == 4);
        assert(d.max_size() > 3);
        test_counter += 4;
    }

    // ====================== ELEMENT ACCESS & ITERATORS ======================
    {
        Deque<String> d = { "A", "B", "C", "D" };

        // Test 8: operator[]
        assert(d[0] == "A");
        assert(d[3] == "D");
        d[1] = "X";
        assert(d[1] == "X");
        ++test_counter;

        //at()
        assert(d.at(2) == "C");
        ++test_counter;

        //Iterator
        auto it = d.begin();
        String result;
        for (; it != d.end(); ++it) {
            result += *it;
        }
        assert(result == "AXCD");
        ++test_counter;

        //Reverse iterator
        String reverse;
        if (!d.empty()) {
            auto rit = d.end();
            do {
                --rit;
                reverse += *rit;
            } while (rit != d.begin());
        }
        assert(reverse == "DCXA");
        ++test_counter;
    }

    // ====================== INSERT & ERASE OPERATIONS ======================
    {
        Deque<std::string> d = { "A", "D" };

        //Insert middle
        auto it = d.begin() + 1;
        d.insert(it, "C");
        assert(d.size() == 3);
        assert(d[1] == "C");
        test_counter += 2;


        //Insert causing reallocation
        size_t old_capacity = d.max_size();
        d.insert(d.begin() + 1, 5, "X");
        assert(d.size() == 8);
        assert(d.max_size() >= old_capacity);
        assert(d[1] == "X");
        test_counter += 3;

        //Erase
        d.erase(d.begin() + 2, d.begin() + 5);
        assert(d.size() == 5);
        assert(d[2] == "X");
        assert(d[3] == "C");
        test_counter += 3;
    }

    // ====================== CAPACITY MANAGEMENT ======================
    {
        Deque<std::string> d;

        //Reserve expansion
        d.reserve(100);
        assert(d.max_size() >= 100);
        ++test_counter;

        //Reserve no-op
        size_t prev_capacity = d.max_size();
        d.reserve(50);
        assert(d.max_size() == prev_capacity);
        ++test_counter;

        //Resize grow
        d.resize(5, "X");
        assert(d.size() == 5);
        for (size_t i = 0; i < 5; ++i) {
            assert(d[i] == "X");
        }
        ++test_counter;

        //Resize shrink
        d.resize(2);
        assert(d.size() == 2);
        assert(d[0] == "X");
        assert(d[1] == "X");
        ++test_counter;
    }

    // ====================== STRESS TESTS ======================
    {
        //Front-heavy workload
        Deque<int> d1;
        for (int i = 0; i < 1000; i++) {
            d1.push_front(i);
        }
        assert(d1.size() == 1000);
        assert(d1.front() == 999);
        assert(d1.back() == 0);
        ++test_counter;

        // Mixed operations
        Deque<int> d2;
        for (int i = 0; i < 500; i++) {
            if (i % 2 == 0) {
                d2.push_front(i);
            }
            else {
                d2.push_back(i);
            }
        }
        assert(d2.size() == 500);
        ++test_counter;

        // Alternating operations
        Deque<int> d3;
        for (int i = 0; i < 1000; i++) {
            if (i % 3 == 0) {
                d3.push_front(i);
            }
            else if (i % 3 == 1) {
                d3.push_back(i);
            }
            else if (d3.size() > 0) {
                d3.pop_front();
            }
        }
        assert(d3.size() > 300);
        ++test_counter;
    }

    // ====================== COMPREHENSIVE VERIFICATION ======================
    {
        // Test 22
        Deque<int> d;
        Vector<int> ref;

        for (int i = 0; i < 200; ++i) {
            int op = i % 6;

            if (op == 0) {
                d.push_front(i);
                ref.insert(i, ref.begin());
            }
            else if (op == 1) {
                d.push_back(i);
                ref.push_back(i);
            }
            else if (op == 2 && !d.empty()) {
                d.pop_front();
                if (!ref.empty()) { ref.erase(ref.begin()); }
            }
            else if (op == 3 && !d.empty()) {
                if (!d.empty()) { d.pop_back(); }
                if (!ref.empty()) { ref.pop_back(); }
            }
            else if (op == 4 && !d.empty()) {
                size_t pos = rand() % d.size();
                d.insert(d.begin() + pos, i);
                ref.insert(i, ref.begin() + pos);
            }
            else if (op == 5 && !d.empty()) {
                size_t pos = rand() % d.size();
                d.erase(d.begin() + pos);
                ref.erase(ref.begin() + pos);
            }

            assert(d.size() == ref.size());
            auto it = d.begin();
            for (size_t j = 0; j < ref.size(); ++j) {
                assert(*it == ref[j]);
                ++it;
            }
        }
        ++test_counter;
    }

    // ====================== ADDITIONAL TESTS ======================
    {
        // Test 23: Insert at front when buffer is full (should trigger reallocation)
        Deque<int> d(3);
        d.push_back(1);
        d.push_back(2);
        d.push_back(3);
        d.push_front(0);  // Should trigger reallocation
        assert(d.size() == 4);
        assert(d.front() == 0);
        assert(d.back() == 3);
        test_counter += 3;

        // Test 24: Erase from middle then insert at new position
        d.erase(d.begin() + 2);
        assert(d.size() == 3);
        d.insert(d.begin() + 1, 10);
        assert(d.size() == 4);
        assert(d[0] == 0);
        assert(d[1] == 10);
        assert(d[2] == 1);
        test_counter += 5;

        // Test 25: Insert at back when front is full (ring buffer behavior)
        Deque<int> d2(5);
        d2.push_front(1);
        d2.push_front(2);
        d2.push_front(3);
        d2.push_back(4);
        d2.push_back(5);
        assert(d2.size() == 5);
        assert(d2[0] == 3);
        assert(d2[4] == 5);
        test_counter += 3;

        // Test 26: Remove from both ends
        d2.pop_front();
        d2.pop_back();
        assert(d2.size() == 3);
        assert(d2.front() == 2);
        assert(d2.back() == 4);
        test_counter += 3;

        // Test 27: Insert into empty deque using iterator
        Deque<std::string> d3;
        d3.insert(d3.begin(), "A");
        assert(d3.size() == 1);
        assert(d3.front() == "A");
        test_counter += 2;

        // Test 28: Erase single element deque
        Deque<int> d4 = { 42 };
        d4.erase(d4.begin());
        assert(d4.empty());
        ++test_counter;

        // Test 29: Iterator validity after reallocation
        Deque<int> d5;
        d5.push_back(1);
        auto it = d5.begin();
        for (int i = 0; i < 100; ++i) {
            d5.push_back(i);
        }
        try {
            *it == 1;  // Iterator should not remain valid
        }
        catch (...) {
            assert(true);
        }
        ++test_counter;

        // Test 30: Iterator arithmetic operations
        Deque<int> d6 = { 10, 20, 30, 40, 50 };
        auto it1 = d6.begin();
        auto it2 = it1 + 3;
        assert(it2 - it1 == 3);
        assert(*it1 == 10);
        assert(*it2 == 40);
        it1 += 2;
        assert(*it1 == 30);
        test_counter += 4;

        // Test 31: Attempt to remove from empty deque
        Deque<int> d7;
        bool exception_caught = false;
        try { d7.pop_back(); }
        catch (const std::out_of_range&) { exception_caught = true; }
        assert(exception_caught);
        ++test_counter;

        // Test 32: Move constructor functionality
        Deque<int> d8;
        d8.push_back(1);
        d8.push_back(2);
        Deque<int> d9 = std::move(d8);
        assert(d9.size() == 2);
        assert(d8.empty());
        test_counter += 2;
    }

    std::cout << "=== All " << test_counter << " deque tests passed! ===\n";
    glob_counter += test_counter;
}


void test_queue_class() {
    std::cout << "\n=== Queue Class Test ===\n";
    int test_counter = 0;

    // ======================================================
    // 1. Basic Operations
    // ======================================================
    {
        Queue<String> q;
        assert(q.empty());                     // Test 1
        ++test_counter;

        q.push("A");
        assert(!q.empty());                    // Test 2
        assert(q.size() == 1);                 // Test 3
        assert(q.front() == "A");              // Test 4
        assert(q.back() == "A");               // Test 5
        test_counter += 4;

        q.push("B");
        assert(q.size() == 2);                 // Test 6
        assert(q.front() == "A");              // Test 7
        assert(q.back() == "B");               // Test 8
        test_counter += 3;

        q.pop();
        assert(q.size() == 1);                 // Test 9
        assert(q.front() == "B");              // Test 10
        assert(q.back() == "B");               // Test 11
        test_counter += 3;

        q.pop();
        assert(q.empty());                     // Test 12
        ++test_counter;
    }

    // ======================================================
    // 2. Initializer List
    // ======================================================
    {
        Queue<String> q = { "One", "Two", "Three" };
        assert(q.size() == 3);                 // Test 13
        assert(q.front() == "One");            // Test 14
        assert(q.back() == "Three");           // Test 15
        test_counter += 3;

        q.pop();
        assert(q.front() == "Two");            // Test 16
        ++test_counter;
    }

    // ======================================================
    // 3. Copy Semantics
    // ======================================================
    {
        Queue<String> q1;
        q1.push("X");
        q1.push("Y");

        // Copy constructor
        Queue<String> q2(q1);
        assert(q2.size() == 2);                // Test 17
        assert(q2.front() == "X");             // Test 18
        assert(q2.back() == "Y");              // Test 19
        test_counter += 3;

        // Modify original
        q1.pop();
        assert(q1.front() == "Y");             // Test 20
        assert(q2.front() == "X");             // Test 21
        test_counter += 2;

        // Copy assignment
        Queue<String> q3;
        q3 = q2;
        assert(q3.size() == 2);                // Test 22
        assert(q3.front() == "X");             // Test 23
        test_counter += 2;

        // Self-assignment
        q3 = q3;
        assert(q3.size() == 2);                // Test 24
        assert(q3.front() == "X");             // Test 25
        test_counter += 2;
    }

    // ======================================================
    // 4. Move Semantics
    // ======================================================
    {
        // Move constructor
        Queue<String> q1;
        q1.push("Move");

        Queue<String> q2(std::move(q1));
        assert(q2.size() == 1);                // Test 26
        assert(q2.front() == "Move");          // Test 27
        assert(q1.empty());                    // Test 28
        test_counter += 3;

        // Move assignment
        Queue<String> q3;
        q3 = std::move(q2);
        assert(q3.size() == 1);                // Test 29
        assert(q3.front() == "Move");          // Test 30
        assert(q2.empty());                    // Test 31
        test_counter += 3;

        // Move self-assignment
        q3 = std::move(q3);
        assert(q3.size() == 1);                // Test 32
        assert(q3.front() == "Move");          // Test 33
        test_counter += 2;
    }

    // ======================================================
    // 5. Capacity and Reservation
    // ======================================================
    {
        Queue<std::string> q;
        assert(q.size() == 0);                 // Test 34
        ++test_counter;

        // Test initial capacity
        for (int i = 0; i < 10; ++i) {
            q.push(std::to_string(i));
        }
        assert(q.size() == 10);                // Test 35
        assert(q.front() == "0");              // Test 36
        test_counter += 2;

        // Trigger reallocation
        q.push("10");
        assert(q.size() == 11);                // Test 37
        assert(q.back() == "10");              // Test 38
        test_counter += 2;

        // Manual reservation
        Queue<std::string> q2;
        q2.reserve(100);
        for (int i = 0; i < 100; ++i) {
            q2.push(std::to_string(i));
        }
        assert(q2.size() == 100);              // Test 39
        assert(q2.front() == "0");             // Test 40
        assert(q2.back() == "99");             // Test 41
        test_counter += 3;

        // Reserve smaller than current
        size_t prev_capacity = q2.size();
        q2.reserve(50);
        assert(q2.size() == 100);              // Test 42
        test_counter += 1;
    }

    // ======================================================
    // 6. Exception Handling
    // ======================================================
    {
        Queue<String> q;
        bool caught = false;

        // front() on empty
        try { q.front(); }
        catch (const std::out_of_range& e) {
            caught = true;
        }
        assert(caught);                        // Test 43
        ++test_counter;

        // back() on empty
        caught = false;
        try { q.back(); }
        catch (const std::out_of_range& e) {
            caught = true;
        }
        assert(caught);                        // Test 44
        ++test_counter;

        // pop() on empty
        caught = false;
        try { q.pop(); }
        catch (const std::out_of_range& e) {
            caught = true;
        }
        assert(caught);                        // Test 45
        ++test_counter;
    }

    // ======================================================
    // 7. Complex Operations and FIFO Property
    // ======================================================
    {
        Queue<std::string> q;
        const int N = 1000;

        // Fill the queue
        for (int i = 0; i < N; ++i) {
            q.push(std::to_string(i));
        }
        assert(q.size() == N);                 // Test 46
        ++test_counter;

        // Verify FIFO order
        for (int i = 0; i < N; ++i) {
            assert(q.front() == std::to_string(i));  // Test 47
            q.pop();
        }
        test_counter += 1;

        // Interleaved push/pop using only queues
        Queue<std::string> ref_queue;  // Reference queue for expected state
        int push_count = 0;

        for (int i = 0; i < 100; ++i) {
            if (i % 3 == 0 && !q.empty()) {
                // Remove from both queues
                q.pop();
                ref_queue.pop();
            }

            std::string val = "Val" + std::to_string(i);
            q.push(val);
            ref_queue.push(val);
            push_count++;

            // Verify sizes match
            assert(q.size() == ref_queue.size());  // Test 48

            // Verify front matches reference
            assert(q.front() == ref_queue.front());  // Test 49

            // Verify back matches reference
            assert(q.back() == ref_queue.back());    // Test 50
        }
        test_counter += 3;

        // Verify final state by comparing with reference queue
        assert(q.size() == push_count - (100 / 3));  // Test 51
        ++test_counter;

        // Verify full content
        while (!ref_queue.empty()) {
            assert(q.front() == ref_queue.front());  // Test 52
            q.pop();
            ref_queue.pop();
        }
        test_counter += 1;
    }
    // ======================================================
    // 8. Comparison Operators
    // ======================================================
    {
        Queue<String> q1 = { "A", "B", "C" };
        Queue<String> q2 = { "A", "B", "C" };
        Queue<String> q3 = { "X", "Y", "Z" };
        Queue<String> q4 = { "A", "B" };

        // Equality
        assert(q1 == q2);                      // Test 52
        ++test_counter;

        // Inequality
        assert(q1 != q3);                      // Test 53
        assert(q1 != q4);                      // Test 54
        test_counter += 2;

        // Empty queues
        Queue<String> q5;
        Queue<String> q6;
        assert(q5 == q6);                      // Test 55
        ++test_counter;

        // Modified copy
        q2.pop();
        assert(q1 != q2);                      // Test 56
        ++test_counter;
    }

    // ======================================================
    // 9. String Edge Cases
    // ======================================================
    {
        // Empty strings
        Queue<std::string> q1;
        q1.push("");
        q1.push("");
        assert(q1.size() == 2);                // Test 57
        assert(q1.front() == "");              // Test 58
        assert(q1.back() == "");               // Test 59
        test_counter += 3;

        q1.pop();
        assert(q1.front() == "");              // Test 60
        ++test_counter;

        // Long strings
        std::string long_str(1000, 'X');
        Queue<std::string> q2;
        q2.push(long_str);
        assert(q2.front() == long_str);        // Test 61
        ++test_counter;

        // Mixed content
        Queue<std::string> q3;
        q3.push("123");
        q3.push("");
        q3.push(" ");
        q3.push("ABC");

        assert(q3.front() == "123");           // Test 62
        q3.pop();
        assert(q3.front() == "");              // Test 63
        q3.pop();
        assert(q3.front() == " ");             // Test 64
        q3.pop();
        assert(q3.front() == "ABC");           // Test 65
        test_counter += 4;
    }

    // ======================================================
    // 10. Stress Test
    // ======================================================
    {
        Queue<std::string> q;
        const int N = 10000;

        for (int i = 0; i < N; ++i) {
            q.push(std::to_string(i));
        }
        assert(q.size() == N);                 // Test 66
        ++test_counter;

        for (int i = 0; i < N; ++i) {
            assert(q.front() == std::to_string(i));  // Test 67
            q.pop();
        }
        test_counter += 1;

        assert(q.empty());                     // Test 68
        ++test_counter;
    }

    std::cout << "=== All " << test_counter << " queue tests passed! ===\n";
    glob_counter += test_counter;
}


void test_list_class() {
    std::cout << "\n=== List Class Test ===";
    int test_counter = 0;

    // ======================================================
    // 1. Constructors and basic operations (Tests 1-20)
    // ======================================================
    {
        // Tests for std::string
        List<String> str_list1;
        assert(str_list1.empty());                     // Test 1
        assert(str_list1.size() == 0);                // Test 2
        test_counter += 2;

        List<String> str_list2(5, "A");
        assert(str_list2.size() == 5);                // Test 3
        assert(str_list2[0] == "A");                  // Test 4
        assert(str_list2[4] == "A");                  // Test 5
        test_counter += 3;

        List<std::string> str_list3{ "A", "B", "C" };
        assert(str_list3.size() == 3);                // Test 6
        assert(str_list3[1] == "B");                  // Test 7
        test_counter += 2;

        // Tests for int
        List<int> int_list1;
        assert(int_list1.empty());                    // Test 8
        test_counter += 1;

        List<int> int_list2(10, 42);
        assert(int_list2.size() == 10);               // Test 9
        assert(int_list2[9] == 42);                  // Test 10
        test_counter += 2;

        List<int> int_list3{ 1, 2, 3, 4, 5 };
        assert(int_list3.size() == 5);                // Test 11
        assert(int_list3[0] == 1);                    // Test 12
        assert(int_list3[4] == 5);                    // Test 13
        test_counter += 3;

        // Copy verification
        List<std::string> str_list4 = str_list3;
        assert(str_list4.size() == 3);                // Test 14
        assert(str_list4[2] == "C");                  // Test 15
        test_counter += 2;

        List<int> int_list4 = int_list3;
        assert(int_list4.size() == 5);                // Test 16
        assert(int_list4[3] == 4);                    // Test 17
        test_counter += 2;

        // Move verification
        List<std::string> str_list5 = std::move(str_list4);
        assert(str_list5.size() == 3);                // Test 18
        assert(str_list4.empty());                    // Test 19
        test_counter += 2;

        List<int> int_list5 = std::move(int_list4);
        assert(int_list5.size() == 5);               // Test 20
        assert(int_list4.empty());                    // Test 21
        test_counter += 2;
    }

    // ======================================================
    // 2. Element addition operations (Tests 22-40)
    // ======================================================
    {
        // Tests for std::string
        List<String> str_list;
        str_list.push_back("A");
        assert(str_list.size() == 1);                 // Test 22
        assert(str_list[0] == "A");                   // Test 23
        test_counter += 2;

        str_list.push_front("B");
        assert(str_list.size() == 2);                 // Test 24
        assert(str_list[0] == "B");                   // Test 25
        test_counter += 2;

        str_list.push_back(std::move("C"));
        assert(str_list.size() == 3);                 // Test 26
        assert(str_list[2] == "C");                   // Test 27
        test_counter += 2;

        // Tests for int
        List<int> int_list;
        int_list.push_back(10);
        assert(int_list.size() == 1);                // Test 28
        assert(int_list[0] == 10);                   // Test 29
        test_counter += 2;

        int_list.push_front(20);
        assert(int_list.size() == 2);                 // Test 30
        assert(int_list[0] == 20);                    // Test 31
        test_counter += 2;

        int_list.push_back(30);
        assert(int_list.size() == 3);                 // Test 32
        assert(int_list[2] == 30);                    // Test 33
        test_counter += 2;

        // Middle insertion for std::string
        List<std::string> str_list2{ "A", "C" };
        auto it = str_list2.begin() + 1;
        str_list2.insert(it, "B");
        assert(str_list2.size() == 3);                // Test 34
        assert(str_list2[1] == "B");                  // Test 35
        test_counter += 2;

        // Middle insertion for int
        List<int> int_list2{ 1, 3 };
        auto it2 = int_list2.begin() + 1;
        int_list2.insert(it2, 2);
        assert(int_list2.size() == 3);                // Test 36
        assert(int_list2[1] == 2);                    // Test 37
        test_counter += 2;

        // Multiple element insertion
        List<int> int_list3{ 1, 5 };
        auto it3 = int_list3.begin() + 1;
        int_list3.insert(it3, 3, 3);
        assert(int_list3.size() == 5);                // Test 38
        assert(int_list3[2] == 3);                   // Test 39
        assert(int_list3[3] == 3);                   // Test 40
        test_counter += 3;
    }

    // ======================================================
    // 3. Element removal operations (Tests 41-60)
    // ======================================================
    {
        // Tests for std::string
        List<std::string> str_list{ "A", "B", "C" };
        str_list.pop_back();
        assert(str_list.size() == 2);                 // Test 41
        assert(str_list[1] == "B");                   // Test 42
        test_counter += 2;

        str_list.pop_front();
        assert(str_list.size() == 1);                 // Test 43
        assert(str_list[0] == "B");                   // Test 44
        test_counter += 2;

        // Tests for int
        List<int> int_list{ 1, 2, 3 };
        int_list.pop_back();
        assert(int_list.size() == 2);                 // Test 45
        assert(int_list[1] == 2);                     // Test 46
        test_counter += 2;

        int_list.pop_front();
        assert(int_list.size() == 1);                 // Test 47
        assert(int_list[0] == 2);                     // Test 48
        test_counter += 2;

        // Iterator-based removal for std::string
        List<std::string> str_list2{ "X", "Y", "Z" };
        auto it = str_list2.begin() + 1;
        it = str_list2.erase(it);
        assert(str_list2.size() == 2);                // Test 49
        assert(*it == "Z");                           // Test 50
        test_counter += 2;

        // Iterator-based removal for int
        List<int> int_list2{ 10, 20, 30 };
        auto it2 = int_list2.begin() + 1;
        it2 = int_list2.erase(it2);
        assert(int_list2.size() == 2);                // Test 51
        assert(*it2 == 30);                           // Test 52
        test_counter += 2;

        // List clearing
        List<int> int_list3{ 1, 2, 3 };
        int_list3.clear();
        assert(int_list3.empty());                    // Test 53
        test_counter += 1;

        // Exceptions on empty list
        List<std::string> empty_list;
        bool exception_thrown = false;
        try { empty_list.pop_back(); }
        catch (...) { exception_thrown = true; }
        assert(exception_thrown);                     // Test 54
        test_counter += 1;

        exception_thrown = false;
        try { empty_list.pop_front(); }
        catch (...) { exception_thrown = true; }
        assert(exception_thrown);                     // Test 55
        test_counter += 1;

        // Removing elements one by one
        List<int> int_list4{ 1, 2, 3 };
        int_list4.pop_back();
        int_list4.pop_back();
        int_list4.pop_back();
        assert(int_list4.empty());                    // Test 56
        test_counter += 1;

        // Removing non-existent iterator
        List<String> str_list3{ "A" };
        auto it3 = str_list3.end();
        exception_thrown = false;
        try { str_list3.erase(it3); }
        catch (...) { exception_thrown = true; }
        assert(exception_thrown);                    // Test 57
        test_counter += 1;

        // Removal followed by addition
        List<int> int_list5{ 1 };
        int_list5.pop_back();
        int_list5.push_back(2);
        assert(int_list5.size() == 1);               // Test 58
        assert(int_list5[0] == 2);                  // Test 59
        test_counter += 2;

        // Multiple removal/addition
        List<std::string> str_list4;
        for (int i = 0; i < 10; i++) {
            str_list4.push_back("X");
            str_list4.pop_back();
        }
        assert(str_list4.empty());                   // Test 60
        test_counter += 1;
    }

    // ======================================================
    // 4. Iterator operations (Tests 61-80)
    // ======================================================
    {
        // Basic iterator operations for std::string
        List<std::string> str_list{ "A", "B", "C" };
        auto it1 = str_list.begin();
        assert(*it1 == "A");                        // Test 61
        ++it1;
        assert(*it1 == "B");                         // Test 62
        test_counter += 2;

        // Basic iterator operations for int
        List<int> int_list{ 1, 2, 3 };
        auto it2 = int_list.begin();
        assert(*it2 == 1);                           // Test 63
        ++it2;
        assert(*it2 == 2);                           // Test 64
        test_counter += 2;

        // List traversal
        auto it3 = str_list.begin();
        it3 += 2;
        assert(*it3 == "C");                         // Test 65
        --it3;
        assert(*it3 == "B");                         // Test 66
        test_counter += 2;

        // Iterator comparison
        auto it4 = int_list.begin();
        auto it5 = int_list.begin();
        assert(it4 == it5);                          // Test 67
        ++it5;
        assert(it4 != it5);                          // Test 68
        test_counter += 2;

        // Constant iterators
        List<String> const_list{ "X", "Y", "Z" };
        auto cit = const_list.begin();
        assert(*cit == "X");                         // Test 69
        test_counter += 1;

        // end() iterator
        auto it6 = str_list.end();
        assert(!it6.is_valid());                     // Test 70
        test_counter += 1;

        // Iterator arithmetic
        List<int> long_list{ 0, 1, 2, 3, 4, 5 };
        auto it7 = long_list.begin() + 3;
        assert(*it7 == 3);                           // Test 71
        it7 = it7 - 2;
        assert(*it7 == 1);                           // Test 72
        test_counter += 2;

        // Iterator invalidation check
        List<std::string> str_list2{ "A", "B", "C" };
        auto it8 = str_list2.begin() + 1;
        str_list2.erase(str_list2.begin());
        assert(*it8 == "B");                         // Test 73
        str_list2.insert(str_list2.begin(), "X");
        assert(*it8 == "B");                         // Test 74
        test_counter += 2;

        // Iterators on empty list
        List<int> empty_list;
        assert(empty_list.begin() == empty_list.end()); // Test 75
        test_counter += 1;

        // Reverse traversal
        List<int> rev_list{ 1, 2, 3 };
        auto rit = rev_list.end() - 1;
        assert(*rit == 3);                           // Test 76
        --rit;
        assert(*rit == 2);                           // Test 77
        test_counter += 2;

        // += and -= operators check
        List<std::string> str_list3{ "A", "B", "C", "D" };
        auto it9 = str_list3.begin();
        it9 += 2;
        assert(*it9 == "C");                        // Test 78
        it9 -= 1;
        assert(*it9 == "B");                        // Test 79
        test_counter += 2;

        // Edge cases for iterators
        List<int> single_list{ 42 };
        auto it10 = single_list.begin();
        ++it10;
        assert(it10 == single_list.end());          // Test 80
        test_counter += 1;
    }

    // ======================================================
    // 5. Assignment operator tests (Tests 81-100)
    // ======================================================
    {
        // Copy assignment for int
        List<int> int_list1{ 1, 2, 3 };
        List<int> int_list2;
        int_list2 = int_list1;
        assert(int_list2.size() == 3);              // Test 81
        assert(int_list2[0] == 1);                 // Test 82
        test_counter += 2;

        // Copy assignment for std::string
        List<String> str_list1{ "A", "B", "C" };
        List<String> str_list2;
        str_list2 = str_list1;
        assert(str_list2.size() == 3);              // Test 83
        assert(str_list2[2] == "C");               // Test 84
        test_counter += 2;

        // Move assignment for int
        List<int> int_list3{ 4, 5, 6 };
        List<int> int_list4;
        int_list4 = std::move(int_list3);
        assert(int_list4.size() == 3);              // Test 85
        assert(int_list3.empty());                  // Test 86
        test_counter += 2;

        // Move assignment for std::string
        List<std::string> str_list3{ "X", "Y", "Z" };
        List<std::string> str_list4;
        str_list4 = std::move(str_list3);
        assert(str_list4.size() == 3);              // Test 87
        assert(str_list3.empty());                  // Test 88
        test_counter += 2;

        // Self-assignment (copy)
        List<int> int_list5{ 7, 8, 9 };
        int_list5 = int_list5;
        assert(int_list5.size() == 3);              // Test 89
        assert(int_list5[1] == 8);                  // Test 90
        test_counter += 2;

        // Self-assignment (move)
        List<std::string> str_list5{ "Self" };
        str_list5 = std::move(str_list5);
        assert(str_list5.size() == 1);              // Test 91
        assert(str_list5[0] == "Self");             // Test 92
        test_counter += 2;

        // Overlapping assignment
        List<int> int_list6{ 10, 20 };
        List<int> int_list7{ 30, 40 };
        int_list6 = int_list7;
        assert(int_list6.size() == 2);              // Test 93
        assert(int_list6[1] == 40);                 // Test 94
        test_counter += 2;

        // Assigning empty list
        List<std::string> empty_list1;
        List<std::string> empty_list2{ "A", "B" };
        empty_list2 = empty_list1;
        assert(empty_list2.empty());                // Test 95
        test_counter += 1;

        // Moving to non-empty list
        List<int> int_list8{ 1, 2 };
        List<int> int_list9{ 3, 4, 5 };
        int_list8 = std::move(int_list9);
        assert(int_list8.size() == 3);              // Test 96
        assert(int_list9.empty());                  // Test 97
        test_counter += 2;
    }

    // ======================================================
    // 6. Additional functionality tests (Tests 98-100)
    // ======================================================
    {
        // clear() method test
        List<int> clear_list{ 1, 2, 3 };
        clear_list.clear();
        assert(clear_list.empty());                 // Test 98
        assert(clear_list.size() == 0);             // Test 99
        test_counter += 2;

        // empty() method test
        List<std::string> empty_test;
        assert(empty_test.empty());                 // Test 100
        test_counter += 1;
    }

    // ======================================================
    // 7. Complex scenario tests (Tests 101-110)
    // ======================================================
    {
        // Combined test: all operations
        List<int> complex_list;
        assert(complex_list.empty());               // Test 101
        test_counter += 1;

        complex_list.push_back(1);
        complex_list.push_front(2);
        assert(complex_list.size() == 2);           // Test 102
        test_counter += 1;

        complex_list.insert(complex_list.begin() + 1, 3);
        assert(complex_list[1] == 3);               // Test 103
        test_counter += 1;

        complex_list.erase(complex_list.begin());
        assert(complex_list[0] == 3);               // Test 104
        test_counter += 1;

        complex_list.reverse();
        assert(complex_list[0] == 1);               // Test 105
        test_counter += 1;

        complex_list.push_back(1);
        complex_list.unique();
        assert(complex_list.size() == 2);           // Test 106
        test_counter += 1;

        List<int> complex_copy = complex_list;
        assert(complex_copy.size() == 2);           // Test 107
        test_counter += 1;

        List<int> complex_move = std::move(complex_copy);
        assert(complex_move.size() == 2);           // Test 108
        assert(complex_copy.empty());               // Test 109
        test_counter += 2;

        complex_move.clear();
        assert(complex_move.empty());               // Test 110
        test_counter += 1;
    }

    std::cout << "\n=== All " << test_counter << " list tests passed! ===\n";
    glob_counter += test_counter;
}


void test_avl_tree_class() {
    std::cout << "\n=== AVL Tree Class Test ===\n";
    int test_counter = 0;

    // ======================================================
    // 1. Basic functionality tests (Tests 1-15)
    // ======================================================
    {
        AVLtree<std::string> tree;

        // Insert and size
        tree.insert("apple");
        tree.insert("banana");
        tree.insert("cherry");
        assert(tree.size() == 3);                  // Test 1
        ++test_counter;

        // Contains
        assert(tree.contains("banana"));           // Test 2
        assert(!tree.contains("mango"));           // Test 3
        test_counter += 2;

        // Height
        tree.insert("date");
        tree.insert("fig");
        assert(tree.height(tree.get_root()) == 3); // Test 4
        ++test_counter;

        // Removal
        tree.remove(tree.find("banana"));
        assert(tree.size() == 4);                  // Test 5
        assert(!tree.contains("banana"));          // Test 6
        test_counter += 2;

        // Copy semantics
        AVLtree<std::string> tree2 = tree;
        assert(tree2.size() == 4);                 // Test 7
        assert(tree2.contains("cherry"));          // Test 8
        test_counter += 2;

        // Move semantics
        AVLtree<std::string> tree3 = std::move(tree2);
        assert(tree3.size() == 4);                 // Test 9
        assert(tree2.size() == 0);                 // Test 10
        test_counter += 2;

        // Case sensitivity
        tree.insert("Apple");
        assert(tree.contains("Apple"));            // Test 11
        test_counter++;
    }

    // ======================================================
    // 2. Iterator tests (Tests 12-20)
    // ======================================================
    {
        AVLtree<int> tree;
        tree.insert(50);
        tree.insert(30);
        tree.insert(70);
        tree.insert(20);
        tree.insert(40);
        tree.insert(60);
        tree.insert(80);

        // Iterator basics
        auto it = tree.begin();
        assert(*it == 20);                         // Test 12
        ++it;
        assert(*it == 30);                         // Test 13
        test_counter += 2;

        // Iterator traversal
        Vector<int> values;
        for (auto iter = tree.begin(); iter != tree.end(); ++iter) {
            values.push_back(*iter);
        }

        // Проверяем конкретную последовательность
        assert(values.size() == 7);                // Test 14
        assert(values[0] == 20);                   // Test 15
        assert(values[1] == 30);                   // Test 16
        assert(values[2] == 40);                   // Test 17
        assert(values[3] == 50);                   // Test 18
        assert(values[4] == 60);                   // Test 19
        assert(values[5] == 70);                   // Test 20
        assert(values[6] == 80);                   // Test 21
        test_counter += 8; // Tests 14-21

        // Iterator invalidation
        auto it2 = tree.begin();
        tree.remove(tree.find(*it2));
        assert(tree.size() == 6);                  // Test 22
        test_counter++;
    }

    // ======================================================
    // 3. Advanced operations (Tests 23-30)
    // ======================================================
    {
        AVLtree<double> tree;

        // Large dataset
        for (int i = 0; i < 100; i++) {
            tree.insert(i / 10.0);
        }
        assert(tree.size() == 100);                // Test 23
        test_counter++;

        // Duplicate handling
        tree.insert(5.0);
        tree.insert(5.0);
        assert(tree.size() == 102);                // Test 24
        test_counter++;

        // Find min/max
        auto minNode = tree.find(0.0);
        auto maxNode = tree.find(9.9);
        assert(minNode != nullptr);                // Test 25
        assert(maxNode != nullptr);                // Test 26
        test_counter += 2;

        // Clear
        tree.clear();
        assert(tree.empty());                      // Test 27
        assert(tree.size() == 0);                  // Test 28
        test_counter += 2;
    }

    // ======================================================
    // 4. Custom type tests (Tests 29-36)
    // ======================================================
    {
        struct Person {
            std::string name;
            int age;

            bool operator<(const Person& other) const {
                return name < other.name || (name == other.name && age < other.age);
            }

            bool operator==(const Person& other) const {
                return name == other.name && age == other.age;
            }
        };

        AVLtree<Person> tree;
        tree.insert({ "Alice", 30 });
        tree.insert({ "Bob", 25 });
        tree.insert({ "Alice", 25 });

        assert(tree.size() == 3);                  // Test 29
        assert(tree.contains({ "Alice", 30 }));      // Test 30
        assert(!tree.contains({ "Alice", 20 }));     // Test 31
        test_counter += 3;

        // Find and remove
        auto node = tree.find({ "Bob", 25 });
        assert(node != nullptr);                   // Test 32
        tree.remove(node);
        assert(tree.size() == 2);                 // Test 33
        test_counter += 2;

        // Iterator order
        auto it = tree.begin();
        assert(it->name == "Alice" && it->age == 25); // Test 34
        ++it;
        assert(it->name == "Alice" && it->age == 30); // Test 35
        test_counter += 2;
    }

    // ======================================================
    // 5. Additional and extended AVL tree tests (Tests 37+)
    // ======================================================
    {
        AVLtree<int> tree;

        // Insert positive and negative values
        tree.insert(0);
        tree.insert(-10);
        tree.insert(10);
        tree.insert(-20);
        tree.insert(20);
        assert(tree.size() == 5);                      // Test 37
        ++test_counter;

        assert(tree.contains(20));                     // Test 38
        assert(tree.contains(-20));                    // Test 39
        test_counter += 2;

        // Remove root via find() + remove()
        auto root = tree.find(0);
        if (root != nullptr) {
            tree.remove(root);
        }
        assert(!tree.contains(0));                     // Test 40
        assert(tree.size() == 4);                      // Test 41
        test_counter += 2;

        // Iterator decrement from end()
        auto it = tree.end();
        bool exception_thrown = false;
        try {
            --it;
        }
        catch (const std::runtime_error&) {
            exception_thrown = true;
        }
        assert(exception_thrown);                      // Test 42
        test_counter++;

        // Clear tree
        tree.clear();
        tree.clear();
        assert(tree.empty());                          // Test 43
        assert(tree.size() == 0);                      // Test 44
        test_counter += 2;

        // Custom comparator (descending)
        AVLtree<int, std::greater<int>> descTree;
        descTree.insert(1);
        descTree.insert(2);
        descTree.insert(3);

        Vector<int> descVals;
        for (auto d : descTree) {
            descVals.push_back(d);
        }
        assert(descVals[0] == 3 && descVals[1] == 2 && descVals[2] == 1); // Test 45
        ++test_counter;

        // Iterator begin() and ++
        auto it2 = descTree.begin();
        assert(*it2 == 3);                             // Test 46
        ++it2;
        assert(*it2 == 2);                             // Test 47
        test_counter += 2;

        // Remove leaf node via find + remove
        auto leaf = descTree.find(1);
        if (leaf != nullptr) {
            descTree.remove(leaf);
        }
        assert(!descTree.contains(1));                 // Test 48
        test_counter++;

        // Remove node with one child via find + remove
        AVLtree<int> t;
        t.insert(5);
        t.insert(3);
        auto oneChild = t.find(5);
        if (oneChild != nullptr) {
            t.remove(oneChild);
        }
        assert(t.size() == 1);                         // Test 49
        assert(t.contains(3));                         // Test 50
        test_counter += 2;

        // Remove node with two children via find + remove
        t.insert(7);
        t.insert(6);
        t.insert(8);
        auto twoChildren = t.find(7);
        if (twoChildren != nullptr) {
            t.remove(twoChildren);
        }
        assert(!t.contains(7));                        // Test 51
        assert(t.contains(6));                         // Test 52
        assert(t.contains(8));                         // Test 53
        test_counter += 3;

        // Test findMin and findMax using public API
        assert(t.findMin(t.get_root())->data == 3);    // Test 54
        assert(t.findMax(t.get_root())->data == 8);    // Test 55
        test_counter += 2;

        // Test height() — simulate by inserting known structure
        AVLtree<int> h;
        h.insert(10);
        h.insert(5);
        h.insert(15);
        h.insert(3);
        h.insert(7);
        size_t height = h.height(h.get_root());
        assert(height == 3);                           // Test 56
        ++test_counter;

        // Re-insert after clear
        h.clear();
        assert(h.empty());                             // Test 57
        h.insert(100);
        assert(h.size() == 1 && h.contains(100));      // Test 58
        ++test_counter;

        // Iterator loop
        h.insert(50);
        h.insert(150);
        Vector<int> inorder;
        for (auto v : h) { inorder.push_back(v); }
        assert((inorder[0] == 50 && inorder[1] == 100 && inorder[2] == 150)); // Test 59
        ++test_counter;

        // Check behavior of end()
        auto eit = h.end();
        auto bit = h.begin();
        assert(bit != eit);                            // Test 60
        ++test_counter;

        // Multiple clears
        h.clear();
        h.clear();
        assert(h.empty());                             // Test 61
        ++test_counter;

        // Duplicate insertion should not increase size
        AVLtree<int> d;
        d.insert(1);
        d.insert(1);
        assert(d.size() == 2);                         // Test 62
        ++test_counter;

        // const correctness (if applicable)
        AVLtree<int>& cref = d;
        assert(cref.contains(1));                      // Test 63
        ++test_counter;

        // Range-based iteration on const tree
        Vector<int> vals2;
        for (auto x : cref) {
            vals2.push_back(x);
        }
        assert(vals2.size() == 2 && vals2[0] == 1);    // Test 64
        ++test_counter;
    }

    std::cout << "=== All " << test_counter << " AVL tree tests passed! ===\n";
    glob_counter += test_counter;
}



void start_all_tests() {
    test_vector_class();
    test_array_class();
    test_string_class();
    test_stack_class();
    test_deque_class();
    test_queue_class();
    test_list_class();
    test_avl_tree_class();
    std::cout << "\n\n=== " << glob_counter << " tests passed! ===" << std::endl;
}


int main() {
    start_all_tests();
    return 0;
}
