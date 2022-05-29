#include "dijkstra/graph.hpp"

Graph::Graph() noexcept : v_number(0){};

Graph::Graph(int v_number) noexcept
    : v_number(v_number), adj_list(std::vector<std::list<Edge>>(v_number)) {
}

Graph::Graph(Graph &that) noexcept
    : v_number(that.v_number), adj_list(std::vector<std::list<Edge>>(v_number)) {
}

void Graph::add_edge(int from, int to, float cost) {
    Edge edge = {to, cost};
    adj_list[from].push_back(std::move(edge));
}

const std::vector<std::list<Edge>> &Graph::as_adj_list() const noexcept {
    return adj_list;
}

int Graph::get_v_number() const noexcept {
    return v_number;
}

void Graph::set_v_number(int v_number) {
    Graph::v_number = v_number;
    adj_list.clear();
    adj_list.resize(v_number);
}

std::istream &operator>>(std::istream &stream, Graph &graph) {
    int v_number, e_number, from, to;
    float cost;

    stream >> v_number >> e_number;
    graph.set_v_number(v_number);

    for (int idx = 0; idx < e_number; ++idx) {
        stream >> from >> to >> cost;
        graph.add_edge(from, to, cost);
    }

    return stream;
}
