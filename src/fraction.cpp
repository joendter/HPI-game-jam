#ifndef FRACTION_CPP
#define FRACTION_CPP
#include <iostream>
#include <numeric> // for std::gcd in C++17
#include <stdexcept>
class Fraction {
  public:
    Fraction(long numerator = 0, int denominator = 1)
        : numerator_(numerator), denominator_(denominator) {
        if (denominator == 0) {
            throw std::invalid_argument("Denominator cannot be zero");
        }
        reduce();
    }

    // Getter functions
    long getNumerator() const { return numerator_; }
    long getDenominator() const { return denominator_; }

    // Arithmetic operations
    Fraction operator+(const Fraction &other) const {
        long common_denominator = std::lcm(denominator_, other.denominator_);
        long new_numerator =
            numerator_ * (common_denominator / denominator_) +
            other.numerator_ * (common_denominator / other.denominator_);
        return Fraction(new_numerator, common_denominator);
    }

    Fraction operator-(const Fraction &other) const {
        long common_denominator = std::lcm(denominator_, other.denominator_);
        long new_numerator =
            numerator_ * (common_denominator / denominator_) -
            other.numerator_ * (common_denominator / other.denominator_);
        return Fraction(new_numerator, common_denominator);
    }

    Fraction operator*(const Fraction &other) const {
        return Fraction(numerator_ * other.numerator_,
                        denominator_ * other.denominator_);
    }

    Fraction operator/(const Fraction &other) const {
        if (other.numerator_ == 0) {
            throw std::invalid_argument("Cannot divide by zero fraction");
        }
        return Fraction(numerator_ * other.denominator_,
                        denominator_ * other.numerator_);
    }

    Fraction &operator*=(const Fraction &other) {
        numerator_ *= other.numerator_;
        denominator_ *= other.denominator_;
        reduce();
        return *this;
    }
    // Overloaded /= operator for division
    Fraction &operator/=(const Fraction &other) {
        numerator_ *= other.denominator_;
        denominator_ *= other.numerator_;
        reduce();
        return *this;
    }


    // Comparison operators
    bool operator==(const Fraction &other) const {
        return numerator_ == other.numerator_ &&
               denominator_ == other.denominator_;
    }

    bool operator<(const Fraction &other) const {
        return numerator_ * other.denominator_ <
               other.numerator_ * denominator_;
    }

    bool operator>(const Fraction &other) const {
        return numerator_ * other.denominator_ >
               other.numerator_ * denominator_;
    }

    bool operator<=(const Fraction &other) const {
        return numerator_ * other.denominator_ <=
               other.numerator_ * denominator_;
    }

    bool operator>=(const Fraction &other) const {
        return numerator_ * other.denominator_ >=
               other.numerator_ * denominator_;
    }

    operator float() const { return (float)numerator_ / denominator_; }

    // Overload the << operator for easy output
    friend std::ostream &operator<<(std::ostream &os,
                                    const Fraction &fraction) {
        os << fraction.numerator_ << '/' << fraction.denominator_;
        return os;
    }

  private:
    long numerator_;
    long denominator_;

    // Utility function to reduce the fraction
    void reduce() {
        long gcd = std::gcd(numerator_, denominator_);
        numerator_ /= gcd;
        denominator_ /= gcd;
        // Ensure the denominator is positive
        if (denominator_ < 0) {
            numerator_ = -numerator_;
            denominator_ = -denominator_;
        }
    }
};
#endif
