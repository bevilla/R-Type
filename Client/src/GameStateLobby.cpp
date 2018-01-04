//
// GameStateLobby.cpp for GameStateLobby in /home/trupint/rendu/R-Type/Client
//
// Made by trupin_t
// Login   <trupint@epitech.net>
//
// Started on Wed Jan 20 15:32:30 2016 trupin_t
// Last update Sun Jan 24 20:58:55 2016 Gabriel NOEL
//

#include	"GameStateLobby.hpp"

GameStateLobby::GameStateLobby(Game *game)
{
  _game = game;
  sf::Vector2f pos = sf::Vector2f(_game->_window.getSize());
  _view.setSize(pos);
  pos *= 0.5f;
  _view.setCenter(pos);
  _background.setTexture(_game->_txmgr.getRef("lobby_room"));
  _readyButton.setTexture(_game->_txmgr.getRef("ready_button"));
  _return = false;
  _isReady = false;
  _lobbyName.setFont(_game->_txmgr.getFontRef("neuropol"));
  for (int i = 0; i < 4; i++)
    {
      _playerNames[i].setFont(_game->_txmgr.getFontRef("neuropol"));
      _lights[i].setTexture(_game->_txmgr.getRef("green_light"));
      _lights[i].setPosition(LIGHTS_X, LIGHT_1+ (i * LIGHT_GAP));
    }
  _readyButton.setPosition(BUTTON_X, BUTTON_Y);
  _lobbyName.setFont(_game->_txmgr.getFontRef("neuropol"));
  _lobbyName.setPosition(LOBBY_NAME_X, LOBBY_NAME_Y);

  _playerNames[0].setPosition(PLAYERS_X, PLAYER_1);
  _playerNames[1].setPosition(PLAYERS_X, PLAYER_2);
  _playerNames[2].setPosition(PLAYERS_X, PLAYER_3);
  _playerNames[3].setPosition(PLAYERS_X, PLAYER_4);

  _lobbyName.setString("Rush fast XP");
}

void		GameStateLobby::draw(const float dt)
{
  (void)dt;
  _game->_window.setView(_view);
  _game->_window.clear(sf::Color::Black);
  _game->_window.draw(_background);
  _game->_window.draw(_readyButton);
  _game->_window.draw(_lobbyName);
  for (int i = 0; i < 4; i++)
    _game->_window.draw(_playerNames[i]);
  for (int i = 0; i < 4; i++)
    _game->_window.draw(_lights[i]);
}

void		GameStateLobby::update(const float)
{
  _game->_players[0].setName(_game->_playerName);
  for (int i = 0; i < 4; i++)
    {
      if (_game->_players[i]._isConected)
	{
	  _playerNames[i].setString(_game->_players[i].getName());
	  if (_game->_players[i]._isReady)
	    _lights[i].setTexture(_game->_txmgr.getRef("green_light"));
	  else
	    _lights[i].setTexture(_game->_txmgr.getRef("red_light"));
	}
      else
	{
	  _playerNames[i].setString("");
	  _lights[i].setTexture(_game->_txmgr.getRef("grey_light"));
	}
    }
  if (_isReady)
    _readyButton.setTexture(_game->_txmgr.getRef("unready_button"));
  else
    _readyButton.setTexture(_game->_txmgr.getRef("ready_button"));
  if (_return)
    _game->popState();
}

bool		GameStateLobby::handleInput()
{
  sf::Event	event;

  while (_game->_window.pollEvent(event))
    {
      switch (event.type)
	{
	case sf::Event::Closed:
	  _game->_window.close();
	case sf::Event::KeyReleased:
	  if (event.key.code == sf::Keyboard::Escape)
	    _return = true;
	case sf::Event::MouseButtonPressed:
	  if (_readyButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
	    {
	      _game->_players[0]._isReady = !_game->_players[0]._isReady;
	      _isReady = !_isReady;
	    }
	default:
	  break;
	}
    }
  return (true);
}
