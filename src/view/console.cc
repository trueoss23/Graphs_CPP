#include "console.h"

const std::string Console::menu_{
    "\n\u001b[42;1m              \
      CHOOSE AN OPTION:                     \u001b[0m\n \
      \033[39m\033[1;29m1. Change file\n \
      2. Graph traversal in depth\n \
      3. Graph traversal in breadth\n \
      4. Search the shortest path between two vertices\n \
      5. Search the shortest paths between all vertices\n \
      6. Search the minimal spanning tree\n \
      7. Solve the traveling salesman problem\n \
      8. Comparison of methods for solving the TSM\n \
      0. Exit\033[0m\n\u001b[42;1m                    \
                                      \u001b[0m\n\n"};

Console::Console(Controller *controller) : controller_(controller) {
  try {
    controller_->FirstItem(filename_);
  } catch (std::exception &e) {
    std::cout << "\u001b[41;1m" << e.what() << "\u001b[0m\n";
    InputFilename();
  }
}

void Console::PrintMatrix(GraphAlgorithms::Matrix const &m) {
  for (size_t i = 0; i < m.size(); ++i) {
    for (size_t j = 0; j < m[i].size(); ++j) {
      std::cout << "\u001b[43;1m" << std::setw(4) << m[i][j] << "\u001b[0m ";
    }
    std::cout << "\n\n";
  }
}

void Console::PrintVector(GraphAlgorithms::Vector const &v) {
  for (size_t i = 0; i < v.size(); ++i) {
    std::cout << "\u001b[43;1m" << v[i] << " ";
  }
  std::cout << "\u001b[0m\n\n";
}

int Console::InputNumber(const std::string &str) {
  int res;
  while (1) {
    std::cin >> res;
    if (std::cin.fail()) {
      system("clear");
      std::cout << "\n\u001b[41;1mWRONG INPUT!\u001b[0m\n" << std::endl;
      std::cout << str << std::endl;
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } else {
      return res;
    }
  }
}

bool Console::ChooseMenuItem() {
  int choice = InputNumber(menu_);
  bool resulst = true;

  switch (choice) {
    case 1:
      system("clear");
      InputFilename();
      break;
    case 2:
      system("clear");
      int vertex;
      std::cout << "\n\u001b[42;1mENTER START VERTEX: \u001b[0m\n\n";
      vertex = InputNumber("\n\u001b[42;1mENTER START VERTEX: \u001b[0m\n\n");
      try {
        PrintVector(controller_->SecondItem(vertex));
      } catch (std::logic_error &e) {
        std::cout << "\u001b[41;1m" << e.what() << "\u001b[0m\n";
      }
      break;
    case 3:
      system("clear");
      std::cout << "\n\u001b[42;1mENTER START VERTEX: \u001b[0m\n\n";
      vertex = InputNumber("\n\u001b[42;1mENTER START VERTEX: \u001b[0m\n\n");
      try {
        PrintVector(controller_->ThirdItem(vertex));
      } catch (std::logic_error &e) {
        std::cout << "\u001b[41;1m" << e.what() << "\u001b[0m\n";
      }
      break;
    case 4:
      system("clear");
      int vertex1, vertex2;
      std::cout << "\n\u001b[42;1mENTER START VERTEX: \u001b[0m\n\n";
      vertex1 = InputNumber("\n\u001b[42;1mENTER START VERTEX: \u001b[0m\n\n");
      std::cout << "\n\u001b[42;1mENTER END VERTEX:   \u001b[0m\n\n";
      vertex2 = InputNumber("\n\u001b[42;1mENTER END VERTEX:\u001b[0m\n\n");
      std::cout << "\n\u001b[43;1mRESULT:             \u001b[0m\n\n";
      try {
        std::cout << controller_->FourthItem(vertex1, vertex2) << std::endl;
      } catch (std::logic_error &e) {
        std::cout << "\u001b[41;1m" << e.what() << "\u001b[0m\n";
      }
      break;
    case 5:
      system("clear");
      try {
        PrintMatrix(controller_->FivthItem());
      } catch (std::logic_error &e) {
        std::cout << "\u001b[41;1m" << e.what() << "\u001b[0m\n";
      }
      break;
    case 6:
      system("clear");
      try {
        PrintMatrix(controller_->SixthItem());
      } catch (std::logic_error &e) {
        std::cout << "\u001b[41;1m" << e.what() << "\u001b[0m\n";
      }
      break;
    case 7:
      system("clear");
      try {
        TsmResult result = controller_->SeventhItem();
        std::string res = "ROUTE:";
        for (size_t i = 0; i < result.vertices.size(); ++i) {
          res += " -> " + std::to_string(result.vertices[i]);
        }
        res += "\n\nLENGTH: " + std::to_string((int)result.distance);
        std::cout << "\n\u001b[43;1m" << res << "\u001b[0m\n\n";
      } catch (const std::logic_error &e) {
        std::cout << "\u001b[41;1m" << e.what() << "\u001b[0m\n\n";
      }
      break;
    case 8:
      system("clear");
      int cycles;
      std::cout << "\n\u001b[42;1mENTER NUMBER OF CYCLES: \u001b[0m\n\n";
      cycles = InputNumber("\n\u001b[42;1mENTER NUMBER OF CYCLES: \u001b[0m\n");
      try {
        std::vector<std::pair<double, double>> res =
            controller_->EighthItem(cycles);
        std::cout << "\u001b[33;1mANT ALGORITHM: \u001b[0m\nDistance: "
                  << (int)res[0].first << " Time: " << res[0].second
                  << std::endl;
        std::cout << "\u001b[33;1mANNEALING ALGORITHM: \u001b[0m\nDistance: "
                  << (int)res[1].first << " Time: " << res[1].second
                  << std::endl;
        std::cout << "\u001b[33;1mGENETIC ALGORITHM: \u001b[0m\nDistance: "
                  << (int)res[2].first << " Time: " << res[2].second
                  << std::endl;
      } catch (std::out_of_range &e) {
        std::cout << "\u001b[41;1m" << e.what() << "\u001b[0m\n\n";
      } catch (std::logic_error &e) {
        std::cout << "\u001b[41;1m" << e.what() << "\u001b[0m\n\n";
      }
      break;
    case 0:
      resulst = false;
      break;
    default:
      system("clear");
      std::cout << "\n\u001b[41;1mWRONG INPUT!\u001b[0m\n";
      break;
  }
  return resulst;
}

void Console::PrintChosenFile() {
  size_t idx = filename_.find_last_of('/');
  std::string file = filename_.substr(idx + 1, filename_.size() - idx);
  std::cout << "\u001b[42;1m                      LOADED FILE:        "
               "                \u001b[0m\n                  ";
  std::cout << "\033[32m" << file << "\033[0m\n";
}

void Console::InputFilename() {
  while (1) {
    std::cout << "\n\u001b[42;1mENTER PATH TO A GRAPH FILE: \u001b[0m\n\n";
    std::string file;
    std::cin >> file;
    system("clear");
    try {
      controller_->Controller::FirstItem(file);
      filename_ = file;
      break;
    } catch (std::logic_error &e) {
      std::cout << "\u001b[41;1m" << e.what() << "\u001b[0m\n";
      continue;
    }
  }
}

void Console::Run() {
  system("clear");
  bool flag = true;
  while (flag) {
    PrintChosenFile();
    std::cout << menu_;
    flag = ChooseMenuItem();
  }
}
