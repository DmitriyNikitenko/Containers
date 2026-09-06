#include "../../../containers/Hash/HashSet.hpp"
#include "../containersTests.hpp"


void test_HashSet(int& glob_counter) {
    std::cout << "\n=== HashSet Class Test ===\n";
    int test_counter = 0;

    // HashSet<int>: Basic Operations
    {
        HashSet<int> set;

        assert(set.empty());
        assert(set.get_element_count() == 0);
        assert(set.get_bucket_count() == 8);
        ++test_counter;

        assert(set.insert(10));
        assert(!set.empty());
        assert(set.get_element_count() == 1);
        assert(set.contains(10));
        test_counter += 3;

        assert(set.insert(20));
        assert(set.contains(20));
        assert(set.get_element_count() == 2);
        test_counter += 3;

        // Duplicate insertion should fail
        assert(!set.insert(10));
        assert(set.get_element_count() == 2);
        test_counter += 2;
    }

    // HashSet<int>: Remove & Contains
    {
        HashSet<int> set;

        set.insert(10);
        set.insert(20);
        set.insert(30);

        assert(set.contains(10));
        assert(set.contains(20));
        assert(set.contains(30));
        test_counter += 3;

        assert(set.remove(20));
        assert(!set.contains(20));
        assert(set.get_element_count() == 2);
        test_counter += 3;

        // Removing a non-existing element should fail
        assert(!set.remove(100));
        assert(set.get_element_count() == 2);
        test_counter += 2;
    }

    // HashSet<int>: Copy Constructor
    {
        HashSet<int> set1;

        set1.insert(1);
        set1.insert(2);
        set1.insert(3);

        HashSet<int> set2(set1);

        assert(set2.get_element_count() == 3);
        assert(set2.contains(1));
        assert(set2.contains(2));
        assert(set2.contains(3));
        test_counter += 4;

        // Modifying the original should not affect the copy
        set1.remove(2);

        assert(!set1.contains(2));
        assert(set2.contains(2));
        test_counter += 2;
    }

    // HashSet<int>: Move Constructor
    {
        HashSet<int> set1;

        set1.insert(100);
        set1.insert(200);
        set1.insert(300);

        HashSet<int> set2(std::move(set1));

        assert(set2.get_element_count() == 3);
        assert(set2.contains(100));
        assert(set2.contains(200));
        assert(set2.contains(300));
        test_counter += 4;

        // Moved-from set should be empty
        assert(set1.empty());
        assert(set1.get_element_count() == 0);
        test_counter += 2;
    }

    // HashSet<int>: Copy Assignment
    {
        HashSet<int> set1;

        set1.insert(10);
        set1.insert(20);
        set1.insert(30);

        HashSet<int> set2;
        set2.insert(999);

        set2 = set1;

        assert(set2.get_element_count() == 3);
        assert(set2.contains(10));
        assert(set2.contains(20));
        assert(set2.contains(30));
        test_counter += 4;

        // The copied set must be independent
        set1.remove(10);

        assert(!set1.contains(10));
        assert(set2.contains(10));
        test_counter += 2;
    }

    // HashSet<int>: Move Assignment
    {
        HashSet<int> set1;

        set1.insert(111);
        set1.insert(222);
        set1.insert(333);

        HashSet<int> set2;
        set2.insert(999);

        set2 = std::move(set1);

        assert(set2.get_element_count() == 3);
        assert(set2.contains(111));
        assert(set2.contains(222));
        assert(set2.contains(333));
        test_counter += 4;

        // Moved-from set should be empty
        assert(set1.empty());
        assert(set1.get_element_count() == 0);
        test_counter += 2;
    }

    // HashSet<int>: Clear
    {
        HashSet<int> set;

        set.insert(1);
        set.insert(2);
        set.insert(3);
        set.insert(4);

        assert(!set.empty());
        assert(set.get_element_count() == 4);
        test_counter += 2;

        set.clear();

        assert(set.empty());
        assert(set.get_element_count() == 0);
        assert(!set.contains(1));
        assert(!set.contains(2));
        assert(!set.contains(3));
        assert(!set.contains(4));
        test_counter += 5;
    }

    // HashSet<int>: Rehashing
    {
        HashSet<int> set;

        assert(set.get_bucket_count() == 8);
        ++test_counter;

        // Inserting 7 elements makes the load factor exceed 0.75
        for (int i = 0; i < 7; ++i) {
            assert(set.insert(i));
        }

        // The number of buckets should double from 8 to 16
        assert(set.get_bucket_count() == 16);
        assert(set.get_element_count() == 7);
        test_counter += 2;

        // All elements must remain accessible after rehashing
        for (int i = 0; i < 7; ++i) {
            assert(set.contains(i));
            ++test_counter;
        }

        // The set must still work after rehashing
        assert(set.insert(100));
        assert(set.contains(100));
        ++test_counter;
        ++test_counter;
    }

    // HashSet<int>: Custom Bucket Count
    {
        HashSet<int> set(32);

        assert(set.get_bucket_count() == 32);
        assert(set.empty());
        test_counter += 2;

        assert(set.insert(42));
        assert(set.contains(42));
        assert(set.get_element_count() == 1);
        test_counter += 3;
    }

    // HashSet<std::string>: Basic & Edge Cases
    {
        HashSet<std::string> set;

        assert(set.empty());
        ++test_counter;

        assert(set.insert("Hello"));
        assert(set.insert("World"));
        assert(set.insert("C++"));

        assert(set.contains("Hello"));
        assert(set.contains("World"));
        assert(set.contains("C++"));
        test_counter += 6;

        // Duplicate string should not be inserted
        assert(!set.insert("Hello"));
        assert(set.get_element_count() == 3);
        test_counter += 2;

        assert(set.remove("World"));
        assert(!set.contains("World"));
        assert(set.get_element_count() == 2);
        test_counter += 3;

        // Copy
        HashSet<std::string> set2(set);

        assert(set2.contains("Hello"));
        assert(set2.contains("C++"));
        assert(!set2.contains("World"));
        test_counter += 3;

        // Move
        HashSet<std::string> set3(std::move(set2));

        assert(set3.contains("Hello"));
        assert(set3.contains("C++"));
        assert(set2.empty());
        test_counter += 3;

        // Clear
        set3.clear();

        assert(set3.empty());
        assert(set3.get_element_count() == 0);
        test_counter += 2;
    }

    std::cout << "=== All " << test_counter << " HashSet tests passed! ===\n";
    glob_counter += test_counter;
}