#ifndef INTERFACE_H
#define INTERFACE_H

#include "algirithm_interface.h"
// #include "buttons.h"
#include "graph.h"
#include "searcher.h"
#include "sorter.h"
#include "trees.h"

class Interface {
 public:
  Interface();
  ~Interface();

  /**
   * @brief Will update the variables and draw everything on the screen
   *
   */
  void draw();

 private:
  AlgorithmInterface *current_interface = nullptr;
  Font inter_regular, inter_light;
};

#endif