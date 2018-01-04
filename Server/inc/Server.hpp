#pragma once

#if defined(__linux__)
# include			<arpa/inet.h>
# include			<unistd.h>
#elif defined(WIN32)
# include			<Windows.h>
#endif

#include			<string.h>
#include			<vector>
#include			"Socket/TcpListener.hpp"
#include			"Socket/TcpSocket.hpp"
#include			"Socket/UdpSocket.hpp"
#include			"command.hpp"
#include			"Player.hpp"
#include			"Room.hpp"

#define MIN(a, b)		((a) < (b) ? (a) : (b))

class				Server
{
private:
  bool				_run;
  int				_errcode;
  std::vector<TcpSocket *>	_clients;
  std::vector<Player *>		_players;
  std::vector<Room *>		_rooms;
  TcpListener			*_listener;
  bool				(Server::*_cmdfunc[command::COUNT])(size_t, void *, size_t);

public:
  Server();
  ~Server();

  bool				init(uint16_t port = 4242);
  int				run();

private:
  bool				addPlayer();
  void				delPlayer(size_t pos);

  bool				handleClientMsg();
  bool				handleClientMsg(size_t pos, void *data, size_t receive);

  bool				cmdListRoom(size_t pos, void *data, size_t size);
  bool				cmdJoinRoom(size_t pos, void *data, size_t size);
  bool				cmdCreateRoom(size_t pos, void *data, size_t size);
  bool				cmdLeaveRoom(size_t pos, void *data, size_t size);
  bool			        cmdReady(size_t pos, void *data, size_t size);
  bool			        cmdDataServ(size_t pos, void *data, size_t size);

  void				updateLobby();
  void				delRoom(size_t pos);
  void				startRoom(size_t pos);
  void				addEnemy(size_t pos);

  size_t			playerIdToVectorPos(size_t playerId);
  size_t			roomIdToVectorPos(size_t roomId);
};
