#include "controller.h"

Controller::Controller(Navigator* model) : model_(model) {}

void Controller::FirstItem(std::string filename) {
  model_->Navigator::FirstItem(filename);
}

GraphAlgorithms::Vector Controller::SecondItem(int start) {
  return model_->SecondItem(start);
}

GraphAlgorithms::Vector Controller::ThirdItem(int start) {
  return model_->ThirdItem(start);
}

int Controller::FourthItem(int vertex1, int vertex2) {
  return model_->FourthItem(vertex1, vertex2);
}

GraphAlgorithms::Matrix Controller::FivthItem() { return model_->FivthItem(); }

GraphAlgorithms::Matrix Controller::SixthItem() { return model_->SixthItem(); }

TsmResult Controller::SeventhItem() { return model_->SeventhItem(); }

std::vector<std::pair<double, double>> Controller::EighthItem(int cycles) {
  return model_->EighthItem(cycles);
}
