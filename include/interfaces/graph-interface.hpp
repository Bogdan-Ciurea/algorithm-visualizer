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
    this->graph = new Graph();
  }
  ~GraphInterface() { delete this->graph; }

  bool draw();

 private:
  Graph *graph = nullptr;

  unsigned long last_draw_time;

  bool directed_graph;
  bool textBoxEditMode1 = false;
  char textBoxText1[64] = "From";
  bool textBoxEditMode2 = false;
  char textBoxText2[64] = "To";
  bool check_input();
  Node *from_node = nullptr;
  Node *to_node = nullptr;

  SelectableModes current_mode = ADD_NODE;
  std::vector<Graph *> animation = std::vector<Graph *>();

  // needed for clicking
  bool pressed = false;
  Node *temp_clicked_node = nullptr;  // Used for the fist node of the edge

  // Drawing functions
  void draw_main_header(float button_height);
  void draw_secondary_header(float button_height);

  void get_canvas_input();

  // Clicking functions
  Vector2 *get_click_location(float ignore_height = 100.0f);

  // bool import_graph();

  // Algorithm related functions
  void run_algorithm();
};

#endif  // GRAPH_INTERFACE_HPP