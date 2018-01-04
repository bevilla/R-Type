#include		"../inc/WinTcpSocket.hpp"

WinTcpSocket::WinTcpSocket() :
  TcpSocket(),
  _closed(true),
  _client(false),
  _cleanup(false)
{
  FILETIME		filetime;

  GetSystemTimeAsFileTime(&filetime);
  _lastMsg.LowPart = filetime.dwLowDateTime;
  _lastMsg.HighPart = filetime.dwHighDateTime;
}

WinTcpSocket::~WinTcpSocket()
{
  if (!_closed)
    closesocket(_socket);
  if (_cleanup)
    WSACleanup();
}

const std::string	&WinTcpSocket::getRemoteAddress() const
{
  return _remoteIpAddress;
}

uint16_t		WinTcpSocket::getRemotePort() const
{
  return _remotePort;
}

bool			WinTcpSocket::connectSocket(const std::string &ipAddress, uint16_t port)
{
  struct protoent	*pe;
  struct sockaddr_in    sin;

  _client = true;
  if (WSAStartup(MAKEWORD(2, 2), &_wsa))
    return false;
  _cleanup = true;
  if ((pe = getprotobyname("TCP")) == NULL)
    return false;
  if ((_socket = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == INVALID_SOCKET)
    return false;
  _closed = false;
  sin.sin_family = AF_INET;
  sin.sin_addr.s_addr = inet_addr(ipAddress.c_str());
  sin.sin_port = htons(port);
  if (connect(_socket, (struct sockaddr *)&sin, sizeof(sin)) == SOCKET_ERROR)
    return false;
  return true;
}

bool		        WinTcpSocket::sendData(const void *data, size_t size)
{
  if (send(_client ? _socket : _remoteSocket, (const char *)data, size, 0) == SOCKET_ERROR)
    return false;
  return true;
}

int			WinTcpSocket::receive(void *&data, size_t &receive)
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
  retval = select(0, &rfds, NULL, NULL, &tv);
  if (retval == -1)
    return TCP_ERROR;
  else if (!retval)
    {
      receive = 0;
      return TCP_NODATA;
    }
  if ((receive = recv(socket, tmp, RECVLEN, 0)) == SOCKET_ERROR)
    return TCP_ERROR;
  if (receive)
    {
      FILETIME		filetime;

      GetSystemTimeAsFileTime(&filetime);
      _lastMsg.LowPart = filetime.dwLowDateTime;
      _lastMsg.HighPart = filetime.dwHighDateTime;
      data = new char[receive];
      for (size_t i = 0; i < receive; i++)
	((char *)data)[i] = tmp[i];
    }
  return TCP_OK;
}

void			WinTcpSocket::create(void *socket, const std::string &ipaddr, uint16_t port)
{
  WSAStartup(MAKEWORD(2, 2), &_wsa);
  _cleanup = true;
  _remoteSocket = *((SOCKET *)socket);
  _remoteIpAddress = ipaddr;
  _remotePort = port;
}

int			WinTcpSocket::lastMsg()
{
  FILETIME		filetime;
  ULARGE_INTEGER	lastMsg;

  GetSystemTimeAsFileTime(&filetime);
  lastMsg.LowPart = filetime.dwLowDateTime;
  lastMsg.HighPart = filetime.dwHighDateTime;
  return (int)((lastMsg.QuadPart - _lastMsg.QuadPart) / 10000000);
}
