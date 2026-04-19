/*
*  Key Properties:
*    - Time Complexity:
*        * Best Case:    O(n log n)
*        * Average Case: O(n log n)
*        * Worst Case:   O(n log n)
*
*    - Space Complexity:
*        * O(n) auxiliary space (requires additional buffer for merging)
*
*    - Stability:
*        * Stable (preserves the relative order of equal elements)
*
*  Notes:
*    - Guarantees consistent O(n log n) performance regardless of input distribution.
*    - Well-suited for large datasets and linked structures.
*    - Requires additional memory, unlike in-place algorithms (e.g., quicksort, heapsort).
*    - Cache performance may be lower compared to some in-place algorithms.
*
*  Educational Note:
*    - This implementation operates directly on Vector<T> for simplicity.
*    - In general-purpose code, sorting algorithms should be implemented
*      using iterators to remain container-agnostic and reusable.
*/
#pragma once
#include "../../containers/Vector/Vector.hpp"

//Recursive mergesort
template<typename T>
void mergeSortR(Vector<T>& v, size_t begin, size_t end) {
    if (end - begin <= 1) return;

    size_t mid = begin + (end - begin) / 2;
    mergesortR(v, begin, mid);
    mergesortR(v, mid, end);

    merge(v, begin, mid, end);
}

template<typename T>
void merge(Vector<T>& v, size_t begin, size_t mid, size_t end) {
    Vector<T> temp;

    size_t left = begin;
    size_t right = mid;

    while (left < mid && right < end) {
        if (v[left] < v[right]) {
            temp.emplace_back(v[left++]);
        } else {
            temp.emplace_back(v[right++]);
        }
    }

    while (left < mid) temp.emplace_back(v[left++]);
    while (right < end) temp.emplace_back(v[right++]);

    for (size_t i = 0; i < temp.size(); ++i) {
        v[begin + i] = temp[i];
    }
}

//Iterative mergesort
template<typename T>
void mergeSortI(Vector<T>& v) {
    size_t n = v.size();

    for (size_t size = 1; size < n; size *= 2) {
        for (size_t left = 0; left < n; left += 2 * size) {
            size_t mid = std::min(left + size, n);
            size_t right = std::min(left + 2 * size, n);

            merge(v, left, mid, right);
        }
    }
}