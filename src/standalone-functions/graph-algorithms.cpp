#include "standalone-functions/graph-algorithms.hpp"

std::vector<Graph *> dijkstra(Node *start, Node *end, Graph *graph) {
  std::vector<Graph *> animation = {graph->get_graph_copy()};

  std::vector<float> distances = std::vector<float>();
  std::vector<Node *> prev = std::vector<Node *>();
  std::queue<Node *> queue = std::queue<Node *>();

  for (auto node : graph->node_list) {
    distances.push_back(INFINITY);
    prev.push_back(nullptr);
    queue.push(node);

    // animation.push_back(animation[animation.size() - 1]->get_graph_copy());
    // animation[animation.size() - 1]->get_node(node->id)->set_state(SELECTED);
  }

  animation.push_back(animation[0]->get_graph_copy());
  distances[graph->get_node_index(start)] = .0f;

  int current_animation_index;

  while (!queue.empty()) {
    Node *current_node = queue.front();
    queue.pop();

    current_animation_index = animation.size() - 1;

    animation.push_back(animation[animation.size() - 1]->get_graph_copy());
    animation[animation.size() - 1]
        ->get_node(current_node->id)
        ->set_state(SELECTED);

    for (auto edge : graph->get_edges_from_node(current_node)) {
      int index = graph->get_node_index(edge->node2);

      if (distances[index] >
          distances[graph->get_node_index(current_node)] + edge->weight) {
        distances[index] =
            distances[graph->get_node_index(current_node)] + edge->weight;
        prev[index] = current_node;

        animation.push_back(
            animation[current_animation_index]->get_graph_copy());
        animation[animation.size() - 1]
            ->get_node(edge->node2->id)
            ->set_state(SEARCHING);

        animation[animation.size() - 1]
            ->get_edge(
                animation[animation.size() - 1]->get_node(edge->node1->id),
                animation[animation.size() - 1]->get_node(edge->node2->id))
            ->set_state(SEARCHING);
      }
    }
  }

  std::vector<Node *> path = std::vector<Node *>();
  Node *current_node = end;

  while (current_node != nullptr) {
    path.push_back(current_node);
    current_node = prev[graph->get_node_index(current_node)];
  }

  std::reverse(path.begin(), path.end());

  // Clear the animation

  animation.push_back(graph->get_graph_copy());
  // Color the first node in the path
  animation[animation.size() - 1]->get_node(start->id)->set_state(MOVED);

  // for (auto node : path) {
  //   animation.push_back(animation[animation.size() - 1]->get_graph_copy());
  //   animation[animation.size() - 1]->get_node(node->id)->set_state(MOVED);
  // }

  // printf("Dijkstra: %d\n", animation.size());
  for (int i = 1; i < path.size(); i++) {
    animation.push_back(animation[animation.size() - 1]->get_graph_copy());
    animation[animation.size() - 1]->get_node(path[i]->id)->set_state(MOVED);

    animation[animation.size() - 1]
        ->get_edge(animation[animation.size() - 1]->get_node(path[i - 1]->id),
                   animation[animation.size() - 1]->get_node(path[i]->id))
        ->set_state(MOVED);
  }

  // Leave the last frame for 2 more frames
  animation.push_back(animation[animation.size() - 1]->get_graph_copy());
  animation.push_back(animation[animation.size() - 1]->get_graph_copy());

  return animation;
}