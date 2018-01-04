//
// main.cpp for main in /home/trupin_t/rendu/gomoku_client
//
// Made by Thomas Trupin
// Login   <trupin_t@epitech.net>
//
// Started on Thu Dec 10 15:53:52 2015 Thomas Trupin
// Last update Sun Jan 24 21:49:58 2016 Alexis Bevillard
//

#include	<exception>
#include	"Game.hpp"
#include	"GameStateStart.hpp"
#include	"GameStateMenu.hpp"

int	main(int ac, char **av)
{
  Game		game;

  if (ac != 2)
    {
      std::cout << "You have to enter an IP to start a game" << std::endl;
      return (-1);
    }
  game.ip = av[1];
  try
    {
      game.pushState(new GameStateMenu(&game));
      game.gameLoop();
    }
  catch (std::exception &e)
    {
      std::cerr << e.what() << std::endl;
      return (-1);
    }
  return (EXIT_SUCCESS);
}
