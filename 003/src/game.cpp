#include <iostream>
#include <bitset>
#include <climits>
#include <sstream>

#include "config.h"
#include "game.h"

using namespace OOP;

int
Game::countWall(int wall_info) const
{
  return wall_info >> 4;
}

int 
Game::outputInfo() const
{
  switch (map->roomOfPosition(current.first, current.second)) {
    case '^':
      std::cout << Config::PROMPTS[0];
      break;
    case 'M':
      std::cout << Config::PROMPTS[1] << std::endl;
      return -1;
    case 'P':
      std::cout << Config::PROMPTS[2] << std::endl;
      return -1;
    case ' ':
      std::cout << Config::PROMPTS[3];
      break;
  }

  int wall_info = map->getWallInfo(current.first, current.second);
  int wall_count = countWall(wall_info);
  int entry_count = 4 - wall_count;

  std::cout << " " << Config::WALL_INFO
    [(entry_count - 1) ? 1 : 0];

  for (auto w : WALL_ITERATION) {
    if (!(wall_info & w)) {
      std::cout << Config::WALL_LITERAL[w];
      if (entry_count > 2)
        std::cout << ", ";
      else if (entry_count == 2)
        std::cout << " and ";
      else
        std::cout << ".";
      --entry_count;
    }
  }
  std::cout << std::endl << Config::COMMAND_PROMPT;

  return wall_info;
}

WALL 
Game::parseDir(const std::string &line) const
{
  std::stringstream sin(line);
  std::string buff;

  sin >> buff;
  if (buff != "go") {
    return static_cast<WALL>(0);
  }
  sin >> buff;

  for (int i = 0; i < 9; ++i)
    if (Config::WALL_LITERAL[i] &&
        Config::WALL_LITERAL[i] == buff)
      return static_cast<WALL>(i);

  return static_cast<WALL>(0);
}

Game::Game(Map *m)
: map(m), current(m->start())
{ }

void
Game::mainLoop()
{
  while (true) {
    auto wall_info = outputInfo();
    if (wall_info == -1)
      return;

    std::string line;
    std::getline(std::cin, line);
    auto dir = parseDir(line);

    while ((!dir) || (dir & wall_info)) {
      std::cout << Config::ERROR_PROMPT << std::endl;
      std::cout << Config::COMMAND_PROMPT;
      std::getline(std::cin, line);
      dir = parseDir(line);
    }

    current = map->goAhead(current, dir);
  }
}
