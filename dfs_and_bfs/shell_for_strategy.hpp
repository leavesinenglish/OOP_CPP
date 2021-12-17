#pragma once
#include "dfs_and_bfs.hpp"


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