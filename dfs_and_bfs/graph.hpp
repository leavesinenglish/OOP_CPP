#pragma once

#include <unordered_map>
#include <vector>

class Graph final {
public:
    using vertex_type = int;

    Graph() = default;

    void add_edge(const vertex_type &first, const vertex_type &second) {
        data[first].push_back(second);
        //check, проверить связность, конструктор с ребрами, стратегия
        data[second];
    }

    [[nodiscard]] const std::vector<vertex_type> &neighbour_vertices(const vertex_type &v) const {
        return data.at(v);
    }

    [[nodiscard]] const size_t vertices_count() const {
        return data.size();
    }

private:
    std::unordered_map<vertex_type, std::vector<vertex_type>> data{};
};