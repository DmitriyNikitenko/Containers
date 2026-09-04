
#pragma once
#include <utility>
#include <random>
#include "../../containers/Stack/Stack.hpp"
#include "../../containers/Vector/Vector.hpp"

namespace detail {
    inline int getRandomPivot(int low, int high) {
        return low + rand() % (high - low + 1);
    }
}


template<typename T>
void quickSortR(Vector<T>& vec, int low, int high){
    // Recursive implementation of quick sort
    if(low < high){
        int pivotIndex = detail::getRandomPivot(low, high);
        std::swap(vec[pivotIndex], vec[high]);
        T pivot = vec[high];
        int i = low - 1; // Index of the last element smaller than the pivot
        for(int j = low; j < high; ++j){
            if(vec[j] < pivot){
                ++i;
                std::swap(vec[i], vec[j]);
            }
        }
        std::swap(vec[i + 1], vec[high]);
        int pivotPos = i + 1;
        quickSortR(vec, low, pivotPos - 1);
        quickSortR(vec, pivotPos + 1, high);
    }
}

template<typename T>
void quickSortI(Vector<T>& vec){
    // Iterative implementation of quick sort
    // The main difference is that we use a own stack instead of use the function call stack.
    Stack<std::pair<int, int>> stack;
    stack.push({0, static_cast<int>(vec.size()) - 1});

    while (!stack.empty()) {
        auto [low, high] = stack.pop();
        if (low < high) {
            int pivotIndex = detail::getRandomPivot(low, high);
            std::swap(vec[pivotIndex], vec[high]);
            T pivot = vec[high];
            int i = low - 1; // Index of the last element smaller than the pivot
            for (int j = low; j < high; ++j) {
                if (vec[j] < pivot) {
                    ++i;
                    std::swap(vec[i], vec[j]);
                }
            }
            std::swap(vec[i + 1], vec[high]);
            int pivotPos = i + 1;
            stack.push({low, pivotPos - 1});
            stack.push({pivotPos + 1, high});
        }
    }
}