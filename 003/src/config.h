#ifndef _OOP_CONFIG_H_
#define _OOP_CONFIG_H_

#include <string>

namespace OOP {

namespace Config {
  static char HELP_TEXT[] =
    "adv : An advanture game power by Clarkok Zhang\n"
    "Usage adv <command>\n"
    "\n"
    "Commands:\n"
    "  random [w] [h] : Generate a random map\n"
    "                   use it by 'adv random > map.txt' or something similar.\n"
    "                   width and height default to 5.\n"
    "  load <file>    : Load a map and start game\n"
    "  help           : print this help\n"
    ;
  static const char *PROMPTS[] = {
    "Welcome to the lobby.",
    "You meet a MONSTOR! You die!",
    "You saved the princess! You WIN!",
    "It is an empty room."
  };
  static const char *WALL_INFO[] = {
    " There is 1 exist as: ",
    " There are several exists as: "
  };
  static const char *WALL_LITERAL[] = {
    nullptr,  // 0
    "north",  // 1
    "east",   // 2
    nullptr,  // 3
    "south",  // 4
    nullptr,  // 5
    nullptr,  // 6
    nullptr,  // 7
    "west"
  };
  static char COMMAND_PROMPT[] = "Enter you command: ";
  static char ERROR_PROMPT[] = "Error in command!";

};

struct Exception
{
  int code;
  std::string msg1;
  std::string msg2;

  Exception(
    int code,
    const std::string &msg1 = "",
    const std::string &msg2 = "")
  : code(code), msg1(msg1), msg2(msg2)
  { }

  inline std::string
  toString() const
  {
    std::string ret(msg1);
    ret += "(";
    ret += std::to_string(code);
    ret += ") : ";
    ret += msg2;
    return ret;
  }

  inline 
  operator bool() const
  {
    return code;
  }

};

}

#endif // _OOP_CONFIG_H_
