#include "sorter.h"

bool Sorter::draw() {
  // Build the header
  float button_height = 100;
  if (GetScreenHeight() * 0.2 > 100) button_height = GetScreenHeight() * 0.2;
  if (button_height > 130) button_height = 130;

  // Draw the header background
  DrawRectangle(0, 0, GetScreenWidth(), button_height, SORTER_BACKGROUND_COLOR);
  DrawRectangle(0, button_height, GetScreenWidth(), 3, BLACK);

  // Draw the back button
  Rectangle back_button_rect = (Rectangle){10, button_height / 2 - 20, 40, 40};
  if (GuiButton(back_button_rect, GuiIconText(RAYGUI_ICON_ARROW_LEFT_FILL, ""))) return true;

  // Draw the "Sorting Algorithms" text
  DrawTextEx(inter_regular, "Sorting Algorithms", (Vector2){65, button_height / 2 - 10}, 20, 0, DARKGRAY);

  // Draw all the algorithm options
  if (GuiDropdownBox((Rectangle){ (float)(80 + MeasureText("Sorting Algorithms", 16)), button_height / 2 - 20, 135, 40},
      "INSERTION;HEAP;SELECTION;MERGE;QUICK;BUBBLE", 
      &dropdown_option, dropdown_enabled)) dropdown_enabled = !dropdown_enabled;


  // Draw the algorithm dropdown buttons
  Rectangle randomize_rect = (Rectangle){(float)(GetScreenWidth() - 260), button_height / 2 - 20, 130, 40};
  GuiButton(randomize_rect, GuiIconText(RAYGUI_ICON_SHUFFLE, "Randomize"));


  // Draw the start/end button
  Rectangle start_end_button_rect = (Rectangle){(float)(GetScreenWidth() - 115), button_height / 2 - 20, 100, 40};
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

void Sorter::add_pillar() {
  if (is_running) {
    return;
  }

  int number = rand() % 100 + 1;
  Pillar new_pill(number);
  pillars.push_back(new_pill);
}

void Sorter::remove_pillar() {
  if (is_running) {
    return;
  }

  pillars.pop_back();
}

void Sorter::randomize(int size) {
  if (is_running) {
    return;
  }

  // Empty the array
  if (!pillars.empty()) {
    for (Pillar cur_pill : pillars) {
      cur_pill.~Pillar();
    }
    pillars.clear();
  }

  for (int i = 0; i < size; i++) {
    Pillar new_pill(rand() % 100 + 1);
    pillars.push_back(new_pill);
  }
}

bool Sorter::sorted_pillars() {
  for (int i = 0; i < pillars.size() - 1; i++) {
    if (pillars.at(i)._value > pillars.at(i + 1)._value) {
      return false;
    }
  }

  return true;
}

void Sorter::get_animation_algorithm(sort_algorithm_options algorithm) {
  if (is_running) {
    return;
  }

  animation.clear();

  // Check if the pillars are ordered. In this case we will draw a special
  // animation
  if (sorted_pillars()) {
    for (int i = 0; i < pillars.size(); i++) {
      animation.push_back(pillars);
      for (int j = 0; j <= i; j++)
        animation.at(animation.size() - 1).at(j).change_state(MOVED);
    }

    animation.push_back(pillars);

    is_running = true;
    last_draw_time = std::chrono::system_clock::now().time_since_epoch() /
                     std::chrono::milliseconds(1);

    return;
  }

  switch (algorithm) {
    case INSERTION:
      animation = insertion_sort_algorithm(pillars);
      break;

    case HEAP:
      animation = heap_sort_algorithm(pillars);
      break;

    case SELECTION:
      animation = selection_sort_algorithm(pillars);
      break;

    case MERGE:
      animation = merge_sort_algorithm(pillars);
      break;

    case QUICK:
      animation = quick_sort_algorithm(pillars);
      break;

    case BUBBLE:
      animation = bubble_sort_algorithm(pillars);
      break;

    default:
      break;
  }

  is_running = true;
  last_draw_time = std::chrono::system_clock::now().time_since_epoch() /
                   std::chrono::milliseconds(1);
}
