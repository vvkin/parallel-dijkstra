#include <iostream>
#include <random>
#include <fstream>
#include <string>
#include <chrono>
#include <functional>

#include "arg_parser.hpp"
#include "dijkstra/common.hpp"
#include "dijkstra/factory.hpp"
#include "dijkstra/writer.hpp"
#include "dijkstra/serial.hpp"
#include "dijkstra/parallel.hpp"

void exec_with_timer(std::function<void(void)> executor, const std::string &label) {
    auto start = std::chrono::high_resolution_clock::now();
    executor();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> ms_double = end - start;
    std::cout << label << ": " << ms_double.count() << "ms\n";
}

void run_dijkstra(const po::variables_map &params) {
    Graph graph;
    std::vector<float> distance;

    if (params["generate"].as<bool>()) {
        auto v_number = params["v-number"].as<unsigned>();
        auto density = params["density"].as<float>();
        graph = GraphFactory::from_random(v_number, density);
    } else {
        auto input_path = params["input-path"].as<std::string>();
        graph = GraphFactory::from_file(input_path);
    }

    auto source = params["source"].as<unsigned>();
    if (params["parallel"].as<bool>()) {
        auto threads_number = params["threads-number"].as<unsigned>();
        exec_with_timer([&]() { distance = parallel_dijkstra(graph, source, threads_number); },
                        "Parallel");
    } else {
        exec_with_timer([&]() { distance = serial_dijkstra(graph, source); }, "Serial");
    }

    if (params.count("output-path")) {
        auto output_path = params["output-path"].as<std::string>();
        GraphWriter::to_file(graph, output_path);
    }

    if (params.count("result-path")) {
        auto distance_path = params["result-path"].as<std::string>();
        GraphWriter::distance_to_file(distance, distance_path);
    }
}

int main(int argc, char *argv[]) {
    auto params = parse_args(argc, argv);
    run_dijkstra(params);
    return 0;
}

// g++ - O3 src/*.cpp -I include/ -o main
