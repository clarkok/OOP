#ifndef _OOP_CONFIG_H_
#define _OOP_CONFIG_H_

#define BOLD_WHITE_TAG "\e[1;37m"
#define RESET "\e[0m"

#define BOLD_WHITE(s) BOLD_WHITE_TAG s RESET

namespace OOP {
  namespace Config {
    static const char HELP_TEXT[] = 
      BOLD_WHITE("PD") " - your personal diary.\n"
      "\n"
      BOLD_WHITE("Usage:\n")
      "  pd <command> [arguments]\n"
      "\n"
      BOLD_WHITE("Command List:\n")
      "  " BOLD_WHITE("add [date]") "       add a entry of the date, and the date default to today.\n"
      "  " BOLD_WHITE("list [from [to]]") " list entries between FROM and TO. List all when no border defined.\n"
      "  " BOLD_WHITE("show <date>") "      print a diary to screen.\n"
      "  " BOLD_WHITE("remove <date>") "    remove an entry of the date.\n"
      "\n"
      BOLD_WHITE("Date format:\n")
      "  All of format below is allowed\n"
      "    YYYY-MM-DD\n"
      "    MM-DD\n"
      "    DD\n"
      "\n"
      BOLD_WHITE("Examples:\n")
      "  pd add               # add a entry for today\n"
      "  pd list 2010-10-31   # list all entries from 2010/10/31\n"
      "  pd show 1 31         # show the entry of 31rd Jan this year\n"
      "  pd remove 1 31       # remove the entry of 31rd Jan this year\n"
      "\n"
      BOLD_WHITE("Alias:\n")
      "  pdadd, pdlist, pdshow, pdremove\n"
      ;
      
    static const char DB_PATH[] = "./pd.db";
  }
}

#endif // _OOP_CONFIG_H_