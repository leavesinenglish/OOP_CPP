#pragma once
#include <memory>
#include <stack>
#include <queue>
#include <set>
#include <utility>
#include "graph.hpp"
#include "path_finder.hpp"


class Strategy {
public:
    using vertex_type = typename Graph::vertex_type;

    explicit Strategy(Graph &graph_, std::shared_ptr<Find_path> path_finder_) : graph(graph_),
                                                                                 path_finder(std::move(path_finder_)) {};
    virtual ~Strategy() = default;

    std::shared_ptr<Find_path> path_finder;

    virtual void run(const vertex_type &first) = 0;

    [[nodiscard]] bool is_cyclic() const {
        return path_finder->is_cyclic();
    }
protected:
    friend class Traverser;

    Graph &graph;

    void begin(const vertex_type &vertex) const { path_finder->begin(vertex); };

    void end() const { path_finder->end(); };

    void visit_vertex(const vertex_type &vertex) const { path_finder->visit_vertex(vertex); };

    void visit_edge(const vertex_type &first, const vertex_type &second) const {
        path_finder->visit_edge(first, second);
    };

    std::unordered_map<vertex_type, vertex_type> prev;
};


class DFS final : public Strategy {
private:
    using vertex_type = typename Graph::vertex_type;
public:
    explicit DFS(Graph &graph_, std::shared_ptr<Find_path> path_finder_) : Strategy(graph_, std::move(path_finder_)) {};

    void run(const vertex_type &first) override {
        if (graph.vertices_count() == 0) {
            return;
        }
        prev.clear();
        std::stack<std::pair<vertex_type, bool>> stack;
        begin(first);
        stack.push(std::make_pair(first, false));
        prev[first] = first;
        while (!stack.empty()) {
            auto&[vertex, visited] = stack.top();
            if (!visited) {
                visit_vertex(vertex);
                visit_edge(prev.at(vertex), vertex);
                visited = true;
                if (path_finder->is_completed()) {
                    break;
                }
                const auto &neighbours = graph.neighbour_vertices(vertex);
                for (auto i = neighbours.crbegin(); i != neighbours.crend(); i++) {
                    if (*i != prev[vertex]) {
                        stack.push(std::make_pair(*i, false));
                        prev[*i] = vertex;
                    }
                }
            } else {
                stack.pop();
            }
        }
        end();
    }
};

class BFS final : public Strategy {
private:
    using vertex_type = typename Graph::vertex_type;
public:
    explicit BFS(Graph &graph_, std::shared_ptr<Find_path> path_finder_) : Strategy(graph_, std::move(path_finder_)) {};

    void run(const vertex_type &first) override {
        if (graph.vertices_count() == 0) {
            return;
        }
        prev.clear();
        std::queue<vertex_type> q;
        begin(first);
        q.push(first);
        prev[first] = first;
        while (!q.empty()) {
            auto cur = q.front();
            q.pop();
            visit_vertex(cur);
            visit_edge(prev.at(cur), cur);
            if (path_finder->is_completed()) {
                break;
            }
            const auto &neighbours = graph.neighbour_vertices(cur);
            for (auto i = neighbours.crbegin(); i != neighbours.crend(); ++i) {
                if (*i != prev[cur]) {
                    q.push(*i);
                    prev[*i] = cur;
                }
            }
        }
        end();
    }
};