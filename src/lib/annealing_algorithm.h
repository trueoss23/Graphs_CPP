#ifndef SRC_LIB_ANNEALING_ALGORITHM_H
#define SRC_LIB_ANNEALING_ALGORITHM_H

#include <random>
#include <vector>

#include "heuristics.h"
#include "s21_graph.h"
#include "tsmresult.h"

class AnnealingAlgorithm {
 public:
  using Vector = std::vector<int>;
  using Matrix = std::vector<std::vector<int>>;

  explicit AnnealingAlgorithm(const Graph &);

  void RunAlgorithm();
  TsmResult GetResult() const;

 private:
  Vector RandomPath();
  int RandomChoice(int max);
  double GetDistance(const TsmResult &);
  TsmResult Shuffle(TsmResult);
  bool MakeDecision(const TsmResult &, const TsmResult &, double);

  const Matrix &graph_;
  const Heuristics consts_;
  TsmResult result_;
};

#endif  // SRC_LIB_ANNEALING_ALGORITHM_H
