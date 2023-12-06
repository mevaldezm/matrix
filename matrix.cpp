#include <iostream>
#include <memory>
#include <iomanip>
using namespace std;

class Matrix
{

  size_t rows, cols;
  double **elems;

public:
  Matrix(size_t, size_t);
  ~Matrix();
  double &operator()(size_t, size_t);
  friend Matrix operator+(Matrix &, Matrix &);
  friend ostream &operator<<(ostream &, const Matrix &);
};

ostream &operator<<(ostream &os, const Matrix &obj)
{
  for (size_t n{}; n < obj.rows; ++n)
  {
    for (size_t m{}; m < obj.cols; ++m)
      os << setw(5) << fixed << setprecision(2) << obj.elems[n][m] << " ";
    os << endl;
  }
  return os;
}
double &Matrix::operator()(size_t row, size_t col)
{
  return elems[row][col];
}

Matrix operator+(Matrix &a, Matrix &b)
{

  Matrix m{a.rows, b.cols};

  // copy first matrix
  for (size_t p{}; p < a.rows; p++)
    for (size_t q{}; q < a.cols; q++)
      m(p, q) = a.elems[p][q];

  // perform addition
  for (size_t p{}; p < b.rows; p++)
    for (size_t q{}; q < b.cols; q++)
      m(p, q) += b.elems[p][q];

  return m;
}

Matrix::Matrix(size_t rows = 3, size_t cols = 3)
{

  Matrix::rows = rows;
  Matrix::cols = cols;

  elems = {new double *[rows] {}};

  for (size_t n{}; n < rows; n++)
    elems[n] = new double[cols]{};
}

Matrix::~Matrix()
{
  for (size_t n{}; n < rows; n++)
    delete[] elems[n];
  delete[] elems;
}

int main(void)
{

  Matrix m1{4, 5};
  Matrix m2{4, 5};
  //
  m1(1, 1) = 0.5;
  m1(2, 0) = -2.0;
  m1(2, 2) = 3.0;
  //
  m2(1, 1) = 1.5;
  m2(2, 0) = 1.0;
  m2(2, 2) = 2.0;
  m2(3, 0) = 0.25;

  Matrix m3 = m1 + m2;

  cout << m1 << endl;
  cout << m2 << endl;
  cout << m3 << endl;

  return EXIT_SUCCESS;
}