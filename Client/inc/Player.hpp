//
// Player.hpp for Player in /home/trupint/rendu/R-Type/Client
// 
// Made by trupin_t
// Login   <trupint@epitech.net>
// 
// Started on Thu Jan 21 11:24:56 2016 trupin_t
// Last update Sat Jan 23 18:52:45 2016 trupin_t
//

#ifndef PLAYER_H_
# define PLAYER_H_

#include	"SFML/Graphics.hpp"

class Player
{
public:
  Player();

  sf::Sprite	_sprite;
  bool		_isConected;
  bool		_isReady;

  void		setID(int);
  void		setName(std::string);
  std::string	getName();
  int		getId();

private:
  std::string	_name;
  int		_id;
};

#endif /*!PLAYER_H_*/
