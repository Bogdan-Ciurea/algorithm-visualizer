/**
 * @file main-interface.hpp
 * @author Bogdan Ciurea
 * @brief This file in responsible for defining the main interface that will be
 * used in the main program and will manage the other interfaces.
 * @version 0.1
 * @date 2023-06-15
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef MAIN_INTERFACE_HPP
#define MAIN_INTERFACE_HPP

#include "blank-interface.hpp"
#include "graph-interface.hpp"
#include "search-interface.hpp"
#include "sorting-interface.hpp"
#include "tree-interface.hpp"

class MainInterface {
 public:
  MainInterface(Font *inter_regular, Font *inter_light) {
    this->inter_regular = inter_regular;
    this->inter_light = inter_light;
  }
  ~MainInterface() {
    if (current_interface != nullptr) delete current_interface;
  };

  /**
   * @brief Will update the variables and draw everything on the screen
   *
   */
  void draw();

 private:
  AlgorithmInterface *current_interface = nullptr;
  Font *inter_regular, *inter_light;
};

#endif  // MAIN_INTERFACE_HPP