#include "matrix.h"

using namespace std;

//CONSTRUCTORS & DESTRUCTORS

Matrix::Matrix(size_t numberOfRows, size_t numberOfColumns) {
    data = new MatrixData(numberOfRows, numberOfColumns);
}

Matrix::~Matrix() {
    if (--(data->numberOfReferences) == 0) {
        delete data;
    }
}

Matrix::Matrix(const Matrix& matrix) {
    matrix.data->numberOfReferences++;
    data = matrix.data;
}

Matrix::Matrix(string fileName) {
    ifstream file;
    file.open(fileName);
    if(!file.is_open()) {
        throw FailedToOpenFileException();
    }
    
    size_t newRows, newColumns;
    file >> newRows >> newColumns;
    data = new MatrixData(newRows, newColumns);
    for (size_t rowIndex = 0; rowIndex < newRows; rowIndex++) {
        for (size_t columnIndex = 0; columnIndex < newColumns; columnIndex++) {
            if(file.eof()) {
                file.close();
                delete data;
                throw InvalidDataInFileException();
            }
            file >> data->elements[rowIndex][columnIndex];
        }
    }
    file.close();
}

//PRIVATE ACCESS

size_t Matrix::getNumberOfRows() const {
    return data->numberOfRows;
}

size_t Matrix::getNumberOfColumns() const {
    return data->numberOfColumns;
}

size_t Matrix::getNumberOfReferences() const {
    return data->numberOfReferences;
}


//ARITHMETIC OPERATOR OVERLOADING

Matrix& Matrix::operator=(const Matrix& matrix) {
    if(&matrix == this) {
        return *this;
    }

    if(--(this->data->numberOfReferences) == 0) {
        delete data;
    }
    matrix.data->numberOfReferences++;
    this->data = matrix.data;
    return *this;
}

Matrix& Matrix::operator+=(const Matrix& matrix) {
    if(!(this->getNumberOfRows() == matrix.getNumberOfRows() && this->getNumberOfColumns() == matrix.getNumberOfColumns())) {
        throw InvalidMatrixSizesException();
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
        throw InvalidMatrixSizesException();
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
    this->data->detach();
    *this = *this * matrix;
    return *this;
}

Matrix matrixMultiplication(const Matrix& matrix1, const Matrix& matrix2) {
    if(!(matrix1.getNumberOfColumns() == matrix2.getNumberOfRows())) {
        throw InvalidMatrixSizesException();
    }
    Matrix resultMatrix(matrix1.getNumberOfRows(), matrix2.getNumberOfColumns());
    for (size_t rowIndex = 0; rowIndex < resultMatrix.getNumberOfRows(); rowIndex++) {
        for (size_t colIndex1 = 0; colIndex1 < resultMatrix.getNumberOfColumns(); colIndex1++) {
            for (size_t colIndex2 = 0; colIndex2 < matrix1.getNumberOfColumns(); colIndex2++) {
                resultMatrix.data->elements[rowIndex][colIndex1] += matrix1.data->elements[rowIndex][colIndex2] * matrix2.data->elements[colIndex2][colIndex1];
            }
        }
    }
    return resultMatrix;
}

Matrix numberMultiplication(const Matrix& matrix, double number) {
    Matrix resultMatrix = matrix;
    for (size_t rowIndex = 0; rowIndex < matrix.getNumberOfRows(); rowIndex++) {
        for (size_t colIndex = 0; colIndex < matrix.getNumberOfColumns(); colIndex++) {
            resultMatrix.data->elements[rowIndex][colIndex] = matrix.data->elements[rowIndex][colIndex] * number;
        }
    }
    return resultMatrix;
}

Matrix operator*(const Matrix& matrix1, const Matrix& matrix2) {
    if(matrix1.getNumberOfColumns() == 1 && matrix1.getNumberOfRows() == 1) {
        return numberMultiplication(matrix2, matrix1.data->elements[0][0]);
    } else if (matrix2.getNumberOfColumns() == 1 && matrix2.getNumberOfReferences() == 1) {
        return numberMultiplication(matrix1, matrix2.data->elements[0][0]);
    } else {
        return matrixMultiplication(matrix1, matrix2);
    }
}

Matrix operator+(const Matrix& matrix1, const Matrix& matrix2) {
    Matrix resultMatrix = matrix1;
    resultMatrix += matrix2;
    return resultMatrix;
}

Matrix operator-(const Matrix& matrix1, const Matrix& matrix2) {
    Matrix resultMatrix = matrix1;
    resultMatrix -= matrix2;
    return resultMatrix;
}

// BOOLEAN OPERATOR OVERLOADING

bool operator==(const Matrix& matrix1, const Matrix& matrix2) {
    if(!(matrix1.getNumberOfRows() == matrix2.getNumberOfRows() && matrix1.getNumberOfColumns() == matrix2.getNumberOfColumns())) {
        return false;
    }
    for (size_t rowIndex = 0; rowIndex < matrix1.getNumberOfRows(); rowIndex++) {
        for (size_t colIndex = 0; colIndex < matrix1.getNumberOfColumns(); colIndex++) {
            if(matrix1.data->elements[rowIndex][colIndex] != matrix2.data->elements[rowIndex][colIndex]) {
                return false;
            }
        }
    }
    return true;
}

bool operator!=(const Matrix& matrix1, const Matrix& matrix2) {
    return !(matrix1 == matrix2);
}

//WRITING, READING, OUTPUT STREAM
MatrixReferenceHandler Matrix::operator()(size_t row, size_t column) {
    if(row < 0 || row >= this->data->numberOfRows || column < 0 || column >= this->data->numberOfColumns) {
        throw MatrixIndexOutOfBoundariesException();
    }
    return MatrixReferenceHandler(this, row, column);
}

double Matrix::reading(size_t rowNumber, size_t columnNumber) const {
    return this->data->elements[rowNumber][columnNumber];
}

void Matrix::writing(size_t rowNumber, size_t columnNumber, double newValue) {
    this->data = this->data->detach();
    this->data->elements[rowNumber][columnNumber] = newValue;
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
// MATRIX DATA

Matrix::MatrixData::MatrixData(size_t initialColumns, size_t initialRows) {
    this->numberOfColumns = initialColumns;
    this->numberOfRows = initialRows;
    this->numberOfReferences = 1;
    this->elements = new double*[numberOfRows];
    for(size_t rowIndex = 0; rowIndex < this->numberOfRows; rowIndex++) {
        this->elements[rowIndex] = new double[this->numberOfColumns]();
    }
}

Matrix::MatrixData::~MatrixData() {
    for(size_t rowIndex = 0; rowIndex < this->numberOfRows; rowIndex++) {
        delete[] this->elements[rowIndex];
    }
    delete[] elements;
}

Matrix::MatrixData* Matrix::MatrixData::detach() {
    if(this->numberOfReferences == 1) {
        return this;
    }

    MatrixData* detachedData = new MatrixData(this->numberOfColumns, this->numberOfRows);
    for (size_t rowIndex = 0; rowIndex < this->numberOfRows; rowIndex++) {
        for (size_t colIndex = 0; colIndex < this->numberOfColumns; colIndex++) {
            detachedData->elements[rowIndex][colIndex] = this->elements[rowIndex][colIndex];
        }
    }
    this->numberOfReferences--;
    return detachedData;
}

// MATRIX REFERENCE HANDLING

MatrixReferenceHandler::MatrixReferenceHandler(Matrix* matrix, size_t row, size_t column) {
    this->matrix = matrix;
    this->row = row;
    this->column = column;
}

MatrixReferenceHandler::operator double() const {
    return this->matrix->reading(this->row, this->column);
}

void MatrixReferenceHandler::operator=(double newValue) {
    this->matrix->writing(this->row, this->column, newValue);
}


