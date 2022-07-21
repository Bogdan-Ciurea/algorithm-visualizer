#ifndef NODE_H
#define NODE_H

#include "utils.h"

class Node {
public:
  Node(int value, int id = -1);
  ~Node();

  void change_state(color_state);
  
  void draw(int x, int y, float radius);

  int  _value;
  int  _id;

private:
  Color _color;
  color_state _state;
};

#endif
