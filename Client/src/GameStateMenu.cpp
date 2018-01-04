//
// GameStateMenu.cpp<2> for  in /home/noel_f/rendu/tmpRTYPE/Client
//
// Made by Gabriel NOEL
// Login   <noel_f@epitech.net>
//
// Started on  Mon Jan 18 12:32:01 2016 Gabriel NOEL
// Last update Sun Jan 24 15:30:43 2016 trupin_t
//

#include	"GameStateMenu.hpp"

GameStateMenu::GameStateMenu(Game *game) :
  _selector(game->_txmgr.getRef("selector_tile"), 650, 100, 1, 6, 0, 0, 0.07)
{
  //Première co au serveur ?
  _game = game;
  sf::Vector2f pos = sf::Vector2f(_game->_window.getSize());
  _view.setSize(pos);
  pos *= 0.5f;
  _view.setCenter(pos);

  _background.setTexture(_game->_txmgr.getRef("bg_menu"));
  _background.setScale(
  		       float(WINDOW_W) / float(_background.getTexture()->getSize().x),
  		       float(WINDOW_H) / float(_background.getTexture()->getSize().y));

  _select = 1;
  _selector.setPosition(MENU_X, MENU_Y);
}

void		GameStateMenu::draw(const float)
{
  _game->_window.setView(_view);
  _game->_window.clear(sf::Color::Black);
  _game->_window.draw(_background);
  _game->_window.draw(_selector.getSprite());
}

void		GameStateMenu::update(const float dt)
{
  if (_select > MENU_ENTRIES)
    {
      _select = 1;
      _selector.setPosition(MENU_X, MENU_Y);
    }
  if (_select <= 0)
    {
      _select = MENU_ENTRIES;
      _selector.setPosition(MENU_X, MENU_Y + MENU_GAP * (_select - 1));
    }
  _selector.updateMenu(dt);
}

bool		GameStateMenu::handleInput()
{
  sf::Event	event;

  while (_game->_window.pollEvent(event))
    {
      switch (event.type)
	{
	case sf::Event::Closed:
	  {
	    _game->_window.close();
	    break;
	  }
	case sf::Event::KeyReleased:
	  {
	    if (event.key.code == sf::Keyboard::Escape)
	      _game->_window.close();
	    else if (event.key.code == sf::Keyboard::Up)
	      {
		_game->_clickSnd.play();
		_select -= 1;
		_selector.move(0, - MENU_GAP);
	      }
	    else if (event.key.code == sf::Keyboard::Down)
	      {
		_game->_clickSnd.play();
		_select += 1;
		_selector.move(0, MENU_GAP);
	      }
	    else if (event.key.code == sf::Keyboard::Return)
	      this->select_choice();
	    else
	      break;
	  }
	case sf::Event::MouseMoved:
	  {
	    int x = event.mouseMove.x;
	    int y = event.mouseMove.y;

	    if (MENU_X <= x && x <= MENU_X + MENU_WIDTH)
	      if (MENU_Y <= y && y <= MENU_Y + (MENU_GAP * MENU_ENTRIES))
		{
		  _select = (y - (MENU_Y / MENU_ENTRIES) - MENU_GAP) / 100;
		  _selector.setPosition(MENU_X, MENU_Y + ((_select - 1) * MENU_GAP));
		}
	  }
	case sf::Event::MouseButtonPressed:
	  {
	    if (event.mouseButton.button == sf::Mouse::Left)
	      {
		int x = event.mouseButton.x;
		int y = event.mouseButton.y;
		if (MENU_X <= x && x <= MENU_X + MENU_WIDTH)
		  if (MENU_Y <= y && y <= MENU_Y + (MENU_GAP * MENU_ENTRIES))
		    this->select_choice();
	      }
	  }
	default:
	  break;
	}
    }
  return (true);
}

void		GameStateMenu::loadGame()
{
  _game->pushState(new GameStateStart(_game));
}

void		GameStateMenu::select_choice()
{
  _game->_selectSnd.play();
  if (_select == 1)
    this->loadGame();
  else if (_select == 2)
    _game->pushState(new GameStateMultiMenu(_game));
  else if (_select == 3)
    _game->pushState(new GameStateSettings(_game));
  else if (_select == 4)
    _game->_window.close();
}
