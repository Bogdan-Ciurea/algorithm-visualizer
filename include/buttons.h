#ifndef BUTTONS_H
#define BUTTONS_H

#include "utils.h"

class Buttons {
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
  sort_search_input_options get_input();

  /**
   * @brief Get the algorithm object
   *
   * @return The selected algorithm
   */
  sort_algorithm_options get_algorithm();

 private:
  Texture2D plus_texture;
  Texture2D minus_texture;
  sort_algorithm_options current_algorithm;
  char *current_algorithm_text;

  sort_search_input_options draw_buttons(int x, int y, char *text,
                                         float font_size,
                                         sort_search_input_options option);
  sort_search_input_options draw_buttons_with_image(
      int x, int y, int size, sort_search_input_options option,
      Texture2D texture);

  bool button_start_pressed = false;
  bool button_random_pressed = false;
  bool button_add_pressed = false;
  bool button_remove_pressed = false;
  bool button_chose_algorithm_pressed = false;
};

#endif