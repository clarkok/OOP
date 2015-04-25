#ifndef _STUDENT_H_
#define _STUDENT_H_

#include <string>

#include "visitor.h"
#include "score.h"

namespace OOP {

/*!
 Student class
 */
class Student
{
public:
  typedef Config::SCORE_TYPE T_score;

private:
  Score<T_score> scores_;
  std::string name_;

public:
  /*!
   get name of student
   @return name of student
   */
  inline std::string 
  name() const
  {
    return name_;
  }

  /*!
   set name of student
   @param n new name
   @return new name of student
   */
  inline std::string 
  name(const std::string &n)
  {
    return (name_ = n);
  }

  /*!
   push a score back to scores
   @param value the score
   */
  inline void
  pushScore(T_score value)
  {
    scores_.push_back(value);
  }

  /*!
   get score by index
   @param index index of score to get
   @return the score
   */
  inline T_score
  getScoreByIndex(int index) const
  {
    return scores_.getScoreByIndex(index);
  }

  /*!
   accept a Visitor
   @see Visitor::visit(Student *)
   @param v the visitor
   */
  inline void 
  accept(Visitor *v)
  {
    v->visit(this);
  }
};

}

#endif
