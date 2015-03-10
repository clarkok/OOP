#ifndef _SCORE_H_
#define _SCORE_H_

#include <vector>

namespace OOP {

/*!
 Score array of a student
 */
template <typename T_num>
class Score : public std::vector<T_num>
{
public:
  /*!
   get score by index
   @param index index to get
   @return the score
   */
  T_num
  getScoreByIndex(int index) const
  {
    return this->at(index);
  }

  /*!
   set score by index
   @param index index to set
   @param value new value
   @return the new value
   */
  T_num
  setScoreByIndex(int index, T_num value)
  {
    return this->at(index) = value;
  }
};

}

#endif
