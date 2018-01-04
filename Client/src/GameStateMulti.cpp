//
// GameStateStart.cpp for  in /home/noel_f/rendu/tmpRTYPE/Client
//
// Made by Gabriel NOEL
// Login   <noel_f@epitech.net>
//
// Started on  Mon Jan 18 12:31:10 2016 Gabriel NOEL
// Last update Sun Jan 24 22:14:05 2016 Gabriel NOEL
//

#include	"GameStateMulti.hpp"

GameStateMulti::GameStateMulti(Game *game)
{
  socket = TcpSocket::newSocket();
  _player_update = new command::player_dataCli();
  _elapsed = 0;
  _start = false;
  _game = game;
  sf::Vector2f pos = sf::Vector2f(_game->_window.getSize());
  _view.setSize(pos);
  pos *= 0.5f;
  _view.setCenter(pos);

  /* Loading des textures */
  /* Texture du background */
  _background.setTexture(_game->_txmgr.getRef("background"));
  _background.setScale(
  		       float(WINDOW_W) / float(_background.getTexture()->getSize().x),
  		       float(WINDOW_H) / float(_background.getTexture()->getSize().y));
  /* Texture du vaisseau */
  _ship[0].init(_game->_txmgr.getRef("ship"), 0, 3);
  _ship[1].init(_game->_txmgr.getRef("ship"), 0, 2);
  _ship[2].init(_game->_txmgr.getRef("ship"), 0, 4);
  _ship[3].init(_game->_txmgr.getRef("ship"), 0, 1);

  if (!socket->connectSocket(game->ip, 4242))
    {
      std::cout << "CONNECT SOCKET FAILURE" << std::endl;
      throw std::invalid_argument(game->ip);
    }

  /* Création ROOM */
  char packet[6];
  uint16_t tmp = htons(command::JOIN_ROOM);
  uint32_t idroom = htonl(0);
  memcpy(packet, &tmp, sizeof(tmp));
  memcpy(packet + sizeof(tmp), &idroom, sizeof(idroom));
  socket->sendData(packet, sizeof(packet));
}

GameStateMulti::~GameStateMulti()
{
  delete socket;
  delete _player_update;
}

void		GameStateMulti::draw(const float dt)
{
  (void)dt;
  _game->_window.setView(_view);
  _game->_window.clear(sf::Color::Black);

  _game->_window.draw(_background);
  _game->_window.draw(_ship[0]);
  _game->_window.draw(_ship[1]);
  _game->_window.draw(_ship[2]);
  _game->_window.draw(_ship[3]);
  for (size_t i = 0; i < _missiles.size(); i++)
    _game->_window.draw(_missiles[i]);
  for (size_t i = 0; i < _missiless.size(); i++)
    _game->_window.draw(_missiless[i].getSprite());
  for (size_t i = 0; i < _explos.size(); i++)
    _game->_window.draw(_explos[i].getSprite());
}

void				GameStateMulti::update(const float dt)
{
  _elapsed += dt;
  for (size_t i = 0; i < _explos.size(); i++)
    _explos[i].updateExpl(dt);
  for (size_t i = 0; i < _missiless.size(); i++)
    _missiless[i].updateMenu(dt);
  size_t i = _explos.size();
  while (i > 0)
    {
      if (_explos[i].getRank())
	_explos.erase(_explos.begin()+i);
      i -= 1;
    }

  if (_elapsed >= 0.01 && _start)
    {
      _elapsed = 0;
      uint16_t ss = _player_update->dir;
      //std::cout << "[DEBUG] tmp.move = " << ss << std::endl;
      char packet[2 + sizeof(_player_update)];
      uint16_t tmp = htons(command::DATA);
      memcpy(packet, &tmp, sizeof(tmp));
      memcpy(packet + sizeof(tmp), (void *)_player_update, sizeof(_player_update));
      socket->sendData(packet, sizeof(packet));
    }

  uint16_t			cmd;
  socket->recvData(data, receive);
  if (receive < sizeof(cmd))
    return;
  command::player_dataServ	pu[4];
  uint32_t			nb;

  cmd = ntohs(*((uint16_t *)data));
  data = (char *)data + sizeof(cmd);
  receive -= sizeof(cmd);

  if (cmd == command::DATA)
    {
      //std::cout << "[RECV] ->";
      nb = ntohl(*((uint32_t *)data));
      data = (char *)data + sizeof(nb);
      receive -= sizeof(nb);
      memset(&pu[0], 0, sizeof(pu[0]));
      memcpy(&pu[0], data, sizeof(pu[0]));
      //std::cout << "[" << cmd << "][" << nb << "][" << pu[0].id << "][" << pu[0].x << ";" << pu[0].y << "]";
      _ship[0].setPosition(pu[0].x, pu[0].y);
      for (int i = 1; i < nb; i++)
	{
	  data = (char *)data + sizeof(pu[i - 1]);
	  receive -= sizeof(pu[i - 1]);
	  memset(&pu[i], 0, sizeof(pu[i]));
	  memcpy(&pu[i], data, sizeof(pu[i]));
	  //std::cout << "[" << cmd << "][" << nb << "][" << pu[i].id << "][" << pu[i].x << ";" << pu[i].y << "]";
      _ship[i].setPosition(pu[i].x, pu[i].y);
	}
      //std::cout << "[END OF RECV]" << std::endl;
    }
}

bool	        GameStateMulti::handleInput()
{
  sf::Event	event;

  _player_update->dir = 0x0;
  _player_update->fire = false;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    _player_update->dir += player_move::LEFT;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    _player_update->dir += player_move::RIGHT;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    _player_update->dir += player_move::UP;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    _player_update->dir += player_move::DOWN;

  //Parcourir la liste, et del dans le if
  for (size_t i = 0; i < _missiles.size(); i++)
    {
      _missiles[i].move(M_SPEED, 0);
      if (_missiles[i].getPosition().x > WINDOW_W - 100)
	_missiles.erase(_missiles.begin()+i);
    }
  for (size_t i = 0; i < _missiless.size(); i++)
    {
      _missiless[i].move(M_SPEED, 0);
      if (_missiless[i].getSprite().getPosition().x > WINDOW_W - 100)
	_missiless.erase(_missiless.begin()+i);
    }
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
	    switch (event.key.code)
	      {
	      case sf::Keyboard::Escape:
		_game->popState();
		return (false);
		break;
	      case sf::Keyboard::T:
		addExplo(200, 200);
		addExplo(480, 400);
		break;
	      case sf::Keyboard::Space:
		addMissile();
		break;
	      case sf::Keyboard::R:
		ready();
		break;
	      default:
		break;
	      }
	  }
	default:
	  break;
	}
    }
  return (true);
}

void		GameStateMulti::ready()
{
  if (_start)
    return;
  _start = true;
  /* We are Ready to play */
  char rdy[2];
  uint16_t ready = htons(command::READY);
  memcpy(rdy, &ready, sizeof(ready));
  socket->sendData(rdy, sizeof(rdy));

  socket->recvData(data, receive);
  if (data != NULL)
    std::cout << "[RECV] ->[" << ntohs(*((uint16_t *)data)) << "][END OF RECV]" << std::endl;
}

void	        GameStateMulti::addMissile()
{
  /* Texture du missile */
  /*  sf::Sprite	tmp;

  tmp.setTexture(_game->_txmgr.getRef("missile"));
  tmp.setTextureRect(sf::IntRect(0, 40, 50, 6));
  tmp.setPosition(_ship.getPosition());
  tmp.setScale(2, 2);
  _missiles.push_back(tmp);
  */
  AnimatedSprite tmps(_game->_txmgr.getRef("missile"), 50, 6, 4, 1, 0, 40, 0.1);

  tmps.setPosition(_ship[0].getPosition().x - 42, _ship[0].getPosition().y);
  tmps.getSprite().setScale(0.337, 2);
  _missiless.push_back(tmps);
}

void	        GameStateMulti::addExplo(int x, int y)
{
  AnimatedSprite tmp(_game->_txmgr.getRef("missile"), 30, 30, 6, 1, 0, 50, 0.1);

  tmp.setPosition(x, y);
  tmp.getSprite().setScale(2, 2);
  _explos.push_back(tmp);
}

void	        GameStateMulti::loadGame()
{
  std::cout << "YOU SHALL NOT PASS" << std::endl;
}
