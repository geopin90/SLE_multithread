#include "modelGauss.h"

#include <chrono>
#include <cmath>
#include <stdexcept>
#include <thread>

namespace gauss {

void Model::gaussMethod(bool isMt) {
  // form stairs-like matrix
  for (int i = 0; i < size_; i++) {
    if (isMt) {
      makeStepMt(i, i);
    } else {
      makeStep(i, i);
    }
  }
  // form result vector
  for (int i = size_ - 1; i >= 0; i--) {
    defineResultValue(i);
  }
  // check result vector for nan
  for (int i = 0; i < size_; i++) {
    if (std::isnan(result_[i])) {
      throw std::runtime_error("Lineary dependent system");
    }
  }
}

void Model::makeStep(int row, int col) {
  for (int i = row; i < size_; i++) {
    multRowOnNumber(i, 1. / matrix_(i, col));
  }
  for (int i = row + 1; i < size_; i++) {
    diffTwoRows(row, i);
  }
}

void Model::makeStepMt(int row, int col) {
  std::vector<std::thread> vThreads;
  for (int i = row; i < size_; i++) {
    std::thread th(&Model::multRowOnNumber, this, i, 1. / matrix_(i, col));
    vThreads.emplace_back(std::move(th));
    // multRowOnNumber(i, 1. / matrix_(i, col));
  }
  for (auto& th : vThreads) {
    th.join();
  }
  vThreads.clear();
  for (int i = row + 1; i < size_; i++) {
    std::thread th(&Model::diffTwoRows, this, row, i);
    vThreads.emplace_back(std::move(th));
    // diffTwoRows(row, i);
  }
  for (auto& th : vThreads) {
    th.join();
  }
}

void Model::defineResultValue(int idx) {
  double res = matrix_(idx, size_);
  for (int i = idx + 1; i < size_; i++) {
    std::cout << "result[i] = " << result_[i] << std::endl;
    res -= matrix_(idx, i) * result_[i];
  }
  result_[idx] = res;
}

void Model::multRowOnNumber(int row, double num) {
  for (int i = 0; i < matrix_.getCols(); i++) {
    matrix_(row, i) *= num;
  }
  /* cause only simple functions can be paralleled in this algorithm
     we need to imitate here some hard job via sleep_for */
  std::this_thread::sleep_for(std::chrono::milliseconds(1));
}

void Model::diffTwoRows(int rSrc, int rDest) {
  for (int i = 0; i < matrix_.getCols(); i++) {
    matrix_(rDest, i) -= matrix_(rSrc, i);
  }
  /* cause only simple functions can be paralleled in this algorithm
     we need to imitate here some hard job via sleep_for */
  std::this_thread::sleep_for(std::chrono::milliseconds(1));
}

inline void Model::init(const s21::Matrix& matrix) {
  matrix_ = matrix;
  size_ = matrix.getRows();
  result_.resize(size_);
}

void Model::calculateResult(const s21::Matrix& matrix) {
  init(matrix);
  gaussMethod();
}

void Model::calculateResultMt(const s21::Matrix& matrix) {
  init(matrix);
  gaussMethod(true);
}

const Result& Model::getResult() const { return result_; }

}  // namespace gauss
