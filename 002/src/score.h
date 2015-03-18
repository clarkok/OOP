#ifndef _SCORE_H_
#define _SCORE_H_

#include <map>
#include <string>

namespace OOP {

/*!
 Score array of a student
 */
template <typename T_num>
class Score : public std::map<std::string, T_num>
{
public:
  /*!
   get score by index
   @param course course name
   @return the score
   */
  T_num
  getScoreByIndex(std::string course) const
  {
    auto p = this->find(course);
    if (p == this->end())
      return -1;
    else
      return p->second;
  }

  /*!
   set score by index
   @param course course name
   @param value new value
   @return the new value
   */
  T_num
  setScoreByIndex(std::string course, T_num value)
  {
    return this->operator[](course) = value;
  }
};

}

#endif
