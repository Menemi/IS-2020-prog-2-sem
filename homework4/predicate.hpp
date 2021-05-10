#pragma once

#include <iterator>
#include <functional>

template<typename InputIterator, typename T>
bool allOf(InputIterator first, InputIterator last, T value) {
    for (first; first != last; ++first)
        if (value(*first) == 0)
            return false;
    return true;
}

template<typename InputIterator, typename T>
bool anyOf(InputIterator first, InputIterator last, T value) {
    for (first; first != last; ++first)
        if (value(*first) == 1)
            return true;
    return false;
}

template<typename InputIterator, typename T>
bool noneOf(InputIterator first, InputIterator last, T value) {
    for (first; first != last; ++first)
        if (value(*first) == 1)
            return false;
    return true;
}

template<typename InputIterator, typename T>
bool oneOf(InputIterator first, InputIterator last, T value) {
    bool flag = false;

    for (first; first != last; ++first) {
        if (value(*first) == 1) {
            if (!flag)
                flag = true;
            else
                return false;
        }
    }
    return flag;
}

template<typename InputIterator, typename T = std::less<>>
bool isSorted(InputIterator first, InputIterator last, T value = T()) {
    InputIterator first1 = first;
    InputIterator second1 = ++first;

    while (second1 != last) {
        if (value(*first1, *second1) == 0)
            return false;
        ++first1;
        ++second1;
    }
    return true;
}

template<typename InputIterator, typename T>
bool isPartitioned(InputIterator first, InputIterator last, T value) {
    bool tempValue = value(*first);
    bool flag = false;
    ++first;

    for (first; first != last; ++first) {
        if (value(*first) != tempValue) {
            if (flag)
                return false;
            flag = true;
            tempValue = !tempValue;
        }
    }
    return true;
}

template<typename ForwardIt, typename T>
ForwardIt findNot(ForwardIt first, ForwardIt last, T value) {
    for (first; first != last; ++first)
        if (*first != value)
            return first;
    return last;
}

template<typename ForwardIt, typename T>
ForwardIt findBackward(ForwardIt first, ForwardIt last, T value) {
    ForwardIt resultLast = last;

    for (first; first != last; ++first)
        if (*first == value)
            resultLast = first;
    return resultLast;
}

template<typename InputIterator, typename T>
bool isPalindrome(InputIterator first, InputIterator last, T value) {
    InputIterator right = first;
    --last;

    while (first != last && right != last) {
        if (value(*first, *last) == 0)
            return false;
        right = first;
        ++first;
        --last;
    }
    return true;
}