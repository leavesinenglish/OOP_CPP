#include "gtest/gtest.h"
#include <deque>
#include <list>
#include  <random>
#include "merging_iterator.hpp"
using namespace std;
#define MAX_SIZE 10

TEST(Vector_container, int_) {
    vector<vector<int>> container_of_int_vectors;
    srand(time(nullptr));
    int number_of_vectors = rand() % MAX_SIZE;
    for (auto i = 0; i < number_of_vectors; ++i) {
        std::vector<int> temp;
        int number_of_elements_in_container = rand() % MAX_SIZE;
        for (auto j = 0; j < number_of_elements_in_container; ++j) {
            temp.emplace_back(rand() % 1000);
        }
        container_of_int_vectors.emplace_back(temp);
        sort(container_of_int_vectors[i].begin(), container_of_int_vectors[i].end());
    }
    using it_pair = pair<vector<int>::iterator, vector<int>::iterator>;
    vector<it_pair> iter_vec;
    for (auto i = 0; i < container_of_int_vectors.size(); ++i) {
        iter_vec.emplace_back(make_pair(container_of_int_vectors[i].begin(), container_of_int_vectors[i].end()));
    }
    const Merge_range<vector<int>::iterator> merge_range(iter_vec);

//    Merge_range<vector<it_pair>> mergeRange({(vector<int> {1}).begin(), (vector<int> {1}).end()});

    auto begin = merge_range.cbegin();
    auto end = merge_range.cend();
    for (auto tmp = begin; tmp != end; tmp++) {
        for (auto tmp2 = tmp; tmp2 != end; tmp2++) {
            auto a = *tmp;
            EXPECT_TRUE(*tmp <= *tmp2);
        }
    }
}

TEST(Vector_container, double_) {
    vector<vector<double>> container_of_double_vectors;
    srand(time(nullptr));
    int number_of_vectors = rand() % MAX_SIZE;
    for (auto i = 0; i < number_of_vectors; ++i) {
        std::vector<double> temp;
        int number_of_elements_in_container = rand() % MAX_SIZE;
        for (auto j = 0; j < number_of_elements_in_container; ++j) {
            temp.emplace_back(rand() % 1000);
        }
        container_of_double_vectors.emplace_back(temp);
        sort(container_of_double_vectors[i].begin(), container_of_double_vectors[i].end());
    }
    using it_pair = pair<vector<double>::iterator, vector<double>::iterator>;
    vector<it_pair> iter_vec;
    for (auto i = 0; i < container_of_double_vectors.size(); ++i) {
        iter_vec.emplace_back(container_of_double_vectors[i].begin(), container_of_double_vectors[i].end());
    }
    Merge_range<vector<double>::iterator> merge_range(iter_vec);
    for (auto tmp = merge_range.begin(); tmp != merge_range.end(); ++tmp) {
        for (auto tmp2 = tmp; tmp2 != merge_range.end(); ++tmp2) {
            EXPECT_TRUE(*tmp <= *tmp2);
        }
    }
}

TEST(Deque_container, int_) {
    srand(time(nullptr));
    vector<deque<int>> container_of_int_deque;
    int number_of_vectors = rand() % MAX_SIZE;
    for (auto i = 0; i < number_of_vectors; ++i) {
        deque<int> temp;
        int number_of_elements_in_container = rand() % MAX_SIZE;
        for (auto j = 0; j < number_of_elements_in_container; ++j) {
            temp.emplace_back(rand() % 1000);
        }
        container_of_int_deque.emplace_back(temp);
        sort(container_of_int_deque[i].begin(), container_of_int_deque[i].end());
    }
    using it_pair = pair<deque<int>::iterator, deque<int>::iterator>;
    vector<it_pair> iter_vec;
    for (auto i = 0; i < container_of_int_deque.size(); ++i) {
        iter_vec.emplace_back(container_of_int_deque[i].begin(), container_of_int_deque[i].end());
    }
    Merge_range<deque<int>::iterator> merge_range(iter_vec);
    for (auto tmp = merge_range.begin(); tmp != merge_range.end(); ++tmp) {
        for (auto tmp2 = tmp; tmp2 != merge_range.end(); ++tmp2) {
            EXPECT_TRUE(*tmp <= *tmp2);
        }
    }
}

TEST(Deque_container, double_) {
    srand(time(nullptr));
    vector<deque<double>> container_of_double_deque;
    int number_of_vectors = rand() % MAX_SIZE;
    for (auto i = 0; i < number_of_vectors; ++i) {
        deque<double> temp;
        int number_of_elements_in_container = rand() % MAX_SIZE;
        for (auto j = 0; j < number_of_elements_in_container; ++j) {
            temp.emplace_back(rand() % 1000);
        }
        container_of_double_deque.emplace_back(temp);
        sort(container_of_double_deque[i].begin(), container_of_double_deque[i].end());
    }
    using it_pair = pair<deque<double>::iterator, deque<double>::iterator>;
    vector<it_pair> iter_vec;
    for (auto i = 0; i < container_of_double_deque.size(); ++i) {
        iter_vec.emplace_back(container_of_double_deque[i].begin(), container_of_double_deque[i].end());
    }
    Merge_range<deque<double>::iterator> merge_range(iter_vec);
    for (auto tmp = merge_range.begin(); tmp != merge_range.end(); ++tmp) {
        for (auto tmp2 = tmp; tmp2 != merge_range.end(); ++tmp2) {
            EXPECT_TRUE(*tmp <= *tmp2);
        }
    }
}

TEST(List_container, int_) {
    srand(time(nullptr));
    vector<list<int>> container_of_int_list;
    int number_of_vectors = rand() % MAX_SIZE;
    for (auto i = 0; i < number_of_vectors; ++i) {
        list<int> temp;
        int number_of_elements_in_container = rand() % MAX_SIZE;
        for (auto j = 0; j < number_of_elements_in_container; ++j) {
            temp.emplace_back(rand() % 1000);
        }
        container_of_int_list.emplace_back(temp);
        container_of_int_list[i].sort();
    }
    using it_pair = pair<list<int>::iterator, list<int>::iterator>;
    vector<it_pair> iter_vec;
    for (auto i = 0; i < container_of_int_list.size(); ++i) {
        iter_vec.emplace_back(container_of_int_list[i].begin(), container_of_int_list[i].end());
    }
    Merge_range<list<int>::iterator> merge_range(iter_vec);
    for (auto tmp = merge_range.begin(); tmp != merge_range.end(); ++tmp) {
        for (auto tmp2 = tmp; tmp2 != merge_range.end(); ++tmp2) {
            EXPECT_TRUE(*tmp <= *tmp2);
        }
    }
}

TEST(List_container, double_) {
    srand(time(nullptr));
    vector<list<double>> container_of_int_list;
    int number_of_vectors = rand() % MAX_SIZE;
    for (auto i = 0; i < number_of_vectors; ++i) {
        list<double> temp;
        int number_of_elements_in_container = rand() % MAX_SIZE;
        for (auto j = 0; j < number_of_elements_in_container; ++j) {
            temp.emplace_back(rand() % 1000);
        }
        container_of_int_list.emplace_back(temp);
        container_of_int_list[i].sort();
    }
    using it_pair = pair<list<double>::iterator, list<double>::iterator>;
    vector<it_pair> iter_vec;
    for (auto i = 0; i < container_of_int_list.size(); ++i) {
        iter_vec.emplace_back(container_of_int_list[i].begin(), container_of_int_list[i].end());
    }
    Merge_range<list<double>::iterator> merge_range(iter_vec);
    for (auto tmp = merge_range.begin(); tmp != merge_range.end(); ++tmp) {
        for (auto tmp2 = tmp; tmp2 != merge_range.end(); ++tmp2) {
            EXPECT_TRUE(*tmp <= *tmp2);
        }
    }
}

TEST(Int_list, empty) {
    using it_pair = std::pair<std::list<int>::iterator, std::list<int>::iterator>;
    std::vector<it_pair> iter_vec;
    Merge_range<std::list<int>::iterator> merge_range(iter_vec);
    auto tmp = merge_range.begin();
    EXPECT_TRUE(tmp == merge_range.end());
    EXPECT_THROW(++tmp, Out_of_range_exception);
    EXPECT_TRUE(tmp == merge_range.end());
    EXPECT_THROW(*tmp, Out_of_range_exception);
}

TEST(Container, throw_) {
    srand(time(nullptr));
    vector<vector<int>> container_of_int_vectors;
    int number_of_vectors = rand() % MAX_SIZE;
    int number_of_elements_in_container = rand() % MAX_SIZE;
    for (auto i = 0; i < number_of_vectors; ++i) {
        vector<int> temp;
        for (auto j = 0; j < number_of_elements_in_container; ++j) {
            temp.emplace_back(rand() % 1000);
        }
        container_of_int_vectors.emplace_back(temp);
        sort(container_of_int_vectors[i].begin(), container_of_int_vectors[i].end());
    }
    using it_pair = pair<vector<int>::iterator, vector<int>::iterator>;
    vector<it_pair> iter_vec;
    for (auto i = 0; i < container_of_int_vectors.size(); ++i) {
        iter_vec.emplace_back(container_of_int_vectors[i].begin(), container_of_int_vectors[i].end());
    }
    Merge_range<vector<int>::iterator> merge_iter(iter_vec);
    for (auto tmp = merge_iter.begin(); tmp != merge_iter.end(); ++tmp) {
        EXPECT_NO_THROW(*tmp);
        for (auto tmp2 = tmp; tmp2 != merge_iter.end(); ++tmp2) {
            EXPECT_TRUE(*tmp <= *tmp2);
            EXPECT_NO_THROW(*tmp2);
        }
    }
}

TEST (Iterators, begin_end_cbegin_cend) {
    vector<int> a,b,c;
    a = {1,2,3};
    b = {4,5,6};
    c = {7,8,9};
    using it_pair = pair<vector<int>::iterator, vector<int>::iterator>;
    vector<it_pair> iter_vec = {{a.begin(), a.end()}, {b.begin(), b.end()}, {c.begin(), c.end()}};
    Merge_range<vector<int>::iterator> m_r(iter_vec);
    const Merge_range<vector<int>::iterator> cm_r(iter_vec);
    auto begin = m_r.begin();
    auto cbegin = m_r.cbegin();
    (*cbegin)++;
    (*begin)++;
    (*c.cbegin())++;
    (*c.begin())++;
    auto _begin = cm_r.begin();
    auto _cbegin = m_r.cbegin();
}