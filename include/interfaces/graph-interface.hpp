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

class GraphInterface : public AlgorithmInterface {
 public:
  GraphInterface(Font *inter_regular, Font *inter_light) {
    this->inter_regular = inter_regular;
    this->inter_light = inter_light;
  }
  ~GraphInterface() {}

  bool draw();

 private:
  std::vector<std::vector<float>> adj_matrix;
  std::vector<Node> node_list;

  bool directed = false;
  bool textBoxEditMode1 = false;
  char textBoxText1[64] = "From";
  bool textBoxEditMode2 = false;
  char textBoxText2[64] = "To";

  void add_node();
  void add_edge();

  void draw_header();

  bool import_graph();
};

#endif  // GRAPH_INTERFACE_HPP