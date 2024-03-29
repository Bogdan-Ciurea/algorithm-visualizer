/**
 * @file sorting-interface.hpp
 * @author Bogdan Ciurea
 * @brief This file in responsible for defining the sorting interface that will
 * be used in the main program and by the main-interface.hpp
 * @version 0.1
 * @date 2023-06-15
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef SORTING_INTERFACE_HPP
#define SORTING_INTERFACE_HPP

#include "../standalone-functions/sorting-algorithms.hpp"
#include "blank-interface.hpp"

class SortInterface : public AlgorithmInterface {
 public:
  SortInterface(Font *inter_regular, Font *inter_light);
  ~SortInterface() {}

  /**
   * @brief Will draw everything to the screen
   *
   */
  bool draw();

 private:
  bool sorted = false;
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
  void shuffle_pillars();

  /**
   * @brief These will be te functions responsible for adding/removing a pillar
   *
   */
  void add_pillar();
  void remove_pillar();

  /**
   * @brief Get the animation object
   *
   */
  void get_animation();
};

#endif  // SORTING_INTERFACE_HPP