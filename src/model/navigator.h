#ifndef MODEL_NAVIGATOR_H
#define MODEL_NAVIGATOR_H

#include <ctime>
#include <set>

#include "../lib/s21_graph_algorithms.h"

class Navigator {
 public:
  void FirstItem(const std::string& filename);
  GraphAlgorithms::Vector SecondItem(int start);
  GraphAlgorithms::Vector ThirdItem(int start);
  int FourthItem(int vertex1, int vertex2);
  GraphAlgorithms::Matrix FivthItem();
  GraphAlgorithms::Matrix SixthItem();
  TsmResult SeventhItem();
  std::vector<std::pair<double, double>> EighthItem(int cycles);

 private:
  Graph graph_;
};

#endif  // MODEL_NAVIGATOR_H
