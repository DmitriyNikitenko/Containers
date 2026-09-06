#include "../../../algorithms/sorting/selectionSort.hpp"
#include "../../../containers/Vector/Vector.hpp"
#include "sortingTests.hpp"

int test_selectionSort(){
    Vector<int> vec = {0, 2 , 6, 5, 12, 25, 32, -125, 36, 0, 1};
    Vector<int> expected = {-125, 0, 0, 1, 2, 5, 6, 12, 25, 32, 36};
    selectionSort(vec);
    if(vec != expected){
        return 1;
    }
    std::cout << "### selectionSort test passed! ###" << std::endl;
    return 0;
}