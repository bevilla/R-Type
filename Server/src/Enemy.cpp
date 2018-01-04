#include		<sstream>
#include		"Enemy.hpp"

size_t			Enemy::idmax = 0;

Enemy::Enemy()
{
  _id = idmax++;
  _x = 1000;
  _y = 50;
  _alive = true;
}

Enemy::~Enemy()
{
}

size_t			Enemy::getId() const
{
  return _id;
}

void			Enemy::die()
{
  _alive = false;
}

bool			Enemy::isAlive() const
{
  return _alive;
}
