/*
 * Selection Sort
 *
 * Repeatedly finds the largest element in the unsorted part
 * and places it at the end of that part.
 *
 * Time complexity:
 *   Best:    O(n^2)
 *   Average: O(n^2)
 *   Worst:   O(n^2)
 *
 * Space complexity: O(1)
 * Stable: No
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
