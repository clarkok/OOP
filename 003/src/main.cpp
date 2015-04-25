#include <iostream>

#include "config.h"
#include "map.h"
#include "game.h"

using namespace OOP;

int
main(int argc, char **argv)
{
  if (argc == 1) {
    std::cout << Config::HELP_TEXT << std::endl;
    return 0;
  }

  if (argv[1] == std::string("random")) {
    int width = 5;
    int height = 5;
    if (argc >= 3) {
      width = std::stoi(argv[2]);
    }
    if (argc >= 4) {
      height = std::stoi(argv[3]);
    }
    RandomMap *m = new RandomMap();
    m->random(height, width);
    m->output(std::cout);
  }
  else if (argv[1] == std::string("load")) {
    FileMap *m = new FileMap();
    try {
      m->load(argv[2]);
      Game g(m);
      g.mainLoop();
    }
    catch (const Exception &e) {
      std::cerr << e.toString() << std::endl;
      return -1;
    }
  }
  else {
    std::cout << Config::HELP_TEXT << std::endl;
  }

  return 0;
}
