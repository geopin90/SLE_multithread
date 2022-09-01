#include <iostream>
#include <vector>
#include <thread>

#include "Matrix.h"

namespace s21 {

class SLEAlgorithm {
 private:
  Matrix data_;
  std::vector<double> answer;
  int mSize = 0;

 public:
  SLEAlgorithm() {}
  void start(const Matrix& m);
  const std::vector<double>& getAnswer();

 private:
  void solveGauss(bool isMulti = false);
  void oneThread(int row, int col);
  void mulThread(int row, int col);
  void forwardStep();
  void backStep();
  void findAnswers(int index);
};

}  // namespace s21