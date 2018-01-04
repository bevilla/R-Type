#ifndef GAME_H_
# define GAME_H_

#include	<stack>
#include	<map>
#include	<cstring>
#include	<string>
#include	<iostream>
#include	<vector>
#include	<SFML/Graphics.hpp>
#include	<SFML/System.hpp>
#include	"SFML/Audio.hpp"
#include	"TextureManager.hpp"
#include	"SoundManager.hpp"
#include	"RessourceManager.hpp"
#include	"Player.hpp"

#define		WINDOW_NAME	"<(O_O<) ~ R-Typu ~ (>O_O)>"
#define		WINDOW_W	1152
#define		WINDOW_H	864

class	GameState;

class	Game
{
public:
  Game();
  ~Game();

  void				pushState(GameState *state);
  void				popState();
  void				changeState(GameState *state);

  GameState			*peekState();

  void				gameLoop();
  void				loadTextures();
  void				loadSounds();
  void				loadFonts();

  std::stack<GameState*>	_states;
  sf::RenderWindow		_window;
  sf::Music			_menuMusic;
  sf::Sound			_clickSnd;
  sf::Sound			_selectSnd;
  Player			_players[4];
  std::string			_playerName;
  char * ip;

  RessourceManager		_txmgr;
  SoundManager			_snmgr;
};

#endif /*!GAME_H_*/
