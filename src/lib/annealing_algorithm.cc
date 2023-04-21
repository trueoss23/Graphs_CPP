#include "./annealing_algorithm.h"

/**
 * @brief Construct a new Annealing Algorithm:: Annealing Algorithm object
 *
 * @param graph
 */
AnnealingAlgorithm::AnnealingAlgorithm(const Graph &graph)
    : graph_(graph.GetGraph()) {}

/**
 * @brief Runs Annealing Algotithm on loaded graph
 *
 */
void AnnealingAlgorithm::RunAlgorithm() {
  double temperature = consts_.kStartTemp;
  int attempts = graph_.size() * consts_.kAttempts;
  TsmResult random_result{{}, 0};
  random_result.vertices = RandomPath();
  random_result.distance = GetDistance(random_result);
  result_ = random_result;
  while (temperature > consts_.kMinTemp) {
    for (int i = 0; i < attempts; ++i) {
      random_result = Shuffle(random_result);
      random_result.distance = GetDistance(random_result);
      if (MakeDecision(result_, random_result, temperature)) {
        result_ = random_result;
      } else {
        random_result = result_;
      }
    }
    temperature *= consts_.kDecrease;
  }
}

/**
 * @brief Returns available random path
 *
 * @return AnnealingAlgorithm::Vector
 */
AnnealingAlgorithm::Vector AnnealingAlgorithm::RandomPath() {
  Vector path;
  size_t vertex = 0;
  int choice = RandomChoice(graph_.size() - 1);
  while (vertex < graph_.size()) {
    path.push_back(choice);
    ++vertex;
    choice = (choice + 1) % graph_.size();
  }
  return path;
}

/**
 * @brief Returns random integer number from range [0, max]
 *
 * @param max right border of range
 * @return int
 */
int AnnealingAlgorithm::RandomChoice(int max) {
  std::uniform_int_distribution<int> dist(0, max);
  std::random_device rd;
  return dist(rd);
}

/**
 * @brief Calculates distance at given TsmResult struct
 *
 * @param tsm
 * @return double
 */
double AnnealingAlgorithm::GetDistance(const TsmResult &tsm) {
  double distance = 0.0;
  for (size_t i = 1; i < graph_.size(); ++i) {
    distance += graph_[tsm.vertices[i - 1]][tsm.vertices[i]];
  }
  distance += graph_[tsm.vertices[graph_.size() - 1]][tsm.vertices[0]];
  return distance;
}

/**
 * @brief Randomly shuffles vertices in TsmResult struct
 *
 * @param tsm
 * @return TsmResult
 */
TsmResult AnnealingAlgorithm::Shuffle(TsmResult tsm) {
  int idx1 = RandomChoice(graph_.size() - 1);
  int idx2 = RandomChoice(graph_.size() - 1);
  std::swap(tsm.vertices[idx1], tsm.vertices[idx2]);
  return tsm;
}

/**
 * @brief Returns random bool depending on current temperature
 *
 * @param tsm
 * @param r_tsm
 * @param temp Temperature value
 * @return true
 * @return false
 */
bool AnnealingAlgorithm::MakeDecision(const TsmResult &tsm,
                                      const TsmResult &r_tsm, double temp) {
  if ((tsm.distance > r_tsm.distance) or
      (static_cast<int>(std::exp((tsm.distance - r_tsm.distance) / temp) *
                        100) > RandomChoice(100)))
    return true;
  return false;
}

/**
 * @brief Returns TsmResult member
 *
 * @return TsmResult
 */
TsmResult AnnealingAlgorithm::GetResult() const { return this->result_; }
