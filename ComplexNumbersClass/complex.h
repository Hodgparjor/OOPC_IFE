#pragma once
#include <iostream>

using namespace std;

class Complex {
  public:
	Complex();
	~Complex();
	Complex(double real = 0, double imaginary = 0);
	Complex(const Complex& c1);
	Complex& operator=(const Complex& c1);
	Complex& operator+=(const Complex& c1);
	Complex& operator-=(const Complex& c1);
	Complex& operator*=(const Complex& c1);
	Complex& operator/=(const Complex& c1);
	double getReal();
	void setReal(double newReal);
	double getImaginary();
	void setImaginary(double newImaginary);
	double getMagnitude();
	double getPhase();

  private:
	double imaginaryPart;
	double realPart;
};

Complex operator+(Complex c1, Complex c2);
Complex operator-(Complex c1, Complex c2);
Complex operator*(Complex c1, Complex c2);
Complex operator/(Complex c1, Complex c2);
bool operator==(Complex c1, Complex c2);
bool operator!=(Complex c1, Complex c2);
ostream& operator<<(ostream& s, const Complex c);