#ifndef SRC_VIEW_CONSOLE_H
#define SRC_VIEW_CONSOLE_H

#include <iomanip>
#include <iostream>
#include <string>

#include "../controller/controller.h"

class Console {
 public:
  explicit Console(Controller* controller);

  Console(const Console& other) = delete;
  Console(Console&& other) = delete;
  Console& operator=(const Console& other) = delete;
  Console& operator=(Console&& other) = delete;

  void PrintMatrix(GraphAlgorithms::Matrix const& m);
  void PrintVector(GraphAlgorithms::Vector const& v);
  bool ChooseMenuItem();
  void PrintChosenFile();
  void InputFilename();
  int InputNumber(const std::string& str);
  void Run();

 private:
  std::string filename_ = "./resources/correct_graphs/graph_undirected.txt";
  Controller* controller_;
  const static std::string menu_;
};

#endif  // SRC_VIEW_CONSOLE_H
