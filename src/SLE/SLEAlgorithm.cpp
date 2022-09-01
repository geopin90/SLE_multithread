#include "SLEAlgorithm.h"

namespace s21 {

void SLEAlgorithm::solveGauss(bool isMulti) {
  int i;
  if (isMulti) {
    std::vector<std::thread> allThreads;
    for (i = 0; i < mSize; i++) {
      std::thread myThread(oneThread, this, i, i);
      allThreads.push_back(std::move(myThread));
    }
    for (size_t j = 0; j < allThreads.size(); j++) {
      allThreads[j].join();
    }
  } else {
    for (i = 0; i < mSize; i++) {
      oneThread(i, i);
    }
  }

  for (i = mSize - 1; i >= 0; i--) {
    findAnswers(i);
  }

  for (i = 0; i < mSize; i++) {
    if (std::isnan(answer[i])) {
      throw std::out_of_range("Cannot solve this matrix");
    }
  }
}

void SLEAlgorithm::oneThread(int row, int col) {
  for (int i = row; i < mSize; i++) {
    double x = 1.0 / data_(i, col);
    for (int j = 0; j < data_.getCols(); j++) {
      data_(i, j) *= x;
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
    result -= data_(index, i) * answer[i];
  }
  answer[index] = result;
}

void SLEAlgorithm::setMatrix(const Matrix& m) {
  data_ = m;
  dataOld = m;
  mSize = m.getRows();
  answer.resize(mSize);
}

void SLEAlgorithm::start(bool isMulti) {
  if (mSize > 0) {
    data_ = dataOld;
    try {
      solveGauss(isMulti);
    } catch (std::exception& e) {
      throw;
    }
  } else {
    throw std::out_of_range("Matrix is not set");
  }
}

const std::vector<double>& SLEAlgorithm::getAnswer() { return answer; }

}  // namespace s21