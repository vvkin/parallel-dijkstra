#include "dijkstra/graph.hpp"

Graph::Graph(int v_number) noexcept {
    this->v_number = v_number;
    this->adj_list = std::vector<std::list<Edge>>(this->v_number);
}

Graph::Graph(Graph &that) noexcept {
    this->v_number = that.v_number;
    this->adj_list = std::vector<std::list<Edge>>(this->v_number);
}

void Graph::add_edge(int from, int to, double cost) {
    Edge edge = {to, cost};
    this->adj_list[from].push_back(edge);
}

std::vector<std::list<Edge>> Graph::as_adj_list() const {
    return this->adj_list;
}

int Graph::get_vertices_number() const {
    return this->v_number;
}
