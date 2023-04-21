#include "ant_algorithm.h"

/**
 * @brief Construct a new Ant:: Ant object
 *
 * @param graph
 * @param start
 */
Ant::Ant(const Graph &graph, size_t start)
    : graph_{graph}, tabu_{Tabu(graph.GetGraph().size())} {
  path_.push_back(start);
  tabu_[start] = true;
}

/**
 * @brief Simulates one pass of the graph by an ant
 *
 * @param Pheromones
 */
void Ant::MakeBypass(const Pheromones &pheromones) {
  for (size_t i = 0; i < graph_.GetGraph().size(); ++i) {
    int next = ChooseNextPath(pheromones, path_.back());
    if (next != -1) {
      visited_.push_back(std::make_pair(path_.back(), next));
      path_.push_back(next);
      tabu_[next] = true;
    }
  }
  path_.push_back(path_.front());
}

/**
 * @brief Randomly choses next available vertex
 *
 * @param Pheromones
 * @param path
 * @return int
 */
int Ant::ChooseNextPath(const Pheromones &pheromones, size_t path) {
  Chances chances = GetChances(pheromones, path);
  double rnd = RandomChoice(0.0, 1.0);
  for (size_t i = 1; i < chances.size(); ++i) {
    if (!tabu_[i - 1] and rnd < chances[i]) return i - 1;
  }
  return -1;
}

/**
 * @brief Returns probabilities of paths transition depending on pheromones
 * values
 *
 * @param Pheromones
 * @param path
 * @return Ant::Chances
 */
Ant::Chances Ant::GetChances(const Pheromones &pheromones, size_t path) {
  Chances chances = Chances(graph_.GetGraph().size());
  double total = 0.0;
  for (size_t i = 0; i < chances.size(); ++i) {
    if (graph_.GetGraph()[path][i] and !tabu_[i]) {
      chances[i] = std::pow(pheromones[path][i], consts_.kAlpha) *
                   std::pow(1.0 / graph_.GetGraph()[path][i], consts_.kBeta);
      total += chances[i];
    } else {
      chances[i] = INFINITY;
    }
  }
  for (size_t i = 0; i < chances.size(); ++i) {
    chances[i] = !std::isinf(chances[i]) ? chances[i] / total : 0;
  }
  Chances cumulate(chances.size() + 1);
  for (size_t i = 0; i < chances.size(); ++i) {
    cumulate[i + 1] = cumulate[i] + chances[i];
  }
  return cumulate;
}

/**
 * @brief Returns random double number from range [min, max]
 *
 * @param min left border of range
 * @param max right border of range
 * @return double
 */
double Ant::RandomChoice(const double min, const double max) {
  std::uniform_real_distribution<double> dist(min, max);
  std::random_device rd;
  return dist(rd);
}

/**
 * @brief Calculates distance of path member
 *
 * @return double
 */
double Ant::GetDistance() const {
  double distance = 0.0;
  for (size_t i = 0; i < path_.size() - 1; ++i) {
    distance += graph_.GetWeight(path_[i], path_[i + 1]);
  }
  return distance;
}

/**
 * @brief Returns path member
 *
 * @return Ant::Path
 */
Ant::Path Ant::GetPath() const { return path_; }

/**
 * @brief Returns true if vertex with (i, j) coordinates in visited member,
 * otherwise - false
 *
 * @param i
 * @param j
 * @return true
 * @return false
 */
bool Ant::IsVisited(size_t i, size_t j) {
  if (std::any_of(visited_.begin(), visited_.end(),
                  [&i, &j](std::pair<size_t, size_t> v) {
                    return v.first == i and v.second == j;
                  }))
    return true;
  return false;
}

/**
 * @brief Construct a new Ant Algorithm:: Ant Algorithm object
 *
 * @param graph
 */
AntAlgorithm::AntAlgorithm(const Graph &graph) : graph_{graph} {}

/**
 * @brief Runs Ant Algotithm on loaded graph
 *
 */
void AntAlgorithm::RunAlgorithm() {
  TsmResult result{Path{}, INFINITY};
  for (size_t i = 0; i < consts_.kColonies; ++i) {
    RunColony();
    TsmResult cur = result_;
    if (cur.distance < result.distance) {
      result = std::move(cur);
    }
  }
  result_ = result;
}

/**
 * @brief Simulates pass of the graph by colony of ants
 *
 */
void AntAlgorithm::RunColony() {
  result_ = TsmResult{Path{}, INFINITY};
  pheromones_ =
      Pheromones(graph_.GetGraph().size(),
                 std::vector<double>(graph_.GetGraph().size(), consts_.kTau));
  for (size_t i = 0; i < consts_.kBypassCount; ++i) {
    RunAnts();
    UpdateResult();
    UpdatePheromones();
  };
}

/**
 * @brief Simulates pass of the graph by ants of colony
 *
 */
void AntAlgorithm::RunAnts() {
  ants_ = Ants(graph_.GetGraph().size());
  for (size_t i = 0; i < graph_.GetGraph().size(); ++i) {
    ants_[i] = std::make_unique<Ant>(graph_, i);
  }
  for (const auto &ant : ants_) {
    ant->MakeBypass(pheromones_);
  }
}

/**
 * @brief Updates pheromones member values
 *
 */
void AntAlgorithm::UpdatePheromones() {
  for (size_t i = 0; i < graph_.GetGraph().size(); ++i) {
    for (size_t j = 0; j < graph_.GetGraph().size(); ++j) {
      for (size_t k = 0; k < ants_.size(); ++k) {
        if (ants_[k]->IsVisited(i, j)) {
          pheromones_[i][j] += (1 - consts_.kRo) * pheromones_[i][j] +
                               consts_.kQ / ants_[k]->GetDistance();
          pheromones_[j][i] = pheromones_[i][j];
        }
      }
    }
  }
}

/**
 * @brief Updates member result with least distance
 *
 */
void AntAlgorithm::UpdateResult() {
  std::sort(ants_.begin(), ants_.end(), [](auto &x, auto &y) {
    return x->GetDistance() < y->GetDistance();
  });
  const auto &path = ants_.front();
  TsmResult result = TsmResult{path->GetPath(), path->GetDistance()};
  if (result.distance < result_.distance) {
    result_ = std::move(result);
  }
}

/**
 * @brief Returns TsmResult member
 *
 * @return TsmResult
 */
TsmResult AntAlgorithm::GetResult() {
  if (!CheckResult()) {
    throw std::logic_error(
        "It is impossible to solve the problem with a given graph");
  }
  TsmResult result = result_;
  std::transform(result.vertices.begin(), result.vertices.end(),
                 result.vertices.begin(), [](int &v) { return ++v; });
  return result;
}

/**
 * @brief Returns true if all vertices have been visited during the execution of
 * the algorithm, otherwise - false
 *
 * @return true
 * @return false
 */
bool AntAlgorithm::CheckResult() {
  Path vertices = Path(graph_.GetGraph().size());
  std::iota(vertices.begin(), vertices.end(), 0);
  Path path = result_.vertices;
  for (auto const &vertex : vertices) {
    if (std::find(path.begin(), path.end(), vertex) == path.end()) return false;
  }
  return true;
}
