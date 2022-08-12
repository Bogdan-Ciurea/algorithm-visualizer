#include "interface.h"

#include <iostream>

Interface::Interface() {
  inter_regular = LoadFontEx("assets/inter-regular.ttf", 20, 0, 0);
  inter_light   = LoadFontEx("assets/inter-light.ttf",   20, 0, 0);
}

Interface::~Interface() {
  UnloadFont(inter_regular);
  UnloadFont(inter_light);
}

void Interface::draw() {
  if (current_interface != nullptr) {
    // Draw the current interface
    if (current_interface->draw()) {
      // If we want to return from the draw() function, we delete the current
      // interface to free the memory
      delete current_interface;
      current_interface = nullptr;
    }
  } else {
    // Draw the main menu

    // Get the sizes for the header (which will contain the buttons for the algorithms)
    float button_width = GetScreenWidth() / 4;
    float button_height = 100;
    if (GetScreenHeight() * 0.2 > 100) button_height = GetScreenHeight() * 0.2;
    if (button_height > 130) button_height = 130;

    // Check if the user selected the Sorting Algorithms
    if (GuiButtonWithColor((Rectangle){0, 0, button_width, button_height},
                           "Sorting Algorithms", SORTER_BACKGROUND_COLOR))
      current_interface = new Sorter();

    // Check if the user selected the Search Algorithms
    if (GuiButtonWithColor(
            (Rectangle){button_width, 0, button_width, button_height},
            "Search Algorithms", SEARCHER_BACKGROUND_COLOR))
      current_interface = new Searcher();

    // Check if the user selected the Graph Algorithms
    if (GuiButtonWithColor(
            (Rectangle){button_width * 2, 0, button_width, button_height},
            "Graph Algorithms", GRAPH_BACKGROUND_COLOR))
      current_interface = new Graph();

    // Check if the user selected the Trees Algorithms
    if (GuiButtonWithColor(
            (Rectangle){button_width * 3, 0, button_width, button_height},
            "Trees Algorithms", TREES_BACKGROUND_COLOR))
      current_interface = new Trees();

    // Draw some margins between the buttons
    DrawRectangle(0, button_height, GetScreenWidth(), 3, BLACK);
    DrawRectangle(button_width - 1, 0, 3, button_height, BLACK);
    DrawRectangle(button_width * 2 - 1, 0, 3, button_height, BLACK);
    DrawRectangle(button_width * 3 - 1, 0, 3, button_height, BLACK);

    // Draw the text. unfortunately there is no better way of drawing centered text so...
    DrawTextEx(inter_regular, "Welcome to my \"Algorithms Visualizer\"", 
               (Vector2){ (float)((GetScreenWidth() - MeasureText("Welcome to my \"Algorithms Visualizer\"", 20) * 0.8f) / 2),
                          (float)((GetScreenHeight() + button_height) / 2 - 20)},
               20.0f, 0.0f, BLACK);
    DrawTextEx(inter_regular, "personal project", 
               (Vector2){ (float)((GetScreenWidth() - MeasureText("personal project", 20) * 0.8f) / 2),
                          (float)((GetScreenHeight() + button_height) / 2)}, 
               20.0f, 0.0f, BLACK);
    DrawTextEx(inter_light, "Made with love by Bogdan Ciurea", 
               (Vector2){ (float)((GetScreenWidth() - MeasureText("Made with love by Bogdan Ciurea", 20) * 0.8f) / 2),
                          (float)((GetScreenHeight() + button_height) / 2 + 20)},
               20.0f, 0.0f, BLACK);
  }
}
