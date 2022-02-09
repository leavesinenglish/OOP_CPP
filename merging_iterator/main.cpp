#include <iostream>
#include <list>
#include <vector>
#include "merging_iterator.hpp"

int main() {
    std::vector<int> first_container = {1, 2, 7};
    std::vector<int> second_container = {3, 5, 8};
    std::vector<int> third_container = {6, 10, 12};

    using it_pair = std::pair<std::vector<int>::iterator, std::vector<int>::iterator>;
    std::vector<it_pair> vector_of_iterators;
    vector_of_iterators.emplace_back(first_container.begin(), first_container.end());
    vector_of_iterators.emplace_back(second_container.begin(), second_container.end());
    vector_of_iterators.emplace_back(third_container.begin(), third_container.end());
    Merge_range<std::vector<int>::iterator> merge_iter(vector_of_iterators);
    int prev_numb = 0;
    try {
        for (auto tmp = merge_iter.begin(); tmp != merge_iter.end(); ++tmp) {
            std::cout << *tmp << " ";
            if (prev_numb > *tmp) {
                std::cout << std::endl << "Something went wrong. Previous number was bigger than next." << std::endl;
            }
            prev_numb = *tmp;
        }
    }
    catch (Out_of_range_exception &exception) {
        exception.print_error();
    }
}
