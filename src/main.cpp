#include "interface.h"

int main()
{
  // Initialization
  //--------------------------------------------------------------------------------------
  const int screenWidth = 1000;
  const int screenHeight = 550;

  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(screenWidth, screenHeight, "Algorithm visualizer");
  SetWindowMinSize(500, 300);

  SetTargetFPS(60); // Set our game to run at 60 frames-per-second
  //--------------------------------------------------------------------------------------

  // Set up the interface;
  Interface current_interface;

  // Main game loop
  while (!WindowShouldClose()) // Detect window close button or ESC key
  {
    // Update

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

    current_interface.draw();

    // TODO: If the window has a certain ration, the buttons will overlap
    // Try to resolve this using "void SetWindowSize(int width, int height);"

    EndDrawing();
    //----------------------------------------------------------------------------------
    }

  // De-Initialization
  //--------------------------------------------------------------------------------------
  CloseWindow(); // Close window and OpenGL context
  //--------------------------------------------------------------------------------------

  return 0;
}
