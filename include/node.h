#ifndef NODE_H
#define NODE_H

#include "utils.h"

class Node {
 public:
  Node(int value, int x, int y, int id = -1);
  ~Node();

  void draw(float r);

  bool is_selected(int x, int y);

  int value;
  int id;

 private:
  int coord_x, coord_y;
  float radius;
  Color color;
  color_state state;
};

#endif
