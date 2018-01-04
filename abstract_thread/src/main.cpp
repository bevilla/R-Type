//
// main.cpp for R-Type in /home/potier_v/rendu/R-Type/abstract_thread/inc
// 
// Made by Valentin Potier
// Login   <potier_v@epitech.net>
// 
// Started on  Sun Jan 17 19:17:04 2016 Valentin Potier
// Last update Sun Jan 17 20:15:31 2016 Valentin Potier
//

#include	<unistd.h>
#include	<stdio.h>
#include	<iostream>
#include	"UnixThread.hpp"

void		topkek(int n)
{
  printf("top zbeb: %d\n", n);
}

void		toplel(int n, char a)
{
  printf("top zbeb: %d, %c\n", n, a);
}

void		topzbeb(const std::string &lel, char a, int *z)
{
  printf("top zbeb: %s, %c, %d\n", lel.c_str(), a, *z);
}

int		main()
{
  std::string	str = "pd";
  int		kek = 2;
  UnixThread	lel(topkek, 1);
  UnixThread	lol(toplel, 1, 'Q');
  UnixThread	lal(topzbeb, str, 'A', &kek);

  std::cout << "avant" << std::endl;
  lel.join(); 
  std::cout << "lel" << std::endl;
  lol.join();
  std::cout << "lol" << std::endl;
  lal.join();
  std::cout << "lal" << std::endl;
  return (0);
}
