#include "interface.h"

Interface::Interface() {
  
}

Interface::~Interface() {
  control.~Buttons();
  sorter.~Sorter();
}

void Interface::draw() {
  int topbar_height = GetScreenHeight() * 0.15;
  if (topbar_height > 80)
    topbar_height = 80;

  check_for_input();

  sorter.draw(topbar_height + 1);

  control.draw(topbar_height);
}

void Interface::check_for_input() {
  switch (control.get_input()) {
  case ADD_PILLAR_BTN:
    if (sorter.get_number_pillars() <= MAX_PILLARS) {
      sorter.add_pillar();
    }
    break;
  
  case REMOVE_PILLAR_BTN:
    if (sorter.get_number_pillars() >= MIN_PILLARS) {
      sorter.remove_pillar();
    }
    break;

  case RANDOMIZE_BTN:
    sorter.randomize(sorter.get_number_pillars());
    break;

  case START_BTN:
    switch (control.get_algorithm()) {
    case INSERTION:
      sorter.get_animation_algorithm(INSERTION);
      break;
    
    case HEAP:
      sorter.get_animation_algorithm(HEAP);
      break;
    
    case SELECTION:
      sorter.get_animation_algorithm(SELECTION);
      break;
    
    case MERGE:
      sorter.get_animation_algorithm(MERGE);
      break;
    
    case QUICK:
      sorter.get_animation_algorithm(QUICK);
      break;

    case BUBBLE:
      sorter.get_animation_algorithm(BUBBLE);
      break;
    
    default:
      break;
    }
    break;

  default:
    break;
  }
}
