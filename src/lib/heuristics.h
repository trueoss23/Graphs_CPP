#ifndef SRC_LIB_HEURISTICS_H
#define SRC_LIB_HEURISTICS_H

/**
 * @brief Hyperparameters for TSM problem algorithms
 *
 */
struct Heuristics {
  const double kStartTemp = 1000.0;
  const double kMinTemp = 0.01;
  const double kDecrease = 0.9;
  const double kAlpha = 1.0;
  const double kBeta = 1.0;
  const double kQ = 4.0;
  const double kTau = 0.2;
  const double kRo = 0.5;
  const size_t kColonies = 100;
  const size_t kBypassCount = 10;
  const size_t kGenerationsCount = 1000;
  const size_t kGenerationSize = 5;
  const size_t kMutation = 4;
  const size_t kAttempts = 100;
};

#endif  // SRC_LIB_HEURISTICS_H
