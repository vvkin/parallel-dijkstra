#include "dijkstra/common.hpp"

bool DijkstraCompare::operator()(const DijkstraQueueEntry &a, const DijkstraQueueEntry &b) const {
    return a.second > b.second;
}
