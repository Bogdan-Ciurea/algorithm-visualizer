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
      this->color = RED;
      break;
    case MOVED:
      this->color = GREEN;
      break;
    default:
      break;
  }
}

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
