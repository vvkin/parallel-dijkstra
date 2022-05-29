#pragma once

#include <list>
#include <vector>
#include <fstream>

struct Edge {
    int to;
    float cost;
};

class Graph {
  public:
    Graph() noexcept;

    Graph(int v_number) noexcept;

    Graph(Graph &that) noexcept;

    void add_edge(int from, int to, float cost);

    const std::vector<std::list<Edge>> &as_adj_list() const noexcept;

    int get_v_number() const noexcept;

    void set_v_number(int v_number);

  private:
    int v_number;
    std::vector<std::list<Edge>> adj_list;
};

std::istream &operator>>(std::istream &stream, Graph &graph);
