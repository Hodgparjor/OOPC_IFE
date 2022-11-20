#pragma once
#include <iostream>
#include <list>
using namespace std;


class PolyElement {
  public:      
    int degree;
    double coefficent;
    PolyElement(double coefficent = 0, int degree = 0);
    PolyElement& operator=(double coefficent);
};

class Poly {
  public:
    Poly();
    Poly(double coefficent);
    Poly(const Poly& p);
    PolyElement& operator[](int degree);
    double operator()(double xval) const;
    Poly operator-() const;
  private:
    list<PolyElement> elements;
    size_t numberOfElements;
  friend list<PolyElement> getListToPrint(const Poly& poly);
  friend ostream& operator<<(ostream& out, const Poly& poly);
  friend Poly operator+(const Poly& p1, const Poly& p2);
  friend Poly operator-(const Poly& p1, const Poly& p2);
  friend Poly operator*(const Poly& p1, const Poly& p2);
};
string BaseOutputElement(const PolyElement& element);
string outputFirstElement(const PolyElement& element, string sign);
string outputElement(const PolyElement& element, string sign);
string getSign(double coefficent);