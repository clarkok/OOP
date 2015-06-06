#ifndef _OOP_FRACTION_H_
#define _OOP_FRACTION_H_

#include <iostream>
#include <string>

namespace OOP {
  class Fraction {
    int a, b;
    static int gcd(int, int);
  public:
    /**
     * Constructor
     * calling with no argument will initialize this fraction to zero
     * calling with one argument will initialize this fraction to the int argument
     * calling with two arguments will initialize this fraction to a / b
     */
    Fraction(int a = 0, int b = 1);
    
    /**
     * Return a fraction which negative from this
     */
    Fraction negative() const;
    
    /**
     * Return a fraction which exchange a and b of this
     */
    Fraction reserve() const;
    
    /**
     * Return a fraction which is the sum of this and the argument
     */
    Fraction add(const Fraction &) const;
    
    /**
     * Return a fraction which is the product of this and the argument
     */
    Fraction mul(const Fraction &) const;
    
    /**
     * Convert this to string
     */
    std::string to_string() const;
    
    /**
     * Convert this to double
     */
    double to_double() const;
  };
  
  /**
   * Insert this into a output stream
   */
  std::ostream &
  operator << (std::ostream &, Fraction);
  
  // Operaters
  inline Fraction
  operator + (Fraction a, Fraction b)
  { return a.add(b); }
  
  inline Fraction
  operator - (Fraction a, Fraction b)
  { return a.add(b.negative()); }
  
  inline Fraction
  operator * (Fraction a, Fraction b)
  { return a.mul(b); }
  
  inline Fraction
  operator / (Fraction a, Fraction b)
  { return a.mul(b.reserve()); }
}

#endif // _OOP_FRACTION_H_
