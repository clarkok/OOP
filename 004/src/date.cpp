#include "date.h"

#include <cstdio>

using namespace OOP;

Date::Date()
: Date(std::time(0))
{ }

Date::Date(const std::string &str)
: Date(std::time(0))
{
#define update_three()  \
year = t_year;    \
month = t_month;  \
day = t_day;      \
return;

#define update_two()  \
month = t_month;  \
day = t_day;      \
return;

#define update_one()  \
day = t_day;      \
return;

  int t_year, t_month, t_day;
  if (3 == std::sscanf(
    str.c_str(),
    "%d-%d-%d",
    &t_year,
    &t_month,
    &t_day
    )) {
    update_three()
  }
  else if (2 == std::sscanf(
    str.c_str(),
    "%d-%d",
    &t_month,
    &t_day
    )) {
    update_two()
  }
  else if (1 == std::sscanf(
    str.c_str(),
    "%d",
    &t_day
    )) {
    update_one()
  }
  else {}
  
#undef update_three
#undef update_two
#undef update_one
}

Date::Date(const Date &date)
: year(date.year), month(date.month), day(date.day)
{ }

Date::Date(std::time_t current)
{
  auto now = localtime(&current);
  year = now->tm_year + 1900;
  month = now->tm_mon + 1;
  day = now->tm_mday;
}

std::string
Date::toString() const
{
  return 
    std::to_string(year) + "-" +
    std::to_string(month) + "-" +
    std::to_string(day);
}

bool
OOP::operator < (const Date &a, const Date &b)
{
  if (a.year != b.year)
    return a.year < b.year;
  if (a.month != b.month)
    return a.month < b.month;
  return a.day < b.day;
}

bool
OOP::operator == (const Date &a, const Date &b)
{
  return (
    a.year == b.year &&
    a.month == b.month &&
    a.day == b.day
  );
}