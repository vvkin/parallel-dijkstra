#pragma once

#include <list>
#include <vector>
#include <ostream>
#include <istream>

struct Edge {
    int to;
    float cost;
};

class Graph {
  public:
    Graph() noexcept;

    Graph(int v_number, int e_number) noexcept;

    Graph(Graph &that) noexcept;

    void add_edge(int from, int to, float cost);

    const std::vector<std::vector<Edge>> &as_adj_list() const noexcept;

    int get_v_number() const noexcept;

    void set_v_number(int v_number);

    int get_e_number() const noexcept;

    void set_e_number(int e_number);

    friend std::istream &operator>>(std::istream &stream, Graph &graph);

  private:
    int v_number;
    int e_number;
    std::vector<std::vector<Edge>> adj_list;
};

std::istream &operator>>(std::istream &stream, Graph &graph);

std::ostream &operator<<(std::ostream &stream, const Graph &graph);
