#pragma once

#include "skip_list_exceptions.hpp"
#include <random>
#include <vector>
#include <utility>

namespace details {
    template<size_t Max_level = 10>
    class level final {
    private:
        size_t level_ = 0;
    public:
        static const level level_min;
        static const level level_max;
        static const size_t max_alloc_size;

        explicit level(size_t lvl) : level_{lvl} {
            if (lvl <= Max_level) {
                level_ = lvl;
            } else {
                throw Out_of_range_exception();
            }
        }

        level &operator++() {
            return *this = level(level_ + 1);
        }

        level operator++(int) {
            auto tmp = *this;
            ++(*this);
            return tmp;
        }

        level operator-(const level &another) const {
            return level(level_ - another.level_);
        }

        bool operator>=(const level &another) {
            return (level_ >= another.level_);
        }

        bool operator<=(const level &another) {
            return (level_ <= another.level_);
        }

        bool operator<(const level &another) {
            return (level_ < another.level_);
        }

        bool operator==(const level &another) {
            return (level_ == another.level_);
        }

        [[nodiscard]] constexpr size_t get_level_number() const noexcept {
            return level_;
        }

        [[nodiscard]] static level get_random_level() noexcept {
            std::mt19937 random(0);
            std::uniform_int_distribution<> uid(0, Max_level);
            return level(uid(random));
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
    using const_reference = std::add_lvalue_reference_t<std::add_const<value_type>>;

private:
    using level = details::level<Max_level>;
    inline static  Compare cmp = Compare();

    class node final {
    public:

        void swap(node &another) noexcept{
            auto tmp = std::move(*this);
            *this = std::move(another);
            another = std::move(tmp);
        }

        bool operator==(const node &another) {
            return data->first == another->data->first
                   && data->second == another->data->second
                   && next_node == another->next_node
                   && Level == another.Level;
        }

        node &operator=(const node &another) {
            if (this != &another) {
                data = another.data;
                Level = another.Level;
                next_node = another.next_node;
            }
            return *this;
        }

        explicit node(const pointer data_, const level &level_) : data(data_), Level(level_), next_node(std::vector<std::shared_ptr<node>>(Level.get_alloc_size())) {};

        const Key &get_key() const {
            return data->first;
        }

        pointer get_data() const {
            return data;
        }

        [[nodiscard]] std::shared_ptr<node> get_next_node_by_level(level i) const {
            return next_node[i.get_level_number()];
        }

        [[nodiscard]] constexpr level get_level() const noexcept {
            return Level;
        }

    private:
        pointer data = nullptr;
        std::vector<std::shared_ptr<node>> next_node;
        level Level;
    };

    node head = node(nullptr, level(Max_level));
    size_t size_ = 0;

    template<bool is_const>
    class skip_list_iterator {
    private:
        std::shared_ptr<node> node_it;
        friend class skip_list<Key, Value>;
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
            node_it = node_it->get_next_node_by_level(level(0));
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

        bool operator==(const skip_list_iterator &another) const {
            return node_it == another.node_it;
        }

        bool operator!=(const skip_list_iterator &another) const {
            return !(*this == another);
        }
    };

public:
    using iterator = skip_list_iterator<false>;
    using const_iterator = skip_list_iterator<true>;

    skip_list() = default;

    explicit skip_list(const Compare &comp) { cmp = comp; }

    skip_list(const skip_list &another) {
        *this = another;
    }

    skip_list(skip_list &&another) noexcept {
        *this = std::move(another);
    }

    skip_list &operator=(const skip_list &another) {
        if (this != &another) {
            clear();
            cmp = another.cmp;
            head = another.head;
            size_ = another.size_;
        }
        return *this;
    }

    void swap(skip_list &another){
        auto tmp = std::move(*this);
        *this = std::move(another);
        another = std::move(tmp);
    }

    skip_list &operator=(skip_list &&another) noexcept {
        head.swap(another.head);
        std::swap(size_, another.size_);
        std::swap(cmp, another.cmp);
        return *this;
    }

    iterator begin() {
        return iterator(head.get_next_node_by_level(level(0)));
    }

    const_iterator begin() const {
        return const_iterator(head.get_next_node_by_level(level(0)));
    }

    iterator end() {
        return {};
    }

    const_iterator end() const {
        return {};
    }

    const_iterator cbegin() const {
        return const_iterator(head.get_next_node_by_level(level(0)));
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
        if (iter->first != key) {
            throw Out_of_range_exception();
        }
        return (*this)[key];
    }

    const Value &at(const Key &key) const {
        const_iterator iter = find(key);
        if (iter->first != key) {
            throw Out_of_range_exception();
        }
        return (*this)[key];
    }

    std::pair<iterator, bool> insert(const value_type &val) {
        auto const &[update, cur] = find_with_update_array(true, val.first);
        if (cur && cur->get_data()) {
            if(cur->get_key() == val.first) {
                return std::make_pair(iterator(cur), false);
            }
        }
        auto val_ptr = new std::pair<const Key, Value>(val.first, val.second);
        auto insert_node = std::make_shared<node>(val_ptr, level::get_random_level());
        ++size_;
        //auto next_node = insert_node->get_next_node_by_level(level(0));
        for (level i = level::level_min; i < insert_node->get_level(); ++i) {
            insert_node->get_next_node_by_level(i) = update[i.get_level_number()]->get_next_node_by_level(i);
            update[i.get_level_number()]->get_next_node_by_level(i) = insert_node;
        }
        insert_node->get_next_node_by_level(insert_node->get_level()) = update[insert_node->get_level().get_level_number()]->get_next_node_by_level(insert_node->get_level());
        update[insert_node->get_level().get_level_number()]->get_next_node_by_level(insert_node->get_level()) = insert_node;
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
        auto const &[update, deletable] = find_with_update_array(true, first->first);
        size_t n_of_delete;
        for (auto a = first; a != last; a++) {
            n_of_delete++;
        }
        size_ -= n_of_delete;
        auto cur = last.node_it; ///node_it привытный а ты его грязными ручонками трогаешь
        for (level i = level::level_min; i <= level::level_max; i++) {
            if (cur->get_level() >= i) {
                update[i.get_level_number()]->get_next_node_by_level(i) = cur;
            } else {
                if (cur->get_next_node_by_level(level::level_min)) {
                    cur = cur->get_next_node_by_level(level::level_min);
                }
            }
        }
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
        std::vector<std::shared_ptr<node>> update(head.get_level().get_alloc_size());
//        if (with_update) {
//            std::fill(update.begin(), update.end(), head);
//        }
        auto cur = head;
        for (level i = level::level_min; i < level::level_max; ++i) {
            while (cur.get_next_node_by_level(cur.get_level() - i) &&
                   cmp(cur.get_next_node_by_level(cur.get_level() - i)->get_data()->first, key)) {
                cur = *cur.get_next_node_by_level(cur.get_level() - i).get();
            }
            if (with_update) {
                update[(cur.get_level() - i).get_level_number()] = std::make_shared<node>(cur);
            }
        }
        while (cur.get_next_node_by_level(level::level_min) &&
               cmp(cur.get_next_node_by_level(level::level_min)->get_data()->first, key)) {
            cur = *cur.get_next_node_by_level(level::level_min).get();
        }
        if (with_update) {
            update[level::level_min.get_level_number()] = std::make_shared<node>(cur);
        }
        if (cur.get_next_node_by_level(level::level_min)) {
            cur = *cur.get_next_node_by_level(level::level_min).get();
        }
        return std::make_pair(update, std::make_shared<node>(cur));
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