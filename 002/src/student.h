#ifndef _STUDENT_H_
#define _STUDENT_H_

#include <string>

#include "config.h"
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
   @param course course name
   @param value the score
   */
  inline void
  pushScore(std::string course, T_score value)
  {
    scores_.setScoreByIndex(course, value);
  }

  /*!
   get score by index
   @param course course name
   @return the score
   */
  inline T_score
  getScoreByIndex(std::string course) const
  {
    return scores_.getScoreByIndex(course);
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

  inline decltype(scores_.cbegin())
  scoreBegin() const
  {
    return scores_.cbegin();
  }

  inline decltype(scores_.cend())
  scoreEnd() const
  {
    return scores_.cend();
  }
};

}

#endif
