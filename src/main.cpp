#include <iostream>
#include <functional>
#include <random>
#include <string>
#include <chrono>

#include "dijkstra/common.hpp"
#include "dijkstra/factory.hpp"
#include "dijkstra/writer.hpp"
#include "dijkstra/serial.hpp"
#include "dijkstra/parallel.hpp"

template <typename T>
bool is_all_reached(const std::vector<T> &distance);

void exec_with_timer(std::function<void(void)> fn, const std::string &label);

int main() {
    std::srand(time(NULL));
    const int THREADS_NUMBER = 4;

    // const float GRAPH_DENSITY = 0.3;
    // const int V_NUMBER = 5000;
    // auto graph = GraphFactory::from_random(V_NUMBER, GRAPH_DENSITY);
    auto graph = GraphFactory::from_file("../../data/graph-5000-0.3.txt");
    auto start = std::rand() % graph.get_v_number();

    std::cout << "Vertices = " << graph.get_v_number() << '\n';
    std::cout << "Edges = " << graph.get_e_number() << '\n';
    std::cout << "Start = " << start << '\n';

    std::vector<float> serial_dist;
    exec_with_timer([&]() { serial_dist = serial_dijkstra(graph, start); }, "SERIAL");

    std::vector<float> parallel_dist;
    exec_with_timer([&]() { parallel_dist = parallel_dijkstra(graph, start, THREADS_NUMBER); },
                    "PARALLEL");

    for (int idx = 0; idx < graph.get_v_number(); ++idx) {
        if (serial_dist[idx] != parallel_dist[idx]) {
            std::cout << "OOPS\n";
            return 1;
        }
    }

    // if (!is_all_reached(distance)) {
    //     std::cout << "Graph is not fully connected!" << '\n';
    //     return 1;
    // }

    // auto path = "../../data/graph-5000-0.9.txt";
    // GraphWriter::to_file(graph, path);
    return 0;
}

// g++ - O3 src/*.cpp -I include/ -o main

template <typename T>
bool is_all_reached(const std::vector<T> &distance) {
    for (auto &dist : distance) {
        if (dist == DIJKSTRA_INF) return false;
    }
    return true;
}

void exec_with_timer(std::function<void(void)> fn, const std::string &label) {
    auto t1 = std::chrono::high_resolution_clock::now();
    fn();
    auto t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> ms_double = t2 - t1;
    std::cout << label << ": " << ms_double.count() << "ms\n";
}
