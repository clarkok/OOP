#ifndef _STUDENT_H_
#define _STUDENT_H_

#include <string>

#include "visitor.h"
#include "score.h"

namespace OOP {

class Student
{
public:
  typedef Config::SCORE_TYPE T_score;

private:
  Score<T_score> scores_;
  std::string name_;

public:
  inline std::string 
  name() const
  {
    return name_;
  }

  inline std::string 
  name(const std::string &n)
  {
    return (name_ = n);
  }

  inline void
  pushScore(T_score value)
  {
    scores_.push_back(value);
  }

  inline T_score
  getScoreByIndex(int index) const
  {
    return scores_.getScoreByIndex(index);
  }

  inline void 
  accept(Visitor *v)
  {
    v->visit(this);
  }
};

}

#endif
