#include "entry.h"

#include <algorithm>

using namespace OOP;

void
Entries::insertDate(Date d)
{
  auto i = std::lower_bound(begin(), end(), d);
  if (i == end() || !(*i == d)) {
    insert(i, d);
  }
}