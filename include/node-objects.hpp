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
  Node *get_node_copy();
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
  Edge(float weight, Node *n1, Node *n2, bool directed);
  Edge *get_edge_copy();
  ~Edge() {}

  void draw(float thickness);

  bool point_on_edge(Vector2 *point);

  void set_state(color_state);
  color_state get_state();
  void set_weight(int new_weight);
  void set_directed(bool new_directed);

  float weight;
  Node *node1, *node2;

 private:
  Color color;
  color_state state;
  Vector2 start_point, end_point;
  bool directed;

  void calculate_start_end_points();
};

class Graph {
 public:
  Graph() {}
  ~Graph() {
    for (auto node : node_list) delete node;
    for (auto edge : edge_list) delete edge;
  }

  void add_node(Vector2 *point);
  Node *get_node(int id);
  int get_node_index(int id);
  int get_node_index(Node *node);
  int generate_id();
  std::vector<Edge *> get_edges_from_node(Node *node);
  std::vector<Node *> get_neighbours(Node *node);

  void add_edge(Node *n1, Node *n2, float weight, color_state state = NORMAL);
  Edge *get_edge(Node *n1, Node *n2);

  void draw(float node_radius, float edge_thickness);

  void remove_element(Vector2 *point);
  void remove_node(Node *node);
  void remove_edge(Edge *edge);

  void set_directed(bool new_directed);
  Node *get_node_in_proximity(Vector2 *point, float radius);

  Graph *get_graph_copy();

  std::vector<Node *> node_list;
  std::vector<Edge *> edge_list;

 private:
  bool directed;
};

#endif  // NODE_OBJECTS_HPP