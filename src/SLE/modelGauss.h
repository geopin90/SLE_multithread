#pragma once

#include <iostream>
#include <vector>

#include "Matrix.h"

namespace gauss {

using Result = std::vector<double>;

class Model {
 private:
  s21::Matrix matrix_;
  int size_ = 0;
  Result result_;

  void gaussMethod(bool isMt = false);
  void makeStep(int row, int col);
  void makeStepMt(int row, int col);
  void defineResultValue(int idx);
  void multRowOnNumber(int row, double num);
  void diffTwoRows(int rSrc, int rDest);
  inline void init(const s21::Matrix& matrix);

 public:
  Model() {}
  void calculateResult(const s21::Matrix& matrix);
  void calculateResultMt(const s21::Matrix& matrix);
  const Result& getResult() const;
};

}  // namespace gauss
