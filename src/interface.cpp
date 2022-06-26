#include "interface.h"

#include <iostream>

Interface::Interface() {
  
}

Interface::~Interface() {
  control.~Buttons();
}

void Interface::draw() {
  // TODO: Implement a way we don't make the topbar bigger from a certain point
  int topbar_height = GetScreenHeight() * 0.15;
  if (topbar_height > 80)
    topbar_height = 80;

  control.draw(topbar_height);

  check_for_input();

  sorter.draw(topbar_height + 1);  
}

void Interface::check_for_input() {
  switch (control.get_input())
  {
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
    switch (control.get_algorithm())
    {
    case INSERTION:
      /* code */
      break;
    
    case HEAP:
      /* code */
      break;
    
    case SELECTION:
      /* code */
      break;
    
    case MERGE:
      /* code */
      break;
    
    case QUICK:
      /* code */
      break;

    case BUBBLE:
      /* code */
      break;
    
    default:
      break;
    }
    break;

  default:
    break;
  }
}
