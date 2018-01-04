#include		"../inc/Socket/TcpListener.hpp"

#if defined(__linux__)
#include		"../inc/Socket/UnixTcpListener.hpp"
#elif defined (WIN32)
#include		"../inc/Socket/WinTcpListener.hpp"
#endif

uint16_t		TcpListener::getPort() const
{
  return _port;
}

TcpListener		*TcpListener::newListener()
{
#if defined(__linux__)
  return new UnixTcpListener();
#elif defined (WIN32)
  return new WinTcpListener();
#endif
  return NULL;
}
