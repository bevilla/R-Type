//
// GameStateGame.hpp for GameStateGame in /home/trupin_t/rendu/LDD/inc
//
// Made by Thomas Trupin
// Login   <trupin_t@epitech.net>
//
// Started on Sat Dec 12 06:00:12 2015 Thomas Trupin
// Last update Sat Jan 23 19:05:12 2016 Gabriel NOEL
//

#ifndef GAMESTATEGAME_H_
# define GAMESTATEGAME_H_

#include	<SFML/Graphics.hpp>
#include	<cstdlib>
#include	<ctime>
#include	"GameState.hpp"
#include	"Game.hpp"
#include	"TcpSocket.hpp"

class GameStateListLobby : public GameState
{
public:
  GameStateListLobby(Game *game);

  virtual void	draw(const float dt);
  virtual void	update(const float dt);
  virtual bool	handleInput();

private:
  sf::View	_view;
};

#endif /*!GAMESTATEGAME_H_*/
