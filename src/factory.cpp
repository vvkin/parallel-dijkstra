#include <string>
#include <fstream>

#include "dijkstra/factory.hpp"

std::ifstream get_ifstream_throwable(const std::string path) {
    std::ifstream in_stream{path};
    if (!in_stream) {
        auto reason = "File " + path + " does not exist";
        throw std::runtime_error(reason);
    }
    return in_stream;
}

std::istream &operator>>(std::istream &stream, Graph &graph) {
    int from, to;
    double cost;
    stream >> from >> to >> cost;
    graph.add_edge(from, to, cost);
    return stream;
}

Graph GraphFactory::from_file(const std::string path) {
    auto stream = get_ifstream_throwable(path);
    int v_number, e_number;

    stream >> v_number >> e_number;
    Graph graph(v_number);

    for (int idx = 0; idx < e_number; ++idx) {
        stream >> graph;
    }

    return graph;
}

Graph GraphFactory::from_random(int v_number, int e_number) {
    Graph graph(v_number);
    // TODO: implement
    return graph;
}
