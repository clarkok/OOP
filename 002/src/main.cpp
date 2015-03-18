#include <iostream>
#include <vector>

#include "config.h"
#include "student.h"
#include "visitor.h"

using namespace OOP;
using namespace std;

/* Students array */
vector<Student> stds;

int
main()
{
  /* Print help text to screen */
  cout << Config::USAGE_TEXT;

  /* Read all students from std::cin */
  ReadVisitor(cin).read(stds);

  /* Calculate indents for all courses, move constructor should be called */
  auto indents = dynamic_cast<IndentVisitor*>(
    IndentVisitor().apply(stds.begin(), stds.end()))->get();

  /* Calculate average for each student and output those students */
  WriteVisitor(cout, indents).write(stds.begin(), stds.end());

  /* Calculate and output average, max and min for each scores */
  AverageVisitor(indents).apply(stds.begin(), stds.end(), cout);
  MaxVisitor(indents).apply(stds.begin(), stds.end(), cout);
  MinVisitor(indents).apply(stds.begin(), stds.end(), cout);

  return 0;
}
