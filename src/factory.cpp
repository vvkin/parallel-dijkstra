#include <string>
#include <fstream>

#include "dijkstra/factory.hpp"

std::ifstream GraphFactory::get_ifstream_throwable(std::string path) {
    std::ifstream in_stream{path};
    if (!in_stream) {
        auto reason = "File " + path + " does not exist";
        throw std::runtime_error(reason);
    }
    return in_stream;
}

Graph GraphFactory::from_file(std::string path) {
    auto stream = GraphFactory::get_ifstream_throwable(path);
    int v_number, e_number, from, to;
    double cost;

    stream >> v_number >> e_number;
    Graph graph(v_number);

    for (int idx = 0; idx < e_number; ++idx) {
        stream >> from >> to >> cost;
        graph.add_edge(from, to, cost);
    }

    return graph;
}

Graph GraphFactory::from_random(int v_number, int e_number) {
    Graph graph(v_number);
    // TODO: implement
    return graph;
}
