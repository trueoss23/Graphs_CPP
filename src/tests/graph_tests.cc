#include <gtest/gtest.h>

#include "../lib/s21_graph.h"

TEST(OpenFile, Exception) {
  Graph graph;
  EXPECT_THROW(graph.LoadGraphFromFile("./FAKE.txt"), std::logic_error);
  EXPECT_THROW(
      graph.LoadGraphFromFile("./resources/incorrect_graphs/size_float.txt"),
      std::logic_error);
  EXPECT_THROW(
      graph.LoadGraphFromFile("./resources/incorrect_graphs/size_negative.txt"),
      std::logic_error);
  EXPECT_THROW(
      graph.LoadGraphFromFile("./resources/incorrect_graphs/size_nondigit.txt"),
      std::logic_error);
  EXPECT_THROW(
      graph.LoadGraphFromFile("./resources/incorrect_graphs/value_float.txt"),
      std::logic_error);
  EXPECT_THROW(graph.LoadGraphFromFile(
                   "./resources/incorrect_graphs/value_negative.txt"),
               std::logic_error);
  EXPECT_THROW(graph.LoadGraphFromFile(
                   "./resources/incorrect_graphs/value_nondigit.txt"),
               std::logic_error);
  EXPECT_THROW(graph.LoadGraphFromFile(
                   "./resources/incorrect_graphs/values_count_greater.txt"),
               std::logic_error);
  EXPECT_THROW(graph.LoadGraphFromFile(
                   "./resources/incorrect_graphs/values_count_less.txt"),
               std::logic_error);
  graph.LoadGraphFromFile("./resources/correct_graphs/graph_directed.txt");
  EXPECT_THROW(graph.GetWeight(-1, 150), std::out_of_range);
}

TEST(OpenFile, CorrectFile1) {
  Graph graph;
  graph.LoadGraphFromFile("./resources/correct_graphs/graph_directed.txt");
  int v[4][4] = {{0, 1, 0, 0}, {0, 0, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}};

  for (auto i = 0; i < 4; ++i)
    for (auto j = 0; j < 4; ++j) EXPECT_EQ(v[i][j], graph.GetGraph()[i][j]);
}

TEST(OpenFile, CorrectFile2) {
  Graph graph;
  graph.LoadGraphFromFile("./resources/correct_graphs/graph_undirected.txt");
  int v[11][11] = {{0, 29, 20, 21, 16, 31, 100, 12, 4, 31, 18},
                   {29, 0, 15, 29, 28, 40, 72, 21, 29, 41, 12},
                   {20, 15, 0, 15, 14, 25, 81, 9, 23, 27, 13},
                   {21, 29, 15, 0, 4, 12, 92, 12, 25, 13, 25},
                   {16, 28, 14, 4, 0, 16, 94, 9, 20, 16, 22},
                   {31, 40, 25, 12, 16, 0, 95, 24, 36, 3, 37},
                   {100, 72, 81, 92, 94, 95, 0, 90, 101, 99, 84},
                   {12, 21, 9, 12, 9, 24, 90, 0, 15, 25, 13},
                   {4, 29, 23, 25, 20, 36, 101, 15, 0, 35, 18},
                   {31, 41, 27, 13, 16, 3, 99, 25, 35, 0, 38},
                   {18, 12, 13, 25, 22, 37, 84, 13, 18, 38, 0}};

  for (auto i = 0; i < 11; ++i)
    for (auto j = 0; j < 11; ++j) EXPECT_EQ(v[i][j], graph.GetGraph()[i][j]);
}

TEST(ExportFile, NoException1) {
  Graph graph;
  EXPECT_NO_THROW(
      graph.LoadGraphFromFile("./resources/correct_graphs/graph_directed.txt"));
  EXPECT_NO_THROW(
      graph.ExportGraphToDot("./resources/correct_graphs/graph_directed.dot"));
}

TEST(ExportFile, NoException2) {
  Graph graph;
  EXPECT_NO_THROW(graph.LoadGraphFromFile(
      "./resources/correct_graphs/graph_directed2.txt"));
  EXPECT_NO_THROW(
      graph.ExportGraphToDot("./resources/correct_graphs/graph_directed2.dot"));
}

TEST(ExportFile, NoException3) {
  Graph graph;
  EXPECT_NO_THROW(graph.LoadGraphFromFile(
      "./resources/correct_graphs/graph_undirected.txt"));
  EXPECT_NO_THROW(graph.ExportGraphToDot(
      "./resources/correct_graphs/graph_undirected.dot"));
}
