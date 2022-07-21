#ifndef EDGE_H
#define EDGE_H

#include "node.h"

class Edge {
public:
  Edge(int weight, Node *n1, Node *n2, bool directed);
  ~Edge();

  void change_state(color_state);
  
  void draw(int x, int y, float radius);

  int  _value;

private:
  Color _color;
  color_state _state;
  Node *node1;
  Node *node2;
  bool directed;
};

#endif