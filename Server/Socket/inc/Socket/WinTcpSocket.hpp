#pragma once
#pragma comment(lib, "ws2_32.lib")

#include			<winsock2.h>
#include			<Windows.h>
#include			"TcpSocket.hpp"

class				WinTcpSocket : public TcpSocket
{
private:
  WSADATA			_wsa;
  SOCKET			_socket;
  bool				_closed;
  bool				_client;
  bool				_cleanup;
  int				_remoteSocket;
  std::string			_remoteIpAddress;
  uint16_t			_remotePort;
  ULARGE_INTEGER		_lastMsg;

public:
  WinTcpSocket();
  virtual ~WinTcpSocket();

  virtual const std::string	&getRemoteAddress() const;
  virtual uint16_t		getRemotePort() const;

  virtual bool			connectSocket(const std::string &ipAddress, uint16_t port);

  virtual bool		        sendData(const void *data, size_t size);

  virtual int			lastMsg();
  
  virtual void			create(void *socket, const std::string &ipaddr, uint16_t port);

private:
  virtual int			receive(void *&data, size_t &receive);
};
