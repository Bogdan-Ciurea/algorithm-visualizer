#ifndef GRAPH_H
#define GRAPH_H

#include "standalone-functions/graph-algorithms.h"

class Graph {
public:
  Graph();
  ~Graph();
  
  void draw();

private:
  bool directed;
};

#endif