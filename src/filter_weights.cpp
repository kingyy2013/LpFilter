#include "filter_weights.h"
#include <QDebug>
#include <fstream>

int FilterWeights::Width() const { return width_; }

int FilterWeights::Height() const { return height_; }

const std::vector<float> &FilterWeights::GetWeights() const {
  return filter_weights_;
}

bool FilterWeights::LoadFromFile(const std::string &file_name) {
  std::ifstream input_fstream;
  input_fstream.open(file_name, std::ios::in);
  if (input_fstream.is_open()) {
    input_fstream >> width_;
    input_fstream >> height_;
    filter_weights_.clear();
    filter_weights_.reserve(width_ * height_);
    for (int i = 0; i < width_; ++i) {
      for (int j = 0; j < height_; ++j) {
        float temp;
        input_fstream >> temp;
        filter_weights_.emplace_back(temp);
        if (!input_fstream.good()) {
          return false;
        }
      }
    }
  } else {
    return false;
  }

  return true;
}
