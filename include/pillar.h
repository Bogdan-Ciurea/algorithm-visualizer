#ifndef PILLAR_H
#define PILLAR_H

#include "utils.h"

class Pillar {
public:
  Pillar(int value);
  ~Pillar();

  void change_state(color_state);
  
  void draw(int x, int y, int width, int height);

  int  _value;

private:
  Color _color;
  color_state _state;
};

#endif