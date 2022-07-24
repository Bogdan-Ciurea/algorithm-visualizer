#ifndef GRAPH_H
#define GRAPH_H

#include "standalone-functions/graph-algorithms.h"

class Graph {
 public:
  Graph();
  ~Graph();

  void draw();

 private:
  std::vector<std::vector<float>> adj_matrix;
  std::vector<Node> node_list;

  void add_node();
  void add_edge();
};

#endif