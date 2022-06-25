#ifndef BUTTONS_H
#define BUTTONS_H

#include "utils.h"

class Buttons
{
public:
  Buttons();
  ~Buttons();

  /**
   * @brief Will draw the buttons to the screen.
   * 
   * @param max_width represents the maximum allocated width of the buttons 
   */
  void draw(int max_width);

  /**
   * @brief Will check on what option the user pressed on
   * 
   * @return The selected input
   */
  input_options get_input();

  /**
   * @brief Get the algorithm object
   * 
   * @return The selected algorithm 
   */
  algorithm_options get_algorithm();

private:
  /* data */
};

#endif