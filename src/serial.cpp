#include <queue>
#include <vector>
#include <limits>

#include "dijkstra/serial.hpp"

using namespace std;

const double INF = std::numeric_limits<double>::max();

vector<double> serial_dijkstra(const Graph &graph, int source) {
    auto v_number = graph.get_vertices_number();
    auto adj_list = graph.as_adj_list();

    auto distance = vector<double>(v_number, INF);
    auto visited = vector<bool>(v_number, false);

    priority_queue<pair<int, double>, vector<pair<int, double>>, DijkstraCompare> queue;
    queue.push({source, 0});
    distance[source] = 0;

    while (!queue.empty()) {
        auto [currIdx, currDist] = queue.top();
        queue.pop();
        visited[currIdx] = true;

        if (distance[currIdx] < currDist) continue;

        for (auto &edge : adj_list[currIdx]) {
            if (visited[edge.to]) continue;

            float nextDist = distance[currIdx] + edge.cost;
            if (nextDist < distance[edge.to]) {
                distance[edge.to] = nextDist;
                queue.push({edge.to, nextDist});
            }
        }
    }

    return distance;
}

bool DijkstraCompare::operator()(const std::pair<int, double> &a,
                                 const std::pair<int, double> &b) const {
    return a.second > b.second;
}