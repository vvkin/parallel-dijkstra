#pragma once

#include "graph.hpp"

const float DIJKSTRA_INF = std::numeric_limits<float>::max();

std::vector<float> serial_dijkstra(const Graph &graph, int src);
