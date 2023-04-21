#ifndef SRC_LIB_TSMRESULT_H
#define SRC_LIB_TSMRESULT_H

#include <vector>

/**
 * @brief Struct for traveling salesman's problem solve storage
 *
 */
struct TsmResult {
  std::vector<int> vertices;
  double distance = 0.0;
};

#endif  // SRC_LIB_TSMRESULT_H
