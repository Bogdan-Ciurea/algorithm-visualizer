#include "interfaces/graph-interface.hpp"

bool GraphInterface::draw() {
  // Build the header
  float button_height = 100;
  if (GetScreenHeight() * 0.2 > 100) button_height = GetScreenHeight() * 0.2;
  if (button_height > 130) button_height = 130;

  // Draw the header background
  DrawRectangle(0, 0, GetScreenWidth(), button_height, GRAPH_BACKGROUND_COLOR);
  DrawRectangle(0, button_height, GetScreenWidth(), 3, DARKGRAY);

  // Draw the back button
  Rectangle back_button_rect = (Rectangle){10, button_height / 2 - 20, 40, 40};
  if (GuiButton(back_button_rect, GuiIconText(RAYGUI_ICON_ARROW_LEFT_FILL, "")))
    return true;

  this->draw_secondary_header(button_height);
  this->draw_main_header(button_height);

  if (this->running) {
    this->run_algorithm();
  } else {
    if (this->animation.size() > 0) {
      this->animation[0]->draw(NODE_RADIUS, EDGE_THICKNESS);
    } else {
      this->graph->draw(NODE_RADIUS, EDGE_THICKNESS);
      this->get_canvas_input();
    }
  }

  return false;
}

void GraphInterface::draw_main_header(float button_height) {
  // Draw the "GraphInterface Algorithms" text
  DrawTextEx(*inter_regular, "GraphInterface Algorithms",
             (Vector2){75, button_height / 2 - 10}, 20, 0, DARKGRAY);

  // Draw all the algorithm options
  if (GuiDropdownBox(
          (Rectangle){
              (float)(80 + MeasureText("GraphInterface Algorithms", 16)),
              button_height / 2 - 20, 170, 40},
          "DIJKSTRA;FLOYD WARSHALL;BSF;DFS;A*;PRIM'S;KRUSKAL'S;TOPOLOGICAL",
          &dropdown_option, dropdown_enabled && !running))
    dropdown_enabled = !dropdown_enabled;

  // Draw the start/end button
  Rectangle start_end_button_rect = (Rectangle){
      (float)(GetScreenWidth() - 115), button_height / 2 - 20, 100, 40};
  if (!running) {
    if (GuiButton(start_end_button_rect,
                  GuiIconText(RAYGUI_ICON_PLAYER_PLAY, "Start"))) {
      if (check_input()) running = true;
      // print_adj_matrix(generate_adj_matrix());
    }
  } else {
    if (GuiButton(start_end_button_rect,
                  GuiIconText(RAYGUI_ICON_PLAYER_PAUSE, "Pause")))
      running = false;
  }

  // Draw the import button
  // Rectangle import_rect = (Rectangle){(float)(GetScreenWidth() - 170),
  //                                     button_height / 2 - 20, 40, 40};
  // if (GuiButton(import_rect, GuiIconText(RAYGUI_ICON_FILE_OPEN, ""))) {
  //   import_graph();
  // }

  if (dropdown_option !=
      7) {  // We need two nodes only if we don't want the topological sorting
    // Draw the "from" input button
    Rectangle input_rect1 = (Rectangle){(float)(GetScreenWidth() - 400),
                                        button_height / 2 - 20, 100, 40};
    if (GuiTextBox(input_rect1, textBoxText1, 64, textBoxEditMode1))
      textBoxEditMode1 = !textBoxEditMode1;

    // Draw the "to" input button
    Rectangle input_rect2 = (Rectangle){(float)(GetScreenWidth() - 285),
                                        button_height / 2 - 20, 100, 40};
    if (GuiTextBox(input_rect2, textBoxText2, 64, textBoxEditMode2))
      textBoxEditMode2 = !textBoxEditMode2;
  }
}

void GraphInterface::draw_secondary_header(float button_height) {
  // We will have 3 buttons under the header that will be:
  // 1. Add node, 2. Add edge, 3. Delete node/edge 4. Directed/Undirected
  // If current_mode is 1 we will draw the "Add node" button in a different
  // color

  Rectangle add_node_rect = (Rectangle){10, button_height + 10, 100, 40};
  if (GuiButton(add_node_rect, GuiIconText(RAYGUI_ICON_PLUS, "Add node"))) {
    current_mode = ADD_NODE;
    if (temp_clicked_node != nullptr) {
      temp_clicked_node->set_state(NORMAL);
      temp_clicked_node = nullptr;
    }
  }

  // Draw the "Add edge" button
  Rectangle add_edge_rect = (Rectangle){120, button_height + 10, 100, 40};
  if (GuiButton(add_edge_rect, GuiIconText(RAYGUI_ICON_PLUS, "Add edge"))) {
    current_mode = ADD_EDGE;
    if (temp_clicked_node != nullptr) {
      temp_clicked_node->set_state(NORMAL);
      temp_clicked_node = nullptr;
    }
  }

  // Draw the "Delete node/edge" button
  Rectangle delete_rect = (Rectangle){230, button_height + 10, 100, 40};
  if (GuiButton(delete_rect, GuiIconText(RAYGUI_ICON_BIN, "Delete"))) {
    current_mode = REMOVE;
    if (temp_clicked_node != nullptr) {
      temp_clicked_node->set_state(NORMAL);
      temp_clicked_node = nullptr;
    }
  }

  // Draw the "Directed" button
  Rectangle directed_rect = (Rectangle){340, button_height + 10, 100, 40};
  if (GuiButton(directed_rect,
                GuiIconText(directed_graph ? RAYGUI_ICON_MUTATE_FILL
                                           : RAYGUI_ICON_CURSOR_SCALE_LEFT_FILL,
                            directed_graph ? "Directed" : "Undirected"))) {
    directed_graph = !directed_graph;
    graph->set_directed(directed_graph);
  }
}

bool GraphInterface::check_input() {
  if (dropdown_option == 7) return true;

  int from = atoi(textBoxText1);
  int to = atoi(textBoxText2);

  if (from < 0 || from >= graph->node_list.size() || to < 0 ||
      to >= graph->node_list.size()) {
    return false;
  }

  this->from_node = graph->get_node(from);
  this->to_node = graph->get_node(to);

  if (this->from_node == nullptr || this->to_node == nullptr) return false;

  return true;
}

void GraphInterface::get_canvas_input() {
  Vector2 *click_position = this->get_click_location(button_height + 10);

  if (click_position) switch (this->current_mode) {
      case ADD_NODE:
        this->graph->add_node(click_position);
        break;

      case ADD_EDGE: {
        if (temp_clicked_node == nullptr) {
          temp_clicked_node =
              this->graph->get_node_in_proximity(click_position, NODE_RADIUS);
          if (temp_clicked_node != nullptr)
            temp_clicked_node->set_state(SELECTED);
        } else {
          Node *second_node =
              this->graph->get_node_in_proximity(click_position, NODE_RADIUS);
          if (second_node != nullptr) {
            // We have both nodes
            // We can add the edge
            this->graph->add_edge(
                temp_clicked_node, second_node,
                VECTOR_DISTANCE(temp_clicked_node->coord, second_node->coord));
          }
          temp_clicked_node->set_state(NORMAL);
          temp_clicked_node = nullptr;
        }
        break;
      }

      case REMOVE: {
        this->graph->remove_element(click_position);
        break;
      }
      default:
        break;
    }

  if (click_position) delete click_position;
}

// bool GraphInterface::import_graph() { return true; }

Vector2 *GraphInterface::get_click_location(float ignore_height) {
  if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && !this->pressed) {
    this->pressed = true;
    const Vector2 mouse_position = GetMousePosition();

    // Must be under the header
    if (mouse_position.y > ignore_height) {
      // Must check that the click is not in the secondary header
      if (mouse_position.x < 450) {
        if (mouse_position.y < ignore_height + 60) {
          return nullptr;
        } else {
          return new Vector2{mouse_position.x, mouse_position.y};
        }
      } else {
        return new Vector2{mouse_position.x, mouse_position.y};
      }
    }
  }

  if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) this->pressed = false;

  return nullptr;
}

void GraphInterface::run_algorithm() {
  if (animation.size() == 0) {
    switch (dropdown_option) {
      case DIJKSTRA:
        animation = dijkstra(this->from_node, this->to_node, this->graph);
        break;

      case FLOYD_WARSHALL:
        /* code */
        break;

      case BFS:
        /* code */
        break;

      case DFS:
        /* code */
        break;

      case AS:
        /* code */
        break;

      case PRIMS:
        /* code */
        break;

      case KRISKAL:
        /* code */
        break;

      case TOPOLOGICAL:
        /* code */
        break;

      default:
        break;
    }  // Update the display time of the last frame
    last_draw_time = std::chrono::system_clock::now().time_since_epoch() /
                     std::chrono::milliseconds(1);
  } else {
    if (std::chrono::system_clock::now().time_since_epoch() /
                std::chrono::milliseconds(1) -
            last_draw_time >=
        1000 / GRAPH_ANIMATION_FPS) {
      animation[0]->draw(NODE_RADIUS, EDGE_THICKNESS);
      delete animation[0];
      animation.erase(animation.begin());
      if (animation.size() == 0) running = false;
      last_draw_time = std::chrono::system_clock::now().time_since_epoch() /
                       std::chrono::milliseconds(1);
    } else {
      animation[0]->draw(NODE_RADIUS, EDGE_THICKNESS);
    }
  }
}