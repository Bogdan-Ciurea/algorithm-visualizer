#include "graph.h"

bool Graph::draw() {
  // Build the header
  float button_height = 100;
  if (GetScreenHeight() * 0.2 > 100) button_height = GetScreenHeight() * 0.2;
  if (button_height > 130) button_height = 130;

  // Draw the header background
  DrawRectangle(0, 0, GetScreenWidth(), button_height, GRAPH_BACKGROUND_COLOR);
  DrawRectangle(0, button_height, GetScreenWidth(), 3, BLACK);

  // Draw the back button
  Rectangle back_button_rect = (Rectangle){10, button_height / 2 - 25, 50, 50};
  if (GuiButton(back_button_rect, GuiIconText(RAYGUI_ICON_ARROW_LEFT_FILL, ""))) return true;

  // Draw the "Graph Algorithms" text
  DrawTextEx(inter_regular, "Graph Algorithms", (Vector2){75, button_height / 2 - 10}, 20, 0, DARKGRAY);

  // Draw all the algorithm options
  if (GuiDropdownBox((Rectangle){ (float)(80 + MeasureText("Graph Algorithms", 16)), button_height / 2 - 20, 170, 40},
      "DIJKSTRA;FLOYD WARSHALL;BSF;DFS;A*;PRIM'S;KRUSKAL'S;TOPOLOGICAL",
      &dropdown_option, dropdown_enabled)) dropdown_enabled = !dropdown_enabled;

  // Draw the start/end button
  Rectangle start_end_button_rect = (Rectangle){(float)(GetScreenWidth() - 115), button_height / 2 - 25, 100, 50};
  if (!running) {
    if (GuiButton(start_end_button_rect, GuiIconText(RAYGUI_ICON_PLAYER_PLAY, "Start"))) {
      running = true;
    }
  }
  else {
    if (GuiButton(start_end_button_rect, GuiIconText(RAYGUI_ICON_PLAYER_STOP, "Stop"))) {
      running = false;
    }
  }

  return false;
}
