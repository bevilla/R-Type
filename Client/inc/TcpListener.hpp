#pragma once

#include		<stdint.h>
#include		"TcpSocket.hpp"

class			TcpListener
{
protected:
  uint16_t		_port;

public:
  TcpListener() {}
  virtual ~TcpListener() {}

  virtual bool		listenSocket(uint16_t port) = 0;
  virtual bool		acceptSocket(TcpSocket *socket) = 0;
  virtual bool		newClient() = 0;

  uint16_t		getPort() const;

  static TcpListener	*newListener();
};
