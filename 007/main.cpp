#include <iostream>

#include "vector.h"

using namespace OOP;
using namespace std;

#define CHECK_EQ(expect, actual, onsucceed, onfailed) \
  do {                                                \
    if ((expect) == (actual))                         \
      do { onsucceed } while (0);                     \
    else                                              \
      do { onfailed } while (0);                      \
  } while (0)

int
main()
{
  Vector<int> uut;

  CHECK_EQ(0, uut.size(), 
    { cout << "Constructed Succeed" << endl; },
    { cout << "Constructed Failed" << endl; }
  );

  try {
    auto t = uut[0];

    // will not exec
    CHECK_EQ(0, t, {;}, {;});
  }
  catch (const IndexOutofBounds &) {
    CHECK_EQ(true, true,
      { cout << "IndexOutofBounds Throwed Succeed" << endl; },
      { cout << "IndexOutofBounds Throwed Failed" << endl; }
    );
  }

  uut.resize(10);
  CHECK_EQ(10, uut.capacity(),
    { cout << "Resize capacity checked Succeed" << endl; },
    { cout << "Resize capacity checked Failed" << endl; }
  );
  CHECK_EQ(0, uut.size(),
    { cout << "Resize size checked Succeed" << endl; },
    { cout << "Resize size checked Failed" << endl; }
  );

  uut.push_back(10);
  CHECK_EQ(10, uut[0],
    { cout << "Index Succeed" << endl; },
    { cout << "Index Failed" << endl; }
  );

  uut.resize(-5);
  CHECK_EQ(5, uut.capacity(),
    { cout << "Resize with content capacity checked Succeed" << endl; },
    { cout << "Resize with content capacity checked Failed" << endl; }
  );
  CHECK_EQ(1, uut.size(),
    { cout << "Resize with content size checked Succeed" << endl; },
    { cout << "Resize with content size checked Failed" << endl; }
  );
  CHECK_EQ(10, uut[0],
    { cout << "Resize with content index Succeed" << endl; },
    { cout << "Resize with content index Failed" << endl; }
  );

  return 0;
}
