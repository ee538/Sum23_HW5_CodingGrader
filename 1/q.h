#ifndef FILES_2_Q
#define FILES_2_Q
#include <iostream>
#include <map>
#include <set>
#include <vector>
/**
 * This class represents a graph. Implement its member functions!
 *
 * The graph is represented as a set of nodes, a set of edges, and a map of
 * edges to weights.
 */
class Graph {
 public:
  /**
   * NOTE: THIS FUNCTION IS ALREADY IMPLEMENTED. NO NEED TO CHANGE
   * Constructs a new graph with the given nodes, edges, and weights.
   *
   * @param nodes The set of nodes in the graph.
   * @param edges The set of edges in the graph.
   * @param weights The map of edges to weights.
   */
  Graph(const std::set<int>& nodes, const std::set<std::pair<int, int>>& edges,
        const std::map<std::pair<int, int>, int>& weights)
      : nodes_(nodes), edges_(edges), weights_(weights) {
    PopulateSuccessorsAndPredecessors();
  }

  /**
   * This is a delegating constructor: it calls the previous constructor with an
   * empty vector for weights. No need to change this.
   *
   * Optional reading on this:
   * https://learn.microsoft.com/en-us/cpp/cpp/delegating-constructors?view=msvc-170
   */
  Graph(const std::set<int>& nodes, const std::set<std::pair<int, int>>& edges)
      : Graph(nodes, edges, /*weights*/ {}) {}
  //-----------------------------------------------------------------------------
  // TODO: Implement the following functions.
  //-----------------------------------------------------------------------------
  /**
   * Populates the successors_ and predecessors_ using edges_.
   * It is already called in the constructor.
   */
  void PopulateSuccessorsAndPredecessors();
  //-----------------------------------------------------------------------------
  /**
   * Finds the shortest paths from the given start node to all other nodes in
   * the graph.
   * It also checks for negative cycles.
   *
   * @param start The start node.
   * @param distances A vector to store the distances from the start node to all
   * other nodes.
   * @return true if there was a negative cycle and false otherwise.
   */
  bool FindShortestDistance(int start, std::vector<int>& distances);

  /**
   * Performs the BFS algorithm on the graph and stores the distances from the
   * start node to all other nodes in the `distances` vector.
   *
   * @param start The start node.
   * @param distances A vector to store the distances from the start node to all
   * other nodes.
   */
  void BFS(int start, std::vector<int>& distances);

  /**
   * Performs the Dijkstra algorithm on the graph and stores the distances from
   * the start node to all other nodes in the `distances` vector.
   *
   * @param start The start node.
   * @param distances A vector to store the distances from the start node to all
   * other nodes.
   */
  void Dijkstra(int start, std::vector<int>& distances);

  /**
   * Performs the Bellman-Ford algorithm on the graph and stores the distances
   * from the start node to all other nodes in the `distances` vector.
   * It also checks for negative cycles.
   *
   * @param start The start node.
   * @param distances A vector to store the distances from the start node to all
   * other nodes.
   * @return true if there was a negative cycle and false otherwise.
   */
  bool BellmanFord(int start, std::vector<int>& distances);

  //  private:
  /**
   * The set of nodes in the graph.
   */
  std::set<int> nodes_;

  /**
   * The set of edges in the graph.
   */
  std::set<std::pair<int, int>> edges_;

  /**
   * The map of edges to weights.
   */
  std::map<std::pair<int, int>, int> weights_;

  /**
   * Map of node to successors.
   */
  std::unordered_map<int, std::vector<int>> successors_;

  /**
   * Map of node to predecessors.
   */
  std::unordered_map<int, std::vector<int>> predecessors_;
};

#endif /* FILES_2_Q */
