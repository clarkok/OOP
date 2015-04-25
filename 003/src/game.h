#ifndef _OOP_GAME_H_
#define _OOP_GAME_H_

#include <string>

#include "config.h"
#include "map.h"

namespace OOP {

class Game
{
  Map *map;

  typedef Map::T_pos T_pos;

  T_pos current;

  int countWall(int wall_info) const;
  int outputInfo() const;
  WALL parseDir(const std::string &line) const;

public:
  Game(Map *m);

  void mainLoop();
};

};

#endif // _OOP_GAME_H_
