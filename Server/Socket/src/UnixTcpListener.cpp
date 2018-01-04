#include	        <signal.h>
#include	        <netdb.h>
#include		"../inc/Socket/UnixTcpListener.hpp"

UnixTcpListener::UnixTcpListener() :
  TcpListener(),
  _closed(true)
{}

UnixTcpListener::~UnixTcpListener()
{
  if (!_closed)
    close(_socket);
}

bool			UnixTcpListener::listenSocket(uint16_t port)
{
  struct protoent	*pe;
  int			optval = 1;

  signal(SIGPIPE, SIG_IGN);
  _port = port;
  if ((pe = getprotobyname("TCP")) == NULL)
    return false;
  if ((_socket = socket(AF_INET, SOCK_STREAM, pe->p_proto)) < 0)
    return false;
  _sin.sin_family = AF_INET;
  _sin.sin_addr.s_addr = INADDR_ANY;
  _sin.sin_port = htons(port);
  _closed = false;
  if (setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0)
    return false;
  if (bind(_socket, (struct sockaddr *)&_sin, sizeof(_sin)) < 0)
    return false;
  if (listen(_socket, SOMAXCONN) < 0)
    return false;
  return true;
}

bool			UnixTcpListener::acceptSocket(TcpSocket *socket)
{
  struct sockaddr_in	sin;
  socklen_t		addrlen = sizeof(sin);
  int		        remoteSocket;

  if ((remoteSocket = accept(_socket, (struct sockaddr *)&sin, &addrlen)) < 0)
    return false;
  socket->create(&remoteSocket, inet_ntoa(sin.sin_addr), ntohs(sin.sin_port));
  return true;
}

bool			UnixTcpListener::newClient()
{
  fd_set		rfds;
  struct timeval	tv;
  int			retval;

  FD_ZERO(&rfds);
  FD_SET(_socket, &rfds);
  tv.tv_sec = 0;
  tv.tv_usec = 0;
  retval = select(_socket + 1, &rfds, NULL, NULL, &tv);
  if (retval <= 0)
    return false;
  return true;
}
