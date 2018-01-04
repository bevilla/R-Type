//
// Game.cpp for Game in /home/trupin_t/rendu/gomoku_client
//
// Made by Thomas Trupin
// Login   <trupin_t@epitech.net>
//
// Started on Thu Dec 10 15:53:30 2015 Thomas Trupin
// Last update Sun Jan 24 18:49:50 2016 trupin_t
//

#include	"Game.hpp"
#include	"GameState.hpp"

Game::Game() : _playerName("Defaultkek")
{
  this->loadTextures();
  this->loadSounds();
  this->loadFonts();
  _window.create(sf::VideoMode(WINDOW_W, WINDOW_H), WINDOW_NAME);
  _window.setFramerateLimit(60);

  // TEST
  _players[0].setID(0);
  _players[1].setID(1);
  _players[2].setID(2);
  _players[0].setName(_playerName);
  _players[1].setName("toplel");
  _players[2].setName("toplawl");
  _players[0]._isConected = true;
  _players[1]._isConected = true;
  _players[1]._isReady = true;
}

Game::~Game()
{
  while (!_states.empty())
    popState();
}

void		Game::loadTextures()
{
  _txmgr.loadTexture("background", JPG_DIR("bg"));
  _txmgr.loadTextureFromImage("ship", GIF_DIR("ship"));
  _txmgr.loadTextureFromImage("missile", GIF_DIR("missile"));
  _txmgr.loadTextureFromImage("bg_menu", SPR_DIR("bg_menu"));
  _txmgr.loadTextureFromImage("selector_tile", SPR_DIR("selector_tile"));
  _txmgr.loadTextureFromImage("multi_menu", SPR_DIR("multi_menu"));
  _txmgr.loadTextureFromImage("multi_selector", SPR_DIR("multi_selector"));
  _txmgr.loadTextureFromImage("ready_button", SPR_DIR("ready_button"));
  _txmgr.loadTextureFromImage("lobby_room", SPR_DIR("lobby_room"));
  _txmgr.loadTextureFromImage("green_light", SPR_DIR("green_light"));
  _txmgr.loadTextureFromImage("red_light", SPR_DIR("red_light"));
  _txmgr.loadTextureFromImage("grey_light", SPR_DIR("grey_light"));
  _txmgr.loadTextureFromImage("unready_button", SPR_DIR("unready_button"));
  _txmgr.loadTextureFromImage("bg_settings", SPR_DIR("bg_settings"));
}

void		Game::loadSounds()
{
  _txmgr.loadSound("click", SND_DIR("click"));
  _txmgr.loadSound("select", SND_DIR("select"));
  _menuMusic.openFromFile("ressources/music/nightcore_menu.ogg");
  _menuMusic.play();
  _menuMusic.setLoop(true);
  _menuMusic.setVolume(10);

  _clickSnd.setBuffer(_txmgr.getSoundRef("click"));
  _selectSnd.setBuffer(_txmgr.getSoundRef("select"));
}

void		Game::loadFonts()
{
  _txmgr.loadFont("neuropol", TTF_DIR("neuropol"));
}

void		Game::pushState(GameState *state)
{
  _states.push(state);
}

void		Game::popState()
{
  delete _states.top();
  _states.pop();
}

void		Game::changeState(GameState *state)
{
  if (!_states.empty())
    popState();
  pushState(state);
}

GameState	*Game::peekState()
{
  if (_states.empty())
    return (nullptr);
  return (_states.top());
}

void		Game::gameLoop()
{
  sf::Clock	clock;

  while (_window.isOpen())
    {
      sf::Time	elapsed = clock.restart();
      float	dt = elapsed.asSeconds();

      if (peekState() == nullptr)
	continue;
      if (!peekState()->handleInput())
	continue;
      peekState()->update(dt);
      _window.clear(sf::Color::Black);
      peekState()->draw(dt);
      _window.display();
    }
}
