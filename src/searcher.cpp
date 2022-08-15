#include "searcher.h"

bool Searcher::draw() {
  // Build the header
  if (GetScreenHeight() * 0.2 > 100) button_height = GetScreenHeight() * 0.2;
  if (button_height > 130) button_height = 130;

  // Draw the header background
  DrawRectangle(0, 0, GetScreenWidth(), button_height,
                SEARCHER_BACKGROUND_COLOR);
  DrawRectangle(0, button_height, GetScreenWidth(), 3, DARKGRAY);

  // Draw the back button
  Rectangle back_button_rect = (Rectangle){10, button_height / 2 - 20, 40, 40};
  if (GuiButton(back_button_rect, GuiIconText(RAYGUI_ICON_ARROW_LEFT_FILL, "")))
    return true;

  draw_header();

  draw_pillars();

  return false;
}

void Searcher::draw_header() {
  // Draw the "Search Algorithms" text
  DrawTextEx(inter_regular, "Search Algorithms",
             (Vector2){75, button_height / 2 - 10}, 20, 0, DARKGRAY);

  // Draw all the algorithm options
  if (GuiDropdownBox(
          (Rectangle){(float)(60 + MeasureText("Searching Algorithms", 16)),
                      button_height / 2 - 20, 160, 40},
          "LINEAR;BINARY;JUMP;INTERPOLATION;EXPONENTIAL", &dropdown_option,
          dropdown_enabled && !running))
    dropdown_enabled = !dropdown_enabled;

  // Draw the start/end button
  Rectangle start_end_button_rect = (Rectangle){
      (float)(GetScreenWidth() - 115), button_height / 2 - 20, 100, 40};
  if (!running) {
    if (GuiButton(start_end_button_rect,
                  GuiIconText(RAYGUI_ICON_PLAYER_PLAY, "Start")))
      running = true;
  } else {
    if (GuiButton(start_end_button_rect,
                  GuiIconText(RAYGUI_ICON_PLAYER_STOP, "Stop")))
      running = false;
    
    // Process the input
    if(!valid_input || check_input()) {
      draw_animation();
    }
  }

  // Draw the randomize/sort buttons
  Rectangle randomize_rect = (Rectangle){(float)(GetScreenWidth() - 260),
                                         button_height / 2 - 20, 130, 40};
  if (sorted) {
    if (GuiButton(randomize_rect,
                  GuiIconText(RAYGUI_ICON_SHUFFLE, "Randomize")) && !running) {
      sorted = false;
      shuffle_pillars();
    }
  } else {
    if (GuiButton(randomize_rect, GuiIconText(RAYGUI_ICON_SORT, "Sort")) && !running) {
      sorted = true;
      sort_pillars();
    }
  }

  // Draw the add/remove pillar buttons
  Rectangle add_rect = (Rectangle){(float)(GetScreenWidth() - 315),
                                         button_height / 2 - 20, 40, 40};
  if (GuiButton(add_rect, GuiIconText(RAYGUI_ICON_PLUS, "")) && !running)
    add_pillar();
  
  Rectangle remove_rect = (Rectangle){(float)(GetScreenWidth() - 370),
                                         button_height / 2 - 20, 40, 40};
  if (GuiButton(remove_rect, GuiIconText(RAYGUI_ICON_MINUS, "")) && !running)
    remove_pillar();
  
  DrawTextEx(inter_regular, "Pillar count",
             (Vector2){(float)(GetScreenWidth() - 363), button_height / 2 + 25}, 20, 0, GRAY);

  // Draw the "take input" button
  Rectangle input_rect = (Rectangle){(float)(GetScreenWidth() - 485),
                                         button_height / 2 - 20, 100, 40};
  if (GuiTextBox(input_rect, textBoxText, 64, textBoxEditMode)) textBoxEditMode = !textBoxEditMode;

  // Draw the "Valid input" label to indicate if the input is valid
  if (!valid_input) {

  }

}

void Searcher::draw_pillars() {}

void Searcher::draw_animation() {}

void Searcher::sort_pillars() {}

void Searcher::shuffle_pillars() {}

void Searcher::add_pillar() {}

void Searcher::remove_pillar() {}

bool Searcher::check_input() {
  valid_input = true;
  return true;
}
