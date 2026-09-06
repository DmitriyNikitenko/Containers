#include "../../../containers/Tree/AAtree.hpp"
#include "../containersTests.hpp"


void test_AAtree(int& glob_counter) {
    std::cout << "\n=== AAtree Class Test ===\n";
    int test_counter = 0;

    // AAtree<int>: Basic Operations
    {
        AAtree<int> tree;

        assert(tree.empty());
        assert(tree.size() == 0);
        ++test_counter;

        tree.insert(10);

        assert(!tree.empty());
        assert(tree.size() == 1);
        assert(tree.contains(10));
        test_counter += 3;

        tree.insert(5);
        tree.insert(15);
        tree.insert(3);
        tree.insert(7);

        assert(tree.size() == 5);
        assert(tree.contains(3));
        assert(tree.contains(5));
        assert(tree.contains(7));
        assert(tree.contains(10));
        assert(tree.contains(15));
        test_counter += 6;

        // Non-existing element should not be found
        assert(!tree.contains(100));
        assert(tree.find(100) == nullptr);
        test_counter += 2;
    }

    // AAtree<int>: Duplicate Insertion
    {
        AAtree<int> tree;

        tree.insert(10);
        tree.insert(5);
        tree.insert(15);

        assert(tree.size() == 3);
        ++test_counter;

        // Duplicate values should be ignored
        tree.insert(10);
        tree.insert(5);
        tree.insert(15);

        assert(tree.size() == 3);
        assert(tree.contains(10));
        assert(tree.contains(5));
        assert(tree.contains(15));
        test_counter += 4;
    }

    // AAtree<int>: Find, Min & Max
    {
        AAtree<int> tree;

        tree.insert(50);
        tree.insert(20);
        tree.insert(80);
        tree.insert(10);
        tree.insert(30);
        tree.insert(70);
        tree.insert(90);

        assert(tree.find(50) != nullptr);
        assert(tree.find(20) != nullptr);
        assert(tree.find(90) != nullptr);
        assert(tree.find(999) == nullptr);
        test_counter += 4;

        assert(tree.findMin(tree.get_root())->value == 10);
        assert(tree.findMax(tree.get_root())->value == 90);
        test_counter += 2;
    }

    // AAtree<int>: Erase Leaf Node
    {
        AAtree<int> tree;

        tree.insert(10);
        tree.insert(5);
        tree.insert(15);
        tree.insert(3);
        tree.insert(7);

        assert(tree.size() == 5);
        ++test_counter;

        tree.erase(3);

        assert(tree.size() == 4);
        assert(!tree.contains(3));
        assert(tree.contains(5));
        assert(tree.contains(7));
        test_counter += 3;
    }

    // AAtree<int>: Erase Node With One Child
    {
        AAtree<int> tree;

        tree.insert(10);
        tree.insert(5);
        tree.insert(15);
        tree.insert(12);

        assert(tree.size() == 4);
        ++test_counter;

        tree.erase(15);

        assert(tree.size() == 3);
        assert(!tree.contains(15));
        assert(tree.contains(12));
        assert(tree.contains(10));
        assert(tree.contains(5));
        test_counter += 4;
    }

    // AAtree<int>: Erase Node With Two Children
    {
        AAtree<int> tree;

        tree.insert(50);
        tree.insert(30);
        tree.insert(70);
        tree.insert(20);
        tree.insert(40);
        tree.insert(60);
        tree.insert(80);

        assert(tree.size() == 7);
        ++test_counter;

        tree.erase(50);

        assert(tree.size() == 6);
        assert(!tree.contains(50));

        assert(tree.contains(20));
        assert(tree.contains(30));
        assert(tree.contains(40));
        assert(tree.contains(60));
        assert(tree.contains(70));
        assert(tree.contains(80));

        test_counter += 6;
    }

    // AAtree<int>: Erase Non-existing Value
    {
        AAtree<int> tree;

        tree.insert(10);
        tree.insert(20);
        tree.insert(30);

        tree.erase(999);

        assert(tree.size() == 3);
        assert(tree.contains(10));
        assert(tree.contains(20));
        assert(tree.contains(30));
        test_counter += 4;
    }

    // AAtree<int>: Clear
    {
        AAtree<int> tree;

        tree.insert(1);
        tree.insert(2);
        tree.insert(3);
        tree.insert(4);
        tree.insert(5);

        assert(tree.size() == 5);
        assert(!tree.empty());
        test_counter += 2;

        tree.clear();

        assert(tree.empty());
        assert(tree.size() == 0);
        assert(tree.get_root() == nullptr);
        test_counter += 3;
    }

    // AAtree<int>: Initial Constructor
    {
        AAtree<int> tree(5, 42);

        assert(tree.size() == 1);
        assert(!tree.empty());
        assert(tree.contains(42));
        test_counter += 3;

        // All inserted values are duplicates, so the implementation
        // actually keeps only one unique value.
        assert(tree.size() == 1);
        ++test_counter;
    }

    // AAtree<int>: Copy Constructor
    {
        AAtree<int> tree1;

        tree1.insert(10);
        tree1.insert(20);
        tree1.insert(30);

        AAtree<int> tree2(tree1);

        assert(tree2.size() == 3);
        assert(tree2.contains(10));
        assert(tree2.contains(20));
        assert(tree2.contains(30));
        test_counter += 4;

        // The copied tree must be independent
        tree1.erase(20);

        assert(!tree1.contains(20));
        assert(tree2.contains(20));
        test_counter += 2;
    }

    // AAtree<int>: Copy Assignment
    {
        AAtree<int> tree1;

        tree1.insert(10);
        tree1.insert(20);
        tree1.insert(30);

        AAtree<int> tree2;

        tree2.insert(100);
        tree2.insert(200);

        tree2 = tree1;

        assert(tree2.size() == 3);
        assert(tree2.contains(10));
        assert(tree2.contains(20));
        assert(tree2.contains(30));
        test_counter += 4;

        // The copied tree must be independent
        tree1.erase(10);

        assert(!tree1.contains(10));
        assert(tree2.contains(10));
        test_counter += 2;
    }

    // AAtree<int>: Move Constructor
    {
        AAtree<int> tree1;

        tree1.insert(10);
        tree1.insert(20);
        tree1.insert(30);

        AAtree<int> tree2(std::move(tree1));

        assert(tree2.size() == 3);
        assert(tree2.contains(10));
        assert(tree2.contains(20));
        assert(tree2.contains(30));
        test_counter += 4;

        // The moved-from tree should be empty
        assert(tree1.empty());
        assert(tree1.size() == 0);
        assert(tree1.get_root() == nullptr);
        test_counter += 3;
    }

    // AAtree<int>: Move Assignment
    {
        AAtree<int> tree1;

        tree1.insert(10);
        tree1.insert(20);
        tree1.insert(30);

        AAtree<int> tree2;

        tree2.insert(100);
        tree2.insert(200);

        tree2 = std::move(tree1);

        assert(tree2.size() == 3);
        assert(tree2.contains(10));
        assert(tree2.contains(20));
        assert(tree2.contains(30));
        test_counter += 4;

        // The moved-from tree should be empty
        assert(tree1.empty());
        assert(tree1.size() == 0);
        assert(tree1.get_root() == nullptr);
        test_counter += 3;
    }

    // AAtree<int>: In-order Iterator
    {
        AAtree<int> tree;

        tree.insert(50);
        tree.insert(20);
        tree.insert(80);
        tree.insert(10);
        tree.insert(30);
        tree.insert(70);
        tree.insert(90);

        int expected[] = {10, 20, 30, 50, 70, 80, 90};
        size_t index = 0;

        for (auto it = tree.begin(); it != tree.end(); ++it) {
            assert(index < 7);
            assert(*it == expected[index]);
            ++index;
            ++test_counter;
        }

        assert(index == 7);
        ++test_counter;
    }

    // AAtree<int>: Iterator Post-increment
    {
        AAtree<int> tree;

        tree.insert(10);
        tree.insert(20);
        tree.insert(30);

        auto it = tree.begin();

        assert(*it == 10);
        ++test_counter;

        auto old = it++;

        assert(*old == 10);
        assert(*it == 20);
        test_counter += 2;

        ++it;

        assert(*it == 30);
        ++test_counter;

        ++it;

        assert(it == tree.end());
        ++test_counter;
    }

    // AAtree<int>: Iterator Arithmetic
    {
        AAtree<int> tree;

        tree.insert(10);
        tree.insert(20);
        tree.insert(30);
        tree.insert(40);
        tree.insert(50);

        auto it = tree.begin();

        it += 2;
        assert(*it == 30);
        ++test_counter;

        auto it2 = tree.begin() + 3;

        assert(*it2 == 40);
        ++test_counter;

        assert(it != it2);
        ++test_counter;
    }

    // AAtree<int>: Iterator Access Operator
    {
        AAtree<int> tree;

        tree.insert(10);
        tree.insert(20);

        auto it = tree.begin();

        assert(*it == 10);
        ++test_counter;

        assert(it.operator->() != nullptr);
        assert(*(it.operator->()) == 10);
        test_counter += 2;
    }

    // AAtree<int>: Invalid Iterator
    {
        AAtree<int> tree;

        auto it = tree.end();

        bool caught = false;

        try {
            *it;
        }
        catch (...) {
            caught = true;
        }

        assert(caught);
        ++test_counter;

        caught = false;

        try {
            it.operator->();
        }
        catch (...) {
            caught = true;
        }

        assert(caught);
        ++test_counter;
    }

    // AAtree<std::string>: Basic Operations
    {
        AAtree<std::string> tree;

        tree.insert("Delta");
        tree.insert("Alpha");
        tree.insert("Charlie");
        tree.insert("Bravo");

        assert(tree.size() == 4);
        assert(tree.contains("Alpha"));
        assert(tree.contains("Bravo"));
        assert(tree.contains("Charlie"));
        assert(tree.contains("Delta"));
        test_counter += 5;

        assert(!tree.contains("Echo"));
        ++test_counter;

        assert(tree.findMin(tree.get_root())->value == "Alpha");
        assert(tree.findMax(tree.get_root())->value == "Delta");
        test_counter += 2;

        tree.erase("Charlie");

        assert(!tree.contains("Charlie"));
        assert(tree.size() == 3);
        test_counter += 2;
    }

    // AAtree<int>: Large Number of Elements
    {
        AAtree<int> tree;

        constexpr int count = 1000;

        for (int i = count; i >= 1; --i) {
            tree.insert(i);
        }

        assert(tree.size() == 1000);
        assert(tree.contains(1));
        assert(tree.contains(500));
        assert(tree.contains(1000));
        test_counter += 4;

        for (int i = 1; i <= count; ++i) {
            assert(tree.contains(i));
        }

        test_counter += count;

        for (int i = 1; i <= count; ++i) {
            tree.erase(i);
        }

        assert(tree.empty());
        assert(tree.size() == 0);
        test_counter += 2;
    }

    std::cout << "=== All " << test_counter
              << " AAtree tests passed! ===\n";

    glob_counter += test_counter;
}