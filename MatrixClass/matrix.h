#pragma once
#include <iostream>
#include <math.h>

using namespace std;

class DiffrentMatrixesDimentionsException : public exception {
  public:
    const char* what() const throw() {
      return "Matrixes have diffrent dimensions";
    }
};

class MatrixIndexOutOfBoundariesException : public exception {
  public:
    const char* what() const throw() {
      return "Index is out of boundaries of matrix";
    }
};



class Matrix {
  public:
    Matrix(size_t numberOfRows = 1, size_t numberOfColumns = 1);
    Matrix(string file);
    Matrix(const Matrix& matrix);
    ~Matrix();
    size_t getNumberOfRows() const;
    size_t getNumberOfColumns() const;
    size_t getNumberOfReferences() const;
    
    Matrix& operator=(const Matrix& matrix);
    Matrix& operator+=(const Matrix& matrix);
    Matrix& operator-=(const Matrix& matrix);
    Matrix& operator*=(const Matrix& matrix);
    friend Matrix operator+(const Matrix& matrix1, const Matrix& matrix2);
    friend Matrix operator-(const Matrix& matrix1, const Matrix& matrix2);
    friend Matrix operator*(const Matrix& matrix1, const Matrix& matrix2);
    friend bool operator==(const Matrix& matrix1, const Matrix& matrix2);
    friend bool operator!=(const Matrix& matrix1, const Matrix& matrix2);
    friend ostream& operator<<(ostream& out, const Matrix& matrix);
    MatrixReferenceHandler operator()(size_t rowNumber, size_t columnNumber);
  private:
    struct MatrixData;
    MatrixData* data;
    double read(size_t rowNumber, size_t columnNumber) const;
};

struct Matrix::MatrixData {
  size_t numberOfRows;
  size_t numberOfColums;
  double** elements;
  size_t numberOfReferences;

  MatrixData(size_t initialColumns, size_t initialRows);
  ~MatrixData();
  MatrixData* detach();
};

class MatrixReferenceHandler {
  private:
    Matrix* matrix;
    size_t numberOfRows;
    size_t numberOfColumns;
  public:
  MatrixReferenceHandler(Matrix* matrix, size_t numberOfRows, size_t numberOfColumns);
  operator double() const;
  void operator=(double number);
};