#include		<iostream>
#include		<cstdlib>
#include		"Server.hpp"

Server::Server() :
  _run(false),
  _errcode(0),
  _listener(NULL)
{
  for (size_t i = 0; i < command::COUNT; i++)
    _cmdfunc[i] = NULL;

  _cmdfunc[command::LIST_ROOM] = &Server::cmdListRoom;
  _cmdfunc[command::JOIN_ROOM] = &Server::cmdJoinRoom;
  _cmdfunc[command::CREATE_ROOM] = &Server::cmdCreateRoom;
  _cmdfunc[command::LEAVE_ROOM] = &Server::cmdLeaveRoom;
  _cmdfunc[command::READY] = &Server::cmdReady;
  _cmdfunc[command::DATA] = &Server::cmdDataServ;
}

Server::~Server()
{
  for (size_t i = 0; i < _clients.size(); i++)
    delete _clients[i];
  for (size_t i = 0; i < _players.size(); i++)
    delete _players[i];
  for (size_t i = 0; i < _rooms.size(); i++)
    delete _rooms[i];
  if (_listener)
    delete _listener;
}

bool			Server::init(uint16_t port)
{
  if (!(_listener = TcpListener::newListener()))
    return false;
  if (!_listener->listenSocket(port))
    return false;
  _run = true;
  _rooms.push_back(new Room("Topkek :^)"));
  return true;
}

int			Server::run()
{
  while (_run)
    {
      if (_listener->newClient() && !addPlayer())
	return -1;
      if (!handleClientMsg())
	return -1;
      updateLobby();

#if defined(__linux__)
      usleep(10);
#elif defined(WIN32)
      Sleep(1);
#endif

    }
  return _errcode;
}

bool			Server::addPlayer()
{
  TcpSocket		*tmp = TcpSocket::newSocket();

  if (tmp == NULL)
    return false;
  if (!(_listener->acceptSocket(tmp)))
    {
      delete tmp;
      return false;
    }
  std::cout << "new player " << *tmp << std::endl;
  _clients.push_back(tmp);
  _players.push_back(new Player);
  std::cout << *(_clients.back()) << std::endl;
  return true;
}

void			Server::delPlayer(size_t pos)
{
  uint16_t		cmd = htons(command::DISCONNECT);

  if (_players[pos]->getRoom() != Player::NO_ROOM)
    _rooms[roomIdToVectorPos(_players[pos]->getRoom())]->removePlayer(_players[pos]);
  _clients[pos]->sendData(&cmd, sizeof(cmd));
  std::cout << "disconnected: " << *(_clients[pos]) << std::endl;
  delete _clients[pos];
  delete _players[pos];
  _clients.erase(_clients.begin() + pos);
  _players.erase(_players.begin() + pos);
}

bool			Server::handleClientMsg()
{
  for (size_t i = 0; i < _clients.size(); i++)
    {
      void		*data;
      size_t		receive;
      int		ret;
      bool		flag = false;

      while ((ret = _clients[i]->recvData(data, receive)) == TcpSocket::TCP_OK)
	{
	  bool		del = (data == NULL);

	  if (data)
	    {
	      del = !handleClientMsg(i, data, receive);
	      TcpSocket::deleteMsg(data);
	    }
	  if (del)
	    {
	      delPlayer(i--);
	      flag = true;
	      break ;
	    }
	}
      if (flag)
	continue ;
      if (_clients[i]->lastMsg() >= 3000)
	{
	  uint16_t	cmd = htons(command::TIMEOUT);

	  _clients[i]->sendData(&cmd, sizeof(cmd));
	  delPlayer(i--);
	  continue ;
	}
    }
  return true;
}

bool			Server::handleClientMsg(size_t pos, void *data, size_t receive)
{
  uint16_t		cmd;

  if (receive < sizeof(cmd))
    return false;
  cmd = ntohs(*((uint16_t *)data));
  data = (char *)data + sizeof(cmd);
  receive -= sizeof(cmd);
  //std::cout << "from " << *(_clients[pos]) << "> [" << cmd << ']';
  //std::cout.write((char *)data, receive);
  //std::cout << std::endl;

  // debug
  if (receive >= 4 && (memcmp(data, "exit", 4) == 0))
    _run = false;
  // debug

  if (cmd >= command::COUNT || _cmdfunc[cmd] == NULL)
    return false;
  return (this->*_cmdfunc[cmd])(pos, data, receive);
}

bool			Server::cmdListRoom(size_t pos, void *data, size_t size)
{
  uint16_t		cmd = htons(command::LIST_ROOM);
  uint32_t	        nb_room = htonl(_rooms.size());
  command::room_info	*room = new command::room_info[ntohl(nb_room)];
  size_t		size_packet = sizeof(cmd) + sizeof(nb_room) + (sizeof(*room) * ntohl(nb_room));
  char			*packet = new char[size_packet];

  memcpy(packet, &cmd, sizeof(cmd));
  memcpy(packet + sizeof(cmd), &nb_room, sizeof(nb_room));
  for (size_t i = 0; i < _rooms.size(); i++)
    {
      Room		*cur_room = _rooms[i];

      room[i].id = htonl(cur_room->getId());
      room[i].ingame = cur_room->isInGame();
      memset(room[i].name, 0, sizeof(room[i].name));
      memcpy(room[i].name, _rooms[i]->getName().c_str(),
	     MIN(sizeof(room[i].name) - 1, _rooms[i]->getName().size()));
      for (size_t j = 0; j < 4; j++)
	{
	  command::player_info *cur_player_info = &(room[i].players[j]);
	  const Player	*cur_player = cur_room->getPlayer(j);

	  cur_player_info->id = htonl((uint32_t)-1);
	  memset(cur_player_info->name, 0, sizeof(cur_player_info->name));
	  if (cur_player)
	    {
	      cur_player_info->id = htonl(cur_player->getId());
	      memcpy(cur_player_info->name, cur_player->getName().c_str(),
		     MIN(sizeof(cur_player_info->name) - 1,
			 cur_player->getName().size()));
	    }
	}
    }
  memcpy(packet + sizeof(cmd) + sizeof(nb_room), room, (sizeof(*room) * ntohl(nb_room)));
  _clients[pos]->sendData(packet, size_packet);
  delete[] packet;
  delete[] room;
  return true;
}

bool			Server::cmdJoinRoom(size_t pos, void *data, size_t size)
{
  uint16_t		cmd = htons(command::OK);
  uint32_t		id;

  if (size != sizeof(id))
    return false;
  memcpy(&id, data, sizeof(id));
  id = ntohl(id);
  if (id >= _rooms.size())
    return false;
  if (!(_rooms[id]->addPlayer(_players[pos])))
    cmd = htons(command::KO);
  _clients[pos]->sendData(&cmd, sizeof(cmd));
  return true;
}

bool			Server::cmdCreateRoom(size_t pos, void *data, size_t size)
{
  command::room_info	room;
  uint16_t		cmd = htons(command::OK);

  memset(room.name, 0, sizeof(room.name));
  if (size != sizeof(room.name))
    return false;
  memcpy(room.name, data, sizeof(room.name) - 1);
  _rooms.push_back(new Room(room.name));
  if (!(_rooms.back()->addPlayer(_players[pos])))
    cmd = htons(command::KO);
  _clients[pos]->sendData(&cmd, sizeof(cmd));
  return true;
}

bool			Server::cmdLeaveRoom(size_t pos, void *data, size_t size)
{
  if (_players[pos]->getRoom() == Player::NO_ROOM)
    return false;
  if (!(_rooms[roomIdToVectorPos(_players[pos]->getRoom())]->removePlayer(_players[pos])))
    return false;
  return true;
}

void			Server::updateLobby()
{
  for (size_t i = 0; i < _rooms.size(); i++)
    {
      Room		*room = _rooms[i];

      if (room->getNbPlayer() == 0 && i)
	{
	  delRoom(i--);
	  continue ;
	}
      if (room->playersReady() && !room->isInGame())
	startRoom(i);
      if (room->isInGame() && ((time(NULL) - room->getLastEnemyTime()) >= (rand() % 10 + 5)))
	addEnemy(i);
    }
}

void			Server::delRoom(size_t pos)
{
  delete _rooms[pos];
  _rooms.erase(_rooms.begin() + pos);
}

void			Server::startRoom(size_t pos)
{
  Room			*room = _rooms[pos];
  uint16_t		cmd = htons(command::START);

  for (size_t i = 0; i < 4; i++)
    {
      if (room->getPlayer(i))
	{
	  size_t		playerPos = playerIdToVectorPos(room->getPlayer(i)->getId());

	  _clients[playerPos]->sendData(&cmd, sizeof(cmd));
	  _players[playerPos]->setInGame(true);
	}
    }
  _rooms[pos]->setInGame(true);
}

void			Server::addEnemy(size_t pos)
{
  Room			*room = _rooms[pos];
  Enemy			*enemy = new Enemy();
  uint16_t		cmd = htons(command::NEW_ENEMY);
  command::player_dataServ enemydata;
  char			*packet = new char[sizeof(cmd) + sizeof(enemydata)];

  room->addEnemy(enemy);
  enemydata.id = enemy->getId();
  enemydata.x = enemy->getX();
  enemydata.y = enemy->getY();
  memcpy(packet, &cmd, sizeof(cmd));
  memcpy(packet + sizeof(cmd), &enemydata, sizeof(enemydata));
  for (size_t i = 0; i < 4; i++)
    {
      if (room->getPlayer(i))
	{
	  size_t		playerPos = playerIdToVectorPos(room->getPlayer(i)->getId());

	  _clients[playerPos]->sendData(&packet, sizeof(cmd) + sizeof(enemydata));
	}
    }
  room->updateLastEnemyTime();
  delete[] packet;
}

bool			Server::cmdReady(size_t pos, void *data, size_t size)
{
  if (_players[pos]->getRoom() == Player::NO_ROOM)
    return false;
  _players[pos]->setReady(!_players[pos]->isReady());
  return true;
}

bool        Server::cmdDataServ(size_t pos, void *data, size_t size)
{

  command::player_dataCli   *client = new command::player_dataCli;
  uint16_t		              cmd = htons(command::DATA);
  uint32_t	                nb_player = htonl(_rooms[roomIdToVectorPos(_players[pos]->getRoom())]->getNbPlayer());
  command::player_dataServ	*stPlayer = new command::player_dataServ[ntohl(nb_player)];
  size_t		                size_packet = sizeof(cmd) + sizeof(nb_player) + sizeof(*stPlayer) * ntohl(nb_player);
  char			                *packet = new char[size_packet];
  int                       a = 1;

  _players[pos]->runtime();
  memcpy(client, (command::player_dataCli *) data, sizeof(client));
  if (client->dir < 16 && client->dir >= 0 && _players[pos]->getDuration() > 0.001)
    _players[pos]->mouv(client->dir);
  if (_players[pos]->getRoom() == Player::NO_ROOM || _players[pos]->isReady() == false)
    {
      delete[] stPlayer;
      return false;
    }

  memcpy(packet, &cmd, sizeof(cmd));
  memcpy(packet + sizeof(cmd), &nb_player, sizeof(nb_player));
  stPlayer[0].id = _players[pos]->getId();
  stPlayer[0].x = _players[pos]->getX();
  stPlayer[0].y = _players[pos]->getY();


  for (int i = 0; i != _players.size(); ++i)
    {
      if (_players[pos]->getRoom() == _players[i]->getRoom() && i != pos)
	{
	  stPlayer[a].id = _players[i]->getId();
	  stPlayer[a].x = _players[i]->getX();
	  stPlayer[a].y = _players[i]->getY();
	  a++;
	}
    }
  memcpy(packet + sizeof(cmd) + sizeof(nb_player) , stPlayer, sizeof(*stPlayer) * ntohl(nb_player));
  _clients[pos]->sendData(packet, size_packet);
  delete[] packet;
  delete client;
  delete[] stPlayer;
  return true;
}

size_t				Server::playerIdToVectorPos(size_t playerId)
{
  for (size_t i = 0; i < _players.size(); i++)
    if (_players[i]->getId() == playerId)
      return i;
  return (size_t)-1;
}

size_t				Server::roomIdToVectorPos(size_t roomId)
{
  for (size_t i = 0; i < _rooms.size(); i++)
    if (_rooms[i]->getId() == roomId)
      return i;
  return (size_t)-1;
}
