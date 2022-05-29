#include <iostream>
#include <random>
#include <string>
#include <chrono>

#include "dijkstra/const.hpp"
#include "dijkstra/factory.hpp"
#include "dijkstra/serial.hpp"
#include "dijkstra/writer.hpp"

template <typename T>
bool is_all_reached(const std::vector<T> &distance);

int main() {
    std::srand(time(NULL));

    // const float GRAPH_DENSITY = 0.3;
    // const int V_NUMBER = 5000;
    // auto graph = GraphFactory::from_random(V_NUMBER, GRAPH_DENSITY);
    auto graph = GraphFactory::from_file("data/graph-5000-0.3.txt");
    auto start = std::rand() % graph.get_v_number();

    std::cout << "Vertices = " << graph.get_v_number() << '\n';
    std::cout << "Edges = " << graph.get_e_number() << '\n';
    std::cout << "Start = " << start << '\n';

    auto t1 = std::chrono::high_resolution_clock::now();
    auto distance = serial_dijkstra(graph, 0);
    auto t2 = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> ms_double = t2 - t1;
    std::cout << ms_double.count() << "ms\n";

    // if (!is_all_reached(distance)) {
    //     std::cout << "Graph is not fully connected!" << '\n';
    //     return 1;
    // }

    // auto path = "data/graph-5000-0.3.txt";
    // GraphWriter::to_file(graph, path);
    // return 0;
}

// g++ - O3 src/*.cpp -I include/ -o main

template <typename T>
bool is_all_reached(const std::vector<T> &distance) {
    for (auto &dist : distance) {
        if (dist == DIJKSTRA_INF) return false;
    }
    return true;
}
