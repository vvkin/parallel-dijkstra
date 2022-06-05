#include <string>
#include <iostream>

#include <boost/program_options.hpp>

namespace po = boost::program_options;

po::variables_map parse_args(int argc, char *argv[]) {
    try {
        // clang-format off
        po::options_description general("General options");
        general.add_options()
            ("help,h", "Show help")
        ;

        po::options_description graph("Graph options");
        graph.add_options()
            ("input-path,i", po::value<std::string>(), "path to file with input graph")
            ("output-path,o", po::value<std::string>(), "path to file to store used graph")
            ("generate,g", po::bool_switch(), "wether to use serial or parallel algorithm")
            ("v-number,v", po::value<unsigned>(), "number of vertices to generate")
            ("density,d", po::value<float>(), "probability of edge existence")
        ;

        po::options_description algo("Algorithm options");
        algo.add_options()
            ("source,s", po::value<unsigned>()->required(), "starting vertex")
            ("result-path,r",po::value<std::string>(), "path to save array with distances")
            ("parallel,p", po::bool_switch(), "wether to use serial or parallel algorithm")
            ("threads-number,t", po::value<unsigned>(), "number of threads to use with parallel algorithm")
        ;
        // clang-format on

        general.add(graph).add(algo);

        po::variables_map params;
        po::store(po::parse_command_line(argc, argv, general), params);

        if (params.count("help")) {
            std::cout << general << '\n';
            exit(0);
        }

        po::notify(params);
        return params;
    } catch (const std::exception &err) {
        std::cerr << err.what() << '\n';
        exit(1);
    }
}
