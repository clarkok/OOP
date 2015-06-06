#include "fraction.h"

using namespace OOP;

int
Fraction::gcd (int a, int b)
{
  a = abs(a);
  b = abs(b);
  if (b == 0)
    return a;
  return gcd(b, a % b);
}

Fraction::Fraction(int a, int b)
: a(a), b(b)
{
  // Make b always >= zero
  if (b < 0) {
    a = -a;
    b = -b;
  }
  
  // Reduce this fraction
  auto t = gcd(a, b);
  a /= t;
  b /= t;
}

Fraction
Fraction::negative() const
{ return Fraction(-a, b); }

Fraction
Fraction::reserve() const
{ return Fraction(b, a); }

Fraction
Fraction::add(const Fraction &b) const
{ return Fraction(this->a * b.b + this->b * b.a, this->b * b.b); }

Fraction
Fraction::mul(const Fraction &b) const
{ return Fraction(this->a * b.a, this->b * b.b); }

std::string
Fraction::to_string() const
{
  return
    std::to_string(a) +
    '/' +
    std::to_string(b);
}

double
Fraction::to_double() const
{ return a / b; }

std::ostream &
OOP::operator << (std::ostream &os, OOP::Fraction f)
{ return os << f.to_string(); }