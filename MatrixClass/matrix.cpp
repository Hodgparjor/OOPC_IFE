#include "matrix.h"

using namespace std;

Matrix::Matrix(size_t numberOfRows, size_t numberOfColumns) {
    data = new MatrixData(numberOfRows, numberOfColumns);
}

Matrix::~Matrix() {
    if (--(data->numberOfReferences) == 0) {
        delete data;
    }
}

size_t Matrix::getNumberOfRows() const {
    return data->numberOfRows;
}

size_t Matrix::getNumberOfColumns() const {
    return data->numberOfColums;
}

size_t Matrix::getNumberOfReferences() const {
    return data->numberOfReferences;
}

Matrix& Matrix::operator+=(const Matrix& matrix) {
    if(!(this->getNumberOfRows() == matrix.getNumberOfRows() && this->getNumberOfColumns() == matrix.getNumberOfColumns())) {
        throw DiffrentMatrixesDimentionsException();
    }
    this->data = this->data->detach();
    for (size_t rowIndex = 0; rowIndex < this->getNumberOfRows(); rowIndex++) {
        for (size_t colIndex = 0; colIndex < this->getNumberOfColumns(); colIndex++) {
            this->data->elements[rowIndex][colIndex] += matrix.data->elements[rowIndex][colIndex];
        }
    }
    return *this;
}

Matrix& Matrix::operator-=(const Matrix& matrix) {
    if(!(this->getNumberOfRows() == matrix.getNumberOfRows() && this->getNumberOfColumns() == matrix.getNumberOfColumns())) {
        throw DiffrentMatrixesDimentionsException();
    }
    this->data = this->data->detach();
    for (size_t rowIndex = 0; rowIndex < this->getNumberOfRows(); rowIndex++) {
        for (size_t colIndex = 0; colIndex < this->getNumberOfColumns(); colIndex++) {
            this->data->elements[rowIndex][colIndex] -= matrix.data->elements[rowIndex][colIndex];
        }
    }
    return *this;
}

Matrix& Matrix::operator*=(const Matrix& matrix) {
    //TODO
    return *this;
}

ostream& operator<<(ostream& out, const Matrix& matrix) {
    for (size_t rowIndex = 0; rowIndex < matrix.getNumberOfRows(); rowIndex++) {
        for (size_t colIndex = 0; colIndex < matrix.getNumberOfColumns(); colIndex++) {
            out << matrix.data->elements[rowIndex][colIndex] << " ";
        }
        out << endl;
    }
    return out;
}


