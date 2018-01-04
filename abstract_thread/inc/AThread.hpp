//
// AThread.hpp for R-Type in /home/potier_v/rendu/R-Type/abstract_thread/inc
// 
// Made by Valentin Potier
// Login   <potier_v@epitech.net>
// 
// Started on  Sun Jan 17 19:16:56 2016 Valentin Potier
// Last update Sun Jan 17 19:41:38 2016 Valentin Potier
//

#pragma	once

class		AThread
{
public:
  AThread() {};

  virtual ~AThread() {}
  virtual void	join() const = 0;
};
