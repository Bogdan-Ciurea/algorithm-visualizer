#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <chrono>
#include <iostream>
#include <vector>

#include "raygui.h"
#include "raylib.h"

// Global values
// --------------------------

#define ANIMATION_FPS 30

// For more colors go to
// https://coolors.co/palette/f94144-f3722c-f8961e-f9c74f-90be6d-43aa8b-577590

#define TOPBAR_COLOR \
  Color { 29, 53, 87, 100 }  // The background color of the top bar
#define TEXT_COLOR \
  Color { 168, 218, 220, 100 }  // The color of the text
#define HOVER_TEXT_COLOR \
  Color { 69, 123, 157, 100 }  // The color of the text when hovered over

// Fonts
// Font inter_regular, inter_light;

// Main menu colors

#define SORTER_BACKGROUND_COLOR \
  Color { 25, 130, 196, 255 }
#define SEARCHER_BACKGROUND_COLOR \
  Color { 243, 114, 44, 255 }
#define GRAPH_BACKGROUND_COLOR \
  Color { 144, 190, 109, 255 }
#define TREES_BACKGROUND_COLOR \
  Color { 67, 170, 139, 255 }
#define MY_BACKGROUND_COLOR \
  Color { 237, 242, 244, 255 }  // The color of the background

// Element color related
#define NORMAL_COLOR \
  Color { 152, 193, 217, 100 }  // The color of an element in the normal state
#define SELECTED_COLOR \
  Color { 69, 123, 157, 100 }  // The color of an element in the selected state
#define MOVED_COLOR \
  Color { 238, 108, 77, 100 }  // The color of an element in the moved state
#define BORDER_COLOR \
  Color { 41, 50, 65, 100 }  // The color of an element's border

// In order to animate everything we will need to have more states
enum color_state { NORMAL, SELECTED, MOVED };

// Used to represent the flow of the program


// Graph and Trees Related
// --------------------------
enum graph_tree_input_options {
  ADD_NODE = 4,
  REMOVE,
  ADD_EDGE,
  SELECT_NODE,
  CLEAR_BTN
};
enum graph_algorithm_option {
  DIJKSTRA,
  FLOYD_WARSHALL,
  BFS,
  DFS,
  AS,
  PRIMS,
  KRISKAL,
  TOPOLOGICAL
};
enum trees_type_option { BINARY_TREE, RED_BLACK_TREE };

// Sorter and Searcher Related
// --------------------------
#define MAX_PILLARS 100
#define MIN_PILLARS 20
#define STARTING_PILLARS 40

enum sort_search_input_options {
  NONE = 0,
  BACK_BTN,
  START_BTN,
  SELECT_ALGORITHM,
  ADD_PILLAR_BTN,
  REMOVE_PILLAR_BTN,
  RANDOMIZE_BTN,
  SORT_BTN
};
enum sort_algorithm_options {
  INSERTION,
  HEAP,
  SELECTION,
  MERGE,
  QUICK,
  BUBBLE
};
enum search_algorithm_options {
  LINEAR,
  BINARY,
  JUMP,
  INTERPOLATION,
  EXPONENTIAL
};

#endif