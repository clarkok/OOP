#ifndef _CONFIG_H_
#define _CONFIG_H_

namespace OOP {

namespace Config {
  static const char USAGE_TEXT[] = 
    "Usage:\n"
    "  Input format:\n"
    "    For each student, you should input a section start with a \n"
    "    line containing the name of the student. After that, several \n"
    "    lines containing a string and a integer should be inputed, \n"
    "    the string is the course name, and the integer is the score.\n"
    "    After all scores have been inputed, a 'END' should follow to\n"
    "    show the student section is ended.\n"
    "    After all students is inputed, an EOF showed appears, or\n"
    "    Ctrl-D is pressed in terminal."
    "\n"
    "  Example:\n"
    "    ClarkokZhang\n"
    "    OOP 5\n"
    "    CProgramingLanguage 5\n"
    "    END\n"
    "    FatMouse\n"
    "    OOP 4\n"
    "    Mathmatical 5\n"
    "    END\n"
    "    [Ctrl-D]\n"
    ;

  static const char NAME_KEY[] = "__name__";

  static const char NA[] = "N/A";

  /*! Type of score */
  typedef int SCORE_TYPE;
}

}

#endif
