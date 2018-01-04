//
// UnixThread.cpp for R-Type in /home/potier_v/rendu/R-Type/abstract_thread
// 
// Made by Valentin Potier
// Login   <potier_v@epitech.net>
// 
// Started on  Thu Jan 14 16:17:17 2016 Valentin Potier
// Last update Sun Jan 17 19:20:54 2016 Valentin Potier
//

#include	<cstddef>
#include	"UnixThread.hpp"

UnixThread::~UnixThread() {}

void		UnixThread::join() const
{
  if (_th->joinable())
    _th->join();
}
