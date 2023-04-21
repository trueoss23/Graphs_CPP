#ifndef SRC_LIB_ANT_ALGORITHM_H
#define SRC_LIB_ANT_ALGORITHM_H

#include <algorithm>
#include <memory>
#include <random>
#include <string>
#include <vector>

#include "heuristics.h"
#include "s21_graph.h"
#include "tsmresult.h"

class Ant {
 public:
  using Path = std::vector<int>;
  using Tabu = std::vector<bool>;
  using Visited = std::vector<std::pair<size_t, size_t>>;
  using Pheromones = std::vector<std::vector<double>>;
  using Chances = std::vector<double>;

  Ant(const Graph &, size_t);

  void MakeBypass(const Pheromones &);
  double GetDistance() const;
  Path GetPath() const;
  bool IsVisited(size_t, size_t);

 private:
  int ChooseNextPath(const Pheromones &, size_t);
  Chances GetChances(const Pheromones &, size_t);
  double RandomChoice(const double, const double);

 private:
  const Graph &graph_;
  Tabu tabu_;
  Path path_;
  Visited visited_;
  Heuristics consts_;
};

class AntAlgorithm {
 public:
  using Path = std::vector<int>;
  using Ants = std::vector<std::unique_ptr<Ant>>;
  using Pheromones = std::vector<std::vector<double>>;
  using Chances = std::vector<double>;

 public:
  explicit AntAlgorithm(const Graph &);

  void RunAlgorithm();
  TsmResult GetResult();

 private:
  void RunColony();
  void RunAnts();
  void UpdatePheromones();
  void UpdateResult();
  bool CheckResult();

 private:
  const Graph &graph_;
  TsmResult result_;
  Ants ants_;
  Pheromones pheromones_;
  Heuristics consts_;
};

#endif  // SRC_LIB_ANT_ALGORITHM_H
