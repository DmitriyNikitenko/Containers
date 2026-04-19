/*
*  Key Properties:
*    - Time Complexity:
*        * Best Case:    O(n)
*        * Average Case: O(n^2)
*        * Worst Case:   O(n^2)
*
*    - Space Complexity:
*        * O(1) auxiliary space (in-place algorithm)
*
*    - Stability:
*        * Stable 
*
*  Notes:
*    - Simple and easy to implement, but inefficient for large datasets.
*    - Performs well only on small or nearly sorted sequences.
*    - Early-exit optimization significantly improves best-case performance.
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
void bubleSort(Vector<T>& vec){
    bool swapped = false;
    size_t n = vec.size();

    for(size_t i = 0; i < n; ++i){
        swapped = false;

        for(size_t j = 0; j < n - i - 1; ++j){
            if(vec[j] > vec[j + 1]){
                std::swap(vec[j],vec[j + 1]);
                swapped = true;
            }
        }

        if(!swapped){ break; }
    }
}