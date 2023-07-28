#include <iostream>
#include <limits>
#include <string>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "q.h"
using ::testing::UnorderedElementsAreArray;
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

template <class T>
void Print2dCollection(std::string_view name, T input) {
  std::cout << name << ": {" << std::endl;
  for (size_t i = 0; i < input.size(); i++) {
    std::cout << "  {";
    int j = 0;
    for (auto e : input[i]) {
      std::cout << e;
      if (j < input[0].size() - 1) {
        std::cout << ", ";
      }
      j++;
    }
    std::cout << "}" << std::endl;
  }
  std::cout << "}" << std::endl;
}
//-----------------------------------------------------------------------------
// Write some test cases for each function.
//-----------------------------------------------------------------------------
TEST(PutInLineTest, Empty) {
  std::vector<int> all_students;
  std::vector<std::set<int>> incompatible_students;
  PrintCollection("all_students", all_students);
  Print2dCollection("incompatible_students", incompatible_students);

  std::vector<std::vector<int>> expected;
  EXPECT_THAT(PutInLine(all_students, incompatible_students),
              UnorderedElementsAreArray(expected));
}

TEST(PutInLineTest, TwoCompatible) {
  std::vector<int> all_students = {0, 1};
  std::vector<std::set<int>> incompatible_students;
  PrintCollection("all_students", all_students);
  Print2dCollection("incompatible_students", incompatible_students);

  std::vector<std::vector<int>> expected{{0, 1}, {1, 0}};
  EXPECT_THAT(PutInLine(all_students, incompatible_students),
              UnorderedElementsAreArray(expected));
}

TEST(PutInLineTest, TwoIncompatible) {
  std::vector<int> all_students = {0, 1};
  std::vector<std::set<int>> incompatible_students{{0, 1}};
  PrintCollection("all_students", all_students);
  Print2dCollection("incompatible_students", incompatible_students);

  std::vector<std::vector<int>> expected;
  EXPECT_THAT(PutInLine(all_students, incompatible_students),
              UnorderedElementsAreArray(expected));
}

TEST(PutInLineTest, ThreeCompatible) {
  std::vector<int> all_students = {0, 1, 2};
  std::vector<std::set<int>> incompatible_students;
  PrintCollection("all_students", all_students);
  Print2dCollection("incompatible_students", incompatible_students);

  std::vector<std::vector<int>> expected{{0, 1, 2}, {0, 2, 1}, {1, 0, 2},
                                         {1, 2, 0}, {2, 0, 1}, {2, 1, 0}};
  EXPECT_THAT(PutInLine(all_students, incompatible_students),
              UnorderedElementsAreArray(expected));
}

TEST(PutInLineTest, ThreeIncompatible1) {
  std::vector<int> all_students = {0, 1, 2};
  std::vector<std::set<int>> incompatible_students{{0, 1}};
  PrintCollection("all_students", all_students);
  Print2dCollection("incompatible_students", incompatible_students);

  std::vector<std::vector<int>> expected{{0, 2, 1}, {1, 2, 0}};
  EXPECT_THAT(PutInLine(all_students, incompatible_students),
              UnorderedElementsAreArray(expected));
}

TEST(PutInLineTest, ThreeIncompatible2) {
  std::vector<int> all_students = {0, 1, 2};
  std::vector<std::set<int>> incompatible_students{{1, 2}};
  PrintCollection("all_students", all_students);
  Print2dCollection("incompatible_students", incompatible_students);

  std::vector<std::vector<int>> expected{{1, 0, 2}, {2, 0, 1}};
  EXPECT_THAT(PutInLine(all_students, incompatible_students),
              UnorderedElementsAreArray(expected));
}

TEST(PutInLineTest, FourCompatible) {
  std::vector<int> all_students = {0, 1, 2, 3};
  std::vector<std::set<int>> incompatible_students;
  PrintCollection("all_students", all_students);
  Print2dCollection("incompatible_students", incompatible_students);

  std::vector<std::vector<int>> expected{
      {0, 1, 2, 3}, {0, 1, 3, 2}, {0, 2, 1, 3}, {0, 2, 3, 1}, {0, 3, 1, 2},
      {0, 3, 2, 1}, {1, 0, 2, 3}, {1, 0, 3, 2}, {1, 2, 0, 3}, {1, 2, 3, 0},
      {1, 3, 0, 2}, {1, 3, 2, 0}, {2, 0, 1, 3}, {2, 0, 3, 1}, {2, 1, 0, 3},
      {2, 1, 3, 0}, {2, 3, 0, 1}, {2, 3, 1, 0}, {3, 0, 1, 2}, {3, 0, 2, 1},
      {3, 1, 0, 2}, {3, 1, 2, 0}, {3, 2, 0, 1}, {3, 2, 1, 0}};
  EXPECT_THAT(PutInLine(all_students, incompatible_students),
              UnorderedElementsAreArray(expected));
}

TEST(PutInLineTest, FourIncompatible) {
  std::vector<int> all_students = {0, 1, 2, 3};
  std::vector<std::set<int>> incompatible_students{{0, 3}};
  PrintCollection("all_students", all_students);
  Print2dCollection("incompatible_students", incompatible_students);

  std::vector<std::vector<int>> expected{
      {0, 1, 2, 3}, {0, 1, 3, 2}, {0, 2, 1, 3}, {0, 2, 3, 1},
      {1, 0, 2, 3}, {1, 3, 2, 0}, {2, 0, 1, 3}, {2, 3, 1, 0},
      {3, 1, 0, 2}, {3, 1, 2, 0}, {3, 2, 0, 1}, {3, 2, 1, 0}};

  EXPECT_THAT(PutInLine(all_students, incompatible_students),
              UnorderedElementsAreArray(expected));
}

TEST(PutInLineTest, FourTwoIncompatible) {
  std::vector<int> all_students = {0, 1, 2, 3};
  std::vector<std::set<int>> incompatible_students{{0, 1}, {0, 2}};
  PrintCollection("all_students", all_students);
  Print2dCollection("incompatible_students", incompatible_students);

  std::vector<std::vector<int>> expected{
      {0, 3, 1, 2}, {0, 3, 2, 1}, {1, 2, 3, 0}, {2, 1, 3, 0}};

  EXPECT_THAT(PutInLine(all_students, incompatible_students),
              UnorderedElementsAreArray(expected));
}

TEST(PutInLineTest, FourImpossible) {
  std::vector<int> all_students = {0, 1, 2, 3};
  // 0 is incompatible with everyone!
  std::vector<std::set<int>> incompatible_students{
      {0, 1}, {0, 2}, {0, 2}, {0, 3}};
  PrintCollection("all_students", all_students);
  Print2dCollection("incompatible_students", incompatible_students);

  std::vector<std::vector<int>> expected{};

  EXPECT_THAT(PutInLine(all_students, incompatible_students),
              UnorderedElementsAreArray(expected));
}

TEST(PutInLineTest, ThreeCompatibleRandomNumbers) {
  std::vector<int> all_students = {1, 7, 4};
  std::vector<std::set<int>> incompatible_students;
  PrintCollection("all_students", all_students);
  Print2dCollection("incompatible_students", incompatible_students);

  std::vector<std::vector<int>> expected{{1, 7, 4}, {1, 4, 7}, {7, 1, 4},
                                         {7, 4, 1}, {4, 1, 7}, {4, 7, 1}};
  EXPECT_THAT(PutInLine(all_students, incompatible_students),
              UnorderedElementsAreArray(expected));
}

TEST(PutInLineTest, ThreeInCompatibleRandomNumbers) {
  std::vector<int> all_students = {1, 7, 4};
  std::vector<std::set<int>> incompatible_students{{1, 7}};
  PrintCollection("all_students", all_students);
  Print2dCollection("incompatible_students", incompatible_students);

  std::vector<std::vector<int>> expected{{1, 4, 7}, {7, 4, 1}};
  EXPECT_THAT(PutInLine(all_students, incompatible_students),
              UnorderedElementsAreArray(expected));
}
