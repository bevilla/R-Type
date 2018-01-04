#include		<iostream>
#include		"Server.hpp"

int			main()
{
  Server		server;

  if (server.init())
    return server.run();
  std::cout << "Cannot initialize server" << std::endl;
  return 1;
}
