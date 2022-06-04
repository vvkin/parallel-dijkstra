#include <vector>

#include "dijkstra/common.hpp"
#include "dijkstra/serial.hpp"

std::vector<float> serial_dijkstra(const Graph &graph, int source) {
    auto v_number = graph.get_v_number();
    auto &adj_list = graph.as_adj_list();

    auto distance = std::vector<float>(v_number, DIJKSTRA_INF);
    auto visited = std::vector<bool>(v_number, false);

    DijkstraQueue queue;
    queue.emplace(source, 0);
    distance[source] = 0;

    while (!queue.empty()) {
        auto [min_idx, min_dist] = queue.top();
        queue.pop();
        visited[min_idx] = true;

        if (distance[min_idx] < min_dist) continue;

        for (auto &edge : adj_list[min_idx]) {
            if (visited[edge.to]) continue;

            float next_dist = distance[min_idx] + edge.cost;
            if (next_dist < distance[edge.to]) {
                distance[edge.to] = next_dist;
                queue.emplace(edge.to, next_dist);
            }
        }
    }

    return distance;
}
