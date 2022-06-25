#include "sorter.h"

Sorter::Sorter() {
  srand (time(NULL));
  randomize(STARTING_PILLARS);
}

Sorter::~Sorter() {

}

void Sorter::draw(int start_height) {
  
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
  pillars.clear();

  for (unsigned int i; i < size; i++) {
    int number = rand() % 100 + 1;
    Pillar new_pill(number);
    pillars.push_back(new_pill);
  }
}
