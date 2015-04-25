#include <iostream>
#include <iterator>

#include "config.h"
#include "student.h"
#include "visitor.h"

using namespace OOP;
using namespace std;

/* Students array */
Student stds[Config::STUDENT_NUMBER];

int
main(int argc, char **argv)
{
  /* Read all students from std::cin */
  ReadVisitor(cin).apply(begin(stds), end(stds));

  /* Output header of the table */
  cout << "no\tname\tscore1\tscore2\tscore3\taverage" << endl;

  /* Calculate average for each student and output those students */
  WriteVisitor(cout).apply(begin(stds), end(stds));

  /* Calculate and output average, max and min for each scores */
  AverageVisitor().apply(begin(stds), end(stds), cout);
  MaxVisitor().apply(begin(stds), end(stds), cout);
  MinVisitor().apply(begin(stds), end(stds), cout);

  return 0;
}
