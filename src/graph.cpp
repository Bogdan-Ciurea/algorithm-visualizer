#include "graph.h"

bool Graph::draw() {
  float button_height = 100;
  if (GetScreenHeight() * 0.2 > 100) button_height = GetScreenHeight() * 0.2;
  DrawRectangle(0, 0, GetScreenWidth(), button_height, GRAPH_BACKGROUND_COLOR);
  Rectangle back_button_rect = (Rectangle){10, button_height / 2 - 25, 50, 50};
  if (GuiButton(back_button_rect, GuiIconText(RAYGUI_ICON_ARROW_LEFT_FILL, ""))) return true;

  return false;
}