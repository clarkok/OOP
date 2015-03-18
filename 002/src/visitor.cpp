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
  string course;
  Config::SCORE_TYPE score;

  while (true) {
    is >> course;
    if (course == "END")
      return;
    is >> score;
    s->pushScore(course, score);
  }
}

void
ReadVisitor::read(std::vector<Student> &s)
{
  string name;

  while (is >> name)
  {
    s.push_back(Student());
    auto p = s.rbegin();
    p->name(name);
    p->accept(this);
  }
}

void
IndentVisitor::visit(Student *s)
{
  for (auto sp = s->scoreBegin(); sp != s->scoreEnd(); ++sp) {
    indents[sp->first] = (sp->first.length() + 7) / 8;
  }

  max_name_length = 
    max_name_length < s->name().length() 
    ? s->name().length() : max_name_length;
}

WriteVisitor::WriteVisitor(ostream &o, decltype(indents) indents)
: counter(0), os(o), indents(indents)
{ }

/* Write info to os */
void
WriteVisitor::visit(Student *s)
{
  Student::T_score sum = 0;
  int count = 0;

  ++counter;

  os << counter << '\t' << s->name();

  for (int i = s->name().length() / 8; i < indents[Config::NAME_KEY]; ++i)
    os << '\t';

  for (auto p = indents.begin(); p != indents.end(); ++p) {
    if (p->first == Config::NAME_KEY)
      continue;

    Student::T_score score = s->getScoreByIndex(p->first);

    if (score != -1) {
      count ++;
      sum += score;
      os << score;
    }
    else
      os << Config::NA;

    for (int i = 0; i < p->second; ++i)
      os << '\t';
  }

  if (count)
    os << static_cast<double>(sum) / count << endl;
  else
    os << Config::NA << endl;
}

void
WriteVisitor::write(
  std::vector<Student>::iterator begin,
  std::vector<Student>::iterator end)
{
  os << "no.\tname";
  for (int i = 0; i < indents[Config::NAME_KEY]; ++i)
    os << '\t';

  for (auto &p : indents)
    if (p.first != Config::NAME_KEY)
      os << p.first << '\t';

  os << "average" << endl;

  for (auto p = begin; p != end; ++p) {
    p->accept(this);
  }
}

void
CountingVisitor::output(std::ostream &) const
{ }

/* Add the scores */
void
AverageVisitor::visit(Student *s)
{
  for (auto p = s->scoreBegin(); p != s->scoreEnd(); ++p) {
    scores_[p->first] += p->second;
    counts_[p->first] ++;
  }
}

/* Calculate the average and output the result */
void
AverageVisitor::output(std::ostream &os) const
{
  os << '\t' << "average";
  for (int i = 0; i < indents.at(Config::NAME_KEY); ++i) {
    os << '\t';
  }

  for (auto s : indents) {
    if (s.first == Config::NAME_KEY)
      continue;
    os << static_cast<double>(scores_.at(s.first)) / counts_.at(s.first);
    for (int i = 0; i < s.second; ++i)
      os << '\t';
  }

  os << endl;
}

void
MaxVisitor::visit(Student *s)
{
  for (auto p = s->scoreBegin(); p != s->scoreEnd(); ++p) {
    scores_[p->first] = scores_[p->first] < p->second
      ? p->second : scores_[p->first];
  }
}

void
MaxVisitor::output(std::ostream &os) const
{
  os << '\t' << "max";
  for (int i = 0; i < indents.at(Config::NAME_KEY); ++i) {
    os << '\t';
  }

  for (auto s : indents) {
    if (s.first == Config::NAME_KEY)
      continue;
    os << scores_.at(s.first);
    for (int i = 0; i < s.second; ++i)
      os << '\t';
  }

  os << endl;
}

void
MinVisitor::visit(Student *s)
{
  for (auto p = s->scoreBegin(); p != s->scoreEnd(); ++p) {
    scores_[p->first] = scores_[p->first] > p->second
      ? p->second : scores_[p->first];
  }
}

void
MinVisitor::output(std::ostream &os) const
{
  os << '\t' << "min";
  for (int i = 0; i < indents.at(Config::NAME_KEY); ++i) {
    os << '\t';
  }

  for (auto s : indents) {
    if (s.first == Config::NAME_KEY)
      continue;
    os << scores_.at(s.first);
    for (int i = 0; i < s.second; ++i)
      os << '\t';
  }

  os << endl;
}
