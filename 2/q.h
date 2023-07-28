#ifndef FILES_2_Q
#define FILES_2_Q
#include <iostream>
#include <map>
#include <set>
#include <vector>

// Function: PutInLine
// Description: This function finds all possible ways to arrange a group of students in a line
//              such that no two incompatible students are next to each other.
// Parameters:
//   - all_students: A reference to a vector of integers representing all the students.
//   - incompatible_students: A reference to a vector of sets containing incompatible student pairs.
// Returns:
//   - std::vector<std::vector<int>>: A vector of vectors, each representing a valid arrangement of students.

// Example 1:
// all_students = {0, 1};
// incompatible_students = {};
// output = {{0, 1}, {1, 0}};

// Example 2:
// all_students = {0, 1, 2};
// incompatible_students = {};
// output = {{0, 1, 2}, {0, 2, 1}, {1, 0, 2},
//           {1, 2, 0}, {2, 0, 1}, {2, 1, 0}};

// Example 3:
// all_students = {0, 1, 2};
// incompatible_students = {{0, 1}};
// output = {{0, 2, 1}, {1, 2, 0}};

// Example 4:
// all_students = {1, 7, 4}
// incompatible_students = {}
// Expected output: There are six possible valid arrangements of the three students:
// - {1, 7, 4}, {1, 4, 7}, {7, 1, 4}, {7, 4, 1}, {4, 1, 7}, {4, 7, 1}.


// Note: The parameter `incompatible_students` is a vector of sets where each set contains
//       a pair of students who cannot be placed next to each other in the line. For example,
//       {{0, 1}} means that student 0 cannot be placed before or after student 1 in the line.


std::vector<std::vector<int>> PutInLine(
    std::vector<int> &all_students,
    std::vector<std::set<int>> &incompatible_students);

#endif