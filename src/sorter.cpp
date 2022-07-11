#include "sorter.h"

Sorter::Sorter() {
  srand (time(NULL));
  randomize(STARTING_PILLARS);
  is_running = false;
}

Sorter::~Sorter() {
  pillars.clear();
  for (std::vector<Pillar> frame : animation) {
    frame.clear();
  }
  animation.clear();
}

void Sorter::draw(int start_height) {
  DrawRectangle(0, start_height, GetScreenWidth(), GetScreenHeight() - start_height, BACKGROUND_COLOR);
  
  float current_x = 2;
  float pillar_width = (float) GetScreenWidth() / (float) pillars.size() - 3.0f;
  float height_multiplier = (float) (GetScreenHeight() - start_height) / 100.0f;

  if (!is_running) {
    for (Pillar cur_pil : pillars) {
      cur_pil.draw(current_x, GetScreenHeight() - height_multiplier * cur_pil._value, pillar_width , height_multiplier * cur_pil._value);
      current_x += pillar_width + 3;
    }
  }
  else {
    if (!animation.empty()) {
      if ( std::chrono::system_clock::now().time_since_epoch() / 
        std::chrono::milliseconds(1) - last_draw_time > 1000 / ANIMATION_FPS) {
        
        // Update the display time of the last frame
        last_draw_time = std::chrono::system_clock::now().time_since_epoch() / 
          std::chrono::milliseconds(1);

        // Display the state of the algorithm
        for (Pillar cur_pil : animation.at(0)) {
          cur_pil.draw(current_x, GetScreenHeight() - height_multiplier * cur_pil._value, pillar_width , height_multiplier * cur_pil._value);
          current_x += pillar_width + 3;
        }

        // Save the last frame with the sorted pillars
        if (animation.size() == 1) {
          pillars = animation.at(0);
        }
        
        // Delete the first frame 
        animation.erase(animation.begin());
      }
      else {
        // Display the state of the algorithm
        for (Pillar cur_pil : animation.at(0)) {
          cur_pil.draw(current_x, GetScreenHeight() - height_multiplier * cur_pil._value, pillar_width , height_multiplier * cur_pil._value);
          current_x += pillar_width + 3;
        }
      }
    }
    else {
      is_running = false;
    }
  }
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

void Sorter::get_animation_algorithm(algorithm_options algorithm) {
  if (is_running) {
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
