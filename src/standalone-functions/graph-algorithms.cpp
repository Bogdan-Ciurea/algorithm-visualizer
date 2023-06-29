#include "standalone-functions/graph-algorithms.hpp"

/**
 * @brief This function adds a node to the queue.
 *
 * @param node  - The node to be added.
 * @param queue - The queue to be used.
 */
void add_node_to_queue(Node *node, std::vector<Node *> &queue) {
  // see if the node is already in the queue
  for (auto n : queue) {
    if (n == node) return;
  }

  queue.push_back(node);
}

/**
 * @brief This function adds a node to the priority queue.
 * The first element in the queue is the one with the lowest distance.
 *
 * @param node      - The node to be added.
 * @param queue     - The queue to be used.
 * @param distances - The distances vector.
 */
void add_node_to_priority_queue(Node *node, std::vector<Node *> &queue,
                                std::vector<float> &distances) {
  // see if the node is already in the queue
  for (auto n : queue) {
    if (n == node) return;
  }

  // find the position to insert the node
  int i = 0;
  for (; i < queue.size(); i++) {
    if (distances[queue[i]->id] > distances[node->id]) break;
  }

  queue.insert(queue.begin() + i, node);
}

/**
 * @brief This function adds a node to the stack.
 *
 * @param node  - The node to be added.
 * @param stack - The stack to be used.
 */
void add_node_to_stack(Node *node, std::vector<Node *> &stack) {
  // see if the node is already in the stack
  for (auto n : stack) {
    if (n == node) return;
  }

  stack.push_back(node);
}

/**
 * @brief This function checks if a mst graph has a cycle using the DFS
 * algorithm.
 *
 * @param mst_edges      - The edges of the mst.
 * @return true          - If the graph has a cycle.
 * @return false         - If the graph does NOT have a cycle.
 */
bool has_cycle(std::vector<Edge *> *mst_edges) {
  Graph *mst_graph = new Graph();

  for (auto edge : *mst_edges) {
    mst_graph->add_node(&edge->node1->coord, edge->node1->id);
    mst_graph->add_node(&edge->node2->coord, edge->node2->id);
    mst_graph->add_edge(mst_graph->get_node(edge->node1->id),
                        mst_graph->get_node(edge->node2->id), edge->weight);
  }

  bool has_cycle = mst_graph->has_cycle();
  delete mst_graph;
  return has_cycle;
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

std::vector<Graph *> bsf(Node *start, Node *end, Graph *graph) {
  std::vector<Graph *> animation = {graph->get_graph_copy()};

  std::vector<bool> visited = std::vector<bool>();
  std::vector<float> distances = std::vector<float>();
  std::vector<Node *> prev = std::vector<Node *>();
  std::vector<Node *> queue = std::vector<Node *>();
  bool can_exit_loop = false;

  for (auto node : graph->node_list) {
    visited.push_back(false);
    distances.push_back(INFINITY);
    prev.push_back(nullptr);
    if (node == start) queue.push_back(node);
  }

  animation.push_back(animation[0]->get_graph_copy());
  distances[graph->get_node_index(start)] = .0f;
  visited[graph->get_node_index(start)] = true;

  while (!queue.empty() && !can_exit_loop) {
    Node *current_node = queue.front();
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
      if (visited[graph->get_node_index(neighbour)]) continue;

      visited[graph->get_node_index(neighbour)] = true;

      float alt = distances[graph->get_node_index(current_node)] +
                  graph->get_edge(current_node, neighbour)->weight;

      // Animate the path to the neighbour
      animation.push_back(animation[animation.size() - 1]->get_graph_copy());

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

      // check if the neighbour is the end node
      if (neighbour == end) {
        can_exit_loop = true;
        break;
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

std::vector<Graph *> dfs(Node *start, Node *end, Graph *graph) {
  std::vector<Graph *> animation = {graph->get_graph_copy()};

  std::vector<bool> visited = std::vector<bool>();
  std::vector<float> distances = std::vector<float>();
  std::vector<Node *> prev = std::vector<Node *>();
  std::vector<Node *> stack = std::vector<Node *>();
  bool can_exit_loop = false;

  for (auto node : graph->node_list) {
    visited.push_back(false);
    distances.push_back(INFINITY);
    prev.push_back(nullptr);
    if (node == start) stack.push_back(node);
  }

  animation.push_back(animation[0]->get_graph_copy());
  distances[graph->get_node_index(start)] = .0f;
  visited[graph->get_node_index(start)] = true;

  while (!stack.empty() && !can_exit_loop) {
    Node *current_node = stack.back();
    stack.pop_back();

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
      if (visited[graph->get_node_index(neighbour)]) continue;

      visited[graph->get_node_index(neighbour)] = true;

      float alt = distances[graph->get_node_index(current_node)] +
                  graph->get_edge(current_node, neighbour)->weight;

      // Animate the path to the neighbour
      animation.push_back(animation[animation.size() - 1]->get_graph_copy());

      distances[graph->get_node_index(neighbour)] = alt;
      prev[graph->get_node_index(neighbour)] = current_node;

      add_node_to_stack(neighbour, stack);

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

      // check if the neighbour is the end node
      if (neighbour == end) {
        can_exit_loop = true;
        break;
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

std::vector<Graph *> as(Node *start, Node *end, Graph *graph) {
  std::vector<Graph *> animation = {graph->get_graph_copy()};

  std::vector<float> distances = std::vector<float>();
  std::vector<float> heuristic = std::vector<float>();
  std::vector<float> total = std::vector<float>();
  std::vector<Node *> prev = std::vector<Node *>();
  std::vector<Node *> queue = std::vector<Node *>();

  for (auto node : graph->node_list) {
    distances.push_back(INFINITY);
    total.push_back(INFINITY);
    prev.push_back(nullptr);
    heuristic.push_back(VECTOR_DISTANCE(node->coord, end->coord));
    if (node == start) queue.push_back(node);

    // animation.push_back(animation[animation.size() - 1]->get_graph_copy());
    // animation[animation.size() - 1]->get_node(node->id)->set_state(SELECTED);
  }

  const int start_index = graph->get_node_index(start);
  animation.push_back(animation[0]->get_graph_copy());
  distances[start_index] = .0f;
  total[start_index] = heuristic[start_index];

  while (!queue.empty()) {
    Node *current_node = queue.front();
    queue.erase(queue.begin());

    animation.push_back(animation[animation.size() - 1]->get_graph_copy());
    animation[animation.size() - 1]
        ->get_node(current_node->id)
        ->set_state(SELECTED);
    const int current_index = graph->get_node_index(current_node);
    // Also colour the edge that led to this node
    if (prev[current_index] != nullptr) {
      animation[animation.size() - 1]
          ->get_edge(
              animation[animation.size() - 1]->get_node(
                  prev[current_index]->id),
              animation[animation.size() - 1]->get_node(current_node->id))
          ->set_state(SELECTED);
    }

    for (Node *neighbour : graph->get_neighbours(current_node)) {
      float alt = distances[current_index] +
                  graph->get_edge(current_node, neighbour)->weight +
                  heuristic[graph->get_node_index(neighbour)];

      // Animate the path to the neighbour
      animation.push_back(animation[animation.size() - 1]->get_graph_copy());
      const int neighbour_index = graph->get_node_index(neighbour);
      if (alt < total[neighbour_index]) {
        distances[neighbour_index] = alt - heuristic[neighbour_index];
        prev[neighbour_index] = current_node;
        total[neighbour_index] = alt;

        add_node_to_priority_queue(neighbour, queue, total);

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

std::vector<Graph *> kruskal(Node *start, Node *end, Graph *graph) {
  std::vector<Graph *> animation = {graph->get_graph_copy()};

  auto temp_graph = graph->get_graph_copy();

  std::vector<Edge *> *edges = &temp_graph->edge_list;
  std::vector<Node *> *nodes = &temp_graph->node_list;
  std::vector<Edge *> mst = std::vector<Edge *>();

  // Sort the edges
  std::sort(edges->begin(), edges->end(),
            [](Edge *a, Edge *b) { return a->weight < b->weight; });

  int last_frame = animation.size() - 1;

  // Create the animation
  for (auto edge : *edges) {
    animation.push_back(animation[last_frame]->get_graph_copy());
    last_frame = animation.size() - 1;
    animation[last_frame]
        ->get_edge(animation[last_frame]->get_node(edge->node1->id),
                   animation[last_frame]->get_node(edge->node2->id))
        ->set_state(SEARCHING);

    mst.push_back(edge);

    // Check if the edge creates a cycle
    if (!has_cycle(&mst)) {
      animation.push_back(animation[last_frame]->get_graph_copy());
      animation[last_frame + 1]
          ->get_edge(animation[last_frame + 1]->get_node(edge->node1->id),
                     animation[last_frame + 1]->get_node(edge->node2->id))
          ->set_state(SELECTED);
      last_frame = animation.size() - 1;
    } else {
      // Remove the edge
      mst.pop_back();

      animation.push_back(animation[last_frame]->get_graph_copy());
      animation[last_frame + 1]
          ->get_edge(animation[last_frame + 1]->get_node(edge->node1->id),
                     animation[last_frame + 1]->get_node(edge->node2->id))
          ->set_state(MOVED);
      animation.push_back(animation[last_frame - 1]->get_graph_copy());
      last_frame = animation.size() - 1;
    }
  }

  // Create the mst graph
  Graph *mst_graph = new Graph();
  for (auto node : graph->node_list) {
    mst_graph->add_node(&node->coord);
    mst_graph->get_node(node->id)->set_state(MOVED);
  }
  for (auto edge : mst) {
    mst_graph->add_edge(mst_graph->get_node(edge->node1->id),
                        mst_graph->get_node(edge->node2->id), edge->weight);
    mst_graph
        ->get_edge(mst_graph->get_node(edge->node1->id),
                   mst_graph->get_node(edge->node2->id))
        ->set_state(MOVED);
  }

  animation.push_back(mst_graph);
  animation.push_back(animation[animation.size() - 1]->get_graph_copy());
  animation.push_back(animation[animation.size() - 1]->get_graph_copy());
  animation.push_back(animation[animation.size() - 1]->get_graph_copy());

  return animation;
}