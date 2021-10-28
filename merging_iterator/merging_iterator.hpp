#pragma once

#include <vector>
#include <iterator>
#include <initializer_list>
#include "m_iter_exceptions.hpp"

template<typename T, typename = void>
class Merge_range;

template<typename Iterator_type>
class Merge_range<Iterator_type> final {

    template<typename iterator_type, bool is_const>
    class Merge_iterator final {
    public:
        using value_type = typename std::iterator_traits<Iterator_type>::value_type;
        using iterator_category = std::forward_iterator_tag;
        using difference_type = typename std::iterator_traits<Iterator_type>::difference_type;
        using reference = typename std::conditional<is_const, const value_type &, value_type &>::type;
        using pointer = typename std::iterator_traits<Iterator_type>::pointer;

        explicit Merge_iterator(Merge_range new_parent) : parent(new_parent) {
            if (!new_parent.iterators.empty())
                position = find_pos_of_min();
        }

        Merge_iterator() = default;

        Merge_iterator &operator++() {
            if (position == stop)
                throw Out_of_range_exception();
            ++parent.iterators[position].first;
            position = find_pos_of_min();
            return *this;
        }

//        template<typename T = void>
//        typename std::enable_if<!std::is_const<typename std::remove_pointer<pointer>::type>::value, reference>::type
        reference operator*() const {
            if (position == stop)
                throw Out_of_range_exception();
            return *parent.iterators[position].first;
        }

//        template<typename T = void>
//        typename std::enable_if<std::is_const<typename std::remove_pointer<pointer>::type>::value, const_reference>::type
//        operator*() const {
//            if (position == stop) {
//                throw Out_of_range_exception();
//            }
//            return *parent.iterators[position].first;
//        }

        Merge_iterator operator++(int) {
            if (position == stop)
                throw Out_of_range_exception();
            Merge_iterator temp = *this;
            ++*this;
            return temp;
        }

        bool operator==(Merge_iterator const &right) {
            return this->position == right.position;
        }

        bool operator!=(Merge_iterator const &right) {
            return this->position != right.position;
        }

    private:
        size_t stop = ~(std::numeric_limits<size_t>::max()) - 1;
        Merge_range parent = {};
        size_t position = stop;

        size_t find_pos_of_min() {
            if (parent.iterators.size() < 1)
                return stop;
            size_t min_idx = 0;
            int amount_of_not_empty_ranges = 0;
            for (int i = 0; i < parent.iterators.size(); i++) {
                if (parent.iterators[i].first != parent.iterators[i].second) {
                    amount_of_not_empty_ranges++;
                    if (*parent.iterators[i].first < *parent.iterators[min_idx].first)
                        min_idx = i;
                }
            }
            if (amount_of_not_empty_ranges)
                return min_idx;
            else return stop;
        }
    };

public:
    using const_iterator = Merge_iterator<Iterator_type, true>;
    using iterator = Merge_iterator<Iterator_type, false>;

    Merge_range() = default;

    explicit Merge_range(std::vector<std::pair<Iterator_type, Iterator_type>> vector_of_iterators_pairs) :
            iterators(std::move(vector_of_iterators_pairs)) {};

    iterator begin() const {
        return iterator(*this);
    }

    iterator end() const {
        return {};
    }

    const_iterator cbegin() const {
        return const_iterator(*this);
    }

    const_iterator cend() const {
        return {};
    }

private:
    std::vector<std::pair<Iterator_type, Iterator_type>> iterators;
};