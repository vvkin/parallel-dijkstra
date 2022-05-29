#include <iostream>
#include <string>

#include "dijkstra/factory.hpp"
#include "dijkstra/serial.hpp"

template <typename T>
void print_vector(std::vector<T> vec) {
    for (auto el : vec) {
        std::cout << el << " ";
    }
}

// g++ - O3 src/*.cpp -I include/ -o main

int main() {
    std::string path = "data/graph.txt";
    auto graph = GraphFactory::from_file(path);
    auto distance = serial_dijkstra(graph, 0);
    print_vector(distance);
    std::cout << '\n';
}
