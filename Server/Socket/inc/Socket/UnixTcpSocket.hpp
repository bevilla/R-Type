#pragma once

#include			<netinet/in.h>
#include			<sys/socket.h>
#include			<arpa/inet.h>
#include			<unistd.h>
#include			"TcpSocket.hpp"

class				UnixTcpSocket : public TcpSocket
{
private:
  int				_socket;
  bool				_closed;
  bool				_client;
  int				_remoteSocket;
  std::string			_remoteIpAddress;
  uint16_t			_remotePort;
  int				_lastMsg;

public:
  UnixTcpSocket();
  virtual ~UnixTcpSocket();

  virtual const std::string	&getRemoteAddress() const;
  virtual uint16_t		getRemotePort() const;

  virtual bool			connectSocket(const std::string &ipAddress, uint16_t port);

  virtual bool		        sendData(const void *data, size_t size);

  virtual void			create(void *socket, const std::string &ipaddr, uint16_t port);

  virtual int			lastMsg();

private:
  virtual int			receive(void *&data, size_t &receive);
};
