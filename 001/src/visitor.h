#ifndef _VISITOR_H_
#define _VISITOR_H_

#include <ostream>

#include "score.h"

namespace OOP {

class Student;

/*!
 Base class of visitors
 */
class Visitor
{
public:
  /*!
   visit a student
   @param st the student
   */
  virtual void visit(Student *st) 
  { };

  /*!
   apply a visitor to a serial of Students
   @param begin the first iterator of the Students
   @param end the iterator points to the Student after the last one
   */
  template <typename T_iter>
  void 
  apply(T_iter begin, T_iter end)
  {
    for (auto i = begin; i != end; ++i)
      i->accept(this);
  }
};

class ReadVisitor : public Visitor
{
  std::istream &is;
public:
  ReadVisitor(std::istream &);

  virtual void visit(Student *);
};

class WriteVisitor : public Visitor
{
  int counter;
  std::ostream &os;
public:
  WriteVisitor(std::ostream &);

  virtual void visit(Student *);
};

class CountingVisitor : public Visitor
{
public:
  virtual void output(std::ostream &os) const;

  template <typename T_iter>
  void apply(T_iter begin, T_iter end, std::ostream &os)
  {
    Visitor::apply(begin, end);
    output(os);
  }
};

class AverageVisitor : public CountingVisitor
{
  Score<Config::SCORE_TYPE> scores_;

public:
  AverageVisitor();

  virtual void  visit(Student *s);

  void output(std::ostream &os) const;
};

class MaxVisitor : public CountingVisitor
{
  Score<Config::SCORE_TYPE> scores_;
public:
  MaxVisitor();

  virtual void visit(Student *s);

  void output(std::ostream &os) const;
};

class MinVisitor : public CountingVisitor
{
  Score<Config::SCORE_TYPE> scores_;
public:
  MinVisitor();

  virtual void visit(Student *s);

  void output(std::ostream &os) const;
};

}

#endif
