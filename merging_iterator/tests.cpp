#include "gtest/gtest.h"
#include <deque>
#include <list>
#include  <random>
#include "merging_iterator.hpp"

#define MAX_SIZE 10

TEST(Vector_container_test, int_test) {
    std::mt19937 random(0);
    std::vector<std::vector<int>> container_of_int_vectors;
    int number_of_vectors = random() % MAX_SIZE;
    for (auto i = 0; i < number_of_vectors; ++i) {
        std::vector<int> temp;
        int number_of_elements_in_container = random() % MAX_SIZE;
        for (auto j = 0; j < number_of_elements_in_container; ++j) {
            temp.push_back(random() % 1000);
        }
        container_of_int_vectors.push_back(temp);
        std::sort(container_of_int_vectors[i].begin(), container_of_int_vectors[i].end());
    }
    using it_pair = std::pair<std::vector<int>::iterator, std::vector<int>::iterator>;
    std::vector<it_pair> iter_vec;
    for (auto i = 0; i < container_of_int_vectors.size(); ++i) {
        iter_vec.emplace_back(container_of_int_vectors[i].begin(), container_of_int_vectors[i].end());
    }
    Merge_range<std::vector<int>::iterator> merge_iter(iter_vec);
    for (auto tmp = merge_iter.begin(); tmp != merge_iter.end(); ++tmp) {
        for (auto tmp2 = tmp; tmp2 != merge_iter.end(); ++tmp2) {
            EXPECT_TRUE(*tmp <= *tmp2);
        }
    }
}

TEST(Vector_container_test, double_test) {
    std::mt19937 random(0);
    std::vector<std::vector<double>> container_of_double_vectors;
    int number_of_vectors = random() % MAX_SIZE;
    for (auto i = 0; i < number_of_vectors; ++i) {
        std::vector<double> temp;
        int number_of_elements_in_container = random() % MAX_SIZE;
        for (auto j = 0; j < number_of_elements_in_container; ++j) {
            temp.push_back(static_cast<double>(random() % 1000));
        }
        container_of_double_vectors.push_back(temp);
        std::sort(container_of_double_vectors[i].begin(), container_of_double_vectors[i].end());
    }
    using it_pair = std::pair<std::vector<double>::iterator, std::vector<double>::iterator>;
    std::vector<it_pair> iter_vec;
    for (auto i = 0; i < container_of_double_vectors.size(); ++i) {
        iter_vec.emplace_back(container_of_double_vectors[i].begin(), container_of_double_vectors[i].end());
    }
    Merge_range<std::vector<double>::iterator> merge_iter(iter_vec);
    for (auto tmp = merge_iter.begin(); tmp != merge_iter.end(); ++tmp) {
        for (auto tmp2 = tmp; tmp2 != merge_iter.end(); ++tmp2) {
            EXPECT_TRUE(*tmp <= *tmp2);
        }
    }
}

TEST(Deque_container_test, int_test) {
    std::mt19937 random(0);
    std::vector<std::deque<int>> container_of_double_deque;
    int number_of_vectors = random() % MAX_SIZE;
    for (auto i = 0; i < number_of_vectors; ++i) {
        std::deque<int> temp;
        int number_of_elements_in_container = random() % MAX_SIZE;
        for (auto j = 0; j < number_of_elements_in_container; ++j) {
            temp.push_back(static_cast<int>(random() % 1000));
        }
        container_of_double_deque.push_back(temp);
        std::sort(container_of_double_deque[i].begin(), container_of_double_deque[i].end());
    }using it_pair = std::pair<std::deque<int>::iterator, std::deque<int>::iterator>;
    std::vector<it_pair> iter_vec;
    for (auto i = 0; i < container_of_double_deque.size(); ++i) {
        iter_vec.emplace_back(container_of_double_deque[i].begin(), container_of_double_deque[i].end());
    }
    Merge_range<std::deque<int>::iterator> merge_iter(iter_vec);
    for (auto tmp = merge_iter.begin(); tmp != merge_iter.end(); ++tmp) {
        for (auto tmp2 = tmp; tmp2 != merge_iter.end(); ++tmp2) {
            EXPECT_TRUE(*tmp <= *tmp2);
        }
    }
}

TEST(Deque_container_test, double_test) {
    std::mt19937 random(0);
    std::vector<std::deque<double>> container_of_double_deque;
    int number_of_vectors = random() % MAX_SIZE;
    for (auto i = 0; i < number_of_vectors; ++i) {
        std::deque<double> temp;
        int number_of_elements_in_container = random() % MAX_SIZE;
        for (auto j = 0; j < number_of_elements_in_container; ++j) {
            temp.push_back(static_cast<double>(random() % 1000));
        }
        container_of_double_deque.push_back(temp);
        std::sort(container_of_double_deque[i].begin(), container_of_double_deque[i].end());
    }
    using it_pair = std::pair<std::deque<double>::iterator, std::deque<double>::iterator>;
    std::vector<it_pair> iter_vec;
    for (auto i = 0; i < container_of_double_deque.size(); ++i) {
        iter_vec.emplace_back(container_of_double_deque[i].begin(), container_of_double_deque[i].end());
    }
    Merge_range<std::deque<double>::iterator> merge_iter(iter_vec);
    for (auto tmp = merge_iter.begin(); tmp != merge_iter.end(); ++tmp) {
        for (auto tmp2 = tmp; tmp2 != merge_iter.end(); ++tmp2) {
            EXPECT_TRUE(*tmp <= *tmp2);
        }
    }
}

TEST(List_container_test, double_test) {
    std::mt19937 random(0);
    std::vector<std::list<double>> container_of_double_list;
    int number_of_vectors = random() % MAX_SIZE;
    for (auto i = 0; i < number_of_vectors; ++i) {
        std::list<double> temp;
        int number_of_elements_in_container = random() % MAX_SIZE;
        for (auto j = 0; j < number_of_elements_in_container; ++j) {
            temp.push_back(static_cast<double>(random() % 1000));
        }
        container_of_double_list.push_back(temp);
        container_of_double_list[i].sort();
    }
    using it_pair = std::pair<std::list<double>::iterator, std::list<double>::iterator>;
    std::vector<it_pair> iter_vec;
    for (auto i = 0; i < container_of_double_list.size(); ++i) {
        iter_vec.emplace_back(container_of_double_list[i].begin(), container_of_double_list[i].end());
    }
    Merge_range<std::list<double>::iterator> merge_iter(iter_vec);
    for (auto tmp = merge_iter.begin(); tmp != merge_iter.end(); ++tmp) {
        for (auto tmp2 = tmp; tmp2 != merge_iter.end(); ++tmp2) {
            EXPECT_TRUE(*tmp <= *tmp2);
        }
    }
}

TEST(List_container_test, int_test) {
    std::mt19937 random(0);
    std::vector<std::list<int>> container_of_int_list;
    int number_of_vectors = random() % MAX_SIZE;
    int number_of_elements_in_container = random() % MAX_SIZE;
    for (auto i = 0; i < number_of_vectors; ++i) {
        std::list<int> temp;
        for (auto j = 0; j < number_of_elements_in_container; ++j) {
            temp.push_back(static_cast<int>(random() % 1000));
        }
        container_of_int_list.push_back(temp);
        container_of_int_list[i].sort();
    }
    using it_pair = std::pair<std::list<int>::iterator, std::list<int>::iterator>;
    std::vector<it_pair> iter_vec;
    for (auto i = 0; i < container_of_int_list.size(); ++i) {
        iter_vec.emplace_back(container_of_int_list[i].begin(), container_of_int_list[i].end());
    }
    Merge_range<std::list<int>::iterator> merge_iter(iter_vec);
    for (auto tmp = merge_iter.begin(); tmp != merge_iter.end(); ++tmp) {
        for (auto tmp2 = tmp; tmp2 != merge_iter.end(); ++tmp2) {
            EXPECT_TRUE(*tmp <= *tmp2);
        }
    }
}

TEST(Special_test, empty_container) {
    using it_pair = std::pair<std::list<int>::iterator, std::list<int>::iterator>;
    std::vector<it_pair> iter_vec;
    Merge_range<std::list<int>::iterator> merge_iter(iter_vec);
    auto tmp = merge_iter.begin();
    EXPECT_TRUE(tmp == merge_iter.end());
    EXPECT_THROW(++tmp, OutOfRangeException);
    EXPECT_TRUE(tmp == merge_iter.end());
    EXPECT_THROW(*tmp, OutOfRangeException);
}

TEST(Special_test, throw_test) {
    std::mt19937 random(0);
    std::vector<std::vector<int>> container_of_int_vectors;
    int number_of_vectors = random() % MAX_SIZE;
    int number_of_elements_in_container = random() % MAX_SIZE;
    for (auto i = 0; i < number_of_vectors; ++i) {
        std::vector<int> temp;
        for (auto j = 0; j < number_of_elements_in_container; ++j) {
            temp.push_back(random() % 1000);
        }
        container_of_int_vectors.push_back(temp);
        std::sort(container_of_int_vectors[i].begin(), container_of_int_vectors[i].end());
    }
    using it_pair = std::pair<std::vector<int>::iterator, std::vector<int>::iterator>;
    std::vector<it_pair> iter_vec;
    for (auto i = 0; i < container_of_int_vectors.size(); ++i) {
        iter_vec.emplace_back(container_of_int_vectors[i].begin(), container_of_int_vectors[i].end());
    }
    Merge_range<std::vector<int>::iterator> merge_iter(iter_vec);
    for (auto tmp = merge_iter.begin(); tmp != merge_iter.end(); ++tmp) {
        EXPECT_NO_THROW(*tmp);
        for (auto tmp2 = tmp; tmp2 != merge_iter.end(); ++tmp2) {
            EXPECT_TRUE(*tmp <= *tmp2);
            EXPECT_NO_THROW(*tmp2);
        }
    }
}