/*
*  Key Properties:
*    - Time Complexity:
*        * Best Case:    O(n^2)
*        * Average Case: O(n^2)
*        * Worst Case:   O(n^2)
*
*    - Space Complexity:
*        * O(1) auxiliary space (in-place algorithm)
*
*    - Stability:
*        * Not stable (relative order of equal elements may change)
*
*  Notes:
*    - Performs a fixed number of comparisons regardless of input order.
*    - Minimizes the number of swaps (at most n swaps).
*    - Inefficient for large datasets compared to O(n log n) algorithms.
*    - Suitable when write operations are expensive and must be minimized.
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
void selectionSort(Vector<T>& vec){
    size_t loc_max;
    size_t n = vec.size();

    for(size_t i = 0; i < n; ++i){
        loc_max = 0;

        for(size_t j = 0; j < n - i; ++j){
            if(vec[j] > vec[loc_max]){
                loc_max = j;
            }
        }

        std::swap(vec[loc_max], vec[n - i - 1]);
    }
}
