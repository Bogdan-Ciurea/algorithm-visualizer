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
  this->color = NORMAL_COLOR;
}

Node::Node(Vector2 coord, int id) {
  this->coord = coord;
  this->id = id;
  this->radius = 20;
  this->state = NORMAL;
  this->color = NORMAL_COLOR;
}

void Node::draw(float r) {
  DrawCircleV(coord, r, color);
  DrawText(std::to_string(id).c_str(), coord.x - 5, coord.y - 5, 10, BLACK);
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
      this->color = NORMAL_COLOR;
      break;
    case SELECTED:
      this->color = SELECTED_COLOR;
      break;
    case MOVED:
      this->color = MOVED_COLOR;
      break;
    default:
      break;
  }
}

void Node::set_id(int new_id) { this->id = new_id; }

Edge::Edge(int weight, Node *n1, Node *n2, bool directed) {
  this->weight = weight;
  this->node1 = n1;
  this->node2 = n2;
  this->directed = directed;
  this->state = NORMAL;
  this->color = NORMAL_COLOR;
}

void Edge::draw(float thickness) {
  if (!directed)
    DrawLineEx(node1->coord, node2->coord, thickness, color);
  else {
    // Draw the line
    DrawLineEx(node1->coord, node2->coord, thickness, color);
    // Draw the arrow. It had just two lines with an angle of 20 degrees
    // between them. The arrow is 50 pixels long.
    Vector2 x3 = {
        node2->coord.x +
            0.1f * ((node1->coord.x - node2->coord.x) * cos(20 * DEG2RAD) -
                    (node1->coord.y - node2->coord.y) * sin(20 * DEG2RAD)),
        node2->coord.y +
            0.1f * ((node1->coord.x - node2->coord.x) * sin(20 * DEG2RAD) +
                    (node1->coord.y - node2->coord.y) * cos(20 * DEG2RAD))};
    Vector2 x4 = {
        node2->coord.x +
            0.1f * ((node1->coord.x - node2->coord.x) * cos(-20 * DEG2RAD) -
                    (node1->coord.y - node2->coord.y) * sin(-20 * DEG2RAD)),
        node2->coord.y +
            0.1f * ((node1->coord.x - node2->coord.x) * sin(-20 * DEG2RAD) +
                    (node1->coord.y - node2->coord.y) * cos(-20 * DEG2RAD))};
    DrawLineEx(node2->coord, x3, thickness, color);
    DrawLineEx(node2->coord, x4, thickness, color);
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
      this->color = NORMAL_COLOR;
      break;
    case SELECTED:
      this->color = SELECTED_COLOR;
      break;
    case MOVED:
      this->color = MOVED_COLOR;
      break;
    default:
      break;
  }
}

void Edge::set_weight(int new_weight) { this->weight = new_weight; }

void Edge::set_directed(bool new_directed) { this->directed = new_directed; }
