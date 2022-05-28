#pragma once

#include <string>
#include <fstream>
#include "graph.hpp"

class GraphFactory {
  public:
    static Graph from_file(std::string path);

    static Graph from_random(int v_number, int e_number);

  private:
    GraphFactory();

    static std::ifstream get_ifstream_throwable(std::string path);
};
