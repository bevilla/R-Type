#pragma once

#include			<iostream>
#include			<stdint.h>
#include			<string>

class				UdpSocket
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

public:
  UdpSocket() {}
  virtual ~UdpSocket() {}

  virtual bool			init() = 0;
  virtual bool			bindSocket(uint16_t port) = 0;

  virtual bool			sendData(const void *data, size_t size, const std::string &ipaddr, uint16_t port) = 0;
  virtual int			receive(void *&data, size_t &receive, std::string &ipaddr, uint16_t &port) = 0;

  virtual int			lastMsg() = 0;

  static void			deleteMsg(const void *data);

  static UdpSocket		*newSocket();
};
