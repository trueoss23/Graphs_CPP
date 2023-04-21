#ifndef SRC_LIB_GENETIC_ALGORITHM_H
#define SRC_LIB_GENETIC_ALGORITHM_H

#include <algorithm>
#include <map>
#include <random>
#include <vector>

#include "heuristics.h"
#include "s21_graph.h"
#include "tsmresult.h"

class GeneticAlgorithm {
 public:
  using Individual = std::vector<int>;
  using Generation = std::vector<std::vector<int>>;
  using Population = std::multimap<int, Individual>;
  using Offspring = std::pair<Individual, Individual>;

  explicit GeneticAlgorithm(const Graph &);

  void RunAlgorithm();
  TsmResult GetResult();

 private:
  Generation MakeGeneration();
  Offspring Procreate(Individual &, Individual &);
  void Mutate(Individual *);

  bool IsGeneInOffspring(const Individual &, int);
  int GetFitness(const Individual &);
  int RandomChoice(int, int);

  Population population_;
  const Generation &graph_;
  const Heuristics consts_;
  TsmResult result_;
};

#endif  // SRC_LIB_GENETIC_ALGORITHM_H
