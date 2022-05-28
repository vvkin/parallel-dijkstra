#pragma once

#include <list>
#include <vector>
#include <string>

struct Edge {
    int to;
    float cost;
};

class Graph {
  public:
    Graph(int v_number);
    Graph(Graph &that);

    void add_edge(int from, int to, float cost);

    std::vector<std::list<Edge>> as_adj_list();

    int get_vertices_number();

  private:
    int v_number;
    std::vector<std::list<Edge>> adj_list;
};
