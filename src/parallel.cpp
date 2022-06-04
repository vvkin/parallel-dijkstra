#include <cmath>
#include <thread>

#include "dijkstra/common.hpp"
#include "dijkstra/parallel.hpp"

void run_in_thread(int source,
                   const std::pair<int, int> &bounds,
                   const std::vector<Edge> &neighbors,
                   const std::vector<bool> &visited,
                   std::vector<float> &distance,
                   DijkstraQueue &queue);

DijkstraQueueEntry pop_queues(std::vector<DijkstraQueue> &queues, const std::vector<bool> &visited);

std::pair<int, int> make_bounds(int chunk_size, int chunk_idx, int total_size);

std::vector<float> parallel_dijkstra(const Graph &graph, int source, int threads_number) {
    auto v_number = graph.get_v_number();
    const auto &adj_list = graph.as_adj_list();

    auto distance = std::vector<float>(v_number, DIJKSTRA_INF);
    auto visited = std::vector<bool>(v_number, false);
    auto queues = std::vector<DijkstraQueue>(threads_number);

    std::thread threads[threads_number];
    int current_idx = source;
    distance[source] = 0;

    while (current_idx != -1) {
        visited[current_idx] = true;

        auto &neighbors = adj_list[current_idx];
        int chunk_size = std::ceil((float)neighbors.size() / threads_number);

        for (int t_idx = 0; t_idx < threads_number; ++t_idx) {
            auto bounds = make_bounds(chunk_size, t_idx, neighbors.size());
            auto &queue = queues[t_idx];
            threads[t_idx] = std::thread(run_in_thread,
                                         current_idx,
                                         bounds,
                                         std::ref(neighbors),
                                         std::ref(visited),
                                         std::ref(distance),
                                         std::ref(queue));
        }

        for (int t_idx = 0; t_idx < threads_number; ++t_idx)
            threads[t_idx].join();

        auto [min_idx, min_dist] = pop_queues(queues, visited);
        current_idx = min_idx;
    }

    return distance;
}

void run_in_thread(int source,
                   const std::pair<int, int> &bounds,
                   const std::vector<Edge> &neighbors,
                   const std::vector<bool> &visited,
                   std::vector<float> &distance,
                   DijkstraQueue &queue) {

    auto [start, end] = bounds;

    for (int e_idx = start; e_idx < end; ++e_idx) {
        auto &edge = neighbors[e_idx];
        if (visited[edge.to]) continue;

        float next_dist = distance[source] + edge.cost;
        if (next_dist < distance[edge.to]) {
            distance[edge.to] = next_dist;
            queue.emplace(edge.to, next_dist);
        }
    }
}

DijkstraQueueEntry pop_queues(std::vector<DijkstraQueue> &queues,
                              const std::vector<bool> &visited) {
    while (true) {
        int global_min_idx, global_q_idx;
        float global_min_dist = DIJKSTRA_INF;

        for (size_t q_idx = 0; q_idx < queues.size(); ++q_idx) {
            auto &queue = queues[q_idx];
            if (queue.empty()) continue;

            auto [min_idx, min_dist] = queue.top();
            if (min_dist < global_min_dist) {
                global_min_dist = min_dist;
                global_min_idx = min_idx;
                global_q_idx = q_idx;
            }
        }

        if (global_min_dist == DIJKSTRA_INF) break; // queues are empty

        queues[global_q_idx].pop();
        if (!visited[global_min_idx]) return {global_min_idx, global_min_dist}; // global min found
    }

    return {-1, -1};
}

std::pair<int, int> make_bounds(int chunk_size, int chunk_idx, int total_size) {
    int start = chunk_idx * chunk_size;
    int end = std::min(total_size, start + chunk_size);
    return {start, end};
}
