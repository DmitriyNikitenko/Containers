/*
 * Cocktail Shaker Sort
 *
 * Performs bidirectional bubble sort by moving larger elements
 * to the end and smaller elements to the beginning of the unsorted part.
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