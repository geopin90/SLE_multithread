// #include <conio.h>
#include <locale.h>
#include <math.h>
// #include <stdafx.h>
#include <stdlib.h>

#include <iostream>
using namespace std;

int main() {
  int i, j, n = 3, m = 4;
  setlocale(LC_ALL, "rus");
  //создаем массив
  //   cout << "введи число уравнений: ";
  //   cin >> n;
  //   cout << "введи число неизвестных: ";
  //   cin >> m;
  //   m += 1;
  float **matrix = new float *[n];
  for (i = 0; i < n; i++) matrix[i] = new float[m];

  //инициализируем
  float mas[12] = {2, 1, -1, 8, -3, -1, 2, -11, -2, 1, 2, -3};
  int count = 0;
  for (i = 0; i < n; i++) {
    for (j = 0; j < m; j++) {
      //   cout << "Элемент "
      //        << "[" << i + 1 << " , " << j + 1 << "]: ";

      //   cin >> matrix[i][j];
      matrix[i][j] = mas[count];
      count++;
    }
  }

  //выводим массив
  cout << "matrix: " << endl;
  for (i = 0; i < n; i++) {
    for (j = 0; j < m; j++) cout << matrix[i][j] << " ";
    cout << endl;
  }
  cout << endl;

  //Метод Гаусса
  //Прямой ход, приведение к верхнетреугольному виду
  float tmp, xx[m];
  int k;

  for (i = 0; i < n; i++) {
    tmp = matrix[i][i];
    for (j = n; j >= i; j--) matrix[i][j] /= tmp;
    for (j = i + 1; j < n; j++) {
      tmp = matrix[j][i];
      for (k = n; k >= i; k--) matrix[j][k] -= tmp * matrix[i][k];
    }
  }
  /*обратный ход*/
  xx[n - 1] = matrix[n - 1][n];
  for (i = n - 2; i >= 0; i--) {
    xx[i] = matrix[i][n];
    for (j = i + 1; j < n; j++) xx[i] -= matrix[i][j] * xx[j];
  }

  //Выводим решения
  for (i = 0; i < n; i++) cout << xx[i] << " ";
  cout << endl;

  delete[] matrix;
  return 0;
}