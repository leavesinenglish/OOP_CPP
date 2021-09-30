#pragma once
#include <iostream>

template<class RandomAccessIterator, class Compare>
typename std::enable_if <std::is_same<typename std::iterator_traits <RandomAccessIterator>::iterator_category, std::random_access_iterator_tag> ::value> ::type
quick_sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
    auto numElements = std::distance(first, last);
    if (numElements <= 1)
        return;
    auto pivot = last;
    --pivot;
    if (numElements > 2) {
        auto middle = first;
        std::advance(middle, numElements / 2);
        std::iter_swap(middle, pivot);
    }
    auto left = first;
    auto right = pivot;
    while (left != right) {
        while (!comp(*pivot, *left) && left != right)
            ++left;
        while (!comp(*right, *pivot) && left != right)
            --right;
        if (left != right)
            std::iter_swap(left, right);
    }
    if (pivot != left && comp(*pivot, *left))
        std::iter_swap(pivot, left);
    quick_sort(first, left, comp);
    quick_sort(++left, last, comp);
}

template<class RandomAccessIterator>
typename std::enable_if<std::is_same<typename std::iterator_traits<RandomAccessIterator>::iterator_category, std::random_access_iterator_tag>::value>::type
quick_sort(RandomAccessIterator first, RandomAccessIterator last) {
    quick_sort(first, last, std::less<typename std::iterator_traits<RandomAccessIterator>::value_type>());
}

template<class Iterator, class Compare>
typename std::enable_if<!std::is_same<typename std::iterator_traits<Iterator>::iterator_category, std::random_access_iterator_tag>::value>::type
quick_sort(Iterator first, Iterator last, Compare cmp){
    std::cout<<"выполнилась сортировка для не RandAccess";
}

template<class Iterator>
typename std::enable_if<!std::is_same<typename std::iterator_traits<Iterator>::iterator_category, std::random_access_iterator_tag>::value>::type
quick_sort(Iterator first, Iterator last){
    std::cout<<"выполнилась сортировка для не RandAccess";
}