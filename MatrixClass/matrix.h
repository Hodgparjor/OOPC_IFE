#pragma once
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class MatrixReferenceHandler;
class Matrix;

class InvalidMatrixSizesException : public exception {
  public:
    const char* what() const throw() {
      return "Matrixes have dimensions invalid for performed operation.";
    }
};

class MatrixIndexOutOfBoundariesException : public exception {
  public:
    const char* what() const throw() {
      return "Index is out of boundaries of matrix";
    }
};

class FailedToOpenFileException : public exception {
  public:
    const char* what() const throw() {
      return "File is not open.";
    }
};

class InvalidDataInFileException : public exception {
  public:
    const char* what() const throw() {
      return "Data in file does not match matrix dimensions.";
    }
};

class Matrix {
  public:
    Matrix(size_t numberOfRows = 1, size_t numberOfColumns = 1);
    Matrix(string fileName);
    Matrix(const Matrix& matrix);
    ~Matrix();
    size_t getNumberOfRows() const;
    size_t getNumberOfColumns() const;
    size_t getNumberOfReferences() const;
    
    Matrix& operator=(const Matrix& matrix);
    Matrix& operator+=(const Matrix& matrix);
    Matrix& operator-=(const Matrix& matrix);
    Matrix& operator*=(const Matrix& matrix);
    friend Matrix matrixMultiplication(const Matrix& matrix1, const Matrix& matrix2);
    friend Matrix numberMultiplication(const Matrix& matrix, double number);
    friend Matrix operator+(const Matrix& matrix1, const Matrix& matrix2);
    friend Matrix operator-(const Matrix& matrix1, const Matrix& matrix2);
    friend Matrix operator*(const Matrix& matrix1, const Matrix& matrix2);
    friend bool operator==(const Matrix& matrix1, const Matrix& matrix2);
    friend bool operator!=(const Matrix& matrix1, const Matrix& matrix2);
    friend ostream& operator<<(ostream& out, const Matrix& matrix);
    friend class MatrixReferenceHandler;
    MatrixReferenceHandler operator()(size_t rowNumber, size_t columnNumber);
  private:
    struct MatrixData;
    MatrixData* data;
    double reading(size_t rowNumber, size_t columnNumber) const;
    void writing(size_t rowNumber, size_t columnNumber, double newValue);
};

struct Matrix::MatrixData {
  size_t numberOfRows;
  size_t numberOfColumns;
  double** elements;
  size_t numberOfReferences;

  MatrixData(size_t initialColumns, size_t initialRows);
  ~MatrixData();
  MatrixData* detach();
};

class MatrixReferenceHandler {
  public:
    MatrixReferenceHandler(Matrix* matrix, size_t row, size_t column);
    operator double() const;
    void operator=(double number);
    Matrix* matrix;
    size_t row;
    size_t column;
};