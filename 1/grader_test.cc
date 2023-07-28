#include <iostream>
#include <limits>
#include <string>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "q.h"

using ::testing::ElementsAre;

/**
 * This function is used by Google Test. Don't touch!
 */
template <class T>
void PrintCollection(std::string_view name, T input, bool add_new_line = true) {
  if (!name.empty()) {
    std::cout << name << ": ";
  }
  std::cout << "{ ";
  unsigned int count = 0;
  for (auto n : input) {
    count++;
    std::cout << n;
    if (count < input.size()) std::cout << ", ";
  }
  std::cout << " }";
  if (add_new_line) {
    std::cout << std::endl;
  }
}

std::ostream& operator<<(std::ostream& os, const std::pair<int, int>& p) {
  os << "(" << p.first << ", " << p.second << ")";
  return os;
}

template <class T, class K>
void PrintPair(std::pair<T, K> input) {
  std::cout << "(" << input.first << " , " << input.second << ")" << std::endl;
}

template <class T>
void PrintCollectionOfPairs(std::string_view name, T input,
                            bool add_new_line = true) {
  if (!name.empty()) {
    std::cout << name << ": ";
  }
  std::cout << "{ ";
  unsigned int count = 0;
  for (auto n : input) {
    count++;
    PrintPair(n);
    if (count < input.size()) std::cout << ", ";
  }
  std::cout << " }";
  if (add_new_line) {
    std::cout << std::endl;
  }
}

//-----------------------------------------------------------------------------
// Write some test cases for each function.
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
TEST(BFS, SimpleGraph) {
  Graph graph({0, 1, 2, 3}, {{0, 1}, {1, 2}, {2, 3}, {0, 3}});
  PrintCollection("nodes", graph.nodes_);
  PrintCollectionOfPairs("edges", graph.edges_);

  std::vector<int> distances(4, INT_MAX);
  graph.BFS(0, distances);
  EXPECT_EQ(distances[1], 1);
  EXPECT_EQ(distances[2], 2);
  EXPECT_EQ(distances[3], 1);
}
//-----------------------------------------------------------------------------
TEST(Dijkstra, SimpleGraph) {
  Graph graph({0, 1, 2}, {{0, 1}, {1, 2}}, {{{0, 1}, 10}, {{1, 2}, 1}});
  PrintCollection("nodes", graph.nodes_);
  PrintCollectionOfPairs("edges", graph.edges_);
  PrintCollectionOfPairs("weights", graph.weights_);

  std::vector<int> distances(3, INT_MAX);
  graph.Dijkstra(0, distances);
  EXPECT_EQ(distances[1], 10);
  EXPECT_EQ(distances[2], 11);
}
//-----------------------------------------------------------------------------
TEST(BellmanFord, SimpleGraph) {
  Graph graph({0, 1, 2}, {{0, 1}, {1, 2}}, {{{0, 1}, 10}, {{1, 2}, 1}});
  PrintCollection("nodes", graph.nodes_);
  PrintCollectionOfPairs("edges", graph.edges_);
  PrintCollectionOfPairs("weights", graph.weights_);

  std::vector<int> distances(3, INT_MAX);
  auto foundNegativeCycle = graph.BellmanFord(0, distances);
  EXPECT_EQ(distances[1], 10);
  EXPECT_EQ(distances[2], 11);
  EXPECT_FALSE(foundNegativeCycle);
}

TEST(BellmanFord, SimpleGraphNegativeEdge) {
  Graph graph({0, 1, 2}, {{0, 1}, {1, 2}}, {{{0, 1}, -1}, {{1, 2}, 1}});
  PrintCollection("nodes", graph.nodes_);
  PrintCollectionOfPairs("edges", graph.edges_);
  PrintCollectionOfPairs("weights", graph.weights_);

  std::vector<int> distances(3, INT_MAX);
  auto foundNegativeCycle = graph.BellmanFord(0, distances);
  EXPECT_EQ(distances[1], -1);
  EXPECT_EQ(distances[2], 0);
  EXPECT_FALSE(foundNegativeCycle);
}

TEST(BellmanFord, SimpleGraphNegativeCycle) {
  Graph graph({0, 1, 2}, {{0, 1}, {1, 2}, {1, 0}},
              {{{0, 1}, 1}, {{1, 2}, 1}, {{1, 0}, -5}});
  PrintCollection("nodes", graph.nodes_);
  PrintCollectionOfPairs("edges", graph.edges_);
  PrintCollectionOfPairs("weights", graph.weights_);

  std::vector<int> distances(3, INT_MAX);
  auto foundNegativeCycle = graph.BellmanFord(0, distances);

  EXPECT_TRUE(foundNegativeCycle);
}
TEST(BellmanFord, NegativeCycleGraph) {
  Graph graph({0, 1, 2}, {{0, 1}, {1, 2}, {2, 0}},
              {{{0, 1}, 1}, {{1, 2}, 1}, {{2, 0}, -3}});
  PrintCollection("nodes", graph.nodes_);
  PrintCollectionOfPairs("edges", graph.edges_);
  PrintCollectionOfPairs("weights", graph.weights_);

  std::vector<int> distances(3, INT_MAX);
  auto foundNegativeCycle = graph.BellmanFord(0, distances);
  EXPECT_TRUE(foundNegativeCycle);
}

TEST(BellmanFord, DisconnectedGraph) {
  Graph graph({0, 1, 2, 3, 4}, {{0, 1}, {1, 2}, {3, 4}},
              {{{0, 1}, 1}, {{1, 2}, 1}, {{3, 4}, -2}});
  PrintCollection("nodes", graph.nodes_);
  PrintCollectionOfPairs("edges", graph.edges_);
  PrintCollectionOfPairs("weights", graph.weights_);

  std::vector<int> distances(5, INT_MAX);

  // Run BellmanFord for each connected component (source nodes).
  auto foundNegativeCycle1 = graph.BellmanFord(0, distances);
  EXPECT_THAT(distances, ElementsAre(0, 1, 2, INT_MAX, INT_MAX));

  auto foundNegativeCycle2 = graph.BellmanFord(3, distances);
  EXPECT_THAT(distances, ElementsAre(INT_MAX, INT_MAX, INT_MAX, 0, -2));

  EXPECT_FALSE(foundNegativeCycle1);
  EXPECT_FALSE(foundNegativeCycle2);
}

TEST(BellmanFord, SingleNegativeCycle) {
  Graph graph({0, 1, 2, 3}, {{0, 1}, {1, 2}, {2, 3}, {3, 1}},
              {{{0, 1}, 1}, {{1, 2}, 1}, {{2, 3}, -4}, {{3, 1}, -1}});
  PrintCollection("nodes", graph.nodes_);
  PrintCollectionOfPairs("edges", graph.edges_);
  PrintCollectionOfPairs("weights", graph.weights_);

  std::vector<int> distances(4, INT_MAX);
  auto foundNegativeCycle = graph.BellmanFord(0, distances);
  EXPECT_TRUE(foundNegativeCycle);
}

TEST(BellmanFord, NoNegativeEdges) {
  Graph graph({0, 1, 2, 3}, {{0, 1}, {1, 2}, {2, 3}},
              {{{0, 1}, 1}, {{1, 2}, 2}, {{2, 3}, 3}});
  PrintCollection("nodes", graph.nodes_);
  PrintCollectionOfPairs("edges", graph.edges_);
  PrintCollectionOfPairs("weights", graph.weights_);

  std::vector<int> distances(4, INT_MAX);
  auto foundNegativeCycle = graph.BellmanFord(0, distances);
  EXPECT_EQ(distances[1], 1);
  EXPECT_EQ(distances[2], 3);
  EXPECT_EQ(distances[3], 6);
  EXPECT_FALSE(foundNegativeCycle);
}

//-----------------------------------------------------------------------------
TEST(FindShortestDistance, SimpleGraph) {
  Graph graph({0, 1, 2}, {{0, 1}, {1, 2}}, {});
  PrintCollection("nodes", graph.nodes_);
  PrintCollectionOfPairs("edges", graph.edges_);
  PrintCollectionOfPairs("weights", graph.weights_);

  std::vector<int> distances(3, INT_MAX);
  auto foundNegativeCycle = graph.FindShortestDistance(0, distances);
  EXPECT_EQ(distances[1], 1);
  EXPECT_EQ(distances[2], 2);
  EXPECT_FALSE(foundNegativeCycle);
}

TEST(FindShortestDistance, SimpleGraphNegativeEdge) {
  Graph graph({0, 1, 2}, {{0, 1}, {1, 2}}, {{{0, 1}, -1}, {{1, 2}, 1}});
  PrintCollection("nodes", graph.nodes_);
  PrintCollectionOfPairs("edges", graph.edges_);
  PrintCollectionOfPairs("weights", graph.weights_);

  std::vector<int> distances(3, INT_MAX);
  auto foundNegativeCycle = graph.FindShortestDistance(0, distances);
  EXPECT_EQ(distances[1], -1);
  EXPECT_EQ(distances[2], 0);
  EXPECT_FALSE(foundNegativeCycle);
}

TEST(FindShortestDistance, SimpleGraphNegativeCycle) {
  Graph graph({0, 1, 2}, {{0, 1}, {1, 2}, {1, 0}},
              {{{0, 1}, 1}, {{1, 2}, 1}, {{1, 0}, -5}});
  PrintCollection("nodes", graph.nodes_);
  PrintCollectionOfPairs("edges", graph.edges_);
  PrintCollectionOfPairs("weights", graph.weights_);

  std::vector<int> distances(3, INT_MAX);
  auto foundNegativeCycle = graph.FindShortestDistance(0, distances);

  EXPECT_TRUE(foundNegativeCycle);
}
