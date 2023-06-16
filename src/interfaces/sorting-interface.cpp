#include "interfaces/sorting-interface.hpp"

Sorter::Sorter() {
  inter_regular = LoadFontEx("assets/inter-regular.ttf", 20, 0, 0);

  int number;
  for (size_t i = 0; i < STARTING_PILLARS; i++) {
    number = rand() % 100 + 1;
    Pillar new_pill(number);
    pillars.push_back(new_pill);
  }
}

bool Sorter::draw() {
  // Build the header
  if (GetScreenHeight() * 0.2 > 100) button_height = GetScreenHeight() * 0.2;
  if (button_height > 130) button_height = 130;

  // Draw the header background
  DrawRectangle(0, 0, GetScreenWidth(), button_height, SORTER_BACKGROUND_COLOR);
  DrawRectangle(0, button_height, GetScreenWidth(), 3, DARKGRAY);

  // Draw the back button
  Rectangle back_button_rect = (Rectangle){10, button_height / 2 - 20, 40, 40};
  if (GuiButton(back_button_rect, GuiIconText(RAYGUI_ICON_ARROW_LEFT_FILL, "")))
    return true;

  draw_header();

  if (!running) draw_pillars(pillars);

  return false;
}

void Sorter::draw_header() {
  // Draw the "Sorting Algorithms" text
  DrawTextEx(inter_regular, "Sorting Algorithms",
             (Vector2){65, button_height / 2 - 10}, 20, 0, DARKGRAY);

  // Draw all the algorithm options
  if (GuiDropdownBox(
          (Rectangle){(float)(80 + MeasureText("Sorting Algorithms", 16)),
                      button_height / 2 - 20, 135, 40},
          "INSERTION;HEAP;SELECTION;MERGE;QUICK;BUBBLE", &dropdown_option,
          dropdown_enabled && !running))
    dropdown_enabled = !dropdown_enabled;

  // Draw the randomize button
  Rectangle randomize_rect = (Rectangle){(float)(GetScreenWidth() - 260),
                                         button_height / 2 - 20, 130, 40};
  if (GuiButton(randomize_rect,
                GuiIconText(RAYGUI_ICON_SHUFFLE, "Randomize")) &&
      !running) {
    shuffle_pillars();
  }

  // Draw the start/end button
  Rectangle start_end_button_rect = (Rectangle){
      (float)(GetScreenWidth() - 115), button_height / 2 - 20, 100, 40};
  if (!running) {
    if (GuiButton(start_end_button_rect,
                  GuiIconText(RAYGUI_ICON_PLAYER_PLAY, "Start"))) {
      running = true;
    }
  } else {
    if (!sorted) {
      if (animation.size() == 0) get_animation();
      draw_animation();
    } else {
      // TODO: Draw Message "already sorted! randomize first"
      running = false;
    }

    if (GuiButton(start_end_button_rect,
                  GuiIconText(RAYGUI_ICON_PLAYER_STOP, "Stop"))) {
      running = false;

      if (animation.size() != 0) pillars = animation.at(0);
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
             (Vector2){(float)(GetScreenWidth() - 363), button_height / 2 + 25},
             20, 0, GRAY);
}

void Sorter::draw_pillars(std::vector<Pillar> state) {
  float current_x = 2;
  float pillar_width = (float)GetScreenWidth() / (float)state.size() - 3.0f;
  float height_multiplier =
      (float)(GetScreenHeight() - button_height - 10) / 100.0f;

  for (auto pillar : state) {
    pillar.draw(current_x,
                GetScreenHeight() - height_multiplier * pillar._value,
                pillar_width, height_multiplier * pillar._value);
    current_x += pillar_width + 3;
  }
}

void Sorter::draw_animation() {
  if (std::chrono::system_clock::now().time_since_epoch() /
              std::chrono::milliseconds(1) -
          last_draw_time >
      1000 / ANIMATION_FPS) {
    // Update the display time of the last frame
    last_draw_time = std::chrono::system_clock::now().time_since_epoch() /
                     std::chrono::milliseconds(1);

    // Display the state of the algorithm
    draw_pillars(animation.at(0));

    // Save the last frame with the sorted pillars
    if (animation.size() == 1) {
      std::cout << "Animation finished!\n";
      running = false;
      sorted = true;
      pillars = animation.at(0);
    }

    // Delete the first frame
    animation.erase(animation.begin());
  } else {
    draw_pillars(animation.at(0));
  }
}

void Sorter::shuffle_pillars() {
  for (auto& cur_pillar : pillars) cur_pillar._value = rand() % 100 + 1;
  sorted = false;
}

void Sorter::add_pillar() {
  if (pillars.size() >= MAX_PILLARS) return;

  int number = rand() % 100 + 1;
  Pillar new_pill(number);
  pillars.push_back(new_pill);
}

void Sorter::remove_pillar() {
  if (pillars.size() <= MIN_PILLARS) return;

  int pillar_index = rand() % pillars.size();
  pillars.erase(pillars.begin() + pillar_index);
}

void Sorter::get_animation() {
  switch (dropdown_option) {
    case 0:
      animation = insertion_sort_algorithm(pillars);
      break;

    case 1:
      animation = heap_sort_algorithm(pillars);
      break;

    case 2:
      animation = selection_sort_algorithm(pillars);
      break;

    case 3:
      animation = merge_sort_algorithm(pillars);
      break;

    case 4:
      animation = quick_sort_algorithm(pillars);
      break;

    case 5:
      animation = bubble_sort_algorithm(pillars);
      break;

    default:
      break;
  }

  last_draw_time = std::chrono::system_clock::now().time_since_epoch() /
                   std::chrono::milliseconds(1);
}
