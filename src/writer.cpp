#include <fstream>
#include <iomanip>

#include "dijkstra/writer.hpp"

std::ofstream get_ofstream_throwable(const std::string &path) {
    std::ofstream out_stream(path, std::ios::binary);
    if (!out_stream.is_open()) {
        auto reason = "Unable to open file " + path;
        throw new std::runtime_error(reason);
    }
    return out_stream;
}

void GraphWriter::to_file(const Graph &graph, const std::string &path) {
    auto stream = get_ofstream_throwable(path);
    stream << graph;
}

void GraphWriter::distance_to_file(const std::vector<float> &distance, const std::string &path) {
    auto stream = get_ofstream_throwable(path);
    stream << std::setprecision(6) << std::fixed;
    for (auto &el : distance) {
        stream << el << '\n';
    }
}
