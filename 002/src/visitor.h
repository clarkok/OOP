#ifndef _VISITOR_H_
#define _VISITOR_H_

#include <ostream>
#include <vector>

#include "config.h"
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
  virtual void visit(Student *) = 0;

  /*!
   apply a visitor to a serial of Students
   @param begin the first iterator of the Students
   @param end the iterator points to the Student after the last one
   */
  template <typename T_iter>
  Visitor *
  apply(T_iter begin, T_iter end)
  {
    for (auto i = begin; i != end; ++i)
      i->accept(this);
    return this;
  }
};

class ReadVisitor : public Visitor
{
  std::istream &is;
public:
  ReadVisitor(std::istream &);

  virtual void visit(Student *);

  void read(std::vector<Student> &);
};

class IndentVisitor : public Visitor
{
  std::map<std::string, int> indents;
  size_t max_name_length = 0;

public:
  virtual void visit(Student *);

  inline std::map<std::string, int>
  get()
  {
    indents[Config::NAME_KEY] = 1 + max_name_length / 8;
    return indents;
  }
};

class WriteVisitor : public Visitor
{
  int counter;
  std::ostream &os;
  std::map<std::string, int> indents;

public:
  WriteVisitor(std::ostream &, decltype(indents) indents);

  virtual void visit(Student *);

  void write(std::vector<Student>::iterator, 
             std::vector<Student>::iterator);
};

class CountingVisitor : public Visitor
{
protected:
  std::map<std::string, int> indents;
  
public:
  CountingVisitor(decltype(indents) indents)
  : indents(indents)
  { }

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
  Score<Config::SCORE_TYPE> counts_;

public:
  AverageVisitor(decltype(indents) indents)
  : CountingVisitor(indents)
  { }

  virtual void  visit(Student *s);

  void output(std::ostream &os) const;
};

class MaxVisitor : public CountingVisitor
{
  Score<Config::SCORE_TYPE> scores_;
public:
  MaxVisitor(decltype(indents) indents)
  : CountingVisitor(indents)
  { }

  virtual void visit(Student *s);

  void output(std::ostream &os) const;
};

class MinVisitor : public CountingVisitor
{
  Score<Config::SCORE_TYPE> scores_;
public:
  MinVisitor(decltype(indents) indents)
  : CountingVisitor(indents)
  {
    for (auto p : indents)
      scores_[p.first] = 0x7FFFFFFF;
  }

  virtual void visit(Student *s);

  void output(std::ostream &os) const;
};

}

#endif
