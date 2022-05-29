#include "dijkstra/graph.hpp"

Graph::Graph(int v_number) noexcept
    : v_number(v_number), adj_list(std::vector<std::list<Edge>>(this->v_number)) {
}

Graph::Graph(Graph &that) noexcept
    : v_number(that.v_number), adj_list(std::vector<std::list<Edge>>(this->v_number)) {
}

void Graph::add_edge(int from, int to, double cost) {
    Edge edge = {to, cost};
    this->adj_list[from].push_back(std::move(edge));
}

const std::vector<std::list<Edge>> &Graph::as_adj_list() const noexcept {
    return this->adj_list;
}

int Graph::get_vertices_number() const noexcept {
    return this->v_number;
}
