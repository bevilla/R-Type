#ifndef GAMESTATEMULTI_H_
# define GAMESTATEMULTI_H_

#include	<SFML/Graphics.hpp>
#include	<iostream>
#include	"Ship.hpp"
#include	"GameState.hpp"
#include	"AnimatedSprite.hpp"
#include	"TcpSocket.hpp"
#include	"command.hpp"

#if defined(__linux__)
# include	<arpa/inet.h>
#elif defined(WIN32)
# include	<Windows.h>
#endif

#define		M_SPEED		13

class			        GameStateMulti : public GameState
{
public:
  GameStateMulti(Game *game);
  ~GameStateMulti();

  virtual void			draw(const float dt);
  virtual void			update(const float dt);
  virtual bool			handleInput();

private:
  sf::View			_view;

  sf::Sprite			_background;
  Ship				_ship[4];
  std::vector<sf::Sprite>	_missiles;
  std::vector<AnimatedSprite>	_missiless;
  std::vector<AnimatedSprite>	_explos;

  double			_elapsed;
  bool				_start;

  TcpSocket *socket;
  size_t receive;
  void *data;
  command::player_dataCli	*_player_update;

  void				addMissile();
  void				addExplo(int, int);
  void				loadGame();
  void				ready();
};

#endif /*!GAMESTATEMULTI_H_*/
