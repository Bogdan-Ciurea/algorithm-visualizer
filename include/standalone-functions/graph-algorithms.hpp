#ifndef GRAPH_ALGORITHMS_HPP
#define GRAPH_ALGORITHMS_HPP

#include "../node-objects.hpp"

/**
 * @brief This function implements the Dijkstra's algorithm.
 *
 * @param start - The starting node.
 * @param end   - The ending node.
 * @param graph - The graph to be used.
 * @return std::vector<Graph *> - The animation vector.
 */
std::vector<Graph *> dijkstra(Node *start, Node *end, Graph *graph);

/**
 * @brief This function implements the Breadth-First Search algorithm.
 *
 * @param start - The starting node.
 * @param end   - The ending node.
 * @param graph - The graph to be used.
 * @return std::vector<Graph *> - The animation vector.
 */
std::vector<Graph *> bsf(Node *start, Node *end, Graph *graph);

/**
 * @brief This function implements the Depth-First Search algorithm.
 *
 * @param start - The starting node.
 * @param end   - The ending node.
 * @param graph - The graph to be used.
 * @return std::vector<Graph *> - The animation vector.
 */
std::vector<Graph *> dfs(Node *start, Node *end, Graph *graph);

/**
 * @brief This function implements the A* algorithm.
 *
 * @param start - The starting node.
 * @param end   - The ending node.
 * @param graph - The graph to be used.
 * @return std::vector<Graph *> - The animation vector.
 */
std::vector<Graph *> as(Node *start, Node *end, Graph *graph);

/**
 * @brief This function implements the Kruskal's algorithm.
 *
 * @param start - The starting node.
 * @param end   - The ending node.
 * @param graph - The graph to be used.
 * @return std::vector<Graph *> - The animation vector.
 */
std::vector<Graph *> kruskal(Node *start, Node *end, Graph *graph);

/**
 * @brief This function implements the topological algorithm.
 *
 * @param start - The starting node.
 * @param end   - The ending node.
 * @param graph - The graph to be used.
 * @return std::vector<Graph *> - The animation vector.
 */
std::vector<Graph *> topological(Node *start, Node *end, Graph *graph);

#endif  // GRAPH_ALGORITHMS_HPP
