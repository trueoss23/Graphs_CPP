#ifndef SRC_CONTROLLER_CONTROLLER_H
#define SRC_CONTROLLER_CONTROLLER_H

#include "../model/navigator.h"

class Controller {
 public:
  explicit Controller(Navigator* model);

  void FirstItem(std::string filename);
  GraphAlgorithms::Vector SecondItem(int start);
  GraphAlgorithms::Vector ThirdItem(int start);
  int FourthItem(int vertex1, int vertex2);
  GraphAlgorithms::Matrix FivthItem();
  GraphAlgorithms::Matrix SixthItem();
  TsmResult SeventhItem();
  std::vector<std::pair<double, double>> EighthItem(int cycles);

 private:
  Navigator* model_;
};

#endif  // SRC_CONTROLLER_CONTROLLER_H
