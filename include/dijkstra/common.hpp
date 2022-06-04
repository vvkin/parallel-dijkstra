#pragma once

#include <limits>
#include <queue>

const float DIJSTRA_MAX_VALUE = 100;

const float DIJKSTRA_INF = std::numeric_limits<float>::max();

using DijkstraQueueEntry = std::pair<int, float>;

struct DijkstraCompare {
    bool operator()(const DijkstraQueueEntry &a, const DijkstraQueueEntry &b) const;
};

using DijkstraQueue =
        std::priority_queue<DijkstraQueueEntry, std::vector<DijkstraQueueEntry>, DijkstraCompare>;
