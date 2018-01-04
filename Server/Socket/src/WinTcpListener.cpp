#include		"../inc/Socket/WinTcpListener.hpp"

WinTcpListener::WinTcpListener() :
  TcpListener(),
  _cleanup(false),
  _closed(true)
{}

WinTcpListener::~WinTcpListener()
{
  if (!_closed)
    closesocket(_socket);
  if (_cleanup)
    WSACleanup();
}

bool			WinTcpListener::listenSocket(uint16_t port)
{
  struct protoent	*pe;

  _port = port;
  if (WSAStartup(MAKEWORD(2, 2), &_wsa))
    return false;
  _cleanup = true;
  if ((pe = getprotobyname("TCP")) == NULL)
    return false;
  if ((_socket = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == INVALID_SOCKET)
    return false;
  _sin.sin_family = AF_INET;
  _sin.sin_addr.s_addr = INADDR_ANY;
  _sin.sin_port = htons(port);
  _closed = false;
  if (bind(_socket, (struct sockaddr *)&_sin, sizeof(_sin)) == SOCKET_ERROR)
    return false;
  if (listen(_socket, SOMAXCONN) == SOCKET_ERROR)
    return false;
  return true;
}

bool			WinTcpListener::acceptSocket(TcpSocket *socket)
{
  struct sockaddr_in	sin;
  int			addrlen = sizeof(sin);
  SOCKET	        remoteSocket;

  if ((remoteSocket = accept(_socket, (struct sockaddr *)&sin, &addrlen)) == INVALID_SOCKET)
    return false;
  socket->create(&remoteSocket, inet_ntoa(sin.sin_addr), ntohs(sin.sin_port));
  return true;
}

bool			WinTcpListener::newClient()
{
  fd_set		rfds;
  struct timeval	tv;
  int			retval;

  FD_ZERO(&rfds);
  FD_SET(_socket, &rfds);
  tv.tv_sec = 0;
  tv.tv_usec = 0;
  retval = select(0, &rfds, NULL, NULL, &tv);
  if (retval <= 0)
    return false;
  return true;
}
