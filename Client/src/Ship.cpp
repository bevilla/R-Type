//
// Ship.cpp for  in /home/noel_f/rendu/tmpRTYPE/Client
//
// Made by Gabriel NOEL
// Login   <noel_f@epitech.net>
//
// Started on  Sat Jan 16 14:01:24 2016 Gabriel NOEL
// Last update Sun Jan 24 17:40:27 2016 Gabriel NOEL
//

#include	"Ship.hpp"

void		Ship::init(sf::Texture &swagg, int du, int poney)
{
  setTexture(swagg);
  setTextureRect(sf::IntRect(33 * du, 17 * poney, 33, 17));
  setOrigin(15, 10);
  setPosition(-50, -50);
  setScale(2, 2);
}
