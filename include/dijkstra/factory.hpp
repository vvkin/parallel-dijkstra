#pragma once

#include <string>

#include "graph.hpp"

// TODO: move to config
const float DIJSTRA_MAX_VALUE = 100;

class GraphFactory {
  public:
    static Graph from_file(const std::string &path);

    static Graph from_random(int v_number, double density);

  private:
    GraphFactory();
};
