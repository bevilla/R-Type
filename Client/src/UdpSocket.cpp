#include			"../inc/UdpSocket.hpp"

#if defined(__linux__)
#include			"../inc/UnixUdpSocket.hpp"
#elif defined (WIN32)
#include			"../inc/WinUdpSocket.hpp"
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
