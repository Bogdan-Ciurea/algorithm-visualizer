#include "standalone-functions/graph-algorithms.hpp"

void add_node_to_queue(Node *node, std::vector<Node *> &queue) {
  // see if the node is already in the queue
  for (auto n : queue) {
    if (n == node) return;
  }

  queue.push_back(node);
}

std::vector<Graph *> dijkstra(Node *start, Node *end, Graph *graph) {
  std::vector<Graph *> animation = {graph->get_graph_copy()};

  std::vector<float> distances = std::vector<float>();
  std::vector<Node *> prev = std::vector<Node *>();
  std::vector<Node *> queue = std::vector<Node *>();

  for (auto node : graph->node_list) {
    distances.push_back(INFINITY);
    prev.push_back(nullptr);
    if (node == start) queue.push_back(node);

    // animation.push_back(animation[animation.size() - 1]->get_graph_copy());
    // animation[animation.size() - 1]->get_node(node->id)->set_state(SELECTED);
  }

  animation.push_back(animation[0]->get_graph_copy());
  distances[graph->get_node_index(start)] = .0f;

  while (!queue.empty()) {               // while Q is not empty:
    Node *current_node = queue.front();  // u ← vertex in Q with min dist[u]
    queue.erase(queue.begin());

    animation.push_back(animation[animation.size() - 1]->get_graph_copy());
    animation[animation.size() - 1]
        ->get_node(current_node->id)
        ->set_state(SELECTED);
    // Also colour the edge that led to this node
    if (prev[graph->get_node_index(current_node)] != nullptr) {
      animation[animation.size() - 1]
          ->get_edge(
              animation[animation.size() - 1]->get_node(
                  prev[graph->get_node_index(current_node)]->id),
              animation[animation.size() - 1]->get_node(current_node->id))
          ->set_state(SELECTED);
    }

    for (Node *neighbour : graph->get_neighbours(current_node)) {
      float alt = distances[graph->get_node_index(current_node)] +
                  graph->get_edge(current_node, neighbour)->weight;

      // Animate the path to the neighbour
      animation.push_back(animation[animation.size() - 1]->get_graph_copy());

      if (alt < distances[graph->get_node_index(neighbour)]) {
        distances[graph->get_node_index(neighbour)] = alt;
        prev[graph->get_node_index(neighbour)] = current_node;

        add_node_to_queue(neighbour, queue);

        // Animate the changed node
        animation.push_back(animation[animation.size() - 1]->get_graph_copy());
        animation[animation.size() - 1]
            ->get_node(neighbour->id)
            ->set_state(SEARCHING);
        animation[animation.size() - 1]
            ->get_edge(
                animation[animation.size() - 1]->get_node(current_node->id),
                animation[animation.size() - 1]->get_node(neighbour->id))
            ->set_state(SEARCHING);
        animation.push_back(animation[animation.size() - 2]->get_graph_copy());
      }
    }
  }

  std::vector<Graph *> path_animation =
      std::vector<Graph *>();  // This path is the animation
  path_animation.push_back(graph->get_graph_copy());

  // Backtrack
  Node *current_node = end;
  std::vector<Node *> path = std::vector<Node *>();
  while (current_node != nullptr) {
    path.push_back(current_node);
    current_node = prev[graph->get_node_index(current_node)];
  }

  path_animation.push_back(
      path_animation[path_animation.size() - 1]->get_graph_copy());
  path_animation[path_animation.size() - 1]->get_node(start->id)->set_state(
      MOVED);

  // Create the path animation
  for (int i = path.size() - 1; i > 0; i--) {
    path_animation.push_back(path_animation[path_animation.size() - 1]
                                 ->get_graph_copy());  // Copy the last frame
    path_animation[path_animation.size() - 1]
        ->get_node(path[i]->id)
        ->set_state(MOVED);
    path_animation[path_animation.size() - 1]
        ->get_node(path[i - 1]->id)
        ->set_state(MOVED);
    path_animation[path_animation.size() - 1]
        ->get_edge(
            path_animation[path_animation.size() - 1]->get_node(path[i]->id),
            path_animation[path_animation.size() - 1]->get_node(
                path[i - 1]->id))
        ->set_state(MOVED);
  }

  // Append the path to the animation 3 times
  // for (int i = 0; i < 3; i++) {
  //   for (int j = 0; j < path_animation.size(); j++) {
  //     animation.push_back(path_animation[j]->get_graph_copy());
  //   }
  // }
  for (int j = 0; j < path_animation.size(); j++) {
    animation.push_back(path_animation[j]->get_graph_copy());
  }

  animation.push_back(animation[animation.size() - 1]->get_graph_copy());
  animation.push_back(graph->get_graph_copy());
  animation.push_back(animation[animation.size() - 2]->get_graph_copy());
  animation.push_back(graph->get_graph_copy());
  animation.push_back(animation[animation.size() - 2]->get_graph_copy());
  animation.push_back(graph->get_graph_copy());

  // Leave the last frame for 2 more frames
  animation.push_back(animation[animation.size() - 2]->get_graph_copy());
  animation.push_back(animation[animation.size() - 1]->get_graph_copy());

  return animation;
}