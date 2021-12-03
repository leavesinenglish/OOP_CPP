#pragma once
#include "graph.hpp"

class Traverser {
public:
    using vertex_type = typename Graph::vertex_type;

    Traverser() = default;
    virtual ~Traverser() = default;
    virtual void begin(const vertex_type &first_) = 0;
    virtual void visit_vertex(const vertex_type &v) = 0;
    virtual void visit_edge(const vertex_type &first, const vertex_type &second) = 0;
    virtual void end() = 0;

    [[nodiscard]] const bool is_completed() const {
        return completed;
    }
    const std::vector<vertex_type>& get_path() const {
        return path;
    }
protected:
    bool completed = false;
    vertex_type first{};
    std::vector<vertex_type> path{};
};

class Find_path : public Traverser {
public:
    using vertex_type = typename Graph::vertex_type;

    Find_path() = default;
    virtual ~Find_path() = default;

    void begin(const vertex_type &first_) override {
        this->first = first_;
        this->completed = false;
        this->path.clear();
    }

    void visit_vertex(const vertex_type &v) override {
        this->completed = comp(v);
    }

    void visit_edge(const vertex_type &first, const vertex_type &second) override {
        this->completed = comp(first, second);
        prev[second] = first;
    }

    void end() override {
        if (!(this->completed)) {
            this->path.clear();
            return;
        }
        trace_path();
        std::reverse(this->path.begin(), this->path.end());
    }
protected:
    std::map<vertex_type, vertex_type> prev{};
    virtual bool comp(const vertex_type &vertex) = 0;
    virtual bool comp(const vertex_type &first, const vertex_type &second) = 0;
    virtual void trace_path() = 0;
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
            this->path.emplace_back(v);
            v = this->prev[v];
        }
        this->path.emplace_back(v);
    }
};

class Find_path_to_edge final : public Find_path {
public:
    using vertex_type = typename Graph::vertex_type;

    Find_path_to_edge() = delete;
    explicit Find_path_to_edge(const vertex_type &first_, const vertex_type &second_) : Find_path(), first(first_), second(second_) {}
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
            this->path.emplace_back(v);
            v = this->prev[v];
        }
        this->path.emplace_back(v);
    }
};