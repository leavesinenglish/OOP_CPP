#include "Complex.hpp"
#define _USE_MATH_DEFINES
#include <cmath>

static const double epsilon = 1e-7;

Complex::Complex(double re, double im) {
    _re = re;
    _im = im;
}

void Complex::Re(double re) {
    _re = re;
}

void Complex::Im(double im) {
    _im = im;
}

double Complex::Re() const {
    return _re;
}

double Complex::Im() const {
    return _im;
}

double Complex::Abs() const {
    return std::sqrt(_re * _re + _im * _im);
}

double Complex::Arg() const {
    if (std::abs(_re) <= epsilon) {
        if (_im > 0)
            return M_PI / 2;
        else if (_im < 0)
            return -M_PI / 2;
    }
    return atan2(_im, _re);
}

Complex Complex::Polar(double modulus, double argument) {
    return Complex(modulus * cos(argument), modulus * sin(argument));
}

Complex &Complex::operator=(double re) {
    _re = re;
    _im = 0;
    return *this;
}

Complex &Complex::operator+=(double re) {
    _re += re;
    return *this;
}

Complex &Complex::operator-=(double re) {
    _re -= re;
    return *this;
}

Complex &Complex::operator*=(double re) {
    _re *= re;
    _im *= re;
    return *this;
}

Complex &Complex::operator/=(double re) {
    _re /= re;
    _im /= re;
    return *this;
}

Complex &Complex::operator=(const Complex &val) = default;

Complex &Complex::operator+=(const Complex &val) {
    _re += val._re;
    _im += val._im;
    return *this;
}

Complex &Complex::operator-=(const Complex &val) {
    _re -= val._re;
    _im -= val._im;
    return *this;
}

Complex &Complex::operator*=(const Complex &val) {
    auto new_re = this->_re * val._re - this->_im * val._im;
    auto new_im = this->_re * val._im + this->_im * val._re;
    _re = new_re;
    _im = new_im;
    return *this;
}

Complex &Complex::operator/=(const Complex &val) {
    auto abs = val.Abs();
    auto new_re = (_re * val._re + _im * val._im) / (abs * abs);
    auto new_im = (_im * val._re - _re * val._im) / (abs * abs);
    _re = new_re;
    _im = new_im;
    return *this;
}

bool Complex::operator==(const Complex &right) const {
    return (fabs(_im - right._im) <= epsilon && fabs(_re - right._re) <= epsilon);
}

bool Complex::operator!=(const Complex &right) const {
    return !(this->operator==(right));
}

Complex Complex::operator+(const Complex &right) const {
    return Complex(_re + right._re, _im + right._im);
}

Complex Complex::operator-(const Complex &right) const {
    return Complex(_re - right._re, _im - right._im);
}

Complex Complex::operator*(const Complex &right) const {
    return Complex(_re * right._re - _im * right._im, _re * right._im + _im * right._re);
}

Complex Complex::operator/(const Complex &right) const {
    auto abs = right.Abs();
    return Complex((_re * right._re + _im * right._im) / (abs * abs), (_im * right._re - _re * right._im) / (abs * abs));
}

Complex Complex::sqrt() const {
    auto abs = Abs();
    auto arg = Arg();
    return Complex(std::sqrt(abs) * cos(arg / 2), std::sqrt(abs) * sin(arg / 2));
}

Complex Complex::pow(int pow) const {
    auto abs = Abs();
    auto arg = Arg();
    return Complex(std::pow(abs, pow) * cos(arg * pow), std::pow(abs, pow) * sin(arg * pow));
}