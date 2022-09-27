#ifndef GRAPH_H
#define GRAPH_H

#include "algirithm_interface.h"
#include "standalone-functions/graph-algorithms.h"

class Graph : public AlgorithmInterface {
 public:
  Graph() { inter_regular = LoadFontEx("assets/inter-regular.ttf", 20, 0, 0); }
  ~Graph() {}

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

#endif