/*
 * Gnome Sort
 *
 * Compares adjacent elements and swaps them when they are
 * in the wrong order, moving backwards after each swap.
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
void gnomeSort(Vector<T>& vec){
    size_t pos = 0;
    size_t n = vec.size();

    while(pos < n){
        if(pos == 0 || vec[pos] >= vec[pos - 1]){
            ++pos;
        }else{
            std::swap(vec[pos], vec[pos - 1]);
            --pos;
        }
    }
}