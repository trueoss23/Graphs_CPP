#include <gtest/gtest.h>

#include "../lib/s21_graph_algorithms.h"

TEST(AntAlgorithm, CorrectFile) {
  Graph graph;
  graph.LoadGraphFromFile("./resources/correct_graphs/graph_undirected2.txt");
  TsmResult result = GraphAlgorithms::SolveTravelingSalesmanProblem(graph);
  TsmResult solution = {{1, 3, 4, 2, 1}, 120};
  EXPECT_EQ(result.vertices.size(), solution.vertices.size());
  EXPECT_EQ(result.distance, solution.distance);
}

TEST(AntAlgorithm, Exception) {
  Graph graph;
  graph.LoadGraphFromFile("./resources/correct_graphs/graph_directed2.txt");
  EXPECT_THROW(GraphAlgorithms::SolveTravelingSalesmanProblem(graph),
               std::logic_error);
}

TEST(AnnealingAlgorithm, CorrectFile) {
  Graph graph;
  graph.LoadGraphFromFile("./resources/correct_graphs/graph_undirected2.txt");
  TsmResult result = GraphAlgorithms::SolveTsmSimulatedAnnealing(graph);
  TsmResult solution = {{1, 3, 4, 2}, 120};
  EXPECT_EQ(result.vertices.size(), solution.vertices.size());
  EXPECT_EQ(result.distance, solution.distance);
}

TEST(GeneticAlgorithm, CorrectFile1) {
  Graph graph;
  graph.LoadGraphFromFile("./resources/correct_graphs/graph_undirected2.txt");
  TsmResult result = GraphAlgorithms::SolveTsmGenetic(graph);
  TsmResult solution = {{1, 3, 4, 2}, 120};
  EXPECT_EQ(result.vertices.size(), solution.vertices.size());
  EXPECT_EQ(result.distance, solution.distance);
}

TEST(GeneticAlgorithm, CorrectFile2) {
  Graph graph;
  graph.LoadGraphFromFile("./resources/correct_graphs/graph_directed2.txt");
  TsmResult result = GraphAlgorithms::SolveTsmGenetic(graph);
  TsmResult solution = {{1, 3, 4, 2}, 5};
  EXPECT_EQ(result.vertices.size(), solution.vertices.size());
  EXPECT_EQ(result.distance, solution.distance);
}

TEST(MST, file_4_dots) {
  Graph graph;
  graph.LoadGraphFromFile(
      "./resources/correct_graphs/graph_undirected_test1.txt");
  GraphAlgorithms::Matrix result = GraphAlgorithms::GetLeastSpanningTree(graph);
  int weigth_MST = 0;
  for (size_t i = 0; i < result.size(); i++) {
    for (size_t j = 0; j < i; j++) {
      weigth_MST += result[i][j];
    }
  }
  EXPECT_TRUE(weigth_MST == 6);
}

TEST(MST, file_5_dots) {
  Graph graph;
  graph.LoadGraphFromFile(
      "./resources/correct_graphs/graph_undirected_test2.txt");
  GraphAlgorithms::Matrix result = GraphAlgorithms::GetLeastSpanningTree(graph);
  int weigth_MST = 0;
  for (size_t i = 0; i < result.size(); i++) {
    for (size_t j = 0; j < i; j++) {
      weigth_MST += result[i][j];
    }
  }
  EXPECT_TRUE(weigth_MST == 49);
}

TEST(MST, Exception1) {
  Graph graph;
  graph.LoadGraphFromFile("./resources/correct_graphs/graph_directed.txt");
  EXPECT_THROW(GraphAlgorithms::GetLeastSpanningTree(graph), std::logic_error);
}

TEST(MST, Exception2) {
  Graph graph;
  graph.LoadGraphFromFile("./resources/correct_graphs/graph_one_dot.txt");
  EXPECT_THROW(GraphAlgorithms::GetLeastSpanningTree(graph), std::logic_error);
}

TEST(FYAlgorithm, file_with_zero_dots) {
  Graph graph;
  graph.LoadGraphFromFile(
      "./resources/correct_graphs/graph_undirected_test1.txt");
  GraphAlgorithms::Matrix current_res =
      GraphAlgorithms::GetShortestPathsBetweenAllVertices(graph);
  GraphAlgorithms::Matrix res = {
      {0, 3, 4, 2}, {3, 0, 1, 5}, {4, 1, 0, 4}, {2, 5, 4, 0}};
  EXPECT_TRUE(res == current_res);
}

TEST(FYAlgorithm, file_without_zero_dots) {
  Graph graph;
  graph.LoadGraphFromFile(
      "./resources/correct_graphs/graph_undirected_test2.txt");
  GraphAlgorithms::Matrix current_res =
      GraphAlgorithms::GetShortestPathsBetweenAllVertices(graph);
  GraphAlgorithms::Matrix res = {{0, 29, 20, 20, 16},
                                 {29, 0, 15, 29, 28},
                                 {20, 15, 0, 15, 14},
                                 {20, 29, 15, 0, 4},
                                 {16, 28, 14, 4, 0}};
  EXPECT_TRUE(res == current_res);
}

TEST(FYAlgorithm, Exception) {
  Graph graph;
  graph.LoadGraphFromFile(
      "./resources/correct_graphs/graph_undirected_two_dots.txt");
  EXPECT_THROW(GraphAlgorithms::GetShortestPathsBetweenAllVertices(graph),
               std::logic_error);
}

TEST(FYAlgorithm, directed_graph) {
  Graph graph;
  graph.LoadGraphFromFile("./resources/correct_graphs/graph_directed.txt");
  GraphAlgorithms::Matrix current_res =
      GraphAlgorithms::GetShortestPathsBetweenAllVertices(graph);
  GraphAlgorithms::Matrix res = {
      {0, 1, 2, 2}, {0, 0, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}};
  EXPECT_TRUE(res == current_res);
}

void compare_result(const std::vector<int>& my_result,
                    const std::vector<int>& correct_result) {
  for (std::size_t i = 0; i < my_result.size(); ++i) {
    EXPECT_EQ(my_result[i], correct_result[i]);
  }
}

TEST(DFS, directed_graph1) {
  Graph graph;
  int start_vertex = 1;
  graph.LoadGraphFromFile("./resources/correct_graphs/graph_directed3.txt");
  std::vector my_algo_result =
      GraphAlgorithms::DepthFirstSearch(graph, start_vertex);
  std::vector correct_result{1, 2, 6, 5, 4, 3, 11, 9, 10, 8, 14, 15, 13, 12, 7};
  compare_result(my_algo_result, correct_result);
}

TEST(DFS, directed_graph2) {
  Graph graph;
  int start_vertex = 18;
  graph.LoadGraphFromFile("./resources/correct_graphs/graph_directed3.txt");
  std::vector my_algo_result =
      GraphAlgorithms::DepthFirstSearch(graph, start_vertex);
  std::vector correct_result{18, 17, 16, 2,  1,  5, 4,  3,  11,
                             9,  10, 8,  14, 15, 6, 13, 12, 7};
  compare_result(my_algo_result, correct_result);
}

TEST(DFS, undirected_graph1) {
  Graph graph;
  int start_vertex = 10;
  graph.LoadGraphFromFile("./resources/correct_graphs/graph_undirected3.txt");
  std::vector my_algo_result =
      GraphAlgorithms::DepthFirstSearch(graph, start_vertex);
  std::vector correct_result{10, 8, 1, 2, 6, 5, 4, 3, 11, 9, 14, 15, 13, 12, 7};
  compare_result(my_algo_result, correct_result);
}

TEST(DFS, undirected_graph2) {
  Graph graph;
  int start_vertex = 4;
  graph.LoadGraphFromFile("./resources/correct_graphs/graph_undirected3.txt");
  std::vector my_algo_result =
      GraphAlgorithms::DepthFirstSearch(graph, start_vertex);
  std::vector correct_result{4, 3, 11, 9, 10, 8, 1, 2, 6, 5, 14, 15, 7, 12, 13};
  compare_result(my_algo_result, correct_result);
}

TEST(DFS, Exception) {
  Graph graph;
  graph.LoadGraphFromFile("./resources/correct_graphs/graph_directed3.txt");
  try {
    int start_vertex = 20;
    GraphAlgorithms::DepthFirstSearch(graph, start_vertex);
  } catch (const std::exception& e) {
    SUCCEED();
  }
}

TEST(BFS, directed_graph1) {
  Graph graph;
  int start_vertex = 17;
  graph.LoadGraphFromFile("./resources/correct_graphs/graph_directed3.txt");
  std::vector my_algo_result =
      GraphAlgorithms::BreadthFirstSearch(graph, start_vertex);
  std::vector correct_result{17, 16, 2,  6,  1,  7, 13, 5, 15,
                             8,  4,  12, 11, 14, 9, 10, 3};
  compare_result(my_algo_result, correct_result);
}

TEST(BFS, directed_graph2) {
  Graph graph;
  int start_vertex = 1;
  graph.LoadGraphFromFile("./resources/correct_graphs/graph_directed3.txt");
  std::vector my_algo_result =
      GraphAlgorithms::BreadthFirstSearch(graph, start_vertex);
  std::vector correct_result{1, 2, 5, 7, 8, 6, 13, 4, 14, 12, 10, 15, 11, 3, 9};
  compare_result(my_algo_result, correct_result);
}

TEST(BFS, undirected_graph1) {
  Graph graph;
  int start_vertex = 7;
  graph.LoadGraphFromFile("./resources/correct_graphs/graph_undirected3.txt");
  std::vector my_algo_result =
      GraphAlgorithms::BreadthFirstSearch(graph, start_vertex);
  std::vector correct_result{7, 1, 2, 4, 12, 5, 8, 6, 13, 3, 9, 14, 10, 15, 11};
  compare_result(my_algo_result, correct_result);
}

TEST(BFS, undirected_graph2) {
  Graph graph;
  int start_vertex = 1;
  graph.LoadGraphFromFile("./resources/correct_graphs/graph_undirected3.txt");
  std::vector my_algo_result =
      GraphAlgorithms::BreadthFirstSearch(graph, start_vertex);
  std::vector correct_result{1, 2, 5, 7, 8, 6, 13, 4, 14, 12, 10, 15, 11, 3, 9};
  compare_result(my_algo_result, correct_result);
}

TEST(BFS, Exception) {
  Graph graph;
  graph.LoadGraphFromFile("./resources/correct_graphs/graph_directed3.txt");
  try {
    int start_vertex = 0;
    GraphAlgorithms::BreadthFirstSearch(graph, start_vertex);
  } catch (const std::exception& e) {
    SUCCEED();
  }
}

TEST(Dijkstra, directed_graph1) {
  Graph graph;
  graph.LoadGraphFromFile("./resources/correct_graphs/graph_directed3.txt");
  int start_vertex = 18;
  int finish_vertex = 14;
  int my_result_way = GraphAlgorithms::GetShortestPathBetweenVertices(
      graph, start_vertex, finish_vertex);
  int correct_result = 11;
  EXPECT_EQ(my_result_way, correct_result);
}

TEST(Dijkstra, directed_graph2) {
  Graph graph;
  graph.LoadGraphFromFile("./resources/correct_graphs/graph_directed3.txt");
  int start_vertex = 3;
  int finish_vertex = 10;
  int my_result_way = GraphAlgorithms::GetShortestPathBetweenVertices(
      graph, start_vertex, finish_vertex);
  int correct_result = 7;
  EXPECT_EQ(my_result_way, correct_result);
}

TEST(Dijkstra, undirected_graph1) {
  Graph graph;
  graph.LoadGraphFromFile("./resources/correct_graphs/graph_undirected3.txt");
  int start_vertex = 12;
  int finish_vertex = 15;
  int my_result_way = GraphAlgorithms::GetShortestPathBetweenVertices(
      graph, start_vertex, finish_vertex);
  int correct_result = 4;
  EXPECT_EQ(my_result_way, correct_result);
}

TEST(Dijkstra, undirected_graph2) {
  Graph graph;
  graph.LoadGraphFromFile("./resources/correct_graphs/graph_undirected3.txt");
  int start_vertex = 15;
  int finish_vertex = 13;
  int my_result_way = GraphAlgorithms::GetShortestPathBetweenVertices(
      graph, start_vertex, finish_vertex);
  int correct_result = 3;
  EXPECT_EQ(my_result_way, correct_result);
}

TEST(Dijkstra, way_not_found) {
  Graph graph;
  graph.LoadGraphFromFile("./resources/correct_graphs/graph_directed3.txt");
  int start_vertex = 2;
  int finish_vertex = 18;
  int my_result_way = GraphAlgorithms::GetShortestPathBetweenVertices(
      graph, start_vertex, finish_vertex);
  int correct_result = -1;
  EXPECT_EQ(my_result_way, correct_result);
}

TEST(Dijkstra, Exception) {
  Graph graph;
  graph.LoadGraphFromFile("./resources/correct_graphs/graph_undirected3.txt");
  try {
    int start_vertex = 1;
    int finish_vertex = 20;
    GraphAlgorithms::GetShortestPathBetweenVertices(graph, start_vertex,
                                                    finish_vertex);
  } catch (const std::exception& e) {
    SUCCEED();
  }
}