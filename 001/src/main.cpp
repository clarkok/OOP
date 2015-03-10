#include <iostream>
#include <iterator>

#include "config.h"
#include "student.h"
#include "visitor.h"

using namespace OOP;
using namespace std;

Student stds[Config::STUDENT_NUMBER];

int
main(int argc, char **argv)
{
  ReadVisitor(cin).apply(begin(stds), end(stds));

  cout << "no\tname\tscore1\tscore2\tscore3\taverage" << endl;

  WriteVisitor(cout).apply(begin(stds), end(stds));

  AverageVisitor().apply(begin(stds), end(stds), cout);
  MaxVisitor().apply(begin(stds), end(stds), cout);
  MinVisitor().apply(begin(stds), end(stds), cout);

  return 0;
}
