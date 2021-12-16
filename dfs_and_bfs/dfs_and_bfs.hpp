#pragma once

#include <memory>
#include <stack>
#include <queue>
#include <set>
#include "graph.hpp"
#include "path_finder.hpp"

class Strategy {
public:
    using vertex_type = typename Graph::vertex_type;

    explicit Strategy(Graph &graph_, std::shared_ptr<Find_path> &path_finder_) : graph(graph_),
                                                                                 path_finder(path_finder_) {};

    virtual ~Strategy() = default;

    std::shared_ptr<Find_path> path_finder;

    virtual void run(const vertex_type &first) = 0;

    [[nodiscard]] bool is_cyclic() const {
        return path_finder->is_cyclic();
    }

protected:
    friend class Founder;

    Graph &graph;

    void begin(const vertex_type &vertex) const { this->path_finder->begin(vertex); };

    void end() const { this->path_finder->end(); };

    void visit_vertex(const vertex_type &vertex) const { this->path_finder->visit_vertex(vertex); };

    void visit_edge(const vertex_type &first, const vertex_type &second) const {
        this->path_finder->visit_edge(first, second);
    };;

    std::unordered_map<vertex_type, vertex_type> prev;
};

class DFS final : public Strategy {
private:
    using vertex_type = typename Graph::vertex_type;
public:
    explicit DFS(Graph &graph_, std::shared_ptr<Find_path> &path_finder_) : Strategy(graph_, path_finder_) {};

    void run(const vertex_type &first) override {
        if (graph.vertices_count() == 0) {
            return;
        }
        this->prev.clear();
        std::stack<std::pair<vertex_type, bool>> stack;
        this->begin(first);
        stack.push(std::make_pair(first, false));
        this->prev[first] = first;
        while (!stack.empty()) {
            auto&[vertex, visited] = stack.top();
            if (!visited) {
                this->visit_vertex(vertex);
                this->visit_edge(this->prev.at(vertex), vertex);
                visited = true;
                if (path_finder->is_completed()) {
                    break;
                }
                const auto &neighbours = this->graph.neighbour_vertices(vertex);
                for (auto i = neighbours.crbegin(); i != neighbours.crend(); i++) {
                    if (*i != this->prev[vertex]) {
                        stack.push(std::make_pair(*i, false));
                        this->prev[*i] = vertex;
                    }
                }
            } else {
                stack.pop();
            }
        }
        this->end();
    }
};

class BFS final : public Strategy {
private:
    using vertex_type = typename Graph::vertex_type;
public:
    explicit BFS(Graph &graph_, std::shared_ptr<Find_path> &path_finder_) : Strategy(graph_, path_finder_) {};

    void run(const vertex_type &first) override {
        if (this->graph.vertices_count() == 0) {
            return;
        }
        this->prev.clear();
        std::queue<vertex_type> q;
        this->begin(first);
        q.push(first);
        this->prev[first] = first;
        while (!q.empty()) {
            auto cur = q.front();
            q.pop();
            this->visit_vertex(cur);
            this->visit_edge(this->prev.at(cur), cur);
            if (this->path_finder->is_completed()) {
                break;
            }
            const auto &neighbours = this->graph.neighbour_vertices(cur);
            for (auto i = neighbours.crbegin(); i != neighbours.crend(); ++i) {
                if (*i != this->prev[cur]) {
                    q.push(*i);
                    this->prev[*i] = cur;
                }
            }
        }
        this->end();
    }
};

class Traverser final {
    using vertex_type = typename Graph::vertex_type;
    const std::shared_ptr<Strategy> strategy;
    const Graph &graph;
public:
    Traverser(Graph &graph, std::shared_ptr<Strategy> &strategy) : graph(graph), strategy(strategy) {}

    void begin_strategy(const vertex_type &first) {
        strategy->run(first);
    }

    [[nodiscard]] std::deque<vertex_type> get_path() const {
        return strategy->path_finder->get_path();
    }

    [[nodiscard]] bool is_cyclic() {
        return strategy->is_cyclic();
    }
};