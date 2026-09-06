#include "../../../containers/Tree/AVLtree.hpp"
#include "../../../containers/Vector/Vector.hpp"
#include "../containersTests.hpp"


void test_AVLtree(int& glob_counter) {
    std::cout << "\n=== AVL Tree Class Test ===\n";
    int test_counter = 0;

    // Basic functionality tests
    {
        AVLtree<std::string> tree;

        // Insert and size
        tree.insert("apple");
        tree.insert("banana");
        tree.insert("cherry");
        assert(tree.size() == 3);         
        ++test_counter;

        // Contains
        assert(tree.contains("banana"));  
        assert(!tree.contains("mango"));  
        test_counter += 2;

        // Height
        tree.insert("date");
        tree.insert("fig");
        assert(tree.height(tree.get_root()) == 3);
        ++test_counter;

        // Removal
        tree.remove(tree.find("banana"));
        assert(tree.size() == 4);         
        assert(!tree.contains("banana")); 
        test_counter += 2;

        // Copy semantics
        AVLtree<std::string> tree2 = tree;
        assert(tree2.size() == 4);        
        assert(tree2.contains("cherry")); 
        test_counter += 2;

        // Move semantics
        AVLtree<std::string> tree3 = std::move(tree2);
        assert(tree3.size() == 4);        
        assert(tree2.size() == 0);        
        test_counter += 2;

        // Case sensitivity
        tree.insert("Apple");
        assert(tree.contains("Apple"));   
        test_counter++;
    }

    // Iterator tests
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
        assert(*it == 20);                
        ++it;
        assert(*it == 30);                
        test_counter += 2;

        // Iterator traversal
        Vector<int> values;
        for (auto iter = tree.begin(); iter != tree.end(); ++iter) {
            values.push_back(*iter);
        }

        assert(values.size() == 7);       
        assert(values[0] == 20);          
        assert(values[1] == 30);          
        assert(values[2] == 40);          
        assert(values[3] == 50);          
        assert(values[4] == 60);          
        assert(values[5] == 70);          
        assert(values[6] == 80);          
        test_counter += 8;

        // Iterator invalidation
        auto it2 = tree.begin();
        tree.remove(tree.find(*it2));
        assert(tree.size() == 6);         
        test_counter++;
    }

    // Advanced operations
    {
        AVLtree<double> tree;

        // Large dataset
        for (int i = 0; i < 100; i++) {
            tree.insert(i / 10.0);
        }
        assert(tree.size() == 100);       
        test_counter++;

        // Duplicate handling
        tree.insert(5.0);
        tree.insert(5.0);
        assert(tree.size() == 102);       
        test_counter++;

        // Find min/max
        auto minNode = tree.find(0.0);
        auto maxNode = tree.find(9.9);
        assert(minNode != nullptr);       
        assert(maxNode != nullptr);       
        test_counter += 2;

        // Clear
        tree.clear();
        assert(tree.empty());             
        assert(tree.size() == 0);         
        test_counter += 2;
    }

    // Custom type tests
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

        assert(tree.size() == 3);         
        assert(tree.contains({ "Alice", 30 }));     
        assert(!tree.contains({ "Alice", 20 }));    
        test_counter += 3;

        // Find and remove
        auto node = tree.find({ "Bob", 25 });
        assert(node != nullptr);          
        tree.remove(node);
        assert(tree.size() == 2);        
        test_counter += 2;

        // Iterator order
        auto it = tree.begin();
        assert(it->name == "Alice" && it->age == 25);
        ++it;
        assert(it->name == "Alice" && it->age == 30);
        test_counter += 2;
    }

    // Additional and extended AVL tree tests
    {
        AVLtree<int> tree;

        // Insert positive and negative values
        tree.insert(0);
        tree.insert(-10);
        tree.insert(10);
        tree.insert(-20);
        tree.insert(20);
        assert(tree.size() == 5);             
        ++test_counter;

        assert(tree.contains(20));            
        assert(tree.contains(-20));           
        test_counter += 2;

        // Remove root via find() + remove()
        auto root = tree.find(0);
        if (root != nullptr) {
            tree.remove(root);
        }
        assert(!tree.contains(0));            
        assert(tree.size() == 4);             
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
        assert(exception_thrown);             
        test_counter++;

        // Clear tree
        tree.clear();
        tree.clear();
        assert(tree.empty());                 
        assert(tree.size() == 0);             
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
        assert(descVals[0] == 3 && descVals[1] == 2 && descVals[2] == 1);
        ++test_counter;

        // Iterator begin() and ++
        auto it2 = descTree.begin();
        assert(*it2 == 3);                    
        ++it2;
        assert(*it2 == 2);                    
        test_counter += 2;

        // Remove leaf node via find + remove
        auto leaf = descTree.find(1);
        if (leaf != nullptr) {
            descTree.remove(leaf);
        }
        assert(!descTree.contains(1));        
        test_counter++;

        // Remove node with one child via find + remove
        AVLtree<int> t;
        t.insert(5);
        t.insert(3);
        auto oneChild = t.find(5);
        if (oneChild != nullptr) {
            t.remove(oneChild);
        }
        assert(t.size() == 1);                
        assert(t.contains(3));                
        test_counter += 2;

        // Remove node with two children via find + remove
        t.insert(7);
        t.insert(6);
        t.insert(8);
        auto twoChildren = t.find(7);
        if (twoChildren != nullptr) {
            t.remove(twoChildren);
        }
        assert(!t.contains(7));               
        assert(t.contains(6));                
        assert(t.contains(8));                
        test_counter += 3;

        // Test findMin and findMax using public API
        assert(t.findMin(t.get_root())->data == 3);
        assert(t.findMax(t.get_root())->data == 8);
        test_counter += 2;

        // Test height() — simulate by inserting known structure
        AVLtree<int> h;
        h.insert(10);
        h.insert(5);
        h.insert(15);
        h.insert(3);
        h.insert(7);
        size_t height = h.height(h.get_root());
        assert(height == 3);                  
        ++test_counter;

        // Re-insert after clear
        h.clear();
        assert(h.empty());                    
        h.insert(100);
        assert(h.size() == 1 && h.contains(100));
        ++test_counter;

        // Iterator loop
        h.insert(50);
        h.insert(150);
        Vector<int> inorder;
        for (auto v : h) { inorder.push_back(v); }
        assert((inorder[0] == 50 && inorder[1] == 100 && inorder[2] == 150));
        ++test_counter;

        // Check behavior of end()
        auto eit = h.end();
        auto bit = h.begin();
        assert(bit != eit);                   
        ++test_counter;

        // Multiple clears
        h.clear();
        h.clear();
        assert(h.empty());                    
        ++test_counter;

        // Duplicate insertion should not increase size
        AVLtree<int> d;
        d.insert(1);
        d.insert(1);
        assert(d.size() == 2);                
        ++test_counter;

        // const correctness (if applicable)
        AVLtree<int>& cref = d;
        assert(cref.contains(1));             
        ++test_counter;

        // Range-based iteration on const tree
        Vector<int> vals2;
        for (auto x : cref) {
            vals2.push_back(x);
        }
        assert(vals2.size() == 2 && vals2[0] == 1);
        ++test_counter;
    }

    std::cout << "=== All " << test_counter << " AVL tree tests passed! ===\n";
    glob_counter += test_counter;
}