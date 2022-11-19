#include "Poly.h"
#include <iterator>

using namespace std;

PolyElement::PolyElement(double coefficent, int degree) {
    this->coefficent = coefficent;
    this->degree = degree;
}

PolyElement& PolyElement::operator=(double newCoefficent) {
    this->coefficent = newCoefficent;
    cout << this->coefficent << endl;
    return *this;
}

Poly::Poly() {
    this->numberOfElements = 0;
}

Poly::Poly(double coefficent) {
    this->numberOfElements = 1;
    this->elements.push_back(PolyElement(coefficent));
}

Poly::Poly(const Poly& p) {}

PolyElement& Poly::operator[](int insertedDegree) {
    PolyElement newElement(0, insertedDegree);
    if(this->numberOfElements == 0) {
        this->elements.push_back(newElement);
        this->numberOfElements++;
        return (elements.front());
    }
    list<PolyElement>::iterator it;
    for(it = elements.begin(); it != elements.end(); ++it) {
        if((*it).degree < insertedDegree) {
            elements.insert(it, newElement);
            numberOfElements++;
            return (*it);
        }
    }
    elements.push_back(newElement);
    numberOfElements++;
    return (elements.back());
}

// void Poly::display() {
//     list<PolyElement>::iterator it;
//     char sign;
//     for(it = elements.begin(); it != elements.end(); ++it) {
//         sign = '+';
//         if((*it).coefficent < 0) {
//             sign = '-';
//         }
//         cout << " \n" << sign << " " << abs((*it).coefficent) << "^" << (*it).degree;
//     }
// }

ostream& operator<<(ostream& out, const Poly& poly){
    list<PolyElement>::const_iterator it;
    char sign;
    for(it = poly.elements.begin(); it != poly.elements.end(); ++it) {
        sign = '+';
        if((*it).coefficent < 0) {
            sign = '-';
        }
        if((&(*it) == &(poly.elements.front()))) {
            if((*it).coefficent >= 0) {
                out << " " << abs((*it).coefficent);
            } else {
                out << sign << " " << abs((*it).coefficent);
            }
        }
        if(((*it).degree == 0)) {
            out << " " << sign << " " << abs((*it).coefficent);
        } else {
            out << " " << sign << " " << abs((*it).coefficent) << "x^" << (*it).degree;
        }
    }
    return out;
}