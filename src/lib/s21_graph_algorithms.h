#ifndef SRC_LIB_S21_GRAPH_ALGORITHMS_H
#define SRC_LIB_S21_GRAPH_ALGORITHMS_H

#include <limits>
#include <queue>
#include <unordered_set>
#include <vector>

#include "../misc/queue.h"
#include "../misc/stack.h"
#include "annealing_algorithm.h"
#include "ant_algorithm.h"
#include "genetic_algorithm.h"
#include "s21_graph.h"
#include "tsmresult.h"

class GraphAlgorithms {
 public:
  using Matrix = std::vector<std::vector<int> >;
  using Vector = std::vector<int>;

  static Vector DepthFirstSearch(const Graph& graph, int start_vertex);
  static Vector BreadthFirstSearch(const Graph& graph, int start_vertex);
  static int GetShortestPathBetweenVertices(const Graph& graph, int vertex1,
                                            int vertex2);
  static Matrix GetShortestPathsBetweenAllVertices(const Graph& graph);
  static Matrix GetLeastSpanningTree(const Graph& graph);
  static TsmResult SolveTravelingSalesmanProblem(const Graph& graph);
  static TsmResult SolveTsmSimulatedAnnealing(const Graph& graph);
  static TsmResult SolveTsmGenetic(const Graph& graph);

 private:
  static bool IsCorrectVertex(int vertex, const Graph&);
};

#endif  // SRC_LIB_S21_GRAPH_ALGORITHMS_H
