#include <iostream>
#include <stdexcept> // std::out_of_range
#include <numeric>   // std::gcd

#include "fraction.h"

Fraction::Fraction(int numerator, int denominator) : numerator_{numerator} {
    if (denominator == 0)
        throw std::invalid_argument("Invalid denominator value: " + denominator);
    denominator_ = denominator;
}

void Fraction::setNumerator(int numerator) noexcept {
    numerator_ = numerator;
}

void Fraction::setDenominator(int denominator) {
    if (denominator == 0)
        throw std::invalid_argument("Invalid denominator value: " + denominator);
    denominator_ = denominator;
}

Fraction Fraction::operator+(const Fraction& term) const {
    int newNumerator = denominator_ * term.numerator_ + numerator_ * term.denominator_;
    int newDenominator = denominator_ * term.denominator_;

    int gcd = std::gcd(newNumerator, newDenominator);
    newNumerator /= gcd;
    newDenominator /= gcd;

    return Fraction(newNumerator, newDenominator);
}

Fraction Fraction::operator*(const Fraction& factor) const {
    int newNumerator = numerator_ * factor.numerator_;
    int newDenominator = denominator_ * factor.denominator_;

    int gcd = std::gcd(newNumerator, newDenominator);
    newNumerator /= gcd;
    newDenominator /= gcd;

    return Fraction(newNumerator, newDenominator);
}
