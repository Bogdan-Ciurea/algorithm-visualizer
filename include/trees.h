#ifndef TREES_H
#define TREES_H

#include "algirithm_interface.h"
#include "standalone-functions/trees-algorithms.h"

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

#endif