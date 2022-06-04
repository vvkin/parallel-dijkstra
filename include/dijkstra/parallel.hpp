#pragma once

#include "graph.hpp"

std::vector<float> parallel_dijkstra(const Graph &graph, int source, int threads_number);
