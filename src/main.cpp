#include <iostream>
#include <random>
#include <string>
#include <chrono>

#include "dijkstra/factory.hpp"
#include "dijkstra/serial.hpp"

template <typename T>
bool is_all_reached(const std::vector<T> &distance) {
    for (auto &dist : distance) {
        if (dist == DIJKSTRA_INF) return false;
    }
    return true;
}

// g++ - O3 src/*.cpp -I include/ -o main

int main() {
    // TODO: move to config
    const int V_NUMBER = 1000;
    const double DENSITY = 0.5;
    std::srand(time(NULL));

    auto graph = GraphFactory::from_random(V_NUMBER, DENSITY);
    auto start = std::rand() % V_NUMBER;

    std::cout << "Vertices = " << graph.get_v_number() << '\n';
    std::cout << "Edges = " << graph.get_e_number() << '\n';
    std::cout << "Start = " << start << '\n';

    auto t1 = std::chrono::high_resolution_clock::now();
    auto distance = serial_dijkstra(graph, 0);
    auto t2 = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> ms_double = t2 - t1;
    std::cout << ms_double.count() << "ms\n";

    if (!is_all_reached(distance)) {
        std::cout << "Graph is not fully connected!" << '\n';
    }
}
