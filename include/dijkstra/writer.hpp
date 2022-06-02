#pragma once

#include <string>

#include "graph.hpp"

class GraphWriter {
  public:
    static void to_file(const Graph &graph, const std::string &path);

  private:
    GraphWriter();
};
