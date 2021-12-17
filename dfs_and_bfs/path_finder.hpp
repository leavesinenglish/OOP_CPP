#pragma once

#include "graph.hpp"
#include <unordered_map>

class Find_path {
public:
    using vertex_type = typename Graph::vertex_type;

    Find_path() = default;

    virtual ~Find_path() = default;

    [[nodiscard]] bool is_completed() const {
        return completed;
    }

    [[nodiscard]] bool is_cyclic() const {
        return cyclic;
    }

    [[nodiscard]] const std::deque<vertex_type> &get_path() const {
        return path;
    }

    virtual void begin(const vertex_type &first_) {
        first = first_;
        completed = false;
        cyclic = false;
        path.clear();
    }

    virtual void visit_vertex(const vertex_type &v) {
        completed = comp(v);
    }

    virtual void visit_edge(const vertex_type &first_, const vertex_type &second) {
        completed = comp(first_, second);
        prev[second] = first_;
    }

    virtual void end() {
        if (!(completed)) {
            path.clear();
            return;
        }
        trace_path();
    }

protected:
    virtual bool comp(const vertex_type &vertex) = 0;

    virtual bool comp(const vertex_type &first, const vertex_type &second) = 0;

    virtual void trace_path() = 0;

    std::unordered_map<vertex_type, vertex_type> prev{};
    bool completed = false;
    bool cyclic = false;
    vertex_type first{};
    std::deque<vertex_type> path{};
};

class Check_cyclic final : public Find_path {
public:
    using vertex_type = typename Graph::vertex_type;

    Check_cyclic() = default;

    void visit_vertex(const vertex_type &v) override {
        if (visited.find(v) != visited.end()) {
            completed = true;
            cyclic = true;
            return;
        }
        visited.emplace(v);
    }

    void visit_edge(const vertex_type &first, const vertex_type &second) override {}

private:
    bool comp(const vertex_type &vertex) final { return false; }

    bool comp(const vertex_type &first, const vertex_type &second) final { return false; }

    void trace_path() final {}

    void begin(const vertex_type &first) override {}

    void end() override {}

    std::set<vertex_type> visited;
    std::unordered_map<vertex_type, vertex_type> prev;
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
        return completed;
    }

    void trace_path() override {
        auto v = target_;
        while (v != first) {
            path.emplace_front(v);
            v = prev[v];
        }
        path.emplace_front(v);
    }
};

class Find_path_to_edge final : public Find_path {
public:
    using vertex_type = typename Graph::vertex_type;

    Find_path_to_edge() = delete;

    explicit Find_path_to_edge(const vertex_type &first_, const vertex_type &second_)
            : Find_path(), source(first_), destination(second_) {}

private:
    const vertex_type source, destination;

    bool comp(const vertex_type &) override {
        return completed;
    }

    bool comp(const vertex_type &first_, const vertex_type &second_) override {
        return source == first_ && destination == second_;
    }

    void trace_path() override {
        auto v = destination;
        while (v != first) {
            path.emplace_front(v);
            v = prev[v];
        }
        path.emplace_front(v);
    }
};