#ifndef _SCORE_H_
#define _SCORE_H_

#include <vector>

namespace OOP {

template <typename T_num>
class Score : public std::vector<T_num>
{
public:
  T_num
  getScoreByIndex(int index) const
  {
    return this->at(index);
  }

  T_num
  setScoreByIndex(int index, T_num value)
  {
    return this->at(index) = value;
  }
};

}

#endif
