#include "../../../containers/List/ListD.hpp"
#include "../../../containers/String/String.hpp"
#include "../containersTests.hpp"


void test_ListD(int& glob_counter) {
    std::cout << "\n=== ListD Class Test ===";
    int test_counter = 0;

    // Constructors and basic operations (Tests 1-20)
    {
        // Tests for std::string
        ListD<String> str_list1;
        assert(str_list1.empty());            
        assert(str_list1.size() == 0);       
        test_counter += 2;

        ListD<String> str_list2(5, "A");
        assert(str_list2.size() == 5);       
        assert(str_list2[0] == "A");         
        assert(str_list2[4] == "A");         
        test_counter += 3;

        ListD<std::string> str_list3{ "A", "B", "C" };
        assert(str_list3.size() == 3);       
        assert(str_list3[1] == "B");         
        test_counter += 2;

        // Tests for int
        ListD<int> int_list1;
        assert(int_list1.empty());           
        test_counter += 1;

        ListD<int> int_list2(10, 42);
        assert(int_list2.size() == 10);      
        assert(int_list2[9] == 42);         
        test_counter += 2;

        ListD<int> int_list3{ 1, 2, 3, 4, 5 };
        assert(int_list3.size() == 5);       
        assert(int_list3[0] == 1);           
        assert(int_list3[4] == 5);           
        test_counter += 3;

        // Copy verification
        ListD<std::string> str_list4 = str_list3;
        assert(str_list4.size() == 3);       
        assert(str_list4[2] == "C");         
        test_counter += 2;

        ListD<int> int_list4 = int_list3;
        assert(int_list4.size() == 5);       
        assert(int_list4[3] == 4);           
        test_counter += 2;

        // Move verification
        ListD<std::string> str_list5 = std::move(str_list4);
        assert(str_list5.size() == 3);       
        assert(str_list4.empty());           
        test_counter += 2;

        ListD<int> int_list5 = std::move(int_list4);
        assert(int_list5.size() == 5);      
        assert(int_list4.empty());           
        test_counter += 2;
    }

    // Element addition operations (Tests 22-40)
    {
        // Tests for std::string
        ListD<String> str_list;
        str_list.push_back("A");
        assert(str_list.size() == 1);        
        assert(str_list[0] == "A");          
        test_counter += 2;

        str_list.push_front("B");
        assert(str_list.size() == 2);        
        assert(str_list[0] == "B");          
        test_counter += 2;

        str_list.push_back(std::move("C"));
        assert(str_list.size() == 3);        
        assert(str_list[2] == "C");          
        test_counter += 2;

        // Tests for int
        ListD<int> int_list;
        int_list.push_back(10);
        assert(int_list.size() == 1);       
        assert(int_list[0] == 10);          
        test_counter += 2;

        int_list.push_front(20);
        assert(int_list.size() == 2);        
        assert(int_list[0] == 20);           
        test_counter += 2;

        int_list.push_back(30);
        assert(int_list.size() == 3);        
        assert(int_list[2] == 30);           
        test_counter += 2;

        // Middle insertion for std::string
        ListD<std::string> str_list2{ "A", "C" };
        auto it = str_list2.begin() + 1;
        str_list2.insert(it, "B");
        assert(str_list2.size() == 3);       
        assert(str_list2[1] == "B");         
        test_counter += 2;

        // Middle insertion for int
        ListD<int> int_list2{ 1, 3 };
        auto it2 = int_list2.begin() + 1;
        int_list2.insert(it2, 2);
        assert(int_list2.size() == 3);       
        assert(int_list2[1] == 2);           
        test_counter += 2;

        // Multiple element insertion
        ListD<int> int_list3{ 1, 5 };
        auto it3 = int_list3.begin() + 1;
        int_list3.insert(it3, 3, 3);
        assert(int_list3.size() == 5);       
        assert(int_list3[2] == 3);          
        assert(int_list3[3] == 3);          
        test_counter += 3;
    }

    // Element removal operations (Tests 41-60)
    {
        // Tests for std::string
        ListD<std::string> str_list{ "A", "B", "C" };
        str_list.pop_back();
        assert(str_list.size() == 2);        
        assert(str_list[1] == "B");          
        test_counter += 2;

        str_list.pop_front();
        assert(str_list.size() == 1);        
        assert(str_list[0] == "B");          
        test_counter += 2;

        // Tests for int
        ListD<int> int_list{ 1, 2, 3 };
        int_list.pop_back();
        assert(int_list.size() == 2);        
        assert(int_list[1] == 2);            
        test_counter += 2;

        int_list.pop_front();
        assert(int_list.size() == 1);        
        assert(int_list[0] == 2);            
        test_counter += 2;

        // Iterator-based removal for std::string
        ListD<std::string> str_list2{ "X", "Y", "Z" };
        auto it = str_list2.begin() + 1;
        it = str_list2.erase(it);
        assert(str_list2.size() == 2);       
        assert(*it == "Z");                  
        test_counter += 2;

        // Iterator-based removal for int
        ListD<int> int_list2{ 10, 20, 30 };
        auto it2 = int_list2.begin() + 1;
        it2 = int_list2.erase(it2);
        assert(int_list2.size() == 2);       
        assert(*it2 == 30);                  
        test_counter += 2;

        // ListD clearing
        ListD<int> int_list3{ 1, 2, 3 };
        int_list3.clear();
        assert(int_list3.empty());           
        test_counter += 1;

        // Exceptions on empty ListD
        ListD<std::string> empty_list;
        bool exception_thrown = false;
        try { empty_list.pop_back(); }
        catch (...) { exception_thrown = true; }
        assert(exception_thrown);            
        test_counter += 1;

        exception_thrown = false;
        try { empty_list.pop_front(); }
        catch (...) { exception_thrown = true; }
        assert(exception_thrown);            
        test_counter += 1;

        // Removing elements one by one
        ListD<int> int_list4{ 1, 2, 3 };
        int_list4.pop_back();
        int_list4.pop_back();
        int_list4.pop_back();
        assert(int_list4.empty());           
        test_counter += 1;

        // Removing non-existent iterator
        ListD<String> str_list3{ "A" };
        auto it3 = str_list3.end();
        exception_thrown = false;
        try { str_list3.erase(it3); }
        catch (...) { exception_thrown = true; }
        assert(exception_thrown);           
        test_counter += 1;

        // Removal followed by addition
        ListD<int> int_list5{ 1 };
        int_list5.pop_back();
        int_list5.push_back(2);
        assert(int_list5.size() == 1);      
        assert(int_list5[0] == 2);         
        test_counter += 2;

        // Multiple removal/addition
        ListD<std::string> str_list4;
        for (int i = 0; i < 10; i++) {
            str_list4.push_back("X");
            str_list4.pop_back();
        }
        assert(str_list4.empty());          
        test_counter += 1;
    }

    // Iterator operations (Tests 61-80)
    {
        // Basic iterator operations for std::string
        ListD<std::string> str_list{ "A", "B", "C" };
        auto it1 = str_list.begin();
        assert(*it1 == "A");               
        ++it1;
        assert(*it1 == "B");                
        test_counter += 2;

        // Basic iterator operations for int
        ListD<int> int_list{ 1, 2, 3 };
        auto it2 = int_list.begin();
        assert(*it2 == 1);                  
        ++it2;
        assert(*it2 == 2);                  
        test_counter += 2;

        // ListD traversal
        auto it3 = str_list.begin();
        it3 += 2;
        assert(*it3 == "C");                
        --it3;
        assert(*it3 == "B");                
        test_counter += 2;

        // Iterator comparison
        auto it4 = int_list.begin();
        auto it5 = int_list.begin();
        assert(it4 == it5);                 
        ++it5;
        assert(it4 != it5);                 
        test_counter += 2;

        // Constant iterators
        ListD<String> const_list{ "X", "Y", "Z" };
        auto cit = const_list.begin();
        assert(*cit == "X");                
        test_counter += 1;

        // end() iterator
        auto it6 = str_list.end();
        assert(!it6.is_valid());            
        test_counter += 1;

        // Iterator arithmetic
        ListD<int> long_list{ 0, 1, 2, 3, 4, 5 };
        auto it7 = long_list.begin() + 3;
        assert(*it7 == 3);                  
        it7 = it7 - 2;
        assert(*it7 == 1);                  
        test_counter += 2;

        // Iterator invalidation check
        ListD<std::string> str_list2{ "A", "B", "C" };
        auto it8 = str_list2.begin() + 1;
        str_list2.erase(str_list2.begin());
        assert(*it8 == "B");                
        str_list2.insert(str_list2.begin(), "X");
        assert(*it8 == "B");                
        test_counter += 2;

        // Iterators on empty list
        ListD<int> empty_list;
        assert(empty_list.begin() == empty_list.end()); // Test 75
        test_counter += 1;

        // Reverse traversal
        ListD<int> rev_list{ 1, 2, 3 };
        auto rit = rev_list.end() - 1;
        assert(*rit == 3);                  
        --rit;
        assert(*rit == 2);                  
        test_counter += 2;

        // += and -= operators check
        ListD<std::string> str_list3{ "A", "B", "C", "D" };
        auto it9 = str_list3.begin();
        it9 += 2;
        assert(*it9 == "C");               
        it9 -= 1;
        assert(*it9 == "B");               
        test_counter += 2;

        // Edge cases for iterators
        ListD<int> single_list{ 42 };
        auto it10 = single_list.begin();
        ++it10;
        assert(it10 == single_list.end()); 
        test_counter += 1;
    }

    // Assignment operator tests (Tests 81-100)
    {
        // Copy assignment for int
        ListD<int> int_list1{ 1, 2, 3 };
        ListD<int> int_list2;
        int_list2 = int_list1;
        assert(int_list2.size() == 3);     
        assert(int_list2[0] == 1);        
        test_counter += 2;

        // Copy assignment for std::string
        ListD<String> str_list1{ "A", "B", "C" };
        ListD<String> str_list2;
        str_list2 = str_list1;
        assert(str_list2.size() == 3);     
        assert(str_list2[2] == "C");      
        test_counter += 2;

        // Move assignment for int
        ListD<int> int_list3{ 4, 5, 6 };
        ListD<int> int_list4;
        int_list4 = std::move(int_list3);
        assert(int_list4.size() == 3);     
        assert(int_list3.empty());         
        test_counter += 2;

        // Move assignment for std::string
        ListD<std::string> str_list3{ "X", "Y", "Z" };
        ListD<std::string> str_list4;
        str_list4 = std::move(str_list3);
        assert(str_list4.size() == 3);     
        assert(str_list3.empty());         
        test_counter += 2;

        // Self-assignment (copy)
        ListD<int> int_list5{ 7, 8, 9 };
        int_list5 = int_list5;
        assert(int_list5.size() == 3);     
        assert(int_list5[1] == 8);         
        test_counter += 2;

        // Self-assignment (move)
        ListD<std::string> str_list5{ "Self" };
        str_list5 = std::move(str_list5);
        assert(str_list5.size() == 1);     
        assert(str_list5[0] == "Self");    
        test_counter += 2;

        // Overlapping assignment
        ListD<int> int_list6{ 10, 20 };
        ListD<int> int_list7{ 30, 40 };
        int_list6 = int_list7;
        assert(int_list6.size() == 2);     
        assert(int_list6[1] == 40);        
        test_counter += 2;

        // Assigning empty list
        ListD<std::string> empty_list1;
        ListD<std::string> empty_list2{ "A", "B" };
        empty_list2 = empty_list1;
        assert(empty_list2.empty());       
        test_counter += 1;

        // Moving to non-empty list
        ListD<int> int_list8{ 1, 2 };
        ListD<int> int_list9{ 3, 4, 5 };
        int_list8 = std::move(int_list9);
        assert(int_list8.size() == 3);     
        assert(int_list9.empty());         
        test_counter += 2;
    }

    // Additional functionality tests (Tests 98-100)
    {
        // clear() method test
        ListD<int> clear_list{ 1, 2, 3 };
        clear_list.clear();
        assert(clear_list.empty());        
        assert(clear_list.size() == 0);    
        test_counter += 2;

        // empty() method test
        ListD<std::string> empty_test;
        assert(empty_test.empty());        
        test_counter += 1;
    }

    // Complex scenario tests (Tests 101-110)
    {
        // Combined test: all operations
        ListD<int> complex_list;
        assert(complex_list.empty());      
        test_counter += 1;

        complex_list.push_back(1);
        complex_list.push_front(2);
        assert(complex_list.size() == 2);  
        test_counter += 1;

        complex_list.insert(complex_list.begin() + 1, 3);
        assert(complex_list[1] == 3);      
        test_counter += 1;

        complex_list.erase(complex_list.begin());
        assert(complex_list[0] == 3);      
        test_counter += 1;

        complex_list.reverse();
        assert(complex_list[0] == 1);      
        test_counter += 1;

        complex_list.push_back(1);
        complex_list.unique();
        assert(complex_list.size() == 2);  
        test_counter += 1;

        ListD<int> complex_copy = complex_list;
        assert(complex_copy.size() == 2);  
        test_counter += 1;

        ListD<int> complex_move = std::move(complex_copy);
        assert(complex_move.size() == 2);  
        assert(complex_copy.empty());      
        test_counter += 2;

        complex_move.clear();
        assert(complex_move.empty());      
        test_counter += 1;
    }

    std::cout << "\n=== All " << test_counter << " ListD tests passed! ===\n";
    glob_counter += test_counter;
}
