#include <string>
#include <fstream>

#include "dijkstra/factory.hpp"

std::ifstream get_ifstream_throwable(const std::string &path) {
    std::ifstream in_stream{path};
    if (!in_stream) {
        auto reason = "File " + path + " does not exist";
        throw std::runtime_error(reason);
    }
    return in_stream;
}

Graph GraphFactory::from_file(const std::string &path) {
    auto stream = get_ifstream_throwable(path);
    Graph graph{};
    stream >> graph;
    return graph;
}

Graph GraphFactory::from_random(int v_number, int e_number) {
    Graph graph(v_number);
    // TODO: implement
    return graph;
}
