/**
 * @file tree-interface.hpp
 * @author Bogdan Ciurea
 * @brief This file in responsible for defining the tree interface that will be
 * used in the main program and by the main-interface.hpp
 * @version 0.1
 * @date 2023-06-15
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef TREE_INTERFACE_HPP
#define TREE_INTERFACE_HPP

#include "../standalone-functions/trees-algorithms.h"
#include "blank-interface.hpp"

class Trees : public AlgorithmInterface {
 public:
  Trees() { inter_regular = LoadFontEx("assets/inter-regular.ttf", 20, 0, 0); }
  ~Trees() {}

  bool draw();

 private:
  Node *selected_node;
  bool textBoxEditMode = false;
  char textBoxText[64] = "Node's value";

  void draw_header();

  void delete_node();
  void add_node();
};

#endif  // TREE_INTERFACE_HPP