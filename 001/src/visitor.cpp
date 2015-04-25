#include <iostream>

#include "config.h"
#include "student.h"
#include "visitor.h"

using namespace OOP;
using namespace std;

ReadVisitor::ReadVisitor(istream &is)
: is(is)
{ }

/* Read info from is to fill a Student */
void 
ReadVisitor::visit(Student *s)
{
  string name;
  is >> name;
  s->name(name);

  for (int i = 0; i < Config::SCORE_NUMBER; ++i) {
    Student::T_score score;
    is >> score;
    s->pushScore(score);
  }
}

WriteVisitor::WriteVisitor(ostream &o)
: counter(0), os(o)
{ }

/* Write info to os */
void
WriteVisitor::visit(Student *s)
{
  Student::T_score sum = 0;

  ++counter;

  os << counter << '\t' << s->name();

  for (int i = 0; i < Config::SCORE_NUMBER; ++i) {
    os << '\t' << s->getScoreByIndex(i);

    sum += s->getScoreByIndex(i);
  }

  os << '\t' << static_cast<double>(sum) / Config::SCORE_NUMBER << endl;
}

void
CountingVisitor::output(std::ostream &os) const
{ }

AverageVisitor::AverageVisitor()
{
  for (int i = 0; i < Config::SCORE_NUMBER; ++i)
    scores_.push_back(0);
}

/* Add the scores */
void
AverageVisitor::visit(Student *s)
{
  for (int i = 0; i < Config::SCORE_NUMBER; ++i)
    scores_[i] += s->getScoreByIndex(i);
}

/* Calculate the average and output the result */
void
AverageVisitor::output(std::ostream &os) const
{
  os << '\t' << "average";
  for (int i = 0; i < Config::SCORE_NUMBER; ++i)
    os << '\t' << static_cast<double>(scores_[i]) / Config::STUDENT_NUMBER;
  os << endl;
}

MaxVisitor::MaxVisitor()
{
  for (int i = 0; i < Config::SCORE_NUMBER; ++i)
    scores_.push_back(-1);
}

void
MaxVisitor::visit(Student *s)
{
  for (int i = 0; i < Config::SCORE_NUMBER; ++i)
    scores_[i] = scores_[i] > s->getScoreByIndex(i) 
      ? scores_[i] : s->getScoreByIndex(i);
}

void
MaxVisitor::output(std::ostream &os) const
{
  os << '\t' << "max";
  for (int i = 0; i < Config::SCORE_NUMBER; ++i)
    os << '\t' << scores_[i];
  os << endl;
}

MinVisitor::MinVisitor()
{
  for (int i = 0; i < Config::SCORE_NUMBER; ++i)
    scores_.push_back(0x7fff);
}

void
MinVisitor::visit(Student *s)
{
  for (int i = 0; i < Config::SCORE_NUMBER; ++i)
    scores_[i] = scores_[i] < s->getScoreByIndex(i) 
      ? scores_[i] : s->getScoreByIndex(i);
}

void
MinVisitor::output(std::ostream &os) const
{
  os << '\t' << "min";
  for (int i = 0; i < Config::SCORE_NUMBER; ++i)
    os << '\t' << scores_[i];
  os << endl;
}
