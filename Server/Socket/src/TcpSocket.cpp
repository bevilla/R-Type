#include			"../inc/Socket/TcpSocket.hpp"

#if defined(__linux__)
#include			<string.h>
#include			"../inc/Socket/UnixTcpSocket.hpp"
#elif defined (WIN32)
#include			"../inc/Socket/WinTcpSocket.hpp"
#endif

TcpSocket::TcpSocket()
{
  _len = 0;
}

TcpSocket::~TcpSocket()
{
}

uint16_t			TcpSocket::getPort() const
{
  return _port;
}

void				TcpSocket::deleteMsg(const void *data)
{
  if (data)
    delete[] (char *)data;
}

TcpSocket			*TcpSocket::newSocket()
{
#if defined(__linux__)
  return new UnixTcpSocket();
#elif defined (WIN32)
  return new WinTcpSocket();
#endif
  return NULL;
}

int				TcpSocket::recvData(void *&data, size_t &receive)
{
  char				*msg;
  uint32_t			len;
  int				ret;

  if ((ret = this->receive(data, receive)) == TCP_ERROR)
    return TCP_ERROR;
  if (ret == TCP_OK)
    {
      if (data == NULL)
	return TCP_OK;
      memcpy(_buff + _len, data, RECV_MIN(receive, RECVLEN - _len));
      _len += RECV_MIN(receive, RECVLEN - _len);
      deleteMsg(data);
    }
  else if (!_len)
    return TCP_NODATA;
  len = ntohl(*((uint32_t *)_buff));
  if (len > (_len - sizeof(len)))
    return TCP_NODATA;
  msg = new char[len];
  _len = _len - sizeof(len) - len;
  memcpy(msg, _buff + sizeof(len), len);
  memmove(_buff, _buff + sizeof(len) + len, _len);
  data = msg;
  receive = len;
  return TCP_OK;
}

std::ostream			&operator<<(std::ostream &os, const TcpSocket &socket)
{
  os << socket.getRemoteAddress() << ':' << socket.getRemotePort();
  return os;
}
