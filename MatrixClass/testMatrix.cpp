#include "matrix.h"

using namespace std;

void testCompoundAddition();
void testCompoundSubstraction();
void testCompoundMultiplication();
void testCompoundOperators();
void testAddition(const Matrix& m1, const Matrix& m2);
void testBracketsOperator();
void testSubstraction(const Matrix& m1, const Matrix& m2);
void testMultiplication(const Matrix& m1, const Matrix& m2);
void testRegularOperators();
void testExceptions();
void testInvalidMatrixSizesException();
void testMatrixIndexOutOfBoundariesException();
void testFailedToOpenFileException();
void testInvalidDataInFileException();
void testReferenceCounting();

int main() {
	testBracketsOperator();
    testCompoundOperators();
    testRegularOperators();
    testExceptions();
    testReferenceCounting();
}

void testCompoundAddition() {
    cout << "Compound addition: ";
    Matrix m1(2, 2);
    m1(0, 0) = 1;
    m1(0, 1) = 3;
    m1(1, 0) = 5;
    m1(1, 1) = 7;
    Matrix m2(2, 2);
    m2(0, 0) = 2;
    m2(0, 1) = 4;
    m2(1, 0) = 6;
    m2(1, 1) = 8;
    
    Matrix properResult(2, 2);
    properResult(0, 0) = 3;
    properResult(0, 1) = 7;
    properResult(1, 0) = 11;
    properResult(1, 1) = 15;
    m1 += m2;
    if (m1 != properResult) {
        cout << "FAILED" << endl;
    }
    else {
        cout << "PASSED" << endl;
    }
}

void testBracketsOperator() {
	Matrix m1("m1.txt");
	Matrix m2("m2.txt");
	cout << "m1:\n" << m1 << endl;
	cout << "m2:\n" << m2 << endl;
	m1(0, 0) = m2(1, 1);
	Matrix properResult(m1);
    properResult(0, 0) = 8;
	cout << "Modified m1:\n" << m1 << endl;
}

void testCompoundSubstraction() {
    cout << "Compound substraction: ";
    Matrix m1("m1.txt");
    Matrix m2("m2.txt");
    Matrix properResult(2,2);
    properResult(0, 0) = -4;
    properResult(0, 1) = -4;
    properResult(1, 0) = -4;
    properResult(1, 1) = -4;
    m1 -= m2;
    if (m1 != properResult) {
        cout << "FAILED" << endl;
    } else {
        cout << "PASSED" << endl;
    }
}

void testCompoundMultiplication() {
    cout << "Compound multiplication: ";
    Matrix m1("m1.txt");
    Matrix m2("m2.txt");
    Matrix properResult(2,2);
    properResult(0, 0) = 19;
    properResult(0, 1) = 22;
    properResult(1, 0) = 43;
    properResult(1, 1) = 50;
    m1 *= m2;
    if (m1 != properResult) {
        cout << "FAILED" << endl;
    } else {
        cout << "PASSED" << endl;
    }
}

void testCompoundOperators() {
    testCompoundAddition();
    testCompoundSubstraction();
    testCompoundMultiplication();
}

void testAddition(const Matrix& m1, const Matrix& m2) {
    cout << "Regular addition: ";
    Matrix properResult(2,2);
    properResult(0, 0) = 6;
    properResult(0, 1) = 8;
    properResult(1, 0) = 10;
    properResult(1, 1) = 12;
    if ((m1 + m2) != properResult) {
        cout << "FAILED" << endl;
    } else {
        cout << "PASSED" << endl;
    }
}

void testSubstraction(const Matrix& m1, const Matrix& m2) {
    cout << "Regular substraction: ";
    Matrix properResult(2,2);
    properResult(0, 0) = -4;
    properResult(0, 1) = -4;
    properResult(1, 0) = -4;
    properResult(1, 1) = -4;
    if ((m1 - m2) != properResult) {
        cout << "FAILED" << endl;
    } else {
        cout << "PASSED" << endl;
    }
}

void testMultiplication(const Matrix& m1, const Matrix& m2) {
    cout << "Regular multiplication: ";
    Matrix properResult(2,2);
    properResult(0, 0) = 19;
    properResult(0, 1) = 22;
    properResult(1, 0) = 43;
    properResult(1, 1) = 50;
    if ((m1 * m2) != properResult) {
        cout << "FAILED" << endl;
    } else {
        cout << "PASSED" << endl;
    }
}

void testRegularOperators() {
    Matrix m1("m1.txt");
    Matrix m2("m2.txt");
    testAddition(m1, m2);
    testSubstraction(m1, m2);
    testMultiplication(m1, m2);
}

void testExceptions() {
    testInvalidMatrixSizesException();
    testMatrixIndexOutOfBoundariesException();
    testFailedToOpenFileException();
    testInvalidDataInFileException();
}

void testInvalidMatrixSizesException() {
    cout << "InvalidMatrixSizesException: ";
    Matrix m1(2, 1);
    Matrix m2(1, 2);
    try {
        m1 += m2;
        cout << "FAILED" << endl;
    } catch (InvalidMatrixSizesException& e) {
        cout << "PASSED" << endl;
    }
}

void testMatrixIndexOutOfBoundariesException() {
    cout << "MatrixIndexOutOfBoundariesException: ";
    Matrix m(1, 2);
    try {
        m(1, 2);
        cout << "FAILED" << endl;
    } catch (MatrixIndexOutOfBoundariesException& e) {
        cout << "PASSED" << endl;
    }
}

void testFailedToOpenFileException() {
    cout << "FailedToOpenFileException: ";
    try {
        Matrix m("thisFileDoesNotExists.txt");
        cout << "FAILED" << endl;
    } catch (FailedToOpenFileException& e) {
        cout << "PASSED" << endl;
    }
}

void testInvalidDataInFileException() {
    cout << "InvalidDataInFileException: ";
    try {
        Matrix m("5x5InvalidMatrix.txt");
        cout << "FAILED" << endl;
    } catch (InvalidDataInFileException& e) {
        cout << "PASSED" << endl;
    }
}

void testReferenceCounting() {
    cout << "Reference counting: ";
    Matrix m1("m1.txt");
    Matrix m2("m2.txt");
    Matrix m3(m1);
    m2 = m3;
    if(m1.getNumberOfReferences() != 3) {
        cout << "FAILED" << endl;
        return;
    }
    m2(0, 1) = 16;
    if(m1.getNumberOfReferences() != 2) {
        cout << "FAILED" << endl;
    } else {
        cout << "PASSED" << endl;
    }
}
