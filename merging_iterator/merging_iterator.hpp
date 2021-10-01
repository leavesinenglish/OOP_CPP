#pragma once
#include <vector>
#include <iterator>
#include <algorithm>
#include "m_iter_exceptions.hpp"

template<typename T, typename = void>
class Merge_range;

template<typename Iterator_type>
class Merge_range<Iterator_type> final{

    class Merge_iterator final{

    public:
        using value_type = typename std::iterator_traits<Iterator_type>::value_type;
        using iterator_category = std::forward_iterator_tag;
        using difference_type = typename std::iterator_traits<Iterator_type>::difference_type;
        using reference = typename std::iterator_traits<Iterator_type>::reference;
        using pointer = typename std::iterator_traits<Iterator_type>::pointer;

        explicit Merge_iterator(Merge_range new_parent) : parent(new_parent){
            position = find_min_element();
        }
        Merge_iterator() = delete;
        Merge_iterator& operator++(){
            if (position == -1) {
                throw OutOfRangeException();
            }
            ++parent.iterators[position];
            position = find_min_element();
            return *this;
        }
        reference operator*(){
            if (position == -1) {
                throw OutOfRangeException();
            }
            return *parent.iterators[position];
        }

        friend bool operator==(Merge_iterator const& left, Merge_iterator const& right){
            return  left.position == right.position;
        }
        friend bool operator!=(Merge_iterator const& left, Merge_iterator const& right){
            return left.position != right.position;
        }

    private:
        Merge_range parent;
        int position = -1;
        int find_min_element(){
            int n = 0;
            std::vector<int> a;
            a.assign(parent.iterators.size() / 2, 0);
            for (int i = 0; i != parent.iterators.size(); i += 2) {
                if (parent.iterators[i] != parent.iterators[i + 1]) {
                    a[n++] = i;
                }
            }
            if (n) {
                auto it = std::min_element(a.begin(), a.begin() + n, [this](int i, int j){
                    return *parent.iterators[i] < *parent.iterators[j];
                });
                return *it;
            }
            return -1;
        }
    };

public:
    explicit Merge_range(const std::vector<std::pair<Iterator_type, Iterator_type>>& vector_of_pairs_of_iterators){
        for (int i = 0; i < vector_of_pairs_of_iterators.size(); ++i){
            iterators.push_back(vector_of_pairs_of_iterators[i].first);
            iterators.push_back(vector_of_pairs_of_iterators[i].second);
        }
    }

    Merge_iterator begin(){
        return Merge_iterator(*this);
    }

    Merge_iterator end(){
        std::vector<std::pair<Iterator_type, Iterator_type>> end = { /*iterators[1] */ };
        static Merge_range end_range(end);
        auto iter = Merge_iterator(end_range);
        return iter;
    }

private:
    std::vector<Iterator_type>  iterators;
};