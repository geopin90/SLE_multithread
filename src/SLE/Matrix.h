#pragma once
#include <cmath>
#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <fstream>

namespace s21 {
class Matrix {
 private:
  int rows, cols;
  double** matrix;

 public:
  Matrix();
  Matrix(int rows, int cols);
  Matrix(const Matrix& other);
  Matrix(Matrix&& other);
  ~Matrix();

  bool eq_matrix(const Matrix& other) const;
  void sum_matrix(const Matrix& other);
  void sub_matrix(const Matrix& other);
  void mul_number(const double num);
  void mul_matrix(const Matrix& other);

  int getRows() const;
  int getCols() const;

  Matrix operator+(const Matrix& other) const;
  Matrix operator-(const Matrix& other) const;
  Matrix operator*(const Matrix& other) const;
  Matrix operator*(const double num) const;

  friend Matrix operator*(const double num, const Matrix& other);
  bool operator==(const Matrix& other) const;
  Matrix& operator=(const Matrix& other);
  Matrix operator+=(const Matrix& other);
  Matrix operator-=(const Matrix& other);
  Matrix operator*=(const Matrix& other);
  Matrix operator*=(const double num);
  const double& operator()(int i, int j) const;
  double& operator()(int i, int j);
  void loadMatrix(std::ifstream& file);
  void setSize(int newRows, int newCols);
  void print();

 private:
  bool isEqualSizes(const Matrix& other) const;
  bool isSquareMatrix() const;
  void allocateMemory(int row, int col);
  void freeMemory();
  void copyMatrix(double** other_matrix);
};

Matrix operator*(double num, const Matrix& other);
}  // namespace s21