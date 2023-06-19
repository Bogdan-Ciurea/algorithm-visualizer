/**
 * @file graph-interface.hpp
 * @author Bogdan Ciurea
 * @brief This file in responsible for defining the graph interface that will be
 * used in the main program and by the main-interface.hpp
 * @version 0.1
 * @date 2023-06-15
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef GRAPH_INTERFACE_HPP
#define GRAPH_INTERFACE_HPP

#include "../standalone-functions/graph-algorithms.hpp"
#include "blank-interface.hpp"

enum SelectableModes { ADD_NODE, ADD_EDGE, EDGE_TYPE, REMOVE };

class GraphInterface : public AlgorithmInterface {
 public:
  GraphInterface(Font *inter_regular, Font *inter_light) {
    this->inter_regular = inter_regular;
    this->inter_light = inter_light;
    this->directed_graph = false;
  }
  ~GraphInterface() {
    for (auto node : node_list) delete node;
    for (auto edge : edge_list) delete edge;
  }

  bool draw();

 private:
  std::vector<std::vector<float>> adj_matrix;
  std::vector<Node *> node_list;
  std::vector<Edge *> edge_list;

  bool directed_graph;
  bool textBoxEditMode1 = false;
  char textBoxText1[64] = "From";
  bool textBoxEditMode2 = false;
  char textBoxText2[64] = "To";

  SelectableModes current_mode = ADD_NODE;
  bool has_deleted = false;

  // needed for clicking
  bool pressed = false;
  Node *temp_clicked_node = nullptr;  // Used for the fist node of the edge

  void draw_main_header(float button_height);
  void draw_secondary_header(float button_height);
  void draw_elements();

  Vector2 *get_click_location(float ignore_height = 100.0f);

  // bool import_graph();

  void add_node(Vector2 *location);
  void remove_node(Node *node);
  int generate_node_id();

  Node *get_node_by_position(Vector2 *location);

  void add_edge(Node *n1, Node *n2);
  void remove_edge(Edge *edge);

  void change_edge_type();

  std::vector<std::vector<float>> generate_adj_matrix();
  void print_adj_matrix(std::vector<std::vector<float>>);
};

#endif  // GRAPH_INTERFACE_HPP