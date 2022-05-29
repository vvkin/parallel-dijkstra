#include <queue>
#include <vector>
#include <limits>

#include "dijkstra/serial.hpp"

using namespace std;

struct DijkstraCompare {
    bool operator()(const pair<int, float> &a, const pair<int, float> &b) const {
        return a.second > b.second;
    }
};

vector<float> serial_dijkstra(const Graph &graph, int source) {
    auto v_number = graph.get_v_number();
    auto &adj_list = graph.as_adj_list();

    auto distance = vector<float>(v_number, DIJKSTRA_INF);
    auto visited = vector<bool>(v_number, false);

    priority_queue<pair<int, float>, vector<pair<int, float>>, DijkstraCompare> queue;
    queue.emplace(source, 0);
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
                queue.emplace(edge.to, nextDist);
            }
        }
    }

    return distance;
}
