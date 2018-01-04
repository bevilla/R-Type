//
// GameStateSettings.hpp for GameStateSettings in /home/trupint/rendu/R-Type/Client
// 
// Made by trupin_t
// Login   <trupint@epitech.net>
// 
// Started on Sun Jan 24 14:35:13 2016 trupin_t
// Last update Sun Jan 24 17:15:02 2016 trupin_t
//

#ifndef GAMESTATESETTINGS_H_
# define GAMESTATESETTINGS_H_

#include	<SFML/Graphics.hpp>
#include	<iostream>
#include	"GameState.hpp"
#include	"GameStateStart.hpp"
#include	"GameStateMultiMenu.hpp"
#include	"AnimatedSprite.hpp"

#define		SE_MENU_X		230
#define		SE_MENU_Y		215
#define		SE_MENU_GAP		60
#define		SE_MENU_WIDTH		700

#define		SE_MENU_ENTRIES	3

class GameStateSettings : public GameState
{
public:
  GameStateSettings(Game *game);

  virtual void	draw(const float dt);
  virtual void	update(const float dt);
  virtual bool	handleInput();

private:
  sf::View		_view;
  sf::Sprite		_background;
  sf::Text		_name;
  AnimatedSprite	_selector;
  int			_select;
  bool			_return;
  bool			_editing;

  void			loadGame();
  void			select_choice();
};

#endif /*!GAMESTATESETTINGS_H_*/
