/*
*  MergeSort Documentation
*
*  Time Complexity:
*    - Best/Average/Worst: O(n log n) - always consistent
*
*  Space Complexity:
*    - O(n) - for temporary vector during merging
*
*  Stability: Stable (preserves relative order of equal elements)
*
*  Variants:
*    - mergesortR: Recursive implementation (top-down)
*    - mergesortI: Iterative implementation (bottom-up)
*/
#pragma once
#include "../../containers/Vector/Vector.hpp"

//Recursive mergesort
template<typename It, typename T>
void mergesortR(It begin, It end){
    if(end - begin <= 1) { return; }
    It mid = begin + (end - begin)/2;
    mergesortR<It, T>(begin, mid);
    mergesortR<It, T>(mid, end);
    
    merge<It, T>(begin, mid, end);
}

template<typename It, typename T>
void merge(It begin, It mid, It end){
    Vector<T> temp;
    It left = begin;
    It right = mid;
    while(left != mid && right != end){
        if(*left < *right){
            temp.emplace_back(*left);
            ++left;
        }
        else{
            temp.emplace_back(*right);
            ++right;
        }
    }
    while(left != mid){
        temp.emplace_back(*left);
        ++left;
    }
    while(right != end){
        temp.emplace_back(*right);
        ++right;
    }
    for(size_t i = 0; i < temp.size(); ++i){
        *begin = temp[i];
        ++begin;
    }
}

template<typename Container>
void mergesortR(Container& container){
    typedef decltype(*container.begin()) T;
    mergesortR<typename Container::Iterator, T>(container.begin(), container.end());
}

//Iterative mergesort
template<typename It, typename T>
void mergesortI(It begin, It end){
    size_t n = end - begin;
    size_t size = 1;
    while (size < n){
        size_t left = 0;
        while (left < n){
            size_t mid = left + size < n ? left + size : n;
            size_t right = left + 2*size < n ? left + 2*size : n;
            merge<It, T>(begin + left, begin + mid, begin + right);
            left += 2*size;
        }
        size *= 2;
    }
}

template<typename Container>
void mergesortI(Container& container){
    typedef decltype(*container.begin()) T;
    mergesortI<typename Container::Iterator, T>(container.begin(), container.end());
}