//
// GameStateLobby.hpp for GameStateLobby in /home/trupint/rendu/R-Type/Client
// 
// Made by trupin_t
// Login   <trupint@epitech.net>
// 
// Started on Wed Jan 20 15:32:46 2016 trupin_t
// Last update Sat Jan 23 19:22:47 2016 trupin_t
//

#ifndef GAMESTATELOBBY_H_
# define GAMESTATELOBBY_H_

#include	"GameState.hpp"

#define		LOBBY_NAME_X	45
#define		LOBBY_NAME_Y	50

#define		PLAYERS_X	210
#define		PLAYER_1	190
#define		PLAYER_2	331
#define		PLAYER_3	472
#define		PLAYER_4	613

#define		BUTTON_X	480
#define		BUTTON_Y	730

#define		LIGHTS_X	84
#define		LIGHT_1		169
#define		LIGHT_GAP	141

class GameStateLobby : public GameState
{
public:
  GameStateLobby(Game *game);

  virtual void	draw(const float dt);
  virtual void	update(const float dt);
  virtual bool	handleInput();

private:
  sf::View		_view;
  sf::Sprite		_background;
  sf::Sprite		_readyButton;
  sf::Sprite		_lights[4];
  sf::Text		_lobbyName;
  sf::Text		_playerNames[4];
  bool			_return;
  bool			_isReady;
};

#endif /*!GAMESTATELOBBY_H_*/
