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
*    - Efficient only for small or nearly sorted datasets.
*    - Performance degrades significantly on large or reverse-sorted inputs.
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