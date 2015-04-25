#ifndef _OOP_MAP_H_
#define _OOP_MAP_H_

#include <string>
#include <vector>
#include <iostream>
#include <utility>

#include "config.h"

namespace OOP {

enum WALL {
  W_NORTH = 1,
  W_EAST = 2,
  W_SOUTH = 4,
  W_WEST = 8
};

static WALL WALL_ITERATION[] = {W_NORTH, W_EAST, W_SOUTH, W_WEST};

class Map : public std::vector<std::string>
{
public:
  typedef std::pair<int, int> T_pos;

protected:
  int width_ = 0;
  int height_ = 0;
  T_pos start_;

  inline void
  checkPositionRange(int y, int x) const
  {
    if (y >= height_ || y < 0)
      throw Exception(
        9,
        "Y Out of map range",
        "(" + std::to_string(y) + "," + std::to_string(x) + ")"
      );
    if (x >= width_ || x < 0)
      throw Exception(
        10,
        "X Out of map range",
        "(" + std::to_string(y) + "," + std::to_string(x) + ")"
      );
  }

  inline bool
  checkPosition(T_pos p) const
  {
    try {
      checkPositionRange(p.first, p.second);
    }
    catch (Exception &e) {
      return false;
    }
    return true;
  }

public:
  void valid();

  inline int 
  width() const
  {
    return width_;
  }

  inline int 
  height() const
  {
    return height_;
  }

  inline T_pos
  start() const
  {
    return start_;
  }

  int getWallInfo(int y, int x) const;

  void
  output(std::ostream &os) const
  {
    for (auto & line : *this)
      os << line << std::endl;
  }

  inline T_pos
  goAhead(T_pos p, WALL w)
  {
    checkPositionRange(p.first, p.second);

    switch (w) {
      case W_NORTH: p.first--; break;
      case W_SOUTH: p.first++; break;
      case W_WEST: p.second--; break;
      case W_EAST: p.second++; break;
    };

    return p;
  }

  inline char &
  roomOfPosition(int y, int x)
  {
    checkPositionRange(y, x);
    return this->at(y * 2 + 1)[x * 2 + 1];
  }

  inline char
  wallOfPosition(int y, int x, WALL w) const
  {
    checkPositionRange(y, x);
    switch (w) {
      case W_NORTH: return this->at(y * 2)[x * 2 + 1];
      case W_SOUTH: return this->at(y * 2 + 2)[x * 2 + 1];
      case W_WEST: return this->at(y * 2 + 1)[x * 2];
      case W_EAST: return this->at(y * 2 + 1)[x * 2 + 2];
    };
  }
};

class FileMap : public Map
{
public:
  void load(const std::string &path);
};

class RandomMap : public Map
{
  char &
  setWallOfPosition(int y, int x, WALL w, char c)
  {
    checkPositionRange(y, x);
    switch (w) {
      case W_NORTH: return this->at(y * 2)[x * 2 + 1] = c;
      case W_SOUTH: return this->at(y * 2 + 2)[x * 2 + 1] = c;
      case W_WEST: return this->at(y * 2 + 1)[x * 2] = c;
      case W_EAST: return this->at(y * 2 + 1)[x * 2 + 2] = c;
    };
  }

  void randPos(T_pos p);
public:
  void random(int height = 5, int width = 5);
};

};

#endif // _OOP_MAP_H_
