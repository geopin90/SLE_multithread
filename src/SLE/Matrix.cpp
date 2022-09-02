#include "Matrix.h"

namespace s21 {
Matrix::Matrix() { allocateMemory(3, 4); }

Matrix::Matrix(int rows, int cols) {
  if (rows > 0 && cols > 0) {
    allocateMemory(rows, cols);
  } else {
    throw std::out_of_range(
        "Incorrect input, matrix should have both sizes > 0");
  }
}

Matrix::Matrix(const Matrix& other) : Matrix(other.rows, other.cols) {
  copyMatrix(other.matrix);
}

Matrix::Matrix(Matrix&& other) {
  rows = other.rows;
  cols = other.cols;
  matrix = other.matrix;
  other.matrix = nullptr;
}

Matrix::~Matrix() {
  if (matrix) {
    freeMemory();
  }
}

bool Matrix::eq_matrix(const Matrix& other) const {
  bool result = true;
  if (isEqualSizes(other)) {
    for (int i = 0; i < rows && result; i++) {
      for (int j = 0; j < cols && result; j++) {
        if (fabs(matrix[i][j] - other.matrix[i][j]) > 1e-7) result = false;
      }
    }
  } else {
    result = false;
  }
  return result;
}

void Matrix::sum_matrix(const Matrix& other) {
  if (isEqualSizes(other)) {
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        matrix[i][j] = matrix[i][j] + other.matrix[i][j];
      }
    }
  } else {
    throw std::invalid_argument(
        "Invalid argument, matrices must be equal sizes");
  }
}

void Matrix::sub_matrix(const Matrix& other) {
  if (isEqualSizes(other)) {
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        matrix[i][j] = matrix[i][j] - other.matrix[i][j];
      }
    }
  } else {
    throw std::invalid_argument(
        "Invalid argument, matrices must be equal sizes");
  }
}

void Matrix::mul_number(const double num) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      matrix[i][j] *= num;
    }
  }
}

void Matrix::mul_matrix(const Matrix& other) {
  if (cols == other.rows) {
    Matrix result(rows, other.cols);
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < other.cols; j++) {
        for (int c = 0; c < cols; c++)
          result.matrix[i][j] += matrix[i][c] * other.matrix[c][j];
      }
    }
    *this = result;
  } else {
    throw std::invalid_argument(
        "Invalid argument, number of cols of the first matrix must be equal to "
        "number of rows of the "
        "second matrix");
  }
}

int Matrix::getRows() const { return rows; }

int Matrix::getCols() const { return cols; }

Matrix Matrix::operator+(const Matrix& other) const {
  Matrix result = *this;
  result.sum_matrix(other);
  return result;
}

Matrix Matrix::operator-(const Matrix& other) const {
  Matrix result = *this;
  result.sub_matrix(other);
  return result;
}

Matrix Matrix::operator*(const Matrix& other) const {
  Matrix result = *this;
  result.mul_matrix(other);
  return result;
}

Matrix Matrix::operator*(const double num) const {
  Matrix result = *this;
  result.mul_number(num);
  return result;
}

Matrix operator*(double num, const Matrix& other) {
  Matrix result = other;
  result.mul_number(num);
  return result;
}

bool Matrix::operator==(const Matrix& other) const { return eq_matrix(other); }

Matrix& Matrix::operator=(const Matrix& other) {
  if (this != &other) {
    freeMemory();
    allocateMemory(other.rows, other.cols);
    copyMatrix(other.matrix);
  }
  return *this;
}

Matrix Matrix::operator+=(const Matrix& other) {
  sum_matrix(other);
  return *this;
}

Matrix Matrix::operator-=(const Matrix& other) {
  sub_matrix(other);
  return *this;
}

Matrix Matrix::operator*=(const Matrix& other) {
  mul_matrix(other);
  return *this;
}

Matrix Matrix::operator*=(const double num) {
  mul_number(num);
  return *this;
}

const double& Matrix::operator()(int i, int j) const {
  if (i >= 0 && i < rows && j >= 0 && j < cols) {
    return matrix[i][j];
  } else {
    throw std::out_of_range("Incorrect input, index out of matrix sizes");
  }
}

double& Matrix::operator()(int i, int j) {
  if (i >= 0 && i < rows && j >= 0 && j < cols) {
    return matrix[i][j];
  } else {
    throw std::out_of_range("Incorrect input, index out of matrix sizes");
  }
}

inline bool Matrix::isEqualSizes(const Matrix& other) const {
  return (rows == other.rows && cols == other.cols);
}

inline bool Matrix::isSquareMatrix() const { return (rows == cols); }

void Matrix::allocateMemory(int row, int col) {
  rows = row;
  cols = col;
  matrix = new double*[rows];
  for (int i = 0; i < rows; i++) {
    matrix[i] = new double[cols]();
  }
}

void Matrix::freeMemory() {
  if (!matrix) {
    for (int i = 0; i < rows; i++) {
      delete[] matrix[i];
    }
    delete[] matrix;
  }
}

void Matrix::copyMatrix(double** other_matrix) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      matrix[i][j] = other_matrix[i][j];
    }
  }
}

void Matrix::loadMatrix(std::ifstream& file) {
  std::string temp = "", tempCol = "";
  file >> temp;
  if (isdigit(temp[0]) && temp[0] != '-') {
    file >> tempCol;
    if (isdigit(tempCol[0]) && tempCol[0] != '-')
      setSize(std::stoi(temp), std::stoi(tempCol));
  } else {
    throw std::invalid_argument("invalid matrix");
  }
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      file >> temp;
      if (isdigit(temp[0]) || (isdigit(temp[1]) && temp[0] == '-'))
        matrix[i][j] = std::stod(temp);
      else
        throw std::invalid_argument("file error");
    }
  }
}

void Matrix::createMatrix() {
  std::string tempRow = "", tempCol = "";
  std::cin >> tempRow;
  std::cin >> tempCol;
  if (!isdigit(tempRow[0]) || !isdigit(tempCol[0]) || tempRow[0] == '-' || tempCol[0] == '-') {
    throw std::invalid_argument("invalid size");
  } else {
    setSize(std::stoi(tempRow), std::stoi(tempCol));
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        std::string tempEl;
        std::cin >> tempEl;
        if (isdigit(tempEl[0]) || (isdigit(tempEl[1]) && tempEl[0] == '-'))
          matrix[i][j] = std::stod(tempEl);
        else
          throw std::invalid_argument("invalid value");
      }
    }
  }
}

void Matrix::setSize(int newRows, int newCols) {
  if (newRows < 1 || newCols < 1) throw std::invalid_argument("size < 1");
  if (newRows == rows && newCols == cols) return;
  Matrix copy(*this);
  freeMemory();
  rows = newRows;
  cols = newCols;
  allocateMemory(rows, cols);
  copyMatrix(copy.matrix);
}


void Matrix::print() {
  std::cout.precision(17);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      std::cout << std::setprecision (15) << matrix[i][j] << ' ';
    }
    std::cout << std::endl;
  }
}

}  // namespace s21