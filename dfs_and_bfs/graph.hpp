#pragma once

#include <unordered_map>
#include <vector>

class Graph final {
public:
    using vertex_type = int;

    Graph() = default;

    explicit Graph(const std::vector<std::pair<const vertex_type, const vertex_type>> &edges) {
        for (const auto &[first, second]: edges) {
            add_edge(first, second);
        }
    }

    void add_edge(const vertex_type &first, const vertex_type &second) {
        auto a = data[first];
        if (std::find(a.begin(), a.end(), second) != a.end()) {
            return;
        }
        data[first].push_back(second);
        data[second];
    }

    [[nodiscard]] const std::vector<vertex_type> &neighbour_vertices(const vertex_type &v) const {
        return data.at(v);
    }

    [[nodiscard]] size_t vertices_count() const {
        return data.size();
    }

private:
    std::unordered_map<vertex_type, std::vector<vertex_type>> data{};
};