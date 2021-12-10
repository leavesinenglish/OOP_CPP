#pragma once

#include "skip_list_exceptions.hpp"
#include <random>
#include <vector>

namespace details {
    template<size_t Max_level = 10>
    class level final {
    private:
        size_t level_ = 0;
    public:
        static const level level_min;
        static const level level_max;
        static const size_t max_alloc_size;

        //level() = delete;

        explicit level(size_t lvl) : level_{lvl} {
            if (lvl < level_max.level_ && lvl > level_min.level_) {
                level_ = lvl;
            } else {
                throw Out_of_range_exception();
            }
        }

        level &operator++() {
            return *this = level(level_ + 1);
        }

        level &operator-(level &another){
            if (level_ - another.level_ < level_max.level_ && level_ - another.level_ > level_min.level_){
                return level(level_ - another.level_);
            } else {
                throw Out_of_range_exception();
            }
        }

        [[nodiscard]] constexpr size_t get_level_number() const noexcept {
            return level_;
        }

        [[nodiscard]] size_t set_random_level() noexcept {
            std::mt19937 random(0);
            std::uniform_int_distribution<> uid(0, Max_level);
            return level_ = uid(random);
        }

        [[nodiscard]] constexpr size_t get_alloc_size() const noexcept {
            return max_alloc_size;
        }

    };

    template<> const level<> level<>::level_min = level(0);
    template<size_t Max_level> const level<Max_level> level<Max_level>::level_max = level(Max_level);
    template<size_t Max_level> const size_t level<Max_level>::max_alloc_size = Max_level + 1;
}

template<typename Key,
        typename Value, size_t Max_level = 10,
        typename Compare = std::less<Key>>

class skip_list final {
public:
    using value_type = std::pair<const Key, Value>;
    using pointer = std::add_pointer_t<value_type>;
    using const_pointer = std::add_const_t<pointer>;
    using reference = std::add_lvalue_reference_t<value_type>;
    using const_reference = std::add_lvalue_reference<std::add_const<value_type>>;

private:
    inline static constexpr Compare cmp = Compare();

    class node final {
    public:
        using level = details::level<Max_level>;

        bool operator==(const node &another) {
            return data->first == another->data->first
                   && data->second == another->data->second
                   && next_node == another->next_node
                   && Level.get_level_number() == another.Level.get_level_number();
        }

        explicit node(size_t lvl) {
            Level = level(lvl);
            next_node(Level.get_alloc_size());
        };

        explicit node(const pointer &data_) : data(data_), Level() {
            next_node(Level.get_alloc_size());
        };

        const Key &get_key() const {
            return data->first;
        }

        pointer get_data() const {
            return data;
        }

        [[nodiscard]] std::shared_ptr<node> &get_next_node_by_level(level i) const {
            return next_node[i.get_level_number()];
        }

        [[nodiscard]] constexpr level get_level() const noexcept {
            return Level;
        }



//        [[nodiscard]] constexpr size_t get_level_number() const noexcept {
//            return Level.get_level_number();
//        }
//
//        [[nodiscard]] constexpr size_t get_alloc_size() const noexcept {
//            return Level.get_alloc_size();
//        }

    private:
        pointer data = nullptr;
        std::vector<std::shared_ptr<node>> next_node;
        level Level;
    };

    node head = node(Max_level);
    size_t size_ = 0;

    template<bool is_const>
    class skip_list_iterator {
    private:
        std::shared_ptr<node> node_it;
    public:
        skip_list_iterator() = default;

        explicit skip_list_iterator(std::shared_ptr<node> node) { node_it = node; }

        using value_type = std::conditional_t<is_const, const value_type, value_type>;
        using reference = std::add_lvalue_reference_t<value_type>;
        using pointer = std::add_pointer_t<value_type>;
        using iterator_category = std::forward_iterator_tag;

        skip_list_iterator &operator++() {
            if (!node_it) {
                throw Out_of_range_exception();
            }
            node_it = node_it->next_node[0];
            return *this;
        }

        skip_list_iterator &operator++(int) {
            auto res = *this;
            ++(*this);
            return res;
        }

        reference operator*() const {
            if (!node_it) {
                throw Out_of_range_exception();
            }
            return *(node_it->get_data());
        }

        pointer operator->() const {
            if (!node_it) {
                throw Out_of_range_exception();
            }
            return node_it->get_data();
        }

        bool operator!=(const skip_list_iterator &another) const {
            return !(*this == another);
        }
    };

public:
    using iterator = skip_list_iterator<false>;
    using const_iterator = skip_list_iterator<true>;
    using level = details::level<Max_level>;

    skip_list() = default;

    explicit skip_list(const Compare &comp) { cmp = comp; }

    skip_list(const skip_list &another) {
        *this = another;
    }

    skip_list(skip_list &&another) noexcept {
        *this = std::move(another);
    }

    skip_list &operator=(const skip_list &another) {
        clear();
        cmp = another.cmp;
        for (auto i = another.begin(); i != another.end(); ++i) {
            (*this)[i->first] = i->second;
        }
        return *this;
    }

    skip_list &operator=(skip_list &&another) noexcept {
        std::swap(head, another.head);
        std::swap(size_, another.size_);
        std::swap(cmp, another.cmp);
        return *this;
    }

    iterator begin() {
        return iterator(head->next_node[0]);
    }

    const_iterator begin() const {
        return const_iterator(head->next_node[0]);
    }

    iterator end() {
        return {};
    }

    const_iterator end() const {
        return {};
    }

    const_iterator cbegin() const {
        return const_iterator(head->next_node[0]);
    }

    const_iterator cend() const {
        return {};
    };

    [[nodiscard]] bool empty() const {
        return size_ == 0;
    }

    [[nodiscard]] size_t size() const {
        return size_;
    }

    Value &operator[](const Key &key) {
        return insert(std::make_pair(key, Value())).first->second;
    }

    const Value &operator[](const Key &key) const {
        return (*this).at(key);
    }

    Value &at(const Key &key) {
        iterator iter = find(key);
        if (*iter != key) {
            throw Out_of_range_exception();
        }
        return (*this)[key];
    }

    const Value &at(const Key &key) const {
        const_iterator iter = find(key);
        if (*iter != key) {
            throw Out_of_range_exception();
        }
        return (*this)[key];
    }

    std::pair<iterator, bool> insert(const_reference val) {
        auto const &[update, cur] = find_with_update_array(true, val.first);
        if (cur && cur->get_key() == val.first) {
            return std::make_pair(iterator(cur), false);
        }
        auto insert_node = new node(val);
        ++size_;
        auto next_node = insert_node->get_next_node_by_level(0);
        for (auto i = 0; i <= insert_node->get_level(); ++i) {
            next_node[i] = update[i]->next_node[i];
            update[i]->get_next_node_by_level(i) = insert_node;
        }
        return std::make_pair(iterator(insert_node), true);
    }

    void erase(iterator position) {
        erase(position->first);
    }

    size_t erase(const Key &key) {
        auto &[update, cur] = find_with_update_array(true, key);
        if (cur && cur->get_key() == key) {
            return 1;
        }
        for (size_t i = 0; i <= cur->get_level_number(); ++i) {
            if (update[i]->get_next_node_by_level(i) != cur) {
                break;
            }
            update[i]->get_next_node_by_level(i) = cur->get_next_node_by_level(i);
        }
        --size_;
        return 0;
    }

    void erase(iterator first, iterator last) {
        if (first == last) {
            return;
        }
        if (first == begin() && last == end()) {
            clear();
            return;
        }
        auto &[update, deletable] = find_with_update_array(true, first->first);
        size_t n_of_delete;
        for (auto a = first; a != last; a++) {
            n_of_delete++;
        }
        size_ -= n_of_delete;
        auto cur = last.node_it;
        for (level i = level::level_min; i <= level::level_max; ++i) {
            if (cur->get_level_number() >= i) {
                update[i.get_level_number()]->get_next_node_by_level(i) = cur;
            } else {
                if (cur->get_next_node_by_level(level::level_min)) {
                    cur = cur->get_next_node_by_level(level::level_min);
                }
            }
        }

    }

    void swap(skip_list &another) {
        auto temp = std::move(*this);
        *this = std::move(another);
        another = std::move(temp);
    }

    void clear() {
        *this = {};
    }

    iterator find(const Key &key) {
        auto cur = find_with_update_array(false, key).second;
        if (cur && cur->get_key() == key) {
            return iterator(cur);
        }
        return end();
    }

    const_iterator find(const Key &key) const {
        auto cur = find_with_update_array(false, key).second;
        if (cur && cur->get_key() == key) {
            return const_iterator(cur);
        }
        return cend();
    }

private:
    std::pair<std::vector<std::shared_ptr<node>>, std::shared_ptr<node>>
    find_with_update_array(bool with_update, const Key &key) const {
        std::vector<std::shared_ptr<node>> update(head.get_alloc_size());
        if (with_update) {
            std::fill(update.begin(), update.end(), head);
        }
        auto cur = head;
        for (level i = level::level_min; i <= level::level_max; ++i) {
            while (cur.get_next_node_by_level(cur.get_level() - i) &&
                   cmp(cur.get_next_node_by_level(cur.get_level() - i)->get_data()->first, key)) {
                cur = cur.get_next_node_by_level(cur.get_level() - i);
            }
            if (with_update) {
                update[(cur.get_level() - i).get_level_number()] = cur;
            }
        }
        cur = cur.get_next_node_by_level(level::level_min);
        return std::make_pair(update, cur);
    }
};

template<typename K, typename V, typename C, size_t M = 10>
bool operator==(const skip_list<K, V, M, C> &x, const skip_list<K, V, M, C> &y) {
    if (x.size() != y.size()) {
        return false;
    }
    for (auto i = x.cbegin(), j = y.cbegin(); i != x.cend(); i++, j++) {
        if (*i != *j) {
            return false;
        }
    }
    return true;
}

template<typename K, typename V, typename C, size_t M = 10>
bool operator!=(const skip_list<K, V, M, C> &x, const skip_list<K, V, M, C> &y) {
    return !(x == y);
}