/**
 * @file node-objects.hpp
 * @author Bogdan Ciurea
 * @brief This file is responsible for defining the classes and their methods
 * that are used in the graph and tree interfaces.
 * @version 0.1
 * @date 2023-06-15
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef NODE_OBJECTS_HPP
#define NODE_OBJECTS_HPP

#include "utils.h"

class Node {
 public:
  Node(int value, int x, int y, int id = -1);
  ~Node() {}

  bool draw(float r);

  bool is_selected(int x, int y);

  int value;
  int id;

 private:
  int coord_x, coord_y;
  float radius;
  Color color;
  color_state state;
};

class Edge {
 public:
  Edge(int weight, Node *n1, Node *n2, bool directed);
  ~Edge();

  void change_state(color_state);

  void draw(float thickness);

  int weight;

 private:
  Color color;
  color_state state;
  Node *node1;
  Node *node2;
  bool directed;
};

#endif  // NODE_OBJECTS_HPP