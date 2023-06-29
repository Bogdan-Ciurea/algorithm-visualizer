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

/**
 * @brief This class is used to represent a node in a graph or a tree.
 *
 */
class Node {
 public:
  // Constructors
  Node(float x, float y, int id = -1);
  Node(Vector2 coord, int id = -1);
  /**
   * @brief Get the node copy object.
   *
   * @return Node*
   */
  Node *get_node_copy() const;
  ~Node() {}

  /**
   * @brief Draw the node on the screen.
   *
   * @param r - The radius of the node.
   */
  void draw(float r) const;
  /**
   * @brief Check if a point is inside the node.
   *
   * @param point  - The point to check.
   * @return true  - If the point is inside the node.
   * @return false - If the point is NOT inside the node.
   */
  bool point_in_node(Vector2 *point) const;

  /**
   * @brief Set the state object.
   *
   * @param new_state - The new state of the node.
   */
  void set_state(color_state);

  /**
   * @brief Set the id object.
   *
   * @param new_id  - The new id of the node.
   */
  void set_id(int new_id);

  int id;         // The id of the node
  Vector2 coord;  // The coordinates of the node

 private:
  Color color;        // The color of the node
  color_state state;  // The state of the node
};

/**
 * @brief This class is used to represent an edge in a graph or a tree.
 *
 */
class Edge {
 public:
  /**
   * @brief Construct a new Edge object
   *
   * @param weight   - The weight of the edge.
   * @param n1       - Pointer to the first/origin node.
   * @param n2       - Pointer to the second/destination node.
   * @param directed - Whether the edge is directed or not.
   */
  Edge(float weight, Node *n1, Node *n2, bool directed);
  /**
   * @brief Get the edge copy object.
   *
   * @return Edge*
   */
  Edge *get_edge_copy() const;
  ~Edge() {}

  /**
   * @brief Draw the edge on the screen.
   *
   * @param thickness - The thickness of the edge.
   */
  void draw(float thickness) const;

  /**
   * @brief Check if a point is on the edge.
   *
   * @param point - The point to check.
   * @return true - If the point is on the edge.
   * @return false - If the point is NOT on the edge.
   */
  bool point_on_edge(Vector2 *point) const;

  /**
   * @brief Set the state object.
   *
   * @param new_state - The new state of the edge.
   */
  void set_state(color_state);

  /**
   * @brief Get the state object.
   *
   * @return color_state - The state of the edge.
   */
  color_state get_state() const;

  /**
   * @brief Set the weight object.
   *
   * @param new_weight - The new weight of the edge.
   */
  void set_weight(int new_weight);

  /**
   * @brief Set the directed object.
   *
   * @param new_directed - The new directed value of the edge.
   */
  void set_directed(bool new_directed);

  float weight;         // The weight of the edge
  Node *node1, *node2;  // The nodes that the edge connects

 private:
  Color color;                     // The color of the edge
  color_state state;               // The state of the edge
  Vector2 start_point, end_point;  // The start and end points of the edge
  bool directed;                   // Whether the edge is directed or not

  /**
   * @brief Calculate the start and end points of the edge.
   * This is used for drawing the edge as we want to draw it from the edge of
   * the node and not from the center.
   *
   */
  void calculate_start_end_points();
};

class Graph {
 public:
  // Constructors
  Graph() {}
  /**
   * @brief Get a copy of the graph.
   *
   * @return Graph* - Pointer to the new graph.
   */
  Graph *get_graph_copy() const;
  ~Graph() {
    for (auto node : node_list) delete node;
    for (auto edge : edge_list) delete edge;
  }

  /**
   * @brief Add a node to the graph.
   *
   * @param point - The coordinates of the node.
   */
  void add_node(Vector2 *point);
  void add_node(Vector2 *point, int id);

  /**
   * @brief Get the node object by it's id.
   *
   * @param id - The id of the node.
   * @return Node* - Pointer to the node.
   * @return nullptr - If the node does not exist.
   */
  Node *get_node(int id) const;

  /**
   * @brief Get the node index object.
   *
   * @param id - The id of the node.
   * @return int - The index of the node in the node_list.
   * @return -1 - If the node does not exist.
   */
  int get_node_index(int id) const;

  /**
   * @brief Get the node index object.
   *
   * @param node - Pointer to the node.
   * @return int - The index of the node in the node_list.
   * @return -1 - If the node does not exist.
   */
  int get_node_index(Node *node) const;

  /**
   * @brief Get the edges from node object.
   *
   * @param node - Pointer to the node.
   * @return std::vector<Edge*> - Vector of pointers to the edges.
   */
  std::vector<Edge *> get_edges_from_node(Node *node) const;

  /**
   * @brief Get the neighbours object.
   *
   * @param node - Pointer to the node.
   * @return std::vector<Node*> - Vector of pointers to the neighbours.
   */
  std::vector<Node *> get_neighbours(Node *node) const;

  /**
   * @brief Add an edge to the graph.
   *
   * @param n1     - Pointer to the first/origin node.
   * @param n2     - Pointer to the second/destination node.
   * @param weight - The weight of the edge.
   * @param state  - The state of the edge.
   */
  void add_edge(Node *n1, Node *n2, float weight, color_state state = NORMAL);

  /**
   * @brief Get the edge object.
   *
   * @param n1 - Pointer to the first/origin node.
   * @param n2 - Pointer to the second/destination node.
   * @return Edge*   - Pointer to the edge.
   * @return nullptr - If the edge does not exist.
   */
  Edge *get_edge(Node *n1, Node *n2) const;

  /**
   * @brief Get the edge index object.
   *
   * @param node_radius    - The radius of the node.
   * @param edge_thickness - The thickness of the edge.
   */
  void draw(float node_radius, float edge_thickness) const;

  /**
   * @brief Remove an element from the graph.
   *
   * @param point  - The coordinates of the point.
   */
  void remove_element(Vector2 *point);
  /**
   * @brief Remove a node from the graph.
   *
   * @param node - Pointer to the node.
   */
  void remove_node(Node *node);
  /**
   * @brief Remove an edge from the graph.
   *
   * @param edge - Pointer to the edge.
   */
  void remove_edge(Edge *edge);

  /**
   * @brief Used to change the state of the graph form directed to undirected
   * and vice-versa.
   *
   * @param new_directed  - The new value of the directed variable.
   *                       true  - The graph is directed.
   *                       false - The graph is undirected.
   */
  void set_directed(bool new_directed);

  /**
   * @brief Get the node in proximity object.
   *
   * @param point   - The coordinates of the point.
   * @param radius  - The radius of the node.
   * @return Node*  - Pointer to the node.
   * @return nullptr - If the node does not exist.
   */
  Node *get_node_in_proximity(Vector2 *point, float radius) const;

  /**
   * @brief Checks if the graph has a cycle.
   *
   * @return true  - If the graph has a cycle.
   * @return false - If the graph does not have a cycle.
   */
  bool has_cycle() const;

  std::vector<Node *> node_list;
  std::vector<Edge *> edge_list;

 private:
  bool directed;
  /**
   * @brief Generate a unique id for a node.
   *
   * @return int - The id.
   */
  int generate_id();

  bool has_cycle_util(Node *node, std::vector<bool> &visited,
                      Node *parent) const;
};

#endif  // NODE_OBJECTS_HPP
