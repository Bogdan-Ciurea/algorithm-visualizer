#ifndef INTERFACE_H
#define INTERFACE_H

#include "buttons.h"
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
  /**
   * @brief Will get the input from the user through the controller
   *
   */
  void check_for_input();

  Buttons control;
  Sorter sorter;
};

#endif