#include <iostream>
#include <vector>

#include "Matrix.h"

namespace s21 {

class SLEAlgorithm {
 private:
  Matrix data_;
  std::vector<double> answer;
  size_t numCycles;

 public:
  std::vector<double> solveGauss();
  void forwardStep();
  void backStep();
};

}  // namespace s21