/**
 * @file node-objects.cpp
 * @author Bogdan Ciurea
 * @brief This file is responsible for defining the classes and their methods
 * @version 0.1
 * @date 2023-06-18
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "node-objects.hpp"

Node::Node(float x, float y, int id) {
  this->coord = {x, y};
  this->id = id;
  this->radius = 20;
  this->state = NORMAL;
  this->color = BLACK;
}

Node::Node(Vector2 coord, int id) {
  this->coord = coord;
  this->id = id;
  this->radius = 20;
  this->state = NORMAL;
  this->color = BLACK;
}

Node *Node::get_node_copy() {
  Node *new_node = new Node(this->coord, this->id);
  new_node->set_state(this->state);
  return new_node;
}

void Node::draw(float r) {
  DrawCircleV(coord, r, color);
  DrawText(std::to_string(id).c_str(), coord.x - 5, coord.y - 5, 10, WHITE);
}

bool Node::point_in_node(Vector2 *point) {
  // Calculate the distance between the point and the center of the node
  float distance =
      sqrt(pow(coord.x - point->x, 2) + pow(coord.y - point->y, 2));

  // If the distance is less than the radius of the node then the point is
  // inside the node
  if (distance <= NODE_RADIUS) {
    return true;
  }

  return false;
}

void Node::set_state(color_state new_state) {
  this->state = new_state;

  switch (new_state) {
    case NORMAL:
      this->color = BLACK;
      break;
    case SELECTED:
      this->color = GREEN;
      break;
    case MOVED:
      this->color = RED;
      break;
    case SEARCHING:
      this->color = BLUE;
      break;
    default:
      break;
  }
}

void Node::set_id(int new_id) { this->id = new_id; }

Edge::Edge(float weight, Node *n1, Node *n2, bool directed) {
  this->weight = weight;
  this->node1 = n1;
  this->node2 = n2;
  this->directed = directed;
  this->state = NORMAL;
  this->color = BLACK;

  this->calculate_start_end_points();
}

Edge *Edge::get_edge_copy() {
  Edge *new_edge =
      new Edge(this->weight, this->node1, this->node2, this->directed);
  new_edge->set_state(this->state);

  return new_edge;
}

void Edge::draw(float thickness) {
  // We want to recalculate the start and end points of the line so that it
  // doesn't intersect with the nodes

  // Draw the line
  DrawLineEx(start_point, end_point, thickness, color);
  // Draw the weight of the edge
  // DrawText(std::to_string((int)weight).c_str(),
  //          (start_point.x + end_point.x) / 2,
  //          (start_point.y + end_point.y) / 2, 10, RED);
  if (directed) {
    // Draw the arrow. It had just two lines with an angle of 20 degrees
    // between them. The arrow is 50 pixels long.
    // Read https://math.stackexchange.com/questions/1314006/drawing-an-arrow
    Vector2 x3 = {
        end_point.x +
            ARROW_PERCENTAGE *
                ((start_point.x - end_point.x) * cos(ARROW_ANGLE * DEG2RAD) -
                 (start_point.y - end_point.y) * sin(ARROW_ANGLE * DEG2RAD)),
        end_point.y +
            ARROW_PERCENTAGE *
                ((start_point.x - end_point.x) * sin(ARROW_ANGLE * DEG2RAD) +
                 (start_point.y - end_point.y) * cos(ARROW_ANGLE * DEG2RAD))};
    Vector2 x4 = {
        end_point.x +
            ARROW_PERCENTAGE *
                ((start_point.x - end_point.x) * cos(-ARROW_ANGLE * DEG2RAD) -
                 (start_point.y - end_point.y) * sin(-ARROW_ANGLE * DEG2RAD)),
        end_point.y +
            ARROW_PERCENTAGE *
                ((start_point.x - end_point.x) * sin(-ARROW_ANGLE * DEG2RAD) +
                 (start_point.y - end_point.y) * cos(-ARROW_ANGLE * DEG2RAD))};
    DrawLineEx(end_point, x3, thickness, color);
    DrawLineEx(end_point, x4, thickness, color);
  }
}

bool Edge::point_on_edge(Vector2 *point) {
  // Calculate the distance between the point and the line
  float distance =
      abs((node2->coord.y - node1->coord.y) * point->x -
          (node2->coord.x - node1->coord.x) * point->y +
          node2->coord.x * node1->coord.y - node2->coord.y * node1->coord.x) /
      sqrt(pow(node2->coord.y - node1->coord.y, 2) +
           pow(node2->coord.x - node1->coord.x, 2));

  // If the distance is less than the thickness of the line then the point is
  // on the line
  if (distance <= EDGE_THICKNESS) {
    // Check if the point is between the two nodes
    if (node1->coord.x <= point->x && point->x <= node2->coord.x) {
      return true;
    } else if (node2->coord.x <= point->x && point->x <= node1->coord.x) {
      return true;
    }
  }

  return false;
}

void Edge::set_state(color_state new_state) {
  this->state = new_state;

  switch (new_state) {
    case NORMAL:
      this->color = BLACK;
      break;
    case SELECTED:
      this->color = GREEN;
      break;
    case MOVED:
      this->color = RED;
      break;
    case SEARCHING:
      this->color = BLUE;
      break;
    default:
      break;
  }
}

color_state Edge::get_state() { return this->state; }

void Edge::set_weight(int new_weight) { this->weight = new_weight; }

void Edge::set_directed(bool new_directed) { this->directed = new_directed; }

void Edge::calculate_start_end_points() {
  // Calculate the distance between the two nodes
  float distance = sqrt(pow(node1->coord.x - node2->coord.x, 2) +
                        pow(node1->coord.y - node2->coord.y, 2));

  // Calculate the start and end points of the line
  this->start_point = {node1->coord.x + (NODE_RADIUS / distance) *
                                            (node2->coord.x - node1->coord.x),
                       node1->coord.y + (NODE_RADIUS / distance) *
                                            (node2->coord.y - node1->coord.y)};
  this->end_point = {node2->coord.x - (NODE_RADIUS / distance) *
                                          (node2->coord.x - node1->coord.x),
                     node2->coord.y - (NODE_RADIUS / distance) *
                                          (node2->coord.y - node1->coord.y)};
}

void Graph::add_node(Vector2 *point) {
  // Check that we have a valid point
  if (point == nullptr) {
    return;
  }

  // Check if the node is not on top of another node
  for (auto node : node_list) {
    // Calculate the distance between the two nodes
    float distance = sqrt(pow(node->coord.x - point->x, 2) +
                          pow(node->coord.y - point->y, 2));

    if (NODE_RADIUS * 2.5f > distance) {
      return;
    }
  }

  // Add the node to the list
  node_list.push_back(new Node(point->x, point->y, this->generate_id()));
}

Node *Graph::get_node(int id) {
  for (auto node : node_list) {
    if (node->id == id) {
      return node;
    }
  }

  return nullptr;
}

int Graph::get_node_index(int id) {
  for (int i = 0; i < node_list.size(); i++) {
    if (node_list[i]->id == id) {
      return i;
    }
  }

  return -1;
}

int Graph::get_node_index(Node *node) {
  for (int i = 0; i < node_list.size(); i++) {
    if (node_list[i] == node) {
      return i;
    }
  }

  return -1;
}

int Graph::generate_id() {
  int id = 0;

  // Keep generating ids until we find one that is not used
  while (true) {
    bool found = false;
    for (auto node : node_list) {
      if (node->id == id) {
        found = true;
        break;
      }
    }

    if (!found) {
      break;
    }

    id++;
  }

  return id;
}

std::vector<Edge *> Graph::get_edges_from_node(Node *node) {
  std::vector<Edge *> edges;

  for (auto edge : edge_list) {
    if (!directed) {
      if (edge->node1 == node || edge->node2 == node) {
        edges.push_back(edge);
      }
    } else {
      if (edge->node1 == node) {
        edges.push_back(edge);
      }
    }
  }

  return edges;
}

void Graph::add_edge(Node *n1, Node *n2, float weight, color_state state) {
  // Check if the nodes are not the same
  if (n1 == n2) {
    return;
  }

  // Check if the nodes exist
  bool n1_exists = false;
  bool n2_exists = false;

  for (auto node : node_list) {
    if (node == n1) {
      n1_exists = true;
    }
    if (node == n2) {
      n2_exists = true;
    }
  }

  if (!n1_exists || !n2_exists) {
    return;
  }

  // Check if the edge already exists
  for (auto edge : edge_list) {
    if (edge->node1 == n1 && edge->node2 == n2) {
      return;
    }
  }

  // Add the edge to the list
  Edge *new_edge = new Edge(weight, n1, n2, directed);
  new_edge->set_state(state);
  edge_list.push_back(new_edge);
}

Edge *Graph::get_edge(Node *n1, Node *n2) {
  if (n1 == n2) {
    return nullptr;
  }

  if (n1 == nullptr || n2 == nullptr) {
    return nullptr;
  }

  for (auto edge : edge_list) {
    if (edge->node1 == n1 && edge->node2 == n2) {
      return edge;
    }
  }

  return nullptr;
}

void Graph::draw(float node_radius, float edge_thickness) {
  // Draw the edges
  for (auto edge : edge_list) {
    edge->draw(edge_thickness);
  }

  // Draw the nodes
  for (auto node : node_list) {
    node->draw(node_radius);
  }
}

void Graph::remove_element(Vector2 *point) {
  for (int i = 0; i < node_list.size(); i++) {
    if (node_list[i]->point_in_node(point)) {
      this->remove_node(node_list[i]);
      return;
    }
  }

  for (int i = 0; i < edge_list.size(); i++) {
    if (edge_list[i]->point_on_edge(point)) {
      this->remove_edge(edge_list[i]);
      return;
    }
  }
}

void Graph::remove_node(Node *node) {
  for (int i = 0; i < edge_list.size(); i++) {
    if (edge_list[i]->node1 == node || edge_list[i]->node2 == node) {
      remove_edge(edge_list[i]);
      i--;
    }
  }

  for (int i = 0; i < node_list.size(); i++) {
    if (node_list[i] == node) {
      node_list.erase(node_list.begin() + i);
      break;
    }
  }

  delete node;
}

void Graph::remove_edge(Edge *edge) {
  for (int i = 0; i < edge_list.size(); i++) {
    if (edge_list[i] == edge) {
      edge_list.erase(edge_list.begin() + i);
      break;
    }
  }

  delete edge;
}

void Graph::set_directed(bool new_directed) {
  this->directed = new_directed;

  for (auto edge : edge_list) {
    edge->set_directed(new_directed);
  }
}

Node *Graph::get_node_in_proximity(Vector2 *point, float radius) {
  for (auto node : node_list) {
    if (node->point_in_node(point)) {
      return node;
    }

    // Check if the point is in the proximity of the node
    float distance = sqrt(pow(node->coord.x - point->x, 2) +
                          pow(node->coord.y - point->y, 2));

    if (distance <= radius) {
      return node;
    }
  }

  return nullptr;
}

Graph *Graph::get_graph_copy() {
  Graph *new_graph = new Graph();
  new_graph->set_directed(this->directed);

  // Copy the nodes
  for (auto node : node_list) {
    new_graph->node_list.push_back(node->get_node_copy());
  }

  // Copy the edges
  for (auto edge : edge_list) {
    new_graph->add_edge(new_graph->get_node(edge->node1->id),
                        new_graph->get_node(edge->node2->id), edge->weight,
                        edge->get_state());
  }

  return new_graph;
}