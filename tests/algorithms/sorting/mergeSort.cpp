#include "../../../algorithms/sorting/mergeSort.hpp"
#include "../../../containers/Vector/Vector.hpp"
#include "sortingTests.hpp"

int test_mergeSort(){
    Vector<int> vec = {0, 2 , 6, 5, 12, 25, 32, -125, 36, 0, 1};
    Vector<int> expected = {-125, 0, 0, 1, 2, 5, 6, 12, 25, 32, 36};
    mergeSortR(vec, size_t(0), size_t(vec.size()));
    if(vec != expected){
        return 1;
    }
    mergeSortI(vec);
    if(vec != expected){
        return 2;
    }
    std::cout << "### mergeSort test passed! ###" << std::endl;
    return 0;
}