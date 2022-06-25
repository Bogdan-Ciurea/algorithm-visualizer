#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <raylib.h>
#include <vector>

#define MAX_PILLARS 100
#define MIN_PILLARS 20
#define STARTING_PILLARS 40

#define BACKGROUND_COLOR Color{241, 250, 238, 100}
#define TOPBAR_COLOR     Color{ 29,  53,  87, 100}
#define TEXT_COLOR       Color{168, 218, 220, 100}
#define HOVER_TEXT_COLOR Color{ 69, 123, 157, 100}
#define NORMAL_COLOR     Color{152, 193, 217, 100}
#define SELECTED_COLOR   Color{ 69, 123, 157, 100}
#define MOVED_COLOR      Color{238, 108,  77, 100}
#define BORDER_COLOR     Color{ 41,  50,  65, 100}



typedef enum color_state {BACKGROUND, NORMAL, SELECTED, MOVED, BORDER};
typedef enum input_options {NONE, ADD_PILLAR_BTN, REMOVE_PILLAR_BTN, RANDOMIZE_BTN, START_BTN, SELECT_ALGORITHM};
typedef enum algorithm_options {INSERTION, HEAP, SELECTION, MERGE, QUICK, BUBBLE};

#endif