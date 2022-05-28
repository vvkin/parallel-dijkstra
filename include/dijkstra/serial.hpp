#pragma once

#include <queue>

#include "graph.hpp"

class DijkstraCompare {
  public:
    bool operator()(const std::pair<int, double> &a, const std::pair<int, double> &b) const;
};

std::vector<double> serial_dijkstra(const Graph &graph, int src);
