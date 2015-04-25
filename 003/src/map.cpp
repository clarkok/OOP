#include <fstream>
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <stack>
#include <utility>

#include <iostream>

#include "config.h"
#include "map.h"

using namespace OOP;

const WALL walls[4] = {W_NORTH, W_EAST, W_SOUTH, W_WEST};

static std::string
generateWall(int row, int width, char room)
{
  std::string ret;

  if (row % 2 == 0) {
    for (int i = 0; i < width * 2 + 1; ++i) {
      if (i % 2 == 0)
        ret += '+';
      else
        ret += '-';
    }
  }
  else {
    for (int i = 0; i < width * 2 + 1; ++i) {
      if (i % 2 == 0)
        ret += '|';
      else
        ret += room;
    }
  }

  return ret;
}

static std::string &
trim(std::string &str) 
{
  str.erase(
    str.begin(),
    std::find_if(
      str.begin(),
      str.end(),
      std::not1(std::ptr_fun<int, int>(std::isspace))));

  str.erase(
    std::find_if(
      str.rbegin(),
      str.rend(),
      std::not1(std::ptr_fun<int, int>(std::isspace))).base(), str.end());

  return str;
}

void
FileMap::load(const std::string &path)
{
  this->clear();

  std::ifstream fin(path);

  if (!fin)
    throw Exception(1, "Cannot open file to read", path);

  std::string line;

  while (fin) {
    std::getline(fin, line);
    if (trim(line).length())
      this->push_back(line);
  }

  this->valid();
}

void
Map::valid()
{
  if (!this->size())
    throw Exception(2, "No data loaded");

  if (this->size() % 2 == 0)
    throw Exception(3, "Invalid row number");

  width_ = this->at(0).length() / 2;
  height_ = this->size() / 2;

  for (unsigned int i = 0; i < this->size(); ++i) {
    auto & line = this->at(i);
    if (line.length() % 2 == 0)
      throw Exception(
        4, 
        "Invalid row length",
        "Row " + std::to_string(i + 1));
    if (width_ != line.length() / 2)
      throw Exception(
        5,
        "Defferent row length",
        "Row " + std::to_string(i + 1));

    if (i % 2 == 0) // For wall
      for (unsigned int j = 0; j < line.length(); ++j) {
        if ((j % 2 == 0) && (line[j] != '+'))
          throw Exception(
            6,
            "Expect +",
            std::to_string(i + 1) + ':' + std::to_string(j + 1));
        else if ((j % 2) && (line[j] != ' ') && (line[j] != '-'))
          throw Exception(
            7,
            "Except - or space",
            std::to_string(i + 1) + ':' + std::to_string(j + 1));
      }
    else
      for (unsigned int j = 0; j < line.length(); ++j) {
        if ((j % 2 == 0) && (line[j] != '|') && (line[j] != ' '))
          throw Exception(
            8,
            "Expect | or space",
            std::to_string(i + 1) + ':' + std::to_string(j + 1));
      }
  }

  for (int i = 0; i < height_; ++i)
    for (int j = 0; j < width_; ++j)
      if (roomOfPosition(i, j) == '^') {
        start_ = std::make_pair(i, j);
        return;
      }
}

int 
Map::getWallInfo(int y, int x) const
{
  int ret = 0;

  for (auto w : walls) {
    if (wallOfPosition(y, x, w) != ' ') {
      ret |= w;
      ret += 16;
    }
  }

  return ret;
}

void
RandomMap::randPos(T_pos p)
{
  if (checkPosition(p)) {
    roomOfPosition(p.first, p.second) = ' ';

    if (getWallInfo(p.first, p.second) == 0)
      return;

    bool flag = true;

    for (int i = 0; i < 2; ++i) {
      WALL dir = walls[std::rand() % 4];
      T_pos next = goAhead(p, dir);

      if (!checkPosition(next)) {
        --i;
        continue;
      }
      if (roomOfPosition(next.first, next.second) == ' ')
        continue;

      flag = false;

      setWallOfPosition(p.first, p.second, dir, ' ');
      randPos(next);
    }

    if (flag && (rand() % 8 > 2))
      roomOfPosition(p.first, p.second) = 'M';
  }
}

void
RandomMap::random(int height, int width)
{
  this->clear();

  for (int i = 0; i < height * 2 + 1; ++i)
    this->push_back(generateWall(i, width, '*'));

  std::srand(std::time(0));
  width_ = width;
  height_ = height;

  T_pos first = T_pos(std::rand() % height, std::rand() % width);
  randPos(first);
  roomOfPosition(first.first, first.second) = '^';
  start_ = first;

  while (true) {
    T_pos p(std::rand() % height, std::rand() % width);
    if (roomOfPosition(p.first, p.second) == ' ') {
      roomOfPosition(p.first, p.second) = 'P';
      break;
    }
  }
}
