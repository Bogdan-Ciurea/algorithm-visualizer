/**
 * @file pillar-objects.hpp
 * @author Bogdan Ciurea
 * @brief This file is responsible for defining the classes and their methods
 * that are used in the sorting and searching interfaces.
 * @version 0.1
 * @date 2023-06-15
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef PILLAR_OBJECTS_HPP
#define PILLAR_OBJECTS_HPP

#include "utils.h"

class Pillar {
 public:
  Pillar(int value);
  ~Pillar();

  void change_state(color_state);

  void draw(int x, int y, int width, int height);

  bool operator>(Pillar &pil) {
    if (this->_value > pil._value) return true;
    return false;
  }

  bool operator<(Pillar &pil) {
    if (this->_value < pil._value) return true;
    return false;
  }

  bool operator==(Pillar &pil) {
    if (this->_value == pil._value) return true;
    return false;
  }

  int _value;

 private:
  Color _color;
  color_state _state;
};

#endif  // PILLAR_OBJECTS_HPP