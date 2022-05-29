#pragma once

#include <list>
#include <vector>

struct Edge {
    int to;
    double cost;

    Edge(const Edge &that) noexcept = default;

    Edge(Edge &&that) noexcept = default;

    Edge() noexcept = default;
};

class Graph {
  public:
    Graph(int v_number) noexcept;
    Graph(Graph &that) noexcept;

    void add_edge(int from, int to, double cost);

    const std::vector<std::list<Edge>> &as_adj_list() const noexcept;

    int get_vertices_number() const noexcept;

  private:
    int v_number;
    std::vector<std::list<Edge>> adj_list;
};
