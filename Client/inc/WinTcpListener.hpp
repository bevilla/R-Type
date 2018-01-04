#pragma once
#pragma comment(lib, "ws2_32.lib")

#include		<winsock2.h>
#include		"TcpListener.hpp"

class			WinTcpListener : public TcpListener
{
private:
  bool			_cleanup;
  struct sockaddr_in	_sin;
  WSADATA		_wsa;
  SOCKET		_socket;
  bool			_closed;

public:
  WinTcpListener();
  virtual ~WinTcpListener();

  virtual bool		listenSocket(uint16_t port);
  virtual bool		acceptSocket(TcpSocket *socket);
  virtual bool		newClient();
};
