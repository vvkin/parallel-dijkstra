#include "dijkstra/graph.hpp"

Graph::Graph() noexcept : v_number(0), e_number(0){};

Graph::Graph(int v_number, int e_number) noexcept
    : v_number(v_number), e_number(e_number), adj_list(std::vector<std::vector<Edge>>(v_number)) {
}

Graph::Graph(Graph &that) noexcept
    : v_number(that.v_number), e_number(that.e_number),
      adj_list(std::vector<std::vector<Edge>>(v_number)) {
}

void Graph::add_edge(int from, int to, float cost) {
    Edge edge = {to, cost};
    adj_list[from].push_back(std::move(edge));
}

const std::vector<std::vector<Edge>> &Graph::as_adj_list() const noexcept {
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

int Graph::get_e_number() const noexcept {
    return e_number;
}

void Graph::set_e_number(int e_number) {
    Graph::e_number = e_number;
}

std::istream &operator>>(std::istream &stream, Graph &graph) {
    int v_number, e_number;
    size_t size;

    stream.read((char *)&v_number, sizeof(v_number));
    stream.read((char *)&e_number, sizeof(e_number));

    graph.set_v_number(v_number);
    graph.set_e_number(e_number);
    auto &adj_list = graph.adj_list;

    for (int v_idx = 0; v_idx < v_number; ++v_idx) {
        stream.read((char *)&size, sizeof(size));
        adj_list[v_idx].resize(size);
        stream.read((char *)&adj_list[v_idx][0], size * sizeof(Edge));
    }

    return stream;
}

std::ostream &operator<<(std::ostream &stream, const Graph &graph) {
    auto v_number = graph.get_v_number();
    auto e_number = graph.get_e_number();
    auto &adj_list = graph.as_adj_list();

    stream.write((char *)&v_number, sizeof(v_number));
    stream.write((char *)&e_number, sizeof(e_number));

    for (int v_idx = 0; v_idx < v_number; ++v_idx) {
        auto &neighbors = adj_list[v_idx];
        size_t size = neighbors.size();

        stream.write((char *)&size, sizeof(size));
        stream.write((char *)&neighbors[0], size * sizeof(Edge));
    }

    return stream;
}
