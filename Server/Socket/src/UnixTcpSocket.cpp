#include	        <signal.h>
#include	        <netdb.h>
#include	        <time.h>
#include		"../inc/Socket/UnixTcpSocket.hpp"

UnixTcpSocket::UnixTcpSocket() :
  TcpSocket(),
  _closed(true),
  _client(false),
  _lastMsg(time(NULL))
{
  signal(SIGPIPE, SIG_IGN);
}

UnixTcpSocket::~UnixTcpSocket()
{
  if (!_closed)
    close(_socket);
}

const std::string	&UnixTcpSocket::getRemoteAddress() const
{
  return _remoteIpAddress;
}

uint16_t		UnixTcpSocket::getRemotePort() const
{
  return _remotePort;
}

bool			UnixTcpSocket::connectSocket(const std::string &ipAddress, uint16_t port)
{
  struct protoent	*pe;
  struct sockaddr_in    sin;

  _client = true;
  if ((pe = getprotobyname("TCP")) == NULL)
    return false;
  if ((_socket = socket(AF_INET, SOCK_STREAM, pe->p_proto)) < 0)
    return false;
  _closed = false;
  sin.sin_family = AF_INET;
  sin.sin_addr.s_addr = inet_addr(ipAddress.c_str());
  sin.sin_port = htons(port);
  if (connect(_socket, (struct sockaddr *)&sin, sizeof(sin)) < 0)
    return false;
  return true;
}

bool		        UnixTcpSocket::sendData(const void *data, size_t size)
{
  uint32_t		len = htonl(size);

  if (send(_client ? _socket : _remoteSocket, &len, sizeof(len), 0) < 0)
    return false;
  if (send(_client ? _socket : _remoteSocket, data, size, 0) < 0)
    return false;
  return true;
}

int			UnixTcpSocket::receive(void *&data, size_t &receive)
{
  char			tmp[RECVLEN];
  fd_set		rfds;
  struct timeval	tv;
  int			retval;
  int			socket = _client ? _socket : _remoteSocket;

  data = NULL;
  FD_ZERO(&rfds);
  FD_SET(socket, &rfds);
  tv.tv_sec = 0;
  tv.tv_usec = 0;
  retval = select(socket + 1, &rfds, NULL, NULL, &tv);
  if (retval == -1)
    return TCP_ERROR;
  else if (!retval)
    {
      receive = 0;
      return TCP_NODATA;
    }
  if ((receive = recv(socket, tmp, RECVLEN, 0)) == (size_t)-1)
    return TCP_ERROR;
  if (receive)
    {
      _lastMsg = time(NULL);
      data = new char[receive];
      for (size_t i = 0; i < receive; i++)
	((char *)data)[i] = tmp[i];
    }
  return TCP_OK;
}

void			UnixTcpSocket::create(void *socket, const std::string &ipaddr, uint16_t port)
{
  _remoteSocket = *((int *)socket);
  _remoteIpAddress = ipaddr;
  _remotePort = port;
}

int			UnixTcpSocket::lastMsg()
{
  return time(NULL) - _lastMsg;
}
