#include "searcher.h"

Searcher::Searcher() {
  inter_regular = LoadFontEx("assets/inter-regular.ttf", 20, 0, 0);

  int number;
  for (size_t i = 0; i < STARTING_PILLARS; i++) {
    number = rand() % 100 + 1;
    Pillar new_pill(number);
    pillars.push_back(new_pill);
  }
  sort_pillars();
}

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

  draw_pillars(pillars);

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
          "LINEAR;BINARY;JUMP;INTERPOLATION", &dropdown_option,
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
                  GuiIconText(RAYGUI_ICON_PLAYER_STOP, "Stop"))) {
      running = false;

      if (animation.size() != 0) pillars = animation.at(0);
    }

    // Process the input
    // If valid input is 'false' will result in calling check_input()
    // Valid input will mean that the pillar's value is valid (not a string)
    // but also that the pillar is in the array
    if (valid_input || check_input())
      draw_animation();
    else
      running = false;
  }

  // Draw the randomize/sort buttons
  Rectangle randomize_rect = (Rectangle){(float)(GetScreenWidth() - 260),
                                         button_height / 2 - 20, 130, 40};
  if (sorted) {
    if (GuiButton(randomize_rect,
                  GuiIconText(RAYGUI_ICON_SHUFFLE, "Randomize")) &&
        !running) {
      sorted = false;
      shuffle_pillars();
    }
  } else {
    if (GuiButton(randomize_rect, GuiIconText(RAYGUI_ICON_SORT, "Sort")) &&
        !running) {
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
             (Vector2){(float)(GetScreenWidth() - 363), button_height / 2 + 25},
             20, 0, GRAY);

  // Draw the "take input" button
  Rectangle input_rect = (Rectangle){(float)(GetScreenWidth() - 485),
                                     button_height / 2 - 20, 100, 40};
  if (GuiTextBox(input_rect, textBoxText, 64, textBoxEditMode))
    textBoxEditMode = !textBoxEditMode;

  // Draw the "Valid input" label to indicate if the input is valid
  if (!valid_input) {
    // TODO: Draw error message ("INVALID INPUT")
  }
}

void Searcher::draw_pillars(std::vector<Pillar> state) {
  float current_x = 2;
  float pillar_width = (float)GetScreenWidth() / (float)state.size() - 3.0f;
  float height_multiplier = (float)(GetScreenHeight() - button_height) / 100.0f;

  for (auto pillar : state) {
    pillar.draw(current_x,
                GetScreenHeight() - height_multiplier * pillar._value,
                pillar_width, height_multiplier * pillar._value);
    current_x += pillar_width + 3;
  }
}

void Searcher::draw_animation() {
  if (!animation.empty()) {
    if (std::chrono::system_clock::now().time_since_epoch() /
                std::chrono::milliseconds(1) -
            last_draw_time >
        1000 / SEARCH_ANIMATION_FPS) {
      // Update the display time of the last frame
      last_draw_time = std::chrono::system_clock::now().time_since_epoch() /
                       std::chrono::milliseconds(1);

      // Display the state of the algorithm
      draw_pillars(animation.at(0));

      // Save the last frame with the sorted pillars
      if (animation.size() == 1) {
        pillars = animation.at(0);
        std::cout << "Animation finished!\n";
      }

      // Delete the first frame
      animation.erase(animation.begin());
    } else {
      draw_pillars(animation.at(0));
    }
  } else {
    valid_input = false;
    running = false;
  }
}

void Searcher::sort_pillars() {
  std::sort(pillars.begin(), pillars.end(),
            [](const Pillar& lhs, const Pillar& rhs) {
              return lhs._value < rhs._value;
            });
}

void Searcher::shuffle_pillars() {
  for (auto& cur_pillar : pillars) cur_pillar._value = rand() % 100 + 1;
}

void Searcher::add_pillar() {
  if (pillars.size() >= MAX_PILLARS) return;

  int number = rand() % 100 + 1;
  Pillar new_pill(number);
  pillars.push_back(new_pill);

  sort_pillars();
}

void Searcher::remove_pillar() {
  if (pillars.size() <= MIN_PILLARS) return;

  int pillar_index = rand() % pillars.size();
  pillars.erase(pillars.begin() + pillar_index);
}

bool Searcher::check_input() {
  valid_input = false;

  value_searched = atoi(textBoxText);
  // Check that the text is an integer
  if (value_searched == 0) {
    std::cout << "Input not an integer!\n";
    return false;
  }

  switch (dropdown_option) {
    case 0:
      animation = search_linear_algo(pillars, value_searched);
      break;

    case 1:
      animation = search_binary_algo(pillars, value_searched);
      break;

    case 2:
      animation = search_jump_algo(pillars, value_searched);
      break;

    case 3:
      animation = search_interpolation_algo(pillars, value_searched);
      break;

    default:
      break;
  }

  last_draw_time = std::chrono::system_clock::now().time_since_epoch() /
                   std::chrono::milliseconds(1);

  valid_input = true;
  return true;
}
