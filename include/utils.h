#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <chrono>

#include "raylib.h"
#include "raygui.h"


// Global values
// --------------------------

#define ANIMATION_FPS    30

#define MY_BACKGROUND_COLOR Color{241, 250, 238, 100} // The color of the background
#define TOPBAR_COLOR        Color{ 29,  53,  87, 100} // The background color of the topbar
#define TEXT_COLOR          Color{168, 218, 220, 100} // The color of the text
#define HOVER_TEXT_COLOR    Color{ 69, 123, 157, 100} // The color of the text when hovered over

// Element color related
#define NORMAL_COLOR        Color{152, 193, 217, 100} // The color of an element in the normal state
#define SELECTED_COLOR      Color{ 69, 123, 157, 100} // The color of an element in the selected state
#define MOVED_COLOR         Color{238, 108,  77, 100} // The color of an element in the moved state
#define BORDER_COLOR        Color{ 41,  50,  65, 100} // The color of an element's border

// In order to animate everything we will need to have more states
enum color_state {NORMAL, SELECTED, MOVED};
enum current_interface {MAIN_MENU, GRAPH, TREES, SORTER, SEARCH};

// Graph and Trees Related
// --------------------------
enum graph_tree_input_options {ADD_NODE = 4, REMOVE, ADD_EDGE, SELECT_NODE, CLEAR_BTN};
enum graph_algorithm_option {DIJKSTRA, FLOYD_WARSHALL, BFS, DFS, AS, PRIMS, KRISKAL, TOPOLOGICAL};
enum trees_type_option {BINARY_TREE, RED_BLACK_TREE};


// Sorter and Searcher Related
// --------------------------
#define MAX_PILLARS      100
#define MIN_PILLARS      20
#define STARTING_PILLARS 40

enum sort_search_input_options {NONE = 0, BACK_BTN, START_BTN, SELECT_ALGORITHM, ADD_PILLAR_BTN, REMOVE_PILLAR_BTN, RANDOMIZE_BTN, SORT_BTN};
enum sort_algorithm_options {INSERTION, HEAP, SELECTION, MERGE, QUICK, BUBBLE};
enum search_algorithm_options {LINEAR, BINARY, JUMP, INTERPOLATION, EXPONENTIAL};

#endif