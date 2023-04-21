#include "s21_graph_algorithms.h"

/**
 * @brief DepthFirstSearch - one of the main graph traversal methods, frequent
 * detection for connectivity testing, searching for a cycle and part of a
 * connectivity sample, and for topological sorting.
 *
 * @param graph Adjacency matrix
 * @param start_vertex The starting vertex from which the traversal begins
 * @return std::vector<int> The order of the vertices
 */
std::vector<int> GraphAlgorithms::DepthFirstSearch(const Graph& graph,
                                                   int start_vertex) {
  if (!GraphAlgorithms::IsCorrectVertex(start_vertex, graph)) {
    throw std::logic_error("The index for vertex incorrect!");
  }
  std::unordered_set<int> visited_vertex;
  std::vector<int> traversal_order;

  Stack search_stack;
  search_stack.Push(start_vertex - 1);
  while (!search_stack.IsEmpty()) {
    int current_index = search_stack.Pop();
    if ((current_index == start_vertex - 1) ||
        visited_vertex.count(current_index) == 0) {
      visited_vertex.insert(current_index);
      traversal_order.push_back(current_index + 1);
      for (int i = graph.GetGraph().size() - 1; i >= 0; --i) {
        if (graph.GetGraph()[current_index][i] &&
            visited_vertex.count(i) == 0) {
          search_stack.Push(i);
        }
      }
    }
  }
  return traversal_order;
}

/**
 * @brief Breadth first search algorithm in an unweighted graph finds the
 * lengths of the shortest paths to all reachable vertices.
 *
 * @param graph Adjacency matrix
 * @param start_vertex The starting vertex from which the traversal begins
 * @return std::vector<int> The order of the vertices
 */
std::vector<int> GraphAlgorithms::BreadthFirstSearch(const Graph& graph,
                                                     int start_vertex) {
  if (!GraphAlgorithms::IsCorrectVertex(start_vertex, graph)) {
    throw std::logic_error("The index for vertex incorrect!");
  }
  std::unordered_set<int> visited_vertex;
  std::vector<int> traversal_order;

  Queue search_queue;
  search_queue.Push(start_vertex - 1);
  visited_vertex.insert(start_vertex - 1);

  while (!search_queue.IsEmpty()) {
    int current_vertex = search_queue.Pop();
    traversal_order.push_back(current_vertex + 1);

    for (std::size_t i = 0; i < graph.GetGraph().size(); ++i) {
      if (graph.GetGraph()[current_vertex][i] && visited_vertex.count(i) == 0) {
        search_queue.Push(i);
        visited_vertex.insert(i);
      }
    }
  }
  return traversal_order;
}

/**
 * @brief Dijksta's algorithm is a very elegant way to find the shortest path
 * through any network, with the ability to set a specific weight for each of
 * the arcs.
 *
 * @param graph Adjacency matrix
 * @param vertex1 The starting vertex from which the search begins
 * @param vertex2 The final vertex where the search ends
 * @return int The distance of traveled
 */
int GraphAlgorithms::GetShortestPathBetweenVertices(const Graph& graph,
                                                    int vertex1, int vertex2) {
  if (!GraphAlgorithms::IsCorrectVertex(vertex1, graph) ||
      !GraphAlgorithms::IsCorrectVertex(vertex2, graph)) {
    throw std::logic_error("The index for vertex incorrect!");
  }
  vertex1 -= 1;
  vertex2 -= 1;
  const int kInfinity = std::numeric_limits<int>::max();
  std::vector<int> min_distance(graph.GetGraph().size(), kInfinity);
  min_distance[vertex1] = 0;

  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                      std::greater<std::pair<int, int>>>
      dist_to_vertex;
  dist_to_vertex.push(std::make_pair(min_distance[vertex1], vertex1));

  while (!dist_to_vertex.empty()) {
    int curr_ver = dist_to_vertex.top().second;
    dist_to_vertex.pop();

    if (curr_ver == vertex2) return min_distance[vertex2];

    for (std::size_t v = 0; v < graph.GetGraph().size(); ++v) {
      int edge_weight = graph.GetGraph()[curr_ver][v];

      if (edge_weight != 0 &&
          min_distance[curr_ver] + edge_weight < min_distance[v]) {
        min_distance[v] = min_distance[curr_ver] + edge_weight;
        dist_to_vertex.push(std::make_pair(min_distance[v], v));
      }
    }
  }
  return -1;
}

/**
 * @brief Floyd-Warshall algorithm is an algorithm for finding the
 * lengths of the shortest paths between all pairs of vertices in a weighted
 * directed graph. Works correctly if there are no cycles of negative value in
 * the graph, and if there is such a cycle, it allows finding at least one such
 * cycle.
 *
 * @param graph Adjacency matrix
 * @return GraphAlgorithms::Matrix The matrix of the shortest paths between all
 * vertices of the graph
 */
GraphAlgorithms::Matrix GraphAlgorithms::GetShortestPathsBetweenAllVertices(
    const Graph& graph) {
  Matrix m = graph.GetGraph();
  if (m.size() <= 2) {
    throw std::logic_error("The size of graph is less than necessary");
  }
  for (size_t k = 0; k < m.size(); ++k) {
    for (size_t i = 0; i < m.size(); ++i) {
      for (size_t j = 0; j < m.size(); ++j) {
        if (i != j && m[i][j] == 0) {
          m[i][j] = std::numeric_limits<int>::max();
        }
        int min = m[i][k] + m[k][j];
        if (m[i][j] > min && (m[i][k] < std::numeric_limits<int>::max() &&
                              m[k][j] < std::numeric_limits<int>::max())) {
          m[i][j] = min;
        }
      }
    }
  }

  for (size_t i = 0; i < m.size(); ++i) {
    for (size_t j = 0; j < m.size(); ++j) {
      if (i != j && m[i][j] == std::numeric_limits<int>::max()) {
        m[i][j] = 0;
      }
    }
  }
  return m;
}

/**
 * @brief Prim's algorithm (also known as Jarník's algorithm) is a greedy
 * algorithm that finds a minimum spanning tree for a weighted undirected graph.
 * This means it finds a subset of the edges that forms a tree that includes
 * every vertex, where the total weight of all the edges in the tree is
 * minimized.
 * @param graph Adjacency matrix
 * @return GraphAlgorithms::Matrix The adjacency matrix for the minimal spanning
 * tree
 */
GraphAlgorithms::Matrix GraphAlgorithms::GetLeastSpanningTree(
    const Graph& graph) {
  if (graph.IsDirected()) {
    throw std::logic_error("Algoritm deal with undirected graphs only");
  }
  if (graph.GetGraph().size() < 2) {
    throw std::logic_error("The size of graph is less than necessary");
  }
  std::vector<bool> span(graph.GetGraph().size());
  span[0] = true;
  int span_cnt = graph.GetGraph().size() - 1;
  Matrix res = Matrix(graph.GetGraph().size(),
                      std::vector<int>(graph.GetGraph().size()));
  while (span_cnt > 0) {
    int min_weigth = std::numeric_limits<int>::max(), i_min = 0, j_min = 0;
    for (size_t i = 0; i < graph.GetGraph().size(); ++i) {
      if (span[i]) {
        for (size_t j = 0; j < graph.GetGraph().size(); ++j) {
          if (!span[j] && graph.GetGraph()[i][j] != 0) {
            if (min_weigth > graph.GetGraph()[i][j]) {
              min_weigth = graph.GetGraph()[i][j];
              i_min = i;
              j_min = j;
            }
          }
        }
      }
    }
    res[i_min][j_min] = res[j_min][i_min] = min_weigth;
    --span_cnt;
    span[j_min] = true;
  }
  return res;
}

/**
 * @brief Solves the traveling salesman's problem on loaded graph using the ant
 * colony algorithm.
 *
 * @param graph
 * @return TsmResult
 */
TsmResult GraphAlgorithms::SolveTravelingSalesmanProblem(const Graph& graph) {
  AntAlgorithm algo(graph);
  algo.RunAlgorithm();
  return algo.GetResult();
}

/**
 * @brief Solves the traveling salesman's problem on loaded graph using the
 * simulated annealing algorithm.
 *
 * @param graph
 * @return TsmResult
 */
TsmResult GraphAlgorithms::SolveTsmSimulatedAnnealing(const Graph& graph) {
  AnnealingAlgorithm algo(graph);
  algo.RunAlgorithm();
  return algo.GetResult();
}

/**
 * @brief Solves the traveling salesman's problem on loaded graph using the
 * genetic algorithm.
 *
 * @param graph
 * @return TsmResult
 */
TsmResult GraphAlgorithms::SolveTsmGenetic(const Graph& graph) {
  GeneticAlgorithm algo(graph);
  algo.RunAlgorithm();
  return algo.GetResult();
}

bool GraphAlgorithms::IsCorrectVertex(int vertex, const Graph& graph) {
  if (vertex < 1 || vertex > static_cast<int>(graph.GetGraph().size())) {
    return false;
  }
  return true;
}
