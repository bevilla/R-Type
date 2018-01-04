//
// Ship.hpp for  in /home/noel_f/rendu/tmpRTYPE/Client
//
// Made by Gabriel NOEL
// Login   <noel_f@epitech.net>
//
// Started on  Sat Jan 16 13:58:56 2016 Gabriel NOEL
// Last update Sat Jan 16 14:05:12 2016 Gabriel NOEL
//

#ifndef SHIP_HPP_
# define SHIP_HPP_

#include	<SFML/Graphics.hpp>
//#include	<iostream>
//#include	"GameState.hpp"
//#include	"GameStateGame.hpp"


class		Ship : public sf::Sprite
{
public:
  Ship(){};

  void		init(sf::Texture&, int, int);
private:
};

#endif /*!SHIP_HPP_*/
