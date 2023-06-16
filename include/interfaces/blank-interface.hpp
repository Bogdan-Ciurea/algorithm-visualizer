/**
 * @file blank-interface.hpp
 * @author Bogdan Ciurea
 * @brief This file is responsible for defining the class that will be
 * inherited by all the interfaces
 * @version 0.1
 * @date 2023-06-15
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef BLANK_INTERFACE_HPP
#define BLANK_INTERFACE_HPP

#include "../utils.h"

class AlgorithmInterface {
 public:
  /**
   * @brief Will update the variables and draw everything on the screen
   *
   * @returns true if we want to exit the interface
   */
  virtual bool draw() { return true; }

  /**
   * @brief The function that will draw the header and will take the input from
   * that user
   *
   */
  virtual void draw_header() {}

  bool running = false;
  Font inter_regular;
  int dropdown_option = 0;
  bool dropdown_enabled = false;
  float button_height = 100;
};

#endif  // BLANK_INTERFACE_HPP