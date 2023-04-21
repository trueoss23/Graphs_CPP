#include "s21_graph.h"

#include <iostream>

/**
 * @brief Loading a graph from a file in the adjacency matrix format
 *
 * @param filename
 */
void Graph::LoadGraphFromFile(const std::string& filename) {
  std::ifstream file(filename);
  if (!file) throw std::logic_error("Open file error");
  int vertex_cnt;
  file >> vertex_cnt;
  if (file.fail() or file.peek() != '\n' or vertex_cnt <= 0) {
    throw std::logic_error("Graph size error");
  }
  CreateGraph(vertex_cnt);
  for (int i = 0; i < vertex_cnt; ++i) {
    for (int j = 0; j < vertex_cnt; ++j) {
      if (file.peek() == EOF) {
        throw std::logic_error("Count of edge less than shape of graph");
      }
      std::string str;
      std::stringstream sstr;
      int value;
      file >> str;
      if (!std::all_of(str.begin(), str.end(), [](char ch) {
            return std::isdigit(static_cast<unsigned char>(ch));
          })) {
        throw std::logic_error("Non-digit edge weights in graph");
      }
      sstr << str;
      sstr >> value;
      graph_[i][j] = value;
    }
  }
  if (file.peek() != EOF) {
    throw std::logic_error("Count of edge greater than shape of graph");
  }
  file.close();
}

/**
 * @brief Exporting a graph to a dot file
 *
 * @param filename
 */
void Graph::ExportGraphToDot(const std::string& filename) const {
  std::ofstream file(filename);
  if (IsDirected()) {
    SaveDirected(file);
  } else {
    SaveUndirected(file);
  }
  file.close();
}

/**
 * @brief Returns true if loaded graph id directed, otherwise - false
 *
 * @return true
 * @return false
 */
bool Graph::IsDirected() const {
  for (size_t i = 0; i < graph_.size(); ++i) {
    for (size_t j = i + 1; j < graph_.size(); ++j) {
      if (graph_[i][j] != graph_[j][i]) return true;
    }
  }
  return false;
}

/**
 * @brief Exporting directed graph to a dot file
 *
 * @param file
 */
void Graph::SaveDirected(std::ofstream& file) const {
  file << "digraph DirectedGraph {\n";
  for (size_t i = 0; i < graph_.size(); ++i) {
    for (size_t j = i; j < graph_.size(); ++j) {
      if (graph_[i][j] > 0 and graph_[j][i] == 0) {
        file << '\t' << i + 1 << " -> " << j + 1
             << " [weight = " << graph_[i][j] << "];\n";
      } else if (graph_[i][j] == 0 and graph_[j][i] > 0) {
        file << '\t' << j + 1 << " -> " << i + 1
             << " [weight = " << graph_[j][i] << "];\n";
      } else if (graph_[i][j] > 0 and graph_[j][i] > 0) {
        file << '\t' << i + 1 << " -> " << j + 1
             << " [weight = " << graph_[i][j] << " dir=\"both\"];\n";
      }
    }
  }
  file << '}';
}

/**
 * @brief Exporting undirected graph to a dot file
 *
 * @param file
 */
void Graph::SaveUndirected(std::ofstream& file) const {
  file << "graph UndirectedGraph {\n";
  for (size_t i = 0; i < graph_.size(); ++i) {
    for (size_t j = i; j < graph_.size(); ++j) {
      if (graph_[i][j] > 0) {
        file << '\t' << i + 1 << " -- " << j + 1
             << " [weight = " << graph_[i][j] << "];\n";
      }
    }
  }
  file << '}';
}

/**
 * @brief Creates graph member
 *
 * @param size
 */
void Graph::CreateGraph(const int& size) {
  this->graph_ = Matrix(size, std::vector<int>(size));
}

/**
 * @brief Returns graph member
 *
 * @return const Graph::Matrix&
 */
const Graph::Matrix& Graph::GetGraph() const { return this->graph_; }

/**
 * @brief Returns weigth at (vertex1, vertex2) coordinate
 *
 * @param vertex1
 * @param vertex2
 * @return int
 */
int Graph::GetWeight(int idx1, int idx2) const {
  if ((idx1 < 0 or idx1 >= static_cast<int>(graph_.size())) or
      (idx2 < 0 or idx2 >= static_cast<int>(graph_.size())))
    throw std::out_of_range("Graph index out of range");
  return graph_[idx1][idx2];
}
