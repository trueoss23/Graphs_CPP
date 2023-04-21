#ifndef SRC_LIB_S21_GRAPH_H
#define SRC_LIB_S21_GRAPH_H

#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

class Graph {
 public:
  using Matrix = std::vector<std::vector<int>>;

  void LoadGraphFromFile(const std::string& filename);
  void ExportGraphToDot(const std::string& filename) const;

  const Matrix& GetGraph() const;
  int GetWeight(int vertex1, int vertex2) const;
  bool IsDirected() const;

 private:
  Matrix graph_;

  void SaveDirected(std::ofstream& file) const;
  void SaveUndirected(std::ofstream& file) const;
  void CreateGraph(const int& size);
};

#endif  // SRC_LIB_S21_GRAPH_H
