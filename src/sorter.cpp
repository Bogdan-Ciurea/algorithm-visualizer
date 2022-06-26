#include "sorter.h"

Sorter::Sorter() {
  srand (time(NULL));
  randomize(STARTING_PILLARS);
  is_running = false;
}

Sorter::~Sorter() {

}

void Sorter::draw(int start_height) {
  DrawRectangle(0, start_height, GetScreenWidth(), GetScreenHeight() - start_height, BACKGROUND_COLOR);

  if (!is_running) {
    int current_x = 2;
    float pillar_width = (float) GetScreenWidth() / (float) pillars.size() - 3;
    float height_multiplier = (float) (GetScreenHeight() - start_height) / 100;

    for (Pillar cur_pil : pillars) {
      cur_pil.draw(current_x, GetScreenHeight() - height_multiplier * cur_pil._value, pillar_width , height_multiplier * cur_pil._value);
      current_x += pillar_width + 3;
    }
  }
}

void Sorter::add_pillar() {
  int number = rand() % 100 + 1;
  Pillar new_pill(number);
  pillars.push_back(new_pill);
}

void Sorter::remove_pillar() {
  pillars.pop_back();
}

void Sorter::randomize(int size) {
  // Empty the array
  if (!pillars.empty()) {
    for (Pillar cur_pill : pillars) {
      cur_pill.~Pillar();
    }
    pillars.clear();
  }
    

  for (unsigned int i = 0; i < size; i++) {
    Pillar new_pill(rand() % 100 + 1);
    pillars.push_back(new_pill);
  }
}
