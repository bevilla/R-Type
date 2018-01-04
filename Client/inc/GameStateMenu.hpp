#ifndef GAMESTATEMENU_HPP_
# define GAMESTATEMENU_HPP_

#include	<SFML/Graphics.hpp>
#include	<iostream>
#include	"GameState.hpp"
#include	"GameStateStart.hpp"
#include	"GameStateSettings.hpp"
#include	"GameStateMultiMenu.hpp"
#include	"AnimatedSprite.hpp"

//	Menu entries coord. :

#define		MENU_X		250
#define		MENU_Y		250
#define		MENU_GAP	90
#define		MENU_WIDTH	400

#define		SEL_TILE_W	650
#define		SEL_TILE_H	100

#define		MENU_ENTRIES	4

class GameStateMenu : public GameState
{
public:
  GameStateMenu(Game *game);

  virtual void	draw(const float dt);
  virtual void	update(const float dt);
  virtual bool	handleInput();

private:
  sf::View		_view;
  sf::Sprite		_background;
  AnimatedSprite	_selector;
  int			_select;

  void			loadGame();
  void			select_choice();
};

#endif /*!GAMESTATEMENU_HPP_*/
