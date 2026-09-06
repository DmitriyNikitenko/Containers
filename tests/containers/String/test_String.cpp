#include "../../../containers/String/String.hpp"
#include "../containersTests.hpp"


void test_String(int& glob_counter) {
    std::cout << "\n=== String Class Test ===\n";
    int test_counter = 0;

    // Constructors and Basic Operations
    {
        String s1;
        assert(s1.is_empty() && s1.capacity() == 1);
        ++test_counter;

        String s2("Hello");
        assert(s2.size() == 5 && s2[4] == 'o');
        ++test_counter;

        String s3("");
        assert(s3.is_empty() && s3.capacity() == 1);
        ++test_counter;

        bool exception = false;
        try { String s4(nullptr); }
        catch (const std::invalid_argument&) { exception = true; }
        assert(exception);
        ++test_counter;
    }

    // Element Access (at, operator[])
    {
        String s("ABCD");
        assert(s.at(0) == 'A' && s[3] == 'D');
        ++test_counter;

        bool exception1 = false;
        try { s.at(5); }
        catch (const std::out_of_range&) { exception1 = true; }
        assert(exception1);
        ++test_counter;

        s[1] = 'X';
        assert(s == "AXCD");
        ++test_counter;

        const String& cs = s;
        assert(cs[2] == 'C');
        ++test_counter;
    }

    // Modifiers (push_back, pop_back, clear)
    {
        String s;
        s.push_back('A');
        assert(s == "A" && s.size() == 1);
        ++test_counter;

        for (char c : {'B', 'C', 'D'}) {
            s.push_back(c);
        }
        assert(s == "ABCD");
        ++test_counter;

        s.pop_back();
        assert(s == "ABC");
        ++test_counter;

        s.clear();
        assert(s.is_empty());
        ++test_counter;

        bool exception = false;
        try { s.pop_back(); }
        catch (const std::out_of_range&) { exception = true; }
        assert(exception);
        ++test_counter;
    }

    // Insert Method
    {
        String s("Hello");
        s.insert(5, " World");
        assert(s == "Hello World");
        ++test_counter;

        s.insert(0, "Start: ");
        assert(s == "Start: Hello World");
        ++test_counter;

        s.insert(7, "Inserted ");
        assert(s == "Start: Inserted Hello World");
        ++test_counter;

        String empty;
        empty.insert(0, "Test");
        assert(empty == "Test");
        ++test_counter;

        bool exception = false;
        try { s.insert(100, "Fail"); }
        catch (const std::out_of_range&) { exception = true; }
        assert(exception);
        ++test_counter;
    }

    // Erase Method
    {
        String s1("ABCDEF");
        s1.erase(0, 2);
        assert(s1 == "DEF" && s1.size() == 3);
        ++test_counter;

        s1.erase(1, 2);
        assert(s1 == "D" && s1.size() == 1);
        ++test_counter;

        s1.erase(0, 0);
        assert(s1 == "" && s1.is_empty());
        ++test_counter;

        bool exception = false;
        try { s1.erase(0, 0); }
        catch (const std::out_of_range&) { exception = true; }
        assert(exception);
        ++test_counter;

        String s2("Complete");
        s2.erase(2, 5);
        assert(s2 == "Cote");
        ++test_counter;
    }
 
    // Replace Method
    {
        String s("ABCDEF");

        s.replace(0, 2, "XY");
        assert(s == "XYDEF" && s.size() == 5);
        ++test_counter;

        s.replace(4, 4, "Z");
        assert(s == "XYDEZ" && s.size() == 5);
        ++test_counter;

        s.replace(0, 4, "Hello");
        assert(s == "Hello" && s.size() == 5);
        ++test_counter;

        s.replace(0, 3, "");
        assert(s == "o" && s.size() == 1);
        ++test_counter;

        bool exception = false;
        try { s.replace(2, 1, "X"); }
        catch (const std::out_of_range&) { exception = true; }
        assert(exception);
        ++test_counter;
    }

    // Combined Operations
    {
        String s("Start");
        s.erase(0, 1);
        assert(s == "art" && s.size() == 3);
        ++test_counter;

        s.replace(1, 1, "eplace");
        assert(s == "aeplacet" && s.size() == 8);
        ++test_counter;

        s.erase(3, 7);
        assert(s == "aep" && s.size() == 3);
        ++test_counter;

        s.insert(3, "END");
        assert(s == "aepEND");
        ++test_counter;
    }

    // Capacity Management
    {
        String s;
        s.reserve(100);
        assert(s.capacity() >= 100 && s.is_empty());
        ++test_counter;

        s = "Hello";
        s.shrink_to_fit();
        assert(s.capacity() == 6 && s == "Hello");
        ++test_counter;

        s.resize(10, 'X');
        assert(s.size() == 10 && s[9] == 'X');
        ++test_counter;

        s.resize(3, 'Y');
        assert(s.size() == 3 && s == "Hel");
        ++test_counter;
    }

    // Move Semantics
    {
        String source("MoveMe");
        String dest(std::move(source));
        assert(dest == "MoveMe" && dest.capacity() == 7);
        assert(source.is_empty() && source.capacity() == 0);
        test_counter += 2;

        String dest2;
        dest2 = std::move(dest);
        assert(dest2 == "MoveMe");
        assert(dest.is_empty());
        test_counter += 2;
    }

 
    // Operators (+, +=, ==, !=)
    {
        String s1("Hello");
        s1 += " ";
        assert(s1 == "Hello ");
        ++test_counter;

        String s2("World");
        s1 += s2;
        assert(s1 == "Hello World");
        ++test_counter;

        String s3 = s1 + "!";
        assert(s3 == "Hello World!");
        ++test_counter;

        assert(String("A") + "B" == "AB");
        ++test_counter;

        assert(s1 != s3 && String("A") != String("B"));
        ++test_counter;

        s1 = "Test";
        s2 = "Test";
        assert(s1 == s2);
        ++test_counter;
    }

    // Copy Semantics
    {
        String orig("Original");
        String copy(orig);
        assert(copy == orig);
        assert(copy.capacity() == orig.capacity());
        ++test_counter;

        copy[0] = 'X';
        assert(orig == "Original" && copy == "Xriginal");
        ++test_counter;

        String copy2;
        copy2 = orig;
        assert(copy2 == orig);
        ++test_counter;
    }
 
    // Edge Cases & Exceptions
    {
        String s;
        s.reserve(0); // Should be no-op
        assert(s.capacity() == 1);
        ++test_counter;

        s = "A";
        s.shrink_to_fit();
        assert(s.capacity() == 2);
        ++test_counter;

        String empty1, empty2;
        empty1 += empty2;
        assert(empty1.is_empty());
        ++test_counter;

        String s2("AB");
        s2.replace(0, 1, s2); // Self-replacement
        assert(s2 == "AB");
        ++test_counter;
    }

    // Iterator Tests
    {
        // Basic iteration
        String s("Hello");
        size_t count = 0;
        for (String::Iterator it = s.begin(); it != s.end(); ++it) {
            ++count;
        }
        assert(count == s.size());
        ++test_counter;

        // Dereference and modification
        String::Iterator it = s.begin();
        *it = 'J';
        assert(s == "Jello");
        ++test_counter;

        // Value access
        it = s.begin() + 1;
        assert(*it == 'e');
        ++test_counter;

        // Increment/Decrement
        ++it;
        assert(*it == 'l');
        ++test_counter;
        it--;
        assert(*it == 'e');
        ++test_counter;

        // Arithmetic operations
        String::Iterator it2 = s.begin() + 3;
        assert(*(it2) == 'l');
        ++test_counter;
        assert(*(it2 + 1) == 'o');
        ++test_counter;

        // Comparison
        assert(it < it2);
        ++test_counter;
        assert(!(it >= it2));
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
        assert(exception);
        ++test_counter;

        // Empty string iteration
        String empty;
        assert(empty.begin() == empty.end());
        ++test_counter;

        // Reverse iteration
        String rev;
        for (String::Iterator rit = s.end() - 1; rit >= s.begin(); --rit) {
            rev.push_back(*rit);
        }
        assert(rev == "olleJ");
        ++test_counter;

        // Partial range
        String part;
        for (String::Iterator pit = s.begin() + 1; pit < s.end() - 1; ++pit) {
            part.push_back(*pit);
        }
        assert(part == "ell");
        ++test_counter;

        // Iterator with replace/insert
        it = s.begin() + 4;
        s.replace(4, 4, "y!");
        it = s.end() - 1;
        assert(*it == '!');
        ++test_counter;
    }

    std::cout << "=== All " << test_counter << " string tests passed! ===\n";
    glob_counter += test_counter;
}