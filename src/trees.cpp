#include "trees.h"

bool Trees::draw() {
  // Build the header
  if (GetScreenHeight() * 0.2 > 100) button_height = GetScreenHeight() * 0.2;
  if (button_height > 130) button_height = 130;

  // Draw the header background
  DrawRectangle(0, 0, GetScreenWidth(), button_height, TREES_BACKGROUND_COLOR);
  DrawRectangle(0, button_height, GetScreenWidth(), 3, DARKGRAY);

  // Draw the back button
  Rectangle back_button_rect = (Rectangle){10, button_height / 2 - 20, 40, 40};
  if (GuiButton(back_button_rect, GuiIconText(RAYGUI_ICON_ARROW_LEFT_FILL, "")))
    return true;
  
  draw_header();

  return false;
}

void Trees::draw_header() {
  // Draw the "Trees Algorithms" text
  DrawTextEx(inter_regular, "Trees Algorithms",
             (Vector2){75, button_height / 2 - 10}, 20, 0, DARKGRAY);

  // Draw all the algorithm options
  if (GuiDropdownBox(
          (Rectangle){(float)(80 + MeasureText("Trees Algorithms", 16)),
                      button_height / 2 - 20, 135, 40},
          "BINARY;RED BLACK", &dropdown_option, dropdown_enabled && !running))
    dropdown_enabled = !dropdown_enabled;

  // Draw the start/end button
  Rectangle start_end_button_rect = (Rectangle){
      (float)(GetScreenWidth() - 115), button_height / 2 - 20, 100, 40};
  if (!running) {
    if (GuiButton(start_end_button_rect,
                  GuiIconText(RAYGUI_ICON_PLAYER_PLAY, "Start"))) {
      running = true;
    }
  } else {
    if (GuiButton(start_end_button_rect,
                  GuiIconText(RAYGUI_ICON_PLAYER_STOP, "Stop"))) {
      running = false;
    }
  }
}