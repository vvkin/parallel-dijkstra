#pragma once

#include <string>

#include "graph.hpp"

class GraphFactory {
  public:
    static Graph from_file(const std::string path);

    static Graph from_random(int v_number, int e_number);

  private:
    GraphFactory();
};

std::istream &operator>>(std::istream &stream, Graph &graph);
