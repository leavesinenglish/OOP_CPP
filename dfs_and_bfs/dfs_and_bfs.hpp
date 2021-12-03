#pragma once

#include <memory>
#include <stack>
#include <queue>
#include <set>
#include "graph.hpp"
#include "traverser.hpp"

class Strategy {
public:
    using vertex_type = typename Graph::vertex_type;

    Strategy() = delete;
    explicit Strategy(Graph &graph_, std::shared_ptr<Traverser> &traverser_) : graph(graph_), traverser(traverser_) {};
    virtual void execute(const vertex_type & first) = 0;

    virtual ~Strategy() = default;

protected:
    Graph &graph;
    std::shared_ptr<Traverser> traverser;
    void begin(const vertex_type &vertex) const { traverser->begin(vertex); };
    void end() const {};
    void visit_vertex(const vertex_type &vertex) const {};
    void visit_edge(const vertex_type &first, const vertex_type &second) const {};
    std::map<vertex_type, vertex_type> prev;
};

class DFS final : Strategy {
public:
    DFS() = delete;
    explicit DFS(Graph &graph_, std::shared_ptr<Traverser> &traverser_): Strategy(graph_, traverser_){};

    using vertex_type = typename Graph::vertex_type;

    void execute(const vertex_type &first) override {
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
                if (traverser->is_completed()) {
                    break;
                }
                const auto &neighbours = this->graph.neighbour_vertices(vertex);
                for (auto i = neighbours.crbegin(); i != neighbours.crend(); ++i) {
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

class BFS final : Strategy {
public:
    BFS() = delete;
    explicit BFS(Graph &graph_, std::shared_ptr<Traverser> &traverser_): Strategy(graph_, traverser_){};

    using vertex_type = typename Graph::vertex_type;

    void execute(const vertex_type &first) override {

    }
};