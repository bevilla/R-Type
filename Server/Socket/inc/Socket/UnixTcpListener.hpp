#pragma once

#include		<netinet/in.h>
#include		<sys/socket.h>
#include		<arpa/inet.h>
#include		<unistd.h>
#include		"TcpListener.hpp"

class			UnixTcpListener : public TcpListener
{
private:
  struct sockaddr_in	_sin;
  int			_socket;
  bool			_closed;

public:
  UnixTcpListener();
  virtual ~UnixTcpListener();

  virtual bool		listenSocket(uint16_t port);
  virtual bool		acceptSocket(TcpSocket *socket);
  virtual bool		newClient();
};
