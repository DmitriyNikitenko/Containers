/*
 * Bubble Sort
 *
 * Repeatedly compares adjacent elements and swaps them
 * if they are in the wrong order.
 *
 * Time complexity:
 *   Best:    O(n)
 *   Average: O(n^2)
 *   Worst:   O(n^2)
 *
 * Space complexity: O(1)
 * Stable: Yes
 */
#pragma once
#include <utility>
#include "../../containers/Vector/Vector.hpp"
template<typename T>
void bubbleSort(Vector<T>& vec){
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