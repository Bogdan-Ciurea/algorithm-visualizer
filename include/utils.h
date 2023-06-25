#ifndef UTILS_HPP
#define UTILS_HPP

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <algorithm>
#include <chrono>
#include <iostream>
#include <queue>
#include <random>
#include <vector>

#include "raygui.h"
#include "raylib.h"

// Helper functions
// --------------------------

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define VECTOR_ADD(v1, v2) \
  Vector2 { v1.x + v2.x, v1.y + v2.y }

// Macro for vector subtraction
#define VECTOR_SUBTRACT(v1, v2) \
  Vector2 { v1.x - v2.x, v1.y - v2.y }

// Macro for vector multiplication
#define VECTOR_MULT(v1, scalar) \
  Vector2 { v1.x *scalar, v1.y *scalar }

#define VECTOR_DISTANCE(v1, v2) sqrt(pow(v1.x - v2.x, 2) + pow(v1.y - v2.y, 2))

// Global values
// --------------------------

#define SEARCH_ANIMATION_FPS 5
#define SORT_ANIMATION_FPS 30
#define GRAPH_ANIMATION_FPS 3
#define TREES_ANIMATION_FPS 30

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
enum color_state { NORMAL, SELECTED, MOVED, SEARCHING };

// Used to represent the flow of the program

// GraphInterface and TreesInterface Related
// --------------------------
enum graph_algorithm_option {
  DIJKSTRA,
  BFS,
  DFS,
  AS,
  PRIMS,
  KRISKAL,
  TOPOLOGICAL
};
enum trees_type_option { BINARY_TREE, RED_BLACK_TREE };

#define NODE_RADIUS 20
#define EDGE_THICKNESS 3
#define ARROW_PERCENTAGE 0.1f
#define ARROW_ANGLE 20

// SortInterface and SearchInterface Related
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

#endif  // UTILS_HPP