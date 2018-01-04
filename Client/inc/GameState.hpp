#ifndef GAMESTATE_H_
# define GAMESTATE_H_

#include	"Game.hpp"

class GameState
{
public:
  virtual   ~GameState(){}

  Game		*_game;

  virtual void	draw(const float dt) = 0;
  virtual void	update(const float dt) = 0;
  virtual bool	handleInput() = 0;
};

#endif /*!GAMESTATE_H_*/
