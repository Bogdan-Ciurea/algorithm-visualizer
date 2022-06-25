#include "interface.h"

Interface::Interface() {
  
}

Interface::~Interface() {
  
}

void Interface::draw() {
  
}

void Interface::check_for_input() {
  switch (control.get_input())
  {
  case ADD_PILLAR_BTN:
    sorter.add_pillar();
    break;
  
  case REMOVE_PILLAR_BTN:
    sorter.remove_pillar();
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
