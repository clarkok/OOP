#include <iostream>
#include "fraction.h"

using namespace std;
using namespace OOP;

#define CHECK_EQ(expect, actual, onsuccess, onerror)  \
  do {                                                \
    if (expect == actual)                             \
      do { onsuccess } while (0);                     \
    else                                              \
      do { onerror } while (0);                       \
  } while (0)

int
main()
{
  Fraction uut;
  
  CHECK_EQ(0, uut.to_double(),
    { cout << "Default Constructor checked" << endl; },
    { cout << "Default Constructor failed" << endl; }
  );
  
  uut = Fraction(10);
  CHECK_EQ(10, uut.to_double(),
    { cout << "Constructor with one argument checked" << endl; },
    { cout << "Constructor with one argument failed" << endl; }
  );
  
  uut = Fraction(10, 2);
  CHECK_EQ(5, uut.to_double(),
    { cout << "Constructor with two argument checked" << endl; },
    { cout << "Constructor with two argument failed" << endl; }
  );
  
  {
    Fraction zero;
    CHECK_EQ(0, zero.to_double(),
      { cout << "Default constructor checked" << endl; },
      { cout << "Default constructor failed" << endl; }
    );
  }
  
  {
    Fraction a(1, 5), b(1, 3);
    auto res = a.add(b);
    CHECK_EQ("8/15", res.to_string(),
      { cout << "Add operation checked" << endl; },
      { cout << "Add operation failed, Actual" << res.to_string() << endl; }
    );
  }
  
  {
    Fraction a(1, 5), b(3);
    auto res = a.mul(b);
    CHECK_EQ("3/5", res.to_string(),
      { cout << "Mul operation checked" << endl; },
      { cout << "Mul operation failed, Actual" << res.to_string() << endl; }
    );
  }
  
  {
    Fraction uut(1);
    auto res = uut.negative();
    CHECK_EQ(-1, res.to_double(),
      { cout << "Negative checked" << endl; },
      { cout << "Negative failed, Actial " << res.to_string() << endl; }
    );
  }
  
  {
    Fraction uut(1, 5);
    auto res = uut.reserve();
    CHECK_EQ(5, res.to_double(),
      { cout << "Reserve checked" << endl; },
      { cout << "Reserve failed, Actial " << res.to_string() << endl; }
    );
  }
  
  {
    Fraction a(1, 5);
    auto res = a * 3 / 5 + 3 - 2;
    CHECK_EQ("28/25", res.to_string(),
      { cout << "Overall checked" << endl; },
      { cout << "Overall failed, Actial " << res.to_string() << endl; }
    );
  }
    
  return 0;
}