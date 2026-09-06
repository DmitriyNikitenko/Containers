/*
*  Key Properties:
*    - Time Complexity:
*        * Best Case:    O(n)
*        * Average Case: O(n^2)
*        * Worst Case:   O(n^2)
*
*    - Space Complexity:
*        * O(1) (in-place algorithm)
*
*    - Stability:
*        * Stable 
*
*  Notes:
*    - Bidirectional variant of bubble sort (also known as shaker sort).
*    - Improves over standard bubble sort by moving elements in both directions
*      during each iteration, reducing the number of passes in some cases.
*    - Efficient only for small or nearly sorted datasets.
*    - Performance remains quadratic for large or highly unsorted inputs.
*
*  Educational Note:
*    - This implementation operates directly on Vector<T> for simplicity.
*    - In general-purpose code, sorting algorithms should be implemented
*      using iterators to remain container-agnostic and reusable.
*/
#pragma once
#include <utility>
#include "../../containers/Vector/Vector.hpp"
template<typename T>
void cocktailShakerSort(Vector<T>& vec){
    if (vec.size() < 2){ return; }

    bool swapped = true;
    size_t begin = 0;
    size_t end = vec.size() - 1;

    while(swapped){
        swapped = false;

        // Forward pass
        for(size_t i = begin; i < end; ++i){
            if(vec[i] > vec[i + 1]){
                std::swap(vec[i], vec[i + 1]);
                swapped = true;
            }
        }
        --end;

        if(!swapped){ break; }

        // Backward pass
        for(size_t i = end; i > begin; --i){
            if(vec[i] < vec[i - 1]){
                std::swap(vec[i], vec[i - 1]);
                swapped = true;
            }
        }
        ++begin;
    }
}