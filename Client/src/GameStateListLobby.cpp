//
// GameStateGame.cpp for GameStateGame in /home/trupin_t/rendu/LDD/src
//
// Made by Thomas Trupin
// Login   <trupin_t@epitech.net>
//
// Started on Sat Dec 12 06:00:29 2015 Thomas Trupin
// Last update Sat Jan 23 19:52:53 2016 Gabriel NOEL
//

#include	"GameStateListLobby.hpp"

GameStateListLobby::GameStateListLobby(Game *game)
{
  _game = game;
  sf::Vector2f pos = sf::Vector2f(_game->_window.getSize());
  _view.setSize(pos);
  pos *= 0.5f;
  _view.setCenter(pos);


  TcpSocket *socket = TcpSocket::newSocket();
  void *data;
  size_t receive;

  if (!socket->connectSocket("127.0.0.1", 4242))
    std::cout << "Ya un Schmolle dans le bignou" << std::endl;

  socket->sendData("dsfqsd", 6);
  socket->recvData(data, receive); // renv enum

  delete socket;
}

void		GameStateListLobby::draw(const float)
{
  _game->_window.setView(_view);
  _game->_window.clear(sf::Color::Black);
}

void	        GameStateListLobby::update(const float)
{

}

bool	        GameStateListLobby::handleInput()
{
  sf::Event	event;

  while (_game->_window.pollEvent(event))
    {
      if (event.type ==  sf::Event::Closed)
      {
	_game->_window.close();
	break;
      }
    }
  return (true);
}
