#include "Poly.h"
#include <iterator>
#include <string>
#include <math.h>

using namespace std;

// --- CONSTRUCTORS ---

PolyElement::PolyElement(double coefficent, int degree) {
    this->coefficent = coefficent;
    this->degree = degree;
}

Poly::Poly() {
    this->numberOfElements = 0;
}

Poly::Poly(double coefficent) {
    Poly newPoly;
    newPoly[0] = coefficent;
    this->elements = newPoly.elements;
    this->numberOfElements = newPoly.numberOfElements;
}

Poly::Poly(const Poly& p) {
    this->numberOfElements = p.numberOfElements;
    this->elements = list<PolyElement>(p.elements);
}

// --- OPERATOR OVERLOADING ---

PolyElement& PolyElement::operator=(double newCoefficent) {
    this->coefficent = newCoefficent;
    return *this;
}

PolyElement& Poly::operator[](int insertedDegree) {
    if(this->numberOfElements == 0) {
        PolyElement newElement(0, insertedDegree);
        this->elements.push_back(newElement);
        this->numberOfElements++;
        return (elements.front());
    }
    list<PolyElement>::iterator it;
    bool inserted = false;
    for(it = elements.begin(); it != elements.end() && inserted == false; ++it) {
        if ((*it).degree == insertedDegree) {
            inserted = true;
            return (*it);
        } else if((*it).degree < insertedDegree) {
            inserted = true;
            PolyElement newElement(0, insertedDegree);
            elements.insert(it, newElement);
            numberOfElements++;
            return (*(--it));
        }
    }
    PolyElement newElement(0, insertedDegree);
    elements.push_back(newElement);
    numberOfElements++;
    return (elements.back());
}

Poly operator+(const Poly& p1, const Poly& p2) {
    Poly newPoly(p1);
    list<PolyElement>::const_iterator it2;
    list<PolyElement>::iterator it1;
    bool foundMatch = false;
    for(it2 = p2.elements.begin(); it2!= p2.elements.end(); ++it2) {
        foundMatch = false;
        for(it1 = newPoly.elements.begin(); it1!= newPoly.elements.end() && !foundMatch; ++it1) {
            if((*it2).degree == (*it1).degree) {
                newPoly[(*it2).degree] = (*it1).coefficent + (*it2).coefficent;
                foundMatch = true;
            }
        }
        if(!foundMatch) {
            newPoly[(*it2).degree] = (*it2).coefficent;
        }
    }
    return newPoly;
}

Poly operator-(const Poly& p1, const Poly& p2) {
    Poly newPoly(p1);
    list<PolyElement>::const_iterator it2;
    list<PolyElement>::iterator it1;
    bool foundMatch = false;
    for(it2 = p2.elements.begin(); it2!= p2.elements.end(); ++it2) {
        foundMatch = false;
        for(it1 = newPoly.elements.begin(); it1!= newPoly.elements.end() && !foundMatch; ++it1) {
            if((*it2).degree == (*it1).degree) {
                newPoly[(*it2).degree] = (*it1).coefficent - (*it2).coefficent;
                foundMatch = true;
            }
        }
        if(!foundMatch) {
            newPoly[(*it2).degree] = -(*it2).coefficent;
        }
    }
    return newPoly;
}

Poly Poly::operator-() const {
    Poly newPoly;
    list<PolyElement>::const_iterator it;
    for(it = this->elements.begin(); it != this->elements.end(); ++it) {
        newPoly[(*it).degree] = -(*it).coefficent;
    }
    return newPoly;
}

double Poly::operator()(double xval) const {
    double result = 0;
    list<PolyElement>::const_iterator it;
    for(it = this->elements.begin(); it != this->elements.end(); ++it) {
        result += (pow(xval, (*it).degree) * (*it).coefficent);
    }
    return result;
}

Poly operator*(const Poly& p1, const Poly& p2) {
    Poly resultPoly;
    list<PolyElement>::const_iterator it2;
    list<PolyElement>::const_iterator it1;

    for(it2 = p2.elements.begin(); it2!= p2.elements.end(); ++it2) {
        Poly tmpPoly;
        for(it1 = p1.elements.begin(); it1!= p1.elements.end(); ++it1) {
            int newDegree = (*it1).degree + (*it2).degree;
            double newCoefficent = (*it1).coefficent * (*it2).coefficent;
            tmpPoly[newDegree] = newCoefficent;
        }
        resultPoly = resultPoly + tmpPoly;
    }
    return resultPoly;
}
// --- OUTPUT STREAM ---

list<PolyElement> getListToPrint(const Poly& poly) {
    list<PolyElement>::const_iterator it;
    list<PolyElement> outputList;
    int numberOfElements = 0;
    for(it = poly.elements.begin(); it != poly.elements.end(); ++it) {
        if(!((*it).coefficent == 0)) {
            outputList.push_back((*it));
            numberOfElements++;
        }
    }
    if((numberOfElements == 0) && (poly.elements.front().degree == 0)) {
        outputList.push_front(poly.elements.front());
    }
    return outputList;
}

string BaseOutputElement(const PolyElement& element) {
    string output;
    if(element.coefficent != 1) {
        output = to_string(abs(element.coefficent));
    }
    output.erase(output.find_last_not_of('0') + 1, string::npos);
    output.erase(output.find_last_not_of('.') + 1, string::npos);
    if(element.degree == 1) {
        output += "x";
    } else if(element.degree > 1) {
        output += "x^" + to_string(element.degree);
    }
    return output;
}

string outputFirstElement(const PolyElement& element, string sign) {
    string output;
    if(element.coefficent >= 0) {
        output =  " ";
    } else {
        output = sign + " ";
    }
    output += BaseOutputElement(element);
    return output;
}

string outputElement(const PolyElement& element, string sign) {
    string output;
    output = " " + sign + " ";
    output += BaseOutputElement(element);
    return output;
}

string getSign(double coefficent) {
    if(coefficent >= 0) {
        return "+";
    } else {
        return "-";
    }
}

ostream& operator<<(ostream& out, const Poly& poly){
    list<PolyElement>::iterator it;
    list<PolyElement> outputList = getListToPrint(poly);
    if(outputList.size() == 0) {
        out << 0;
    }
    string sign;
    for(it = outputList.begin(); it != outputList.end(); ++it) {
        if((*it).coefficent != 0) {
            sign = getSign((*it).coefficent);
            if((&(*it) == &(outputList.front()))) {
                out << outputFirstElement((*it), sign);
            } else {
                out << outputElement((*it), sign);
            }
        }
    }
    return out;
}