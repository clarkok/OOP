#ifndef _OOP_DATE_H_
#define _OOP_DATE_H_

#include <cstdint>
#include <string>
#include <ctime>

namespace OOP {
  
  struct Date
  {
    std::int32_t year;    // NOTE: to make the size of Date 8 bytes
    std::int16_t month;
    std::int16_t day;
    
    // make Date from today's date
    Date();

    // parse string to Date
    Date(const std::string &);

    // copy Date
    Date(const Date &);

    // convert std::time_t to Date
    Date(std::time_t);

    // convert Date to string
    std::string toString() const;
  };
  
  // Operators
  bool operator < (const Date &, const Date &);
  bool operator == (const Date &, const Date &);
}

#endif // _OOP_DATE_H_
