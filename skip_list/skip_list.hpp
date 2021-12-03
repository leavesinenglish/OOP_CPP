#pragma once

#include "skip_list_exceptions.hpp"
#include <random>
#include <vector>

template<typename Key,
        typename Value,size_t Max_level = 10,
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

    class node final{
    public:
        bool operator == (const node &another){
            if (*this && another) {
                return *this->data->first == another->data->first
                       && *this->data->second == another->data->second
                       && *this->next_node == another->next_node;
            }
            if (!*this && !another) {
                return true;
            }
            return false;
        }

        node() = default;
        explicit node(const pointer &data_, size_t level_) : data(data_), level(level_) {
            next_node(Max_level+1);
        };
        const Key &get_key() const {
            return data->first;
        }

        pointer get_data() const {
            return data;
        }

        [[nodiscard]] std::shared_ptr<node> &get_next_node_by_index(size_t i) const {
            return next_node[i];
        }

        [[nodiscard]] constexpr size_t get_level() const noexcept{
            return level;
        }
    private:
        pointer data;
        std::vector<std::shared_ptr<node>> next_node;
        size_t level;
    };

    node head = {};
    size_t size_ = 0;

    template<bool is_const>
    class skip_list_iterator {
    public:
        std::shared_ptr<node> node_it;

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
            return *(node_it->data);
        }

        pointer operator->() const {
            if (!node_it) {
                throw Out_of_range_exception();
            }
            return node_it->data;
        }

//        bool operator==(const skip_list_iterator &another) const {
//            if (node_it && another.node_it) {
//                return node_it->data->first == another.node_it->data->first
//                       && node_it->data->second == another.node_it->data->second
//                       && node_it->next_node == another.node_it->next_node;
//            }
//            if (!node_it && !another.node_it) {
//                return true;
//            }
//            return false;
//        }

        bool operator!=(const skip_list_iterator &another) const {
            return !(*this == another);
        }
    };

public:
    using iterator = skip_list_iterator<false>;
    using const_iterator = skip_list_iterator<true>;

    skip_list() = default;

    explicit skip_list(const Compare &comp) {cmp = comp;}

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
        //std::swap(level_, another.level_);
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
        if (*iter != key){
            throw Out_of_range_exception();
        }
        return (*this)[key];
    }

    const Value &at(const Key &key) const {
        const_iterator iter = find(key);
        if (*iter != key){
            throw Out_of_range_exception();
        }
        return (*this)[key];
    }

    std::pair<iterator, bool> insert(const_reference val) {
        std::mt19937 random(0);
        std::uniform_int_distribution<> uid(0, Max_level);
        auto const &[update, cur] = find_with_update_array(val.first);
        if (cur && cur->get_key() == val.first) {
            return std::make_pair(iterator(cur), false);
        }
        size_t new_level = uid(random);
        auto insert_node = new node(val.first, new_level);
        ++size_;
        auto next_node = insert_node->get_next_node_vector();
        for (auto i = 0; i <= new_level; ++i) {
            next_node[i] = update[i]->next_node[i];
            update[i]->get_next_node_vector()[i] = insert_node;
        }
        return std::make_pair(iterator(insert_node), true);
    }

    void erase(iterator position) {
        erase(position->first);
    }

    size_t erase(const Key &key) {
        auto[update, cur] = find_with_update_array(key);
        if (cur && cur->get_key() == key) {
            return 1;
        }
        for (size_t i = 0; i <= Max_level; ++i) {
            if (update[i]->get_next_node_vector()[i] != cur) {
                break;
            }
            update[i]->get_next_node_vector()[i] = cur->get_next_node_vector()[i];
        }
        --size_;
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
        *this = {};
    }

    iterator find(const Key &key) {
        auto cur = find_without_update_array(key);
        if (cur && cur->get_key() == key) {
            return iterator(cur);
        }
        return end();
    }

    const_iterator find(const Key &key) const {
        auto cur = find_without_update_array(key);
        if (cur && cur->get_key() == key) {
            return const_iterator(cur);
        }
        return cend();
    }

private:
    std::shared_ptr<node> find_without_update_array(const Key &key) const {
        auto cur = head;
        for (auto i = 0; i <= Max_level; ++i) {
            while (cur.get_next_node_vector()[Max_level - i] && cmp(cur.get_next_node_vector()[Max_level - i]->get_data()->first, key)) {
                cur = cur.get_next_node_vector()[Max_level - i];
            }
        }
        return cur->next_node[0];
    }

    std::pair<std::vector<std::shared_ptr<node>>, std::shared_ptr<node>> find_with_update_array(const Key &key) const {
        std::vector<std::shared_ptr<node>> update(Max_level+1);
        std::fill(update.begin(), update.end(), head);
        auto cur = head;
        for (auto i = 0; i <= Max_level; ++i) {
            while (cur.get_next_node_vector()[Max_level - i] && cmp(cur.get_next_node_vector()[Max_level - i]->get_data()->first, key)) {
                cur = cur.get_next_node_vector()[Max_level - i];
            }
            update[Max_level - i] = cur;
        }
        cur = cur.get_next_node_vector()[0];
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