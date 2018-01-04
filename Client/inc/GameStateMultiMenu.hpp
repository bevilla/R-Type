//
// GameStateMultiMenu.hpp for GameStateMultiMenu in /home/trupint/rendu/R-Type/Client
//
// Made by trupin_t
// Login   <trupint@epitech.net>
//
// Started on Wed Jan 20 16:17:47 2016 trupin_t
// Last update Sun Jan 24 16:31:55 2016 Gabriel NOEL
//

#ifndef GAMESTATEMULTIMENU_H_
# define GAMESTATEMULTIMENU_H_

#include	<SFML/Graphics.hpp>
#include	<iostream>
#include	"GameState.hpp"
#include	"GameStateStart.hpp"
#include	"AnimatedSprite.hpp"
#include	"GameStateMenu.hpp"
#include	"GameStateMulti.hpp"
#include	"GameStateLobby.hpp"
#include	"GameStateListLobby.hpp"

//	Menu entries coord. :

#define		MULTI_MENU_ENTRIES	4

#define		MULTI_X			130
#define		MULTI_Y			255
#define		MULTI_GAP		90
#define		MULTI_WIDTH		600

class GameStateMultiMenu : public GameState
{
public:
  GameStateMultiMenu(Game *game);

  virtual void	draw(const float dt);
  virtual void	update(const float dt);
  virtual bool	handleInput();

private:
  sf::View		_view;
  sf::Sprite		_background;
  AnimatedSprite	_selector;
  int			_select;
  bool			_return;

  void			select_choice();
  void			createLobby();
};
#endif /*!GAMESTATEMULTIMENU_H_*/
