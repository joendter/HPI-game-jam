#ifndef FRACTION_H
#define FRACTION_H
#include <iostream>
#include <numeric> // for std::gcd in C++17
#include <stdexcept>
class Fraction {
  public:
    Fraction(long numerator = 0, long denominator = 1);

    // Getter functions
    long getNumerator() const ;
    long getDenominator() const ;

    // Arithmetic operations
    Fraction operator+(const Fraction &other) const ;
    Fraction operator-(const Fraction &other) const ;
    Fraction operator*(const Fraction &other) const ;
    Fraction operator/(const Fraction &other) const ;
    

    Fraction &operator*=(const Fraction &other) ;
    Fraction &operator/=(const Fraction &other) ;

    // Comparison operators
    bool operator==(const Fraction &other) const ;
    bool operator<(const Fraction &other) const ;
    bool operator>(const Fraction &other) const ;
    bool operator<=(const Fraction &other) const ;
    bool operator>=(const Fraction &other) const ;

    operator float() const ;

    // Overload the << operator for easy output
    friend std::ostream &operator<<(std::ostream &os,
                                    const Fraction &fraction) ;
  private:
    long numerator_;
    long denominator_;

    // Utility function to reduce the fraction
    void reduce() ;

};
#endif
