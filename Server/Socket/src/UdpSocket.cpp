#include			"../inc/Socket/UdpSocket.hpp"

#if defined(__linux__)
#include			"../inc/Socket/UnixUdpSocket.hpp"
#elif defined (WIN32)
#include			"../inc/Socket/WinUdpSocket.hpp"
#endif

void				UdpSocket::deleteMsg(const void *data)
{
  if (data)
    delete[] (char *)data;
}

UdpSocket			*UdpSocket::newSocket()
{
#if defined(__linux__)
  return new UnixUdpSocket();
#elif defined (WIN32)
  return new WinUdpSocket();
#endif
  return NULL;
}
