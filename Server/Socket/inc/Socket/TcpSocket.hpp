#pragma once

#include			<iostream>
#include			<stdint.h>
#include			<string>

#define RECV_MIN(a, b)		((a) < (b) ? (a) : (b))

class				TcpSocket
{
public:
  enum
    {
      TCP_OK,
      TCP_NODATA,
      TCP_ERROR
    };

protected:
  static const size_t		RECVLEN = 0xffff;
  char				_buff[RECVLEN];
  size_t			_len;
  uint16_t			_port;

public:
  TcpSocket();
  virtual ~TcpSocket();

  virtual const std::string	&getRemoteAddress() const = 0;
  virtual uint16_t		getRemotePort() const = 0;

  virtual bool			connectSocket(const std::string &ipAddress, uint16_t port) = 0;
  int				recvData(void *&data, size_t &receive);

  virtual bool			sendData(const void *data, size_t size) = 0;

  virtual void			create(void *socket, const std::string &ipaddr, uint16_t port) = 0;

  virtual int			lastMsg() = 0;

  uint16_t			getPort() const;

  static void			deleteMsg(const void *data);

  static TcpSocket		*newSocket();

private:
  virtual int			receive(void *&data, size_t &receive) = 0;
};

std::ostream			&operator<<(std::ostream &os, const TcpSocket &socket);
