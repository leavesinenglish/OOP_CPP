#pragma once

#include "skip_list_exceptions.hpp"
#include <random>
#include <algorithm>
#include <functional>
#include <array>

template<typename Key,
        typename Value,
        typename Compare = std::less<Key>,
        typename Alloc = std::allocator<std::pair<const Key, Value>>>

class skip_list {
public:
    using value_type = std::pair<const Key, Value>;
    using pointer = value_type *;
    using const_pointer = const value_type *;
    using reference = value_type &;
    using const_reference = const value_type &;

private:
    static const size_t max_level = 10;
    Compare cmp = Compare();
    Alloc alloc = Alloc();
    using value_ptr = std::unique_ptr<value_type>;

    struct node {
        value_ptr data;
        std::array<std::shared_ptr<node>, max_level> next_node;
        node() = default;

        explicit node(value_ptr &&data) : data(std::move(data)) {}
    };

    using node_ptr = std::shared_ptr<node>;

    node_ptr constr_node(Key &&key, Value &&value) {
        auto val_ptr = value_ptr(new value_type(key, value));
        return std::make_shared<node>(std::move(val_ptr));
    }

    node_ptr head = constr_node(Key(), Value());
    size_t size_of_list = 0;
    size_t level = 0;

    template<bool is_const>
    class skip_list_iterator {
    public:
        std::shared_ptr<node> node_it;

        skip_list_iterator() = default;

        explicit skip_list_iterator(node_ptr &node) { node_it = node; }

        using value_type = std::conditional_t<is_const, const value_type, value_type>;
        using reference = value_type &;
        using pointer = value_type *;
        using iterator_category = std::forward_iterator_tag;

        skip_list_iterator &operator++() {
            if (!node_it) {
                throw Out_of_range_exception();
            }
            node_it = node_it->next_node[0];
            return *this;
        }

        skip_list_iterator &operator++(int) {
            if (!node_it) {
                throw Out_of_range_exception();
            }
            auto res = *this;
            node_it = node_it->next_node[0];
            return res;
        }

        reference operator*() const {
            if (!node_it) {
                throw Out_of_range_exception();
            }
            return *(node_it->data);
        }

        pointer operator->() const {
            if (!node_it) {
                throw Out_of_range_exception();
            }
            return node_it->data.get();
        }

        bool operator==(const skip_list_iterator &another) const {
            if (node_it && another.node_it) {
                return node_it->data->first == another.node_it->data->first
                       && node_it->data->second == another.node_it->data->second
                       && node_it->next_node == another.node_it->next_node;
            }
            if (!node_it && !another.node_it) {
                return true;
            }
            return false;
        }

        bool operator!=(const skip_list_iterator &another) const {
            return !(*this == another);
        }
    };

public:
    using iterator = skip_list_iterator<false>;
    using const_iterator = skip_list_iterator<true>;

    skip_list() = default;

    explicit skip_list(const Compare &comp, const Alloc &a = Alloc()) : cmp(comp), alloc(a) {}

    skip_list(const skip_list &another) {
        *this = another;
    }

    skip_list(skip_list &&another) noexcept {
        *this = std::move(another);
    }

    skip_list &operator=(const skip_list &another) {
        clear();
        cmp = another.cmp;
        alloc = another.alloc;
        for (auto i = another.begin(); i != another.end(); ++i) {
            (*this)[i->first] = i->second;
        }
        return *this;
    }

    skip_list &operator=(skip_list &&another)  noexcept {
        std::swap(head, another.head);
        std::swap(size_of_list, another.size_of_list);
        std::swap(level, another.level);
        std::swap(cmp, another.cmp);
        std::swap(alloc, another.alloc);
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
        return size_of_list == 0;
    }

    [[nodiscard]] size_t size() const {
        return size_of_list;
    }

    Value &operator[](const Key &key) {
        if(find(key) != end()) {
            return find(key)->second;
        }
        return insert(std::make_pair(key, Value())).first->second;
    }

    Value &at(const Key &key) {
        return (*this)[key];
    }

    const Value &at(const Key &key) const {
        return (*this)[key];
    }

    std::pair<iterator, bool> insert(const_reference val) {
        auto ret_pair = find_with_update_array(val.first);
        auto update = ret_pair.first;
        auto cur = ret_pair.second;
        if (cur && cur->data->first == val.first) {
            return std::make_pair(iterator(cur), false);
        }
        size_t new_level;
        for (new_level = 0; rand() < RAND_MAX / 2 && new_level < max_level; ++new_level) {}
        level = (new_level > level) ? new_level : level;
        node_ptr insert_node = constr_node(std::move(Key(val.first)), std::move(Value(val.second)));
        ++size_of_list;
        for (auto i = 0; i <= new_level; ++i) {
            insert_node->next_node[i] = update[i]->next_node[i];
            update[i]->next_node[i] = insert_node;
        }
        return std::make_pair(iterator(insert_node), true);
    }

    void erase(iterator position) {
        erase(position->first);
    }

    size_t erase(const Key &key) {
        auto ret_pair = find_with_update_array(key);
        auto update = ret_pair.first;
        auto cur = ret_pair.second;
        if (cur && cur->data->first == key) {
            return 1;
        }
        for (size_t i = 0; i <= level; ++i) {
            if (update[i]->next_node[i] != cur) {
                break;
            }
            update[i]->next_node[i] = cur->next_node[i];
        }
        while (level > 0 && head->next_node[level]) {
            --level;
        }
        --size_of_list;
        return 0;
    }

    void erase(iterator first, iterator last) {
        for (auto i = first; i != last;) {
            auto cur = i++;
            erase(cur);
        }
    }

    void swap(skip_list &another) {
        auto temp = std::move(*this);
        *this = std::move(another);
        another = std::move(temp);
    }

    void clear() {
        size_of_list = 0;
        level = 0;
        head = constr_node(Key(), Value());
    }

    iterator find(const Key &key) {
        auto cur = find_with_update_array(key).second;
        if (cur&& cur->data->first == key) {
            return iterator(cur);
        }
        return end();
    }

    const_iterator find(const Key &key) const {
        auto cur = find_with_update_array(key).second;
        if (cur&& cur->data->first == key) {
            return const_iterator(cur);
        }
        return cend();
    }

private:
    std::pair<std::array<node_ptr, max_level>, node_ptr> find_with_update_array(const Key &key) const{
        std::array<node_ptr, max_level> update;
        std::fill(update.begin(), update.end(), head);
        auto cur = head;
        for (auto i = 0; i <= level; ++i) {
            while (cur->next_node[level - i] && cmp(cur->next_node[level - i]->data->first, key)) {
                cur = cur->next_node[level - i];
            }
            update[level - i] = cur;
        }
        cur = cur->next_node[0];
        return std::make_pair(update, cur);
    }
};

template<typename K, typename V, typename C, typename A>
bool operator==(const skip_list<K, V, C, A> &x, const skip_list<K, V, C, A> &y) {
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

template<typename K, typename V, typename C, typename A>
bool operator!=(const skip_list<K, V, C, A> &x, const skip_list<K, V, C, A> &y) {
    return !(x == y);
}