#include "../../../algorithms/sorting/quickSort.hpp"
#include "../../../containers/Vector/Vector.hpp"
#include "sortingTests.hpp"

int test_quickSort(){
    Vector<int> vec = {0, 2 , 6, 5, 12, 25, 32, -125, 36, 0, 1};
    Vector<int> expected = {-125, 0, 0, 1, 2, 5, 6, 12, 25, 32, 36};
    quickSortR(vec, 0, vec.size() - 1);
    if(vec != expected){
        return 1;
    }
    quickSortI(vec);
    if(vec != expected){
        return 2;
    }
    std::cout << "### quickSort test passed! ###" << std::endl;
    return 0;
}