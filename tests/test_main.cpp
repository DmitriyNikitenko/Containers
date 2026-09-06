#include <iostream>
#include "algorithms/sorting/sortingTests.hpp"
#include "containers/containersTests.hpp"


void start_all_tests() {
    // ======== Algorithm tests ========
    std::cout << "\n ##### ALGORITHMS ####\n";

    std::cout << " \n### SORTING ###\n";
    //Sorting algorithms
    test_bubbleSort();
    test_gnomeSort();
    test_mergeSort();
    test_quickSort();
    test_selectionSort();
    test_shakerSort();


    // ======== Container tests ========
    std::cout << "\n\n ===== CONTAINERS =====\n";
    int glob_counter = 0;
    // Hash
    test_HashSet(glob_counter);
    // List
    test_ListD(glob_counter);
    // Queue
    test_Queue(glob_counter);
    test_QueueOn2Stack(glob_counter);
    test_QueueOnList(glob_counter);
    // Stack
    test_Stack(glob_counter);
    // String
    test_String(glob_counter);
    // Tree
    test_AAtree(glob_counter);
    test_AVLtree(glob_counter);
    test_FibHeap(glob_counter);
    // Vector
    test_Array(glob_counter);
    test_Vector(glob_counter);


    std::cout << "\n=== " << glob_counter << " tests passed! ===" << std::endl;
}

int main() {
    start_all_tests();
    return 0;
}