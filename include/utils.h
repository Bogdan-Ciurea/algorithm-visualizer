#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <raylib.h>
#include <vector>
#include <chrono>

#define MAX_PILLARS      100
#define MIN_PILLARS      20
#define STARTING_PILLARS 40
#define ANIMATION_FPS    30

#define MY_BACKGROUND_COLOR Color{241, 250, 238, 100} // The color of the background
#define TOPBAR_COLOR        Color{ 29,  53,  87, 100} // The background color of the topbar
#define TEXT_COLOR          Color{168, 218, 220, 100} // The color of the text
#define HOVER_TEXT_COLOR    Color{ 69, 123, 157, 100} // The color of the text when hovered over
#define NORMAL_COLOR        Color{152, 193, 217, 100} // The color of a pillar in the normal state
#define SELECTED_COLOR      Color{ 69, 123, 157, 100} // The color of a pillar in the selected state
#define MOVED_COLOR         Color{238, 108,  77, 100} // The color of a pillar in the moved state
#define BORDER_COLOR        Color{ 41,  50,  65, 100} // The color of the border of the pillars

enum color_state {BACKGROUND, NORMAL, SELECTED, MOVED};
enum input_options {NONE, ADD_PILLAR_BTN, REMOVE_PILLAR_BTN, RANDOMIZE_BTN, START_BTN, SELECT_ALGORITHM};
enum algorithm_options {INSERTION, HEAP, SELECTION, MERGE, QUICK, BUBBLE};

#endif