//
// UnixThread.hpp for R-Type in /home/potier_v/rendu/R-Type/abstract_thread/inc
// 
// Made by Valentin Potier
// Login   <potier_v@epitech.net>
// 
// Started on  Sun Jan 17 19:17:09 2016 Valentin Potier
// Last update Sun Jan 17 19:56:02 2016 Valentin Potier
//

#pragma	once

#include	<utility>
#include	<thread>
#include	"AThread.hpp"

class		UnixThread : public AThread
{
private:
  std::thread	*_th;
public:
  template	<class Callable, typename... Args>
  UnixThread(Callable&& f, Args&&... args)
  {
    _th = new std::thread(std::forward<Callable>(f), std::forward<Args>(args)...);
  }

  virtual ~UnixThread();
  virtual void	join() const;
};
