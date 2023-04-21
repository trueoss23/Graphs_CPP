#include "navigator.h"

void Navigator::FirstItem(const std::string& filename) {
  graph_.LoadGraphFromFile(filename);
}

GraphAlgorithms::Vector Navigator::SecondItem(int start) {
  return GraphAlgorithms::DepthFirstSearch(graph_, start);
}

GraphAlgorithms::Vector Navigator::ThirdItem(int start) {
  return GraphAlgorithms::BreadthFirstSearch(graph_, start);
}

int Navigator::FourthItem(int vertex1, int vertex2) {
  return GraphAlgorithms::GetShortestPathBetweenVertices(graph_, vertex1,
                                                         vertex2);
}

GraphAlgorithms::Matrix Navigator::FivthItem() {
  return GraphAlgorithms::GetShortestPathsBetweenAllVertices(graph_);
}

GraphAlgorithms::Matrix Navigator::SixthItem() {
  return GraphAlgorithms::GetLeastSpanningTree(graph_);
}

TsmResult Navigator::SeventhItem() {
  return GraphAlgorithms::SolveTravelingSalesmanProblem(graph_);
}

std::vector<std::pair<double, double>> Navigator::EighthItem(int cycles) {
  if (cycles <= 0 or cycles > 1000) {
    throw std::logic_error("Number of cycles between 1 and 1000");
  }
  std::vector<std::pair<double, double>> result;
  std::set<double> answers;
  AntAlgorithm ant(graph_);
  AnnealingAlgorithm annealing(graph_);
  GeneticAlgorithm genetic(graph_);

  double start = std::clock();
  for (int i = cycles; i > 0; --i) {
    ant.RunAlgorithm();
    answers.insert(ant.GetResult().distance);
  }
  double end = std::clock();
  result.push_back({*answers.begin(), (end - start) / CLOCKS_PER_SEC});
  answers.clear();

  start = std::clock();
  for (int i = cycles; i > 0; --i) {
    annealing.RunAlgorithm();
    answers.insert(ant.GetResult().distance);
  }
  end = std::clock();
  result.push_back({*answers.begin(), (end - start) / CLOCKS_PER_SEC});
  answers.clear();

  start = std::clock();
  for (int i = cycles; i > 0; --i) {
    genetic.RunAlgorithm();
    answers.insert(ant.GetResult().distance);
  }
  end = std::clock();
  result.push_back({*answers.begin(), (end - start) / CLOCKS_PER_SEC});

  return result;
}
