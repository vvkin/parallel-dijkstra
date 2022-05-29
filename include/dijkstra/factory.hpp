#pragma once

#include <string>

#include "graph.hpp"

class GraphFactory {
  public:
    static Graph from_file(const std::string &path);

    static Graph from_random(int v_number, float density);

  private:
    GraphFactory();
};
