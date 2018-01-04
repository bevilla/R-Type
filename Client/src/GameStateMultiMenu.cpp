//
// GameStateMultiMenu.cpp for GameStateMultiMenu in /home/trupint/rendu/R-Type/Client
//
// Made by trupin_t
// Login   <trupint@epitech.net>
//
// Started on Wed Jan 20 16:17:30 2016 trupin_t
// Last update Sun Jan 24 16:31:30 2016 Gabriel NOEL
//

#include	"GameStateMultiMenu.hpp"

GameStateMultiMenu::GameStateMultiMenu(Game *game) :
  _selector(game->_txmgr.getRef("multi_selector"), 915, 100, 1, 6, 0, 0, 0.07)
{
  _game = game;
  sf::Vector2f pos = sf::Vector2f(_game->_window.getSize());
  _view.setSize(pos);
  pos *= 0.5f;
  _view.setCenter(pos);

  _background.setTexture(_game->_txmgr.getRef("multi_menu"));
  _background.setScale(
  		       float(WINDOW_W) / float(_background.getTexture()->getSize().x),
  		       float(WINDOW_H) / float(_background.getTexture()->getSize().y));

  _select = 1;
  _selector.setPosition(MULTI_X, MULTI_Y);
  _return = false;
}

void		GameStateMultiMenu::draw(const float)
{
  _game->_window.setView(_view);
  _game->_window.clear(sf::Color::Black);
  _game->_window.draw(_background);
  _game->_window.draw(_selector.getSprite());
}

void		GameStateMultiMenu::update(const float dt)
{
  if (_select > MULTI_MENU_ENTRIES)
    {
      _select = 1;
      _selector.setPosition(MULTI_X, MULTI_Y);
    }
  if (_select <= 0)
    {
      _select = MENU_ENTRIES;
      _selector.setPosition(MULTI_X, MULTI_Y + MULTI_GAP * (_select - 1));
    }
  _selector.updateMenu(dt);
  if (_return)
    _game->popState();
}

bool		GameStateMultiMenu::handleInput()
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
	      _return = true;
	    else if (event.key.code == sf::Keyboard::Up)
	      {
		_select -= 1;
		_selector.move(0, - MULTI_GAP);
		_game->_clickSnd.play();
	      }
	    else if (event.key.code == sf::Keyboard::Down)
	      {
		_game->_clickSnd.play();
		_select += 1;
		_selector.move(0, MULTI_GAP);
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

	    if (MULTI_X <= x && x <= MULTI_X + MULTI_WIDTH)
	      if (MULTI_Y <= y && y <= MULTI_Y + (MULTI_GAP * MULTI_MENU_ENTRIES))
		{
		  _select = (y - (MULTI_Y / MULTI_MENU_ENTRIES) - MULTI_GAP) / 100;
		  _selector.setPosition(MULTI_X, MULTI_Y + ((_select - 1) * MULTI_GAP));
		}
	  }
	case sf::Event::MouseButtonPressed:
	  {
	    if (event.mouseButton.button == sf::Mouse::Left)
	      {
		int x = event.mouseButton.x;
		int y = event.mouseButton.y;
		if (MULTI_X <= x && x <= MULTI_X + MULTI_WIDTH)
		  if (MULTI_Y <= y && y <= MULTI_Y + (MULTI_GAP * MULTI_MENU_ENTRIES))
		    this->select_choice();
	      }
	  }
	default:
	  break;
	}
    }
  return (true);
}

void		GameStateMultiMenu::createLobby()
{
  std::cout << "Creating new lobby" << std::endl;
  _game->pushState(new GameStateLobby(_game));
}

void		GameStateMultiMenu::select_choice()
{
  _game->_selectSnd.play();
  if (_select == 1)
    this->createLobby();
  else if (_select == 2)
    {
      std::cout << "Browse => GameStateBrowse" << std::endl;
      _game->pushState(new GameStateListLobby(_game));
    }
  else if (_select == 3)
    {
      std::cout << "QuickJoin => GameStateLobby" << std::endl;
      _game->pushState(new GameStateMulti(_game));
    }
  else if (_select == 4)
    _return = true;
}
