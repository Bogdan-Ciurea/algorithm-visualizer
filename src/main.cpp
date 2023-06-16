#include "interfaces/main-interface.hpp"

int main() {
  // Initialization
  //--------------------------------------------------------------------------------------
  int const screenWidth = 1000;
  int const screenHeight = 550;

  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(screenWidth, screenHeight, "Algorithm visualizer");
  SetWindowMinSize(1000, 550);

  SetTargetFPS(60);  // Set our game to run at 60 frames-per-second
  //--------------------------------------------------------------------------------------

  // Set up the interface;
  Interface current_interface;

  // Set the current font
  Font inter_regular = LoadFontEx("assets/inter-regular.ttf", 20, 0, 0);

  GuiSetFont(inter_regular);

  // Main game loop
  while (!WindowShouldClose())  // Detect window close button or ESC key
  {
    // Update

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

    ClearBackground(MY_BACKGROUND_COLOR);

    current_interface.draw();

    // TODO: If the window has a certain ration, the buttons will overlap
    // Try to resolve this using "void SetWindowSize(int width, int height);"

    // TODO: Add fonts from assets/
    // https://www.raylib.com/examples/text/loader.html?name=text_font_filters

    EndDrawing();
    //----------------------------------------------------------------------------------
  }

  UnloadFont(inter_regular);

  // De-Initialization
  //--------------------------------------------------------------------------------------
  CloseWindow();  // Close window and OpenGL context
  //--------------------------------------------------------------------------------------

  return 0;
}
