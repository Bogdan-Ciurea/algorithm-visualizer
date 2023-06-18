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

  this->draw_main_header(button_height);
  this->draw_secondary_header(button_height);
  this->draw_elements();

  Vector2 *click_position = this->get_click_location(button_height + 10);

  if (click_position) switch (this->current_mode) {
      case ADD_NODE:
        add_node(click_position);
        break;

      case ADD_EDGE:
        if (temp_clicked_node == nullptr) {
          temp_clicked_node = get_node_by_position(click_position);
          if (temp_clicked_node != nullptr)
            temp_clicked_node->set_state(SELECTED);
        } else {
          Node *second_node = get_node_by_position(click_position);
          if (second_node != nullptr) {
            // We have both nodes
            // We can add the edge
            add_edge(temp_clicked_node, second_node);
          }
          temp_clicked_node->set_state(NORMAL);
          temp_clicked_node = nullptr;
        }

      default:
        break;
    }

  delete click_position;
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
                  GuiIconText(RAYGUI_ICON_PLAYER_PLAY, "Start")))
      running = true;
  } else {
    if (GuiButton(start_end_button_rect,
                  GuiIconText(RAYGUI_ICON_PLAYER_STOP, "Stop")))
      running = false;
  }

  // Draw the import button
  Rectangle import_rect = (Rectangle){(float)(GetScreenWidth() - 170),
                                      button_height / 2 - 20, 40, 40};
  if (GuiButton(import_rect, GuiIconText(RAYGUI_ICON_FILE_OPEN, ""))) {
    import_graph();
  }

  if (dropdown_option !=
      7) {  // We need two nodes only if we don't want the topological sorting
    // Draw the "from" input button
    Rectangle input_rect1 = (Rectangle){(float)(GetScreenWidth() - 285),
                                        button_height / 2 - 20, 100, 40};
    if (GuiTextBox(input_rect1, textBoxText1, 64, textBoxEditMode1))
      textBoxEditMode1 = !textBoxEditMode1;

    // Draw the "to" input button
    Rectangle input_rect2 = (Rectangle){(float)(GetScreenWidth() - 400),
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
  }

  // Draw the "Add edge" button
  Rectangle add_edge_rect = (Rectangle){120, button_height + 10, 100, 40};
  if (GuiButton(add_edge_rect, GuiIconText(RAYGUI_ICON_PLUS, "Add edge"))) {
    current_mode = ADD_EDGE;
  }

  // Draw the "Delete node/edge" button
  Rectangle delete_rect = (Rectangle){230, button_height + 10, 100, 40};
  if (GuiButton(delete_rect, GuiIconText(RAYGUI_ICON_BIN, "Delete"))) {
    current_mode = REMOVE;
  }

  // Draw the "Directed" button
  Rectangle directed_rect = (Rectangle){340, button_height + 10, 100, 40};
  if (GuiButton(directed_rect,
                GuiIconText(directed_edge ? RAYGUI_ICON_MUTATE_FILL
                                          : RAYGUI_ICON_CURSOR_SCALE_LEFT_FILL,
                            directed_edge ? "Directed" : "Undirected"))) {
    directed_edge = !directed_edge;
    change_edge_type();
  }
}

void GraphInterface::draw_elements() {
  // Draw all the nodes
  for (auto node : node_list) {
    node->draw(NODE_RADIUS);
  }

  // Draw all the edges
  for (auto edge : edge_list) {
    edge->draw(EDGE_THICKNESS);
  }
}

bool GraphInterface::import_graph() { return true; }

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

  // if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON && this->pressed == true)) {
  //   this->pressed = false;
  //   const Vector2 mouse_position = GetMousePosition();

  //   // Must be under the header
  //   if (mouse_position.y > ignore_height) {
  //     // Must check that the click is not in the secondary header
  //     if (mouse_position.x < 450) {
  //       if (mouse_position.y < ignore_height + 60) {
  //         return nullptr;
  //       } else {
  //         return new Vector2{mouse_position.x, mouse_position.y};
  //       }
  //     } else {
  //       return new Vector2{mouse_position.x, mouse_position.y};
  //     }
  //   }
  // }

  return nullptr;
}

void GraphInterface::add_node(Vector2 *location) {
  // Check if there is already a node in that location
  // or if the location is too close to another node

  // If there is no node in that location we can add it

  if (location == nullptr) return;

  for (auto node : node_list) {
    // Calculate the distance between the two nodes
    float distance = sqrt(pow(node->coord.x - location->x, 2) +
                          pow(node->coord.y - location->y, 2));

    if (NODE_RADIUS * 2.5 > distance) {
      return;
    }
  }
  node_list.push_back(
      new Node(location->x, location->y, this->generate_node_id()));
}

int GraphInterface::generate_node_id() {
  int id = 0;
  for (auto node : node_list) {
    if (node->id == id) {
      id++;
    } else {
      return id;
    }
  }
  return id;
}

Node *GraphInterface::get_node_by_position(Vector2 *location) {
  for (auto &node : node_list) {
    // Calculate the distance between the two nodes
    float distance = sqrt(pow(node->coord.x - location->x, 2) +
                          pow(node->coord.y - location->y, 2));

    if (NODE_RADIUS >= distance) {
      return node;
    }
  }

  return nullptr;
}

void GraphInterface::add_edge(Node *n1, Node *n2) {
  edge_list.push_back(new Edge(1, n1, n2, directed_edge));
}

void GraphInterface::change_edge_type() {
  for (auto edge : edge_list) {
    edge->set_directed(directed_edge);
  }
}
