#pragma once

#include			<netinet/in.h>
#include			<sys/socket.h>
#include			<arpa/inet.h>
#include			<unistd.h>
#include		        "UdpSocket.hpp"

class			        UnixUdpSocket : public UdpSocket
{
private:
  int				_socket;
  bool				_closed;
  int				_lastMsg;

public:
  UdpSocket() {}
  virtual ~UdpSocket() {}

  virtual bool			init();
  virtual bool			bindSocket(uint16_t port);

  virtual bool			sendData(const void *data, size_t size, const std::string &ipaddr, uint16_t port);
  virtual int			receive(void *&data, size_t &receive, std::string &ipaddr, uint16_t &port);

  virtual int			lastMsg();
};
