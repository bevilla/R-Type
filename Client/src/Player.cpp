//
// Player.cpp for Player in /home/trupint/rendu/R-Type/Client
// 
// Made by trupin_t
// Login   <trupint@epitech.net>
// 
// Started on Thu Jan 21 11:25:40 2016 trupin_t
// Last update Sat Jan 23 18:48:25 2016 trupin_t
//

#include "Player.hpp"

Player::Player()
{
  _isConected = false;
  _isReady = false;
}

void		Player::setID(int newid)
{
  _id = newid;
}

void		Player::setName(std::string newString)
{
  _name = newString;
}

std::string	Player::getName()
{
  return (_name);
}

int		Player::getId()
{
  return (_id);
}
