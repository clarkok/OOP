#ifndef _OOP_DATE_H_
#define _OOP_DATE_H_

#include <cstdint>
#include <string>
#include <ctime>

namespace OOP {
  
  struct Date
  {
    std::int32_t year;
    std::int16_t month;
    std::int16_t day;
    
    Date();
    Date(const std::string &);
    Date(const Date &);
    Date(std::time_t);
    std::string toString() const;
  };
  
  bool operator < (const Date &, const Date &);
  bool operator == (const Date &, const Date &);
}

#endif // _OOP_DATE_H_