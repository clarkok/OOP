#ifndef _OOP_ENTRY_H_
#define _OOP_ENTRY_H_

#include <vector>

#include "date.h"

namespace OOP {
  class Entries : public std::vector<Date>
  {
  public:
    Entries(const Date * begin, const Date * end)
    : std::vector<Date>(begin, end)
    { }
    
    void insertDate(Date);
  };
}

#endif // _OOP_ENTRY_H_