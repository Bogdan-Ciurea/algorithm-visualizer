#ifndef SORTER_H
#define SORTER_H

#include "standalone-functions/sorting-algorithms.h"

class Sorter {
 public:
  Sorter();
  ~Sorter();

  /**
   * @brief Will draw everything to the screen
   *
   * @param start_height represents the starting height on which we can draw
   */
  void draw(int start_height);

  /**
   * @brief Will add one pillar to the list
   *
   */
  void add_pillar();

  /**
   * @brief Will remove the last pillar of the list
   *
   */
  void remove_pillar();

  /**
   * @brief Will randomize the array
   *
   * @param size represents the size of the desired array
   */
  void randomize(int size);

  /**
   * @brief Will get the number of pillars in the list
   *
   * @return int the number of pillars in the list
   */
  int get_number_pillars() { return pillars.size(); }

  /**
   * @brief Will say if the array is sorted or not
   *
   * @return true   if the array is sorted
   * @return false  if the array is NOT sorted
   */
  bool sorted_pillars();

  /**
   * @brief Will initialise the algorithm
   *
   * @param algorithm the selected algorithm
   */
  void get_animation_algorithm(sort_algorithm_options algorithm);

 private:
  // 'pillars' will act as a state of the currently displayed pillars
  std::vector<Pillar> pillars;

  // 'animation' will act as an array of frames, thus creating an animation
  std::vector<std::vector<Pillar>> animation;
  int pillar_width;
  bool is_running;
  unsigned long last_draw_time;
};

#endif