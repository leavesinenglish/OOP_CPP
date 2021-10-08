#pragma once

#include <vector>
#include <iterator>
#include <initializer_list>
#include "m_iter_exceptions.hpp"

template<typename T, typename = void>
class Merge_range;

template<typename Iterator_type>
class Merge_range<Iterator_type> final {

    class Merge_iterator final {

    public:
        using value_type = typename std::iterator_traits<Iterator_type>::value_type;
        using iterator_category = std::forward_iterator_tag;
        using difference_type = typename std::iterator_traits<Iterator_type>::difference_type;
        using reference = typename std::iterator_traits<Iterator_type>::reference;
        using pointer = typename std::iterator_traits<Iterator_type>::pointer;

        explicit Merge_iterator(Merge_range new_parent) : parent(new_parent) {
            if (!new_parent.iterators.empty())
                position = find_pos_of_min();
        }

        Merge_iterator() = delete;

        Merge_iterator &operator++() {
            if (position == NULL) {
                throw Out_of_range_exception();
            }
            ++parent.iterators[position];
            position = find_pos_of_min();
            return *this;
        }

        reference operator*() {
            if (position == NULL) {
                throw Out_of_range_exception();
            }
            return *parent.iterators[position];
        }

        bool operator==(Merge_iterator const &right) {
            return this->position == right.position;
        }

        bool operator!=(Merge_iterator const &right) {
            return this->position != right.position;
        }

    private:
        Merge_range parent;
        int position = NULL;

        int find_pos_of_min() {
            if (parent.iterators.size() <= 1)
                return NULL;
            int min_idx = 0;
            int amount_of_empty_ranges = 0;
            for (int i = 0; i < parent.iterators.size(); i += 2) {
                if (parent.iterators[i] != parent.iterators[i + 1]) {
                    amount_of_empty_ranges++;
                    if (*parent.iterators[i] < *parent.iterators[min_idx])
                        min_idx = i;
                }
            }
            if (amount_of_empty_ranges)
                return min_idx;

//            int n = 0;
//            std::vector<int> a;
//            a.assign(parent.iterators.size() / 2, 0);
//            for (int i = 0; i != parent.iterators.size(); i += 2) {
//                if (parent.iterators[i] != parent.iterators[i + 1]) {
//                    a[n++] = i;
//                }
//            }
//            if (n) {
//                auto it = std::min_element(a.begin(), a.begin() + n, [this](int i, int j){
//                    return *parent.iterators[i] < *parent.iterators[j];
//                });
//                return *it;
//            }
//            else return -1;
        }
    };

public:
    explicit Merge_range(std::vector<std::pair<Iterator_type, Iterator_type>> vector_of_iterators_pairs) {
        iterators(std::move(vector_iterators_pairs));
    }

//    Merge_range(const std::initializer_list<Iterator_type> iterators_list) {
//        iterators = iterators_list;
//    }

    Merge_iterator begin() {
        return Merge_iterator(*this);
    }

    Merge_iterator end() {
        std::vector<std::pair<Iterator_type, Iterator_type>> end = {};
        Merge_range end_range(end);
        auto iter = Merge_iterator(end_range);
        return iter;
    }

private:
    std::vector<Iterator_type> iterators;
};