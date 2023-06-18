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
  Node(float x, float y, int id = -1);
  Node(Vector2 coord, int id = -1);
  ~Node() {}

  void draw(float r);
  bool point_in_node(Vector2 *point);

  void set_state(color_state);
  void set_id(int new_id);

  int id;
  Vector2 coord;

 private:
  float radius;
  Color color;
  color_state state;
};

class Edge {
 public:
  Edge(int weight, Node *n1, Node *n2, bool directed);
  ~Edge() {}

  void draw(float thickness);

  bool point_on_edge(Vector2 *point);

  void set_state(color_state);
  void set_weight(int new_weight);
  void set_directed(bool new_directed);

  int weight;
  Node *node1, *node2;

 private:
  Color color;
  color_state state;
  bool directed;
};

#endif  // NODE_OBJECTS_HPP