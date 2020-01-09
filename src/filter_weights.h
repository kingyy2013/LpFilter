#ifndef FILTERWEIGHTS_H
#define FILTERWEIGHTS_H

#include <string>
#include <vector>

class FilterWeights {
public:
  FilterWeights() = default;
  // Load the filter from file.
  bool LoadFromFile(const std::string &file_name);
  // Width of the filter matrix.
  int Width() const;
  // Height of the filter matrix.
  int Height() const;
  // Get filter weights.
  const std::vector<float> &GetWeights() const;

private:
  // Width of the filter matrix.
  int width_;
  // Height of the filter matrix.
  int height_;
  // The weights of each entry of the filter matrix.
  std::vector<float> filter_weights_;
};

#endif // FILTERWEIGHTS_H
