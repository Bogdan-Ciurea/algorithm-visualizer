#include "pillar.h"

Pillar::Pillar(int size) {
  _value = size;
  _color = NORMAL_COLOR;
}

Pillar::~Pillar() {}

void Pillar::change_state(color_state state_change) {
  _state = state_change;

  switch (_state) {
    case NORMAL:
      _color = NORMAL_COLOR;
      break;

    case SELECTED:
      _color = SELECTED_COLOR;
      break;

    case MOVED:
      _color = MOVED_COLOR;
      break;

    default:
      break;
  }
}

void Pillar::draw(int x, int y, int width, int height) {
  Rectangle r = {(float)x, (float)y, (float)width, (float)height};

  DrawRectangleLines(x, y, width, height, BORDER_COLOR);
  DrawRectangle(x, y, width, height, _color);
}
