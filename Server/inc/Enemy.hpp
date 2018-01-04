#pragma once

#include		<iostream>
#include		<string>
#include <cstdio>
#include <ctime>
#include <stdint.h>

class			Enemy
{
private:
  static size_t		idmax;
  size_t		_id;
  int       _x;
  int       _y;
  bool			_alive;

public:
  Enemy();
  ~Enemy();

  size_t		getId() const;
  int getX() const {return _x;}
  void setX(int x) {_x = x;}
  int getY() const {return _y;}
  void setY(int y) {_y = y;}

  void			die();
  bool			isAlive() const;
};
