#include <iostream>
#include <string>

#include "dijkstra/factory.hpp"

int main() {
    std::string path = "../../data/graph.txt";
    auto graph = GraphFactory::from_file(path);
    std::cout << "Done!";
}
