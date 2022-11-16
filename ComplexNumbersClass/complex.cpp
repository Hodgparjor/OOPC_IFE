#include "complex.h"
#include <math.h>

Complex::~Complex() {}

Complex::Complex(double real, double imaginary) {
	this->realPart = real;
	this->imaginaryPart = imaginary;
}

Complex::Complex(const Complex& c1) {
	this->realPart = c1.realPart;
	this->imaginaryPart = c1.imaginaryPart;
}

Complex& Complex::operator=(const Complex& c1) {
	this->realPart = c1.realPart;
	this->imaginaryPart = c1.imaginaryPart;
	return *this;
}

ostream& operator<<(ostream& out, Complex complex) {
	char imaginarySign = '+';
	if (complex.getImaginary() < 0) {
		imaginarySign = '-';
	}
	out << complex.getReal() << " " << imaginarySign << " " << abs(complex.getImaginary()) << "i ";
	return out;
}

Complex& Complex::operator+=(const Complex& c1) {
	this->realPart = this->realPart + c1.realPart;
	this->imaginaryPart = this->imaginaryPart + c1.imaginaryPart;
	return *this;
}

Complex& Complex::operator-=(const Complex& c1) {
	this->realPart = this->realPart - c1.realPart;
	this->imaginaryPart = this->imaginaryPart - c1.imaginaryPart;
	return *this;
}

Complex& Complex::operator*=(const Complex& c1) {
	this->realPart = this->realPart * c1.realPart - this->imaginaryPart * c1.imaginaryPart;
	this->imaginaryPart = this->imaginaryPart * c1.realPart + this->realPart * c1.realPart;
	return *this;
}

Complex& Complex::operator/=(const Complex& c1) {
	this->realPart = (this->realPart * c1.realPart + this->imaginaryPart * c1.imaginaryPart) / (pow(c1.realPart, 2) + pow(c1.imaginaryPart, 2));
	this->imaginaryPart = (this->imaginaryPart * c1.realPart - this->realPart * c1.imaginaryPart) / (pow(c1.realPart, 2) + pow(c1.imaginaryPart, 2));
	return *this;
}

double Complex::getReal() {
	return this->realPart;
}

void Complex::setReal(double newReal) {
	this->realPart = newReal;
}

double Complex::getImaginary() {
	return this->imaginaryPart;
}

void Complex::setImaginary(double newImaginary) {
	this->imaginaryPart = newImaginary;
}

double Complex::getMagnitude()
{
	return(sqrt(pow(this->realPart, 2) + pow(this->imaginaryPart, 2)));
}

double Complex::getPhase()
{
    if(this->imaginaryPart != 0 || this->realPart > 0) {
        return(2 * atan(this->imaginaryPart / (this->getMagnitude() + this->realPart)));
    } else if(this->realPart < 0 && this->imaginaryPart == 0) {
        return M_PI;
    } else {
        cout << "Phase can't be caluclated" << endl;
        return 0;
    }
}

Complex operator+(Complex complex1, Complex complex2) {
	complex1 += complex2;
	return complex1;
}

Complex operator-(Complex complex1, Complex complex2) {
	complex1 -= complex2;
	return complex1;
}

Complex operator*(Complex complex1, Complex complex2) {
	complex1 *= complex2;
	return complex1;
}

Complex operator/(Complex complex1, Complex complex2) {
	complex1 /= complex2;
	return complex1;
}

bool operator==(Complex complex1, Complex complex2)
{
	if ((complex1.getReal() == complex2.getReal()) && (complex1.getImaginary() == complex2.getImaginary())) {
		return true;
	}
	else {
		return false;
	}
}

bool operator!=(Complex complex1, Complex complex2)
{
	if ((complex1.getReal() != complex2.getReal()) || (complex1.getImaginary() != complex2.getImaginary())) {
		return true;
	}
	else {
		return false;
	}
}