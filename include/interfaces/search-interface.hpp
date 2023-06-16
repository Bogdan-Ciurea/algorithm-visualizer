/**
 * @file search-interface.hpp
 * @author Bogdan Ciurea
 * @brief This file in responsible for defining the search interface that will
 * be used in the main program and by the main-interface.hpp
 * @version 0.1
 * @date 2023-06-15
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef SEARCH_INTERFACE_HPP
#define SEARCH_INTERFACE_HPP

#include "../standalone-functions/search-algorithms.h"
#include "blank-interface.hpp"

class SearchInterface : public AlgorithmInterface {
 public:
  SearchInterface(Font *inter_regular, Font *inter_light);
  ~SearchInterface() {}

  bool draw();

 private:
  // Variables that are used for flow control
  bool sorted = true;
  bool textBoxEditMode = false;
  char textBoxText[64] = "Input";
  bool valid_input =
      false;  // This valid be used as an indicator of the fact that we
              // processed the input and it was valid Will also work as a toggle
              // that we want to start showing the animation

  // Variables that represent the processed input
  int value_searched = -1;

  unsigned long last_draw_time;

  std::vector<Pillar> pillars;
  // 'animation' will act as an array of frames, thus creating an animation
  std::vector<std::vector<Pillar>> animation;

  /**
   * @brief The main function that will process the input
   *
   */
  void run_program();

  /**
   * @brief The function responsible for drawing the pillars
   *
   */
  void draw_pillars(std::vector<Pillar> *state);

  /**
   * @brief The function that will draw the header and will take the input from
   * that user
   *
   */
  void draw_header();

  /**
   * @brief The function that will draw the animation that we want to get
   *
   */
  void draw_animation();

  /**
   * @brief These are the functions responsible for sorting/shuffling the
   * pillars
   *
   */
  void sort_pillars();
  void shuffle_pillars();

  /**
   * @brief These will be te functions responsible for adding/removing a pillar
   *
   */
  void add_pillar();
  void remove_pillar();

  /**
   * @brief This function is responsible for checking the input number from the
   * user
   *
   * @return bool false for an error input. True if we can start running the
   * program
   */
  bool check_input();
};

#endif  // SEARCH_INTERFACE_HPP