#pragma once
#include "graph.hpp"
#include <unordered_map>

class Find_path {
public:
    using vertex_type = typename Graph::vertex_type;

    Find_path() = default;

    virtual ~Find_path() = default;

    virtual void begin(const vertex_type &first_)  {
        first = first_;
        completed = false;
        path.clear();
    }

    virtual void visit_vertex(const vertex_type &v)  {
        completed = comp(v);
    }

    virtual void visit_edge(const vertex_type &first, const vertex_type &second) {
        completed = comp(first, second);
        prev[second] = first;
    }

    virtual void end() {
        if (!(completed)) {
            path.clear();
            return;
        }
        trace_path();
    }

    [[nodiscard]] const bool is_completed() const {
        return completed;
    }

    [[nodiscard]] const std::deque<vertex_type> &get_path() const {
        return path;
    }

protected:
    std::unordered_map<vertex_type, vertex_type> prev{};

    virtual bool comp(const vertex_type &vertex) = 0;

    virtual bool comp(const vertex_type &first, const vertex_type &second) = 0;

    virtual void trace_path() = 0;

    bool completed = false;
    vertex_type first{};
    std::deque<vertex_type> path{};
};

class Find_path_to_vertex final : public Find_path {
public:
    using vertex_type = typename Graph::vertex_type;

    Find_path_to_vertex() = delete;

    explicit Find_path_to_vertex(const vertex_type &target) : Find_path(), target_(target) {}

private:
    const vertex_type target_;

    bool comp(const vertex_type &vertex) override {
        return vertex == target_;
    }

    bool comp(const vertex_type &first, const vertex_type &second) override {
        return this->completed;
    }

    void trace_path() override {
        auto v = target_;
        while (v != this->first) {
            this->path.emplace_front(v);
            v = this->prev[v];
        }
        this->path.emplace_front(v);
    }
};

class Find_path_to_edge final : public Find_path {
public:
    using vertex_type = typename Graph::vertex_type;

    Find_path_to_edge() = delete;

    explicit Find_path_to_edge(const vertex_type &first_, const vertex_type &second_)
            : Find_path(), first(first_), second(second_) {}

private:
    const vertex_type first, second;

    bool comp(const vertex_type &) override {
        return this->completed;
    }

    bool comp(const vertex_type &first_, const vertex_type &second_) override {
        return first == first_ && second == second_;
    }

    void trace_path() override {
        auto v = second;
        while (v != this->first) {
            this->path.emplace_front(v);
            v = this->prev[v];
        }
        this->path.emplace_front(v);
    }
};