#ifndef SORTER_H
#define SORTER_H

#include "algirithm_interface.h"
#include "standalone-functions/sorting-algorithms.h"

class Sorter : public AlgorithmInterface {
 public:
  Sorter();
  ~Sorter() {}

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
  void draw_pillars(std::vector<Pillar> state);

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

#endif