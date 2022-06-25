#include "buttons.h"

#include <iostream>

Buttons::Buttons() {
  Image minus = LoadImage("assets/minus.png");
  Image plus  = LoadImage("assets/plus.png");

  minus_texture = LoadTextureFromImage(minus);
  plus_texture  = LoadTextureFromImage(plus);

  UnloadImage(minus);
  UnloadImage(plus);

  current_algorithm = QUICK;
  current_algorithm_text = "Quick Sort";
}

Buttons::~Buttons() {
  UnloadTexture(plus_texture);
  UnloadTexture(minus_texture);
}

void Buttons::draw(int max_height) {
  // Draw the top bar
  DrawRectangle(0, 0, GetScreenWidth(), max_height, TOPBAR_COLOR);

  // The size of the font
  float font_size = max_height / 3.5;
  // The distance between two buttons
  float border_space = max_height / 4;

  DrawText("Algorithm visualizer", 5, 10, font_size / 1.5, TEXT_COLOR);

  // Width of the text we are going to display
  float start_text_width   = MeasureText("Start", font_size);
  float random_text_width  = MeasureText("Randomize", font_size);
  float pillars_text_width = MeasureText("Pillars", font_size);
  float minus_sign_width   = minus_texture.width * font_size / 300; // Don't even ask how I got this value 😅
  float plus_sign_width    = plus_texture.width * font_size / 300;

  float distance_from_border = border_space + start_text_width;  

  // Draw the Start btn and listen to the signal
  if (draw_buttons(GetScreenWidth() - distance_from_border,
      (max_height - font_size) / 2,  "Start", font_size, START_BTN)) {
    button_start_pressed = true;
  }

  distance_from_border += border_space + random_text_width; 

  // Draw the Randomize btn and listen to the signal
  if (draw_buttons(GetScreenWidth()- distance_from_border,
      (max_height - font_size) / 2,  "Randomize", font_size, RANDOMIZE_BTN)) {
    button_random_pressed = true;
  }

  distance_from_border += border_space + plus_sign_width;

  // Draw the Add btn and listen to the signal
  if (draw_buttons_with_image(GetScreenWidth()- distance_from_border, 
      (max_height - font_size) / 2, font_size, ADD_PILLAR_BTN, plus_texture)) {
    button_add_pressed = true;
  }

  distance_from_border += border_space + pillars_text_width;

  // Draw the Pillar text
  DrawText("Pillars", GetScreenWidth() - distance_from_border, (max_height - font_size) / 2, font_size, TEXT_COLOR);

  distance_from_border += border_space + minus_sign_width;

  // Draw the Remove btn and listen to the signal
  if (draw_buttons_with_image(GetScreenWidth()- distance_from_border, 
      (max_height - font_size) / 2, font_size,  REMOVE_PILLAR_BTN, minus_texture)) {
    button_remove_pressed = true;
  }
  
  // TODO: Draw a button on the left of the canvas
  // It should contain the name of the current algorithm

  if (draw_buttons(MeasureText("Algorithm visualizer", font_size / 1.5) + 5 + border_space, (max_height - font_size) / 2, 
  current_algorithm_text, font_size, SELECT_ALGORITHM)) {
    button_chose_algorithm_pressed = true;
  }


  if (button_chose_algorithm_pressed) {
    // Draw every algorithm in order, one under the other like a drop down menu
  }
}

input_options Buttons::get_input() {
  if (button_start_pressed) {
    button_start_pressed = false;
    return input_options::START_BTN;
  }
  if (button_random_pressed) {
    button_random_pressed = false;
    return input_options::RANDOMIZE_BTN;
  }
  if (button_add_pressed) {
    button_add_pressed = false;
    return input_options::ADD_PILLAR_BTN;
  }
  if (button_remove_pressed) {
    button_remove_pressed = false;
    return input_options::REMOVE_PILLAR_BTN;
  }

  return input_options::NONE;
}

algorithm_options Buttons::get_algorithm() {
  return current_algorithm;
}

input_options Buttons::draw_buttons(int x, int y, char* text, float font_size, input_options option) {
  Rectangle r1 = { (float) x, (float) y, (float) MeasureText(text, font_size), (float) font_size };

  if (CheckCollisionPointRec(GetMousePosition(), r1)) {
    DrawText(text, x, y, font_size, HOVER_TEXT_COLOR); // On hover
    if (IsMouseButtonPressed(MOUSE_CURSOR_DEFAULT)) {
      return option;
    }
  }
  else {
    DrawText(text, x, y, font_size, TEXT_COLOR);
  }

  return input_options::NONE;
}

input_options Buttons::draw_buttons_with_image(int x, int y, int size, input_options option, Texture2D texture) {
  DrawTextureEx(texture, Vector2{(float) x, (float) y}, 0.0f, (float) size / 300, WHITE);
  Rectangle r1 = { (float) x, (float) y, (float) texture.width * size / 300, (float) texture.width * size / 300};

  if (CheckCollisionPointRec(GetMousePosition(), r1) && IsMouseButtonPressed(MOUSE_CURSOR_DEFAULT)) {
    return option;
  }

  return input_options::NONE;
}