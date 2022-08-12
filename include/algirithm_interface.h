#ifndef ALGORITHM_INTERFACE_H
#define ALGORITHM_INTERFACE_H

#include "utils.h"

class AlgorithmInterface {
 public:
  /**
   * @brief Will update the variables and draw everything on the screen
   *
   * @returns true if we want to exit the interface
   */
  virtual bool draw() { return true; }

  bool running = false;
  Font inter_regular;
  int dropdown_option = 0;
  bool dropdown_enabled = false;
};

#endif