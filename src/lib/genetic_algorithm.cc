#include "./genetic_algorithm.h"

/**
 * @brief Construct a new Genetic Algorithm:: Genetic Algorithm object
 *
 * @param graph
 */
GeneticAlgorithm::GeneticAlgorithm(const Graph &graph)
    : graph_{graph.GetGraph()} {}

/**
 * @brief Runs Genetic Algotithm on loaded graph
 *
 */
void GeneticAlgorithm::RunAlgorithm() {
  Generation generation = MakeGeneration();
  for (size_t i = 0; i < generation.size(); ++i) {
    population_.insert(
        std::pair<int, Individual>(GetFitness(generation[i]), generation[i]));
  }
  for (size_t i = 0; i < consts_.kGenerationsCount; ++i) {
    auto it = population_.begin();
    ++it;
    Offspring offspring =
        Procreate((*(population_.begin())).second, (*it).second);
    Mutate(&offspring.first);
    Mutate(&offspring.second);
    population_.insert(std::pair<int, Individual>(GetFitness(offspring.first),
                                                  offspring.first));
    population_.insert(std::pair<int, Individual>(GetFitness(offspring.second),
                                                  offspring.second));
    population_.erase(--(population_.end()));
    population_.erase(--(population_.end()));
  }
  Individual ind;
  for (size_t i = 0; i < (*(population_.begin())).second.size(); ++i) {
    ind.push_back((*(population_.begin())).second[i]);
  }
  result_.vertices = ind;
  result_.distance = (*(population_.begin())).first;
}

/**
 * @brief Returns random generation
 *
 * @return GeneticAlgorithm::Generation
 */
GeneticAlgorithm::Generation GeneticAlgorithm::MakeGeneration() {
  Generation generation(consts_.kGenerationSize);
  Individual ind;
  for (size_t i = 0; i < graph_.size(); ++i) {
    ind.push_back(i + 1);
  }
  for (size_t i = 0; i < consts_.kGenerationSize; ++i) {
    std::shuffle(ind.begin(), ind.end(), std::mt19937(std::random_device()()));
    for (size_t j = 0; j < ind.size(); ++j) {
      generation[i].push_back(ind[j]);
    }
  }
  return generation;
}

/**
 * @brief Simulates breeding process
 *
 * @param Individual
 * @param Individual
 * @return GeneticAlgorithm::Offspring
 */
GeneticAlgorithm::Offspring GeneticAlgorithm::Procreate(Individual &ancestor1,
                                                        Individual &ancestor2) {
  Individual offspring1, offspring2;
  int choice = RandomChoice(1, ancestor1.size());
  for (int i = 0; i < choice; ++i) {
    offspring1.push_back(ancestor1[i]);
    offspring2.push_back(ancestor2[i]);
  }
  for (size_t i = 0; i < ancestor1.size(); ++i) {
    if (!IsGeneInOffspring(offspring1, ancestor2[i])) {
      offspring1.push_back(ancestor2[i]);
    }
    if (!IsGeneInOffspring(offspring2, ancestor1[i])) {
      offspring2.push_back(ancestor1[i]);
    }
  }
  return Offspring(offspring1, offspring2);
}

/**
 * @brief Randomly cnanges genes
 *
 * @param Individual
 */
void GeneticAlgorithm::Mutate(Individual *ind) {
  for (size_t i = 0; i < graph_.size() / consts_.kMutation; ++i) {
    int idx1 = RandomChoice(0, ind->size() - 1);
    int idx2 = RandomChoice(0, ind->size() - 1);
    std::swap(ind->at(idx1), ind->at(idx2));
  }
}

/**
 * @brief Returns true if gene in offspring, otherwise - false
 *
 * @param Individual
 * @param gene
 * @return true
 * @return false
 */
bool GeneticAlgorithm::IsGeneInOffspring(const Individual &ind, int gene) {
  for (size_t i = 0; i < ind.size(); ++i) {
    if (gene == ind[i]) return true;
  }
  return false;
}

/**
 * @brief Calculates optimized value
 *
 * @param Individual
 * @return int
 */
int GeneticAlgorithm::GetFitness(const Individual &ind) {
  if (ind.size() == 0) return -1;
  if (graph_[0][ind[0] - 1] == 0 or graph_[ind.back() - 1][0] == 0)
    return std::numeric_limits<int>::max();

  int fitness = graph_[0][ind[0] - 1] + graph_[ind.back() - 1][0];

  for (size_t i = 0; i < ind.size() - 1; ++i) {
    if (graph_[ind[i] - 1][ind[i + 1] - 1] == 0)
      return std::numeric_limits<int>::max();
    fitness += graph_[ind[i] - 1][ind[i + 1] - 1];
  }
  return fitness;
}

/**
 * @brief Returns random integer number from range [min, max]
 *
 * @param min left border of range
 * @param max right border of range
 * @return int
 */
int GeneticAlgorithm::RandomChoice(int min, int max) {
  std::uniform_int_distribution<int> dist(min, max);
  std::random_device rd;
  return dist(rd);
}

/**
 * @brief Returns TsmResult member
 *
 * @return TsmResult
 */
TsmResult GeneticAlgorithm::GetResult() { return this->result_; }
