#include <iostream>
#include <vector>

#include "SLE/Matrix.h"
#include "SLE/modelGauss.h"
#include "SLE/SLEAlgorithm.h"

int main() {
  s21::Matrix matrix(3, 4);
  matrix(0, 0) = 2.0;
  matrix(0, 1) = 1.0;
  matrix(0, 2) = -1.0;
  matrix(0, 3) = 8.0;
  matrix(1, 0) = -3.0;
  matrix(1, 1) = -1.0;
  matrix(1, 2) = 2.0;
  matrix(1, 3) = -11.0;
  matrix(2, 0) = -2.0;
  matrix(2, 1) = 1.0;
  matrix(2, 2) = 2.0;
  matrix(2, 3) = -3.0;

  s21::SLEAlgorithm algo;
  algo.start(matrix);
  const auto& v = algo.getAnswer();
  for (unsigned int i = 0; i < v.size(); i++) {
    std::cout << v[i] << ' ';
  }
  std::cout << std::endl;

  // gauss::Model model;
  // model.calculateResult(matrix);
  // const auto& vResAct = model.getResult();
  // for (unsigned int i = 0; i < vResAct.size(); i++) {
  //   std::cout << vResAct[i] << ' ';
  // }
  // std::cout << std::endl;


  return 0;
}