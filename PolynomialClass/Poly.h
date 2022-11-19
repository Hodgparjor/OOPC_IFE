#pragma once
#include <iostream>
#include <list>
using namespace std;


class PolyElement {
  public:      
    PolyElement(double coefficent = 0, int degree = 0);
    int degree;
    double coefficent;
    PolyElement& operator=(double coefficent);
};

class Poly {
  public:
    Poly();
    Poly(double coefficent);
    Poly(const Poly& p);
    PolyElement& operator[](int degree);
    void display();

  private:
    list<PolyElement> elements;
    size_t numberOfElements;
  friend ostream& operator<<(ostream& out, const Poly& poly);
};