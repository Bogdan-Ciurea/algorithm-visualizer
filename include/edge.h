#ifndef EDGE_H
#define EDGE_H

#include "node.h"

class Edge {
 public:
  Edge(int weight, Node *n1, Node *n2, bool directed);
  ~Edge();

  void change_state(color_state);

  bool draw(float thickness);

  int weight;

 private:
  Color color;
  color_state state;
  Node *node1;
  Node *node2;
  bool directed;
};

#endif