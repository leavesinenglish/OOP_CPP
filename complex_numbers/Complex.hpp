#ifndef COMPLEX_COMPLEX_H
#define COMPLEX_COMPLEX_H

class Complex {
public:
    Complex() = default;
    Complex(double re, double im = 0);
    Complex(const Complex &val) = default;
    void Re(double re);
    void Im(double im);
    [[nodiscard]]
    double Re() const;
    [[nodiscard]]
    double Im() const;
    [[nodiscard]]
    double Abs() const;
    [[nodiscard]]
    double Arg() const;
    static Complex Polar(double modulus, double argument = 0);
    Complex &operator=(double re);
    Complex &operator+=(double re);
    Complex &operator-=(double re);
    Complex &operator*=(double re);
   Complex &operator/=(double re);
    Complex &operator=(const Complex &val);
    Complex &operator+=(const Complex &val);
    Complex &operator-=(const Complex &val);
    Complex &operator*=(const Complex &val);
    Complex &operator/=(const Complex &val);
    bool operator==(const Complex &right) const;
    bool operator!=(const Complex &right) const;
    Complex operator+(const Complex &right) const;
    Complex operator-(const Complex &right) const;
    Complex operator*(const Complex &right) const;
    Complex operator/(const Complex &right) const;
    [[nodiscard]]
    Complex sqrt() const;
    [[nodiscard]]
    Complex pow(int pow) const;

protected:
    double _re = 0;
    double _im = 0;

private:
};

#endif //COMPLEX_COMPLEX_H
