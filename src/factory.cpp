#include <string>
#include <iostream>
#include <random>
#include <fstream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/erdos_renyi_generator.hpp>
#include <boost/random/linear_congruential.hpp>

#include "dijkstra/factory.hpp"
#include "dijkstra/const.hpp"

using BoostGraph = boost::adjacency_list<>;
using ERGen = boost::erdos_renyi_iterator<boost::minstd_rand, BoostGraph>;

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

Graph map_boost_graph(const BoostGraph &boost_graph);

Graph GraphFactory::from_random(int v_number, float density) {
    boost::minstd_rand engine(std::random_device{}());
    BoostGraph boost_graph(ERGen(engine, v_number, density), ERGen(), v_number);
    return map_boost_graph(boost_graph);
}

Graph map_boost_graph(const BoostGraph &boost_graph) {
    auto v_number = boost::num_vertices(boost_graph);
    auto e_number = boost::num_edges(boost_graph);
    Graph graph(v_number, e_number);

    std::mt19937 engine(std::random_device{}());
    auto weight_gen = bind(std::uniform_real_distribution<float>(0, DIJSTRA_MAX_VALUE), engine);
    const auto edges = boost::make_iterator_range(boost::edges(boost_graph));

    for (const auto &edge : edges) {
        auto cost = weight_gen();
        graph.add_edge(edge.m_source, edge.m_target, cost);
    }

    return graph;
}
