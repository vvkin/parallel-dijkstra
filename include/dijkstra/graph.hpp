#pragma once

#include <list>
#include <vector>
#include <string>

struct Edge {
    int to;
    double cost;
};

class Graph {
  public:
    Graph(int v_number) noexcept;
    Graph(Graph &that) noexcept;

    void add_edge(int from, int to, double cost);

    std::vector<std::list<Edge>> as_adj_list() const;

    int get_vertices_number() const;

  private:
    int v_number;
    std::vector<std::list<Edge>> adj_list;
};
