/*
 * Merge Sort
 *
 * Divides the sequence into smaller parts and merges
 * the sorted parts.
 *
 * Time complexity:
 *   Best:    O(n log n)
 *   Average: O(n log n)
 *   Worst:   O(n log n)
 *
 * Space complexity: O(n)
 * Stable: Yes
 */
#pragma once
#include "../../containers/Vector/Vector.hpp"


namespace detail{
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
}


//Recursive mergesort
template<typename T>
void mergeSortR(Vector<T>& v, size_t begin, size_t end) {
    if (end - begin <= 1) return;

    size_t mid = begin + (end - begin) / 2;
    mergeSortR(v, begin, mid);
    mergeSortR(v, mid, end);

    detail::merge(v, begin, mid, end);
}

//Iterative mergesort
template<typename T>
void mergeSortI(Vector<T>& v) {
    size_t n = v.size();

    for (size_t size = 1; size < n; size *= 2) {
        for (size_t left = 0; left < n; left += 2 * size) {
            size_t mid = std::min(left + size, n);
            size_t right = std::min(left + 2 * size, n);

            detail::merge(v, left, mid, right);
        }
    }
}