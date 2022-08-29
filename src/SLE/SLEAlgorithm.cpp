#include "SLEAlgorithm.h"

namespace s21 {

void SLEAlgorithm::solveGauss() {
  for (int i = 0; i < mSize; i++) {
    oneThread(i, i);
  }

  for (int i = mSize - 1; i >= 0; i--) {
    findAnswers(i);
  }
}

void SLEAlgorithm::oneThread(int row, int col) {
  for (int i = row; i < mSize; i++) {
    for (int j = 0; j < data_.getCols(); j++) {
      data_(i, j) *= 1.0 / data_(i, col);
    }
  }

  for (int i = row + 1; i < mSize; i++) {
    for (int j = 0; j < data_.getCols(); j++) {
      data_(i, j) -= data_(row, j);
    }
  }
}

void SLEAlgorithm::findAnswers(int index) {
  double result = data_(index, mSize);
  for (int i = index + 1; i < mSize; i++) {
    std::cout << "answer[i] = " << answer[i] << std::endl;
    result -= data_(index, i) * answer[i];
  }
  answer[index] = result;
  //   answer.push_back(result);
}

void SLEAlgorithm::start(const Matrix& m) {
  data_ = m;
  mSize = m.getRows();
  answer.resize(mSize);
  solveGauss();
}

const std::vector<double>& SLEAlgorithm::getAnswer() { return answer; }

}  // namespace s21