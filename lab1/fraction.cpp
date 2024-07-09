#include <iostream>
#include <cstring>
#include <cctype>

using namespace std;

#include "fraction.h"

Fraction::Fraction() : fractionName_("Maciej"){
    numerator_ = 0;
    denominator_ = 1;
}

Fraction::Fraction(int num, int denom, const string name) : fractionName_(name){
    numerator_ = num;
    denominator_ = denom;
}

Fraction::~Fraction(){
    removedFractions_++;
}

int Fraction::getNumerator() const{
    return numerator_;
}

int Fraction::getDenominator() const{
    return denominator_;
}

void Fraction::setNumerator(int num){
    numerator_ = num;
}

void Fraction::setDenominator(int denom){
    denominator_ = denom;
}

void Fraction::print() const{
    cout << numerator_ << "/" << denominator_ << "\n";
}

int Fraction::removedFractions_ = 0;

int Fraction::removedFractions(){
    return removedFractions_;
}

void Fraction::save(ostream& os) const{
    os << numerator_ << "/" << denominator_;
}

void Fraction::load(istream& is){
    string reader;
    std::getline(is, reader, '/');
    numerator_ = stoi(reader);
    is >> reader;
    denominator_ = stoi(reader);
}

string Fraction::getFractionName() const{
    return fractionName_;
}

int Fraction::getInvalidDenominatorValue(){
    return invalidDenominatorValue;
}
