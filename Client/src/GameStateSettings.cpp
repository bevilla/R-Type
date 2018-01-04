//
// GameStateSettings.cpp for GameStateSettings in /home/trupint/rendu/R-Type/Client
// 
// Made by trupin_t
// Login   <trupint@epitech.net>
// 
// Started on Sun Jan 24 14:36:59 2016 trupin_t
// Last update Sun Jan 24 18:56:54 2016 trupin_t
//

#include	"GameStateSettings.hpp"

GameStateSettings::GameStateSettings(Game *game):
  _selector(game->_txmgr.getRef("selector_tile"), 650, 100, 1, 6, 0, 0, 0.07)
{
  _game = game;
  sf::Vector2f pos = sf::Vector2f(_game->_window.getSize());
  _view.setSize(pos);
  pos *= 0.5f;
  _view.setCenter(pos);

  _background.setTexture(_game->_txmgr.getRef("bg_settings"));
  _background.setScale(
  		       float(WINDOW_W) / float(_background.getTexture()->getSize().x),
  		       float(WINDOW_H) / float(_background.getTexture()->getSize().y));

  _select = 1;
  _selector.setPosition(SE_MENU_X, SE_MENU_Y);
  _return = false;
  _editing = false;
  _name.setFont(_game->_txmgr.getFontRef("neuropol"));
  _name.setPosition(465, 307);
  _name.setString(_game->_playerName);
  _name.setColor(sf::Color::White);
}


void		GameStateSettings::draw(const float)
{
  _game->_window.setView(_view);
  _game->_window.clear(sf::Color::Black);
  _game->_window.draw(_background);
  _game->_window.draw(_selector.getSprite());
  _game->_window.draw(_name);
}

void		GameStateSettings::update(const float dt)
{
  if (_select > SE_MENU_ENTRIES)
    {
      _select = 1;
      _selector.setPosition(SE_MENU_X, SE_MENU_Y);
    }
  if (_select <= 0)
    {
      _select = SE_MENU_ENTRIES;
      _selector.setPosition(SE_MENU_X, SE_MENU_Y + SE_MENU_GAP * (_select - 1));
    }
  _selector.updateMenu(dt);
  if (_return)
    _game->popState();
}

bool		GameStateSettings::handleInput()
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
		_game->_clickSnd.play();
		_select -= 1;
		_selector.move(0, - SE_MENU_GAP);
	      }
	    else if (event.key.code == sf::Keyboard::Down)
	      {
		_game->_clickSnd.play();
		_select += 1;
		_selector.move(0, SE_MENU_GAP);
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

	    if (SE_MENU_X <= x && x <= SE_MENU_X + SE_MENU_WIDTH)
	      if (SE_MENU_Y <= y && y <= SE_MENU_Y + (SE_MENU_GAP * SE_MENU_ENTRIES))
		{
		  _select = (y - (SE_MENU_Y / SE_MENU_ENTRIES) - SE_MENU_GAP) / 100;
		  _selector.setPosition(SE_MENU_X, SE_MENU_Y + ((_select - 1) * SE_MENU_GAP));
		}
	  }
	case sf::Event::MouseButtonPressed:
	  {
	    if (event.mouseButton.button == sf::Mouse::Left)
	      {
		int x = event.mouseButton.x;
		int y = event.mouseButton.y;
		if (SE_MENU_X <= x && x <= SE_MENU_X + SE_MENU_WIDTH)
		  if (SE_MENU_Y <= y && y <= SE_MENU_Y + (SE_MENU_GAP * SE_MENU_ENTRIES))
		    this->select_choice();
	      }
	  }
	case sf::Event::TextEntered:
	  {
	    if (_editing)
	      {
		std::string	temp = _name.getString();

		if (event.text.unicode == 8 && _name.getString().getSize() != 0)
		  temp.pop_back();
		else if (event.text.unicode > 48 && event.text.unicode < 128 && event.text.unicode != 58)
		  {
		    temp.push_back((char)event.text.unicode);
		  }
		_name.setString(temp);
		_game->_playerName = _name.getString();
	      }
	  }
	default:
	  break;
	}
      return (true);
    }
}

void		GameStateSettings::loadGame()
{
  _game->pushState(new GameStateStart(_game));
}

void		GameStateSettings::select_choice()
{
  _game->_selectSnd.play();
  if (_select == 1)
    {
      if (_game->_menuMusic.getStatus() == sf::SoundSource::Status::Paused)
	_game->_menuMusic.play();
      else
	_game->_menuMusic.pause();
    }
  else if (_select == 2)
    {
      if (!_editing)
	{
	  _game->_playerName = "";
	  _name.setString(_game->_playerName);
	}
      _editing = !_editing;
    }
  else if (_select == 3)
    _return = true;
}
