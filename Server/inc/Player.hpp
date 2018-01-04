#pragma once

#include		<iostream>
#include		<string>
#include <cstdio>
#include <ctime>
#include <stdint.h>


class			Player
{
public:
  static const size_t	NO_ROOM = (size_t)-1;

private:
  static size_t		idmax;
  size_t		_id;
  std::string		_name;
  size_t		_room;
  bool			_ready;
  bool			_inGame;
  int       _x;
  int       _y;
  std::clock_t start;
  double duration;
  void				(Player::*_cmdfunc[16])();

public:
  Player();
  ~Player();

  size_t		getId() const;
  const std::string	&getName() const;
  void			setName(const std::string &name);
  size_t		getRoom() const;
  void			setRoom(size_t room);
  bool			isReady() const;
  void			setReady(bool ready);
  bool			isInGame() const;
  void		        setInGame(bool inGame);
  int getX(){return _x;}
  void setX(int x) {_x = x;}
  int getY(){return _y;}
  void setY(int y) {_y = y;}
  double getDuration() { return duration;}
  void mouveSUD();
  void mouveOUEST();
  void mouveEST();
  void mouveNORD();
  void mouveSUDOUEST();
  void mouveSUDEST();
  void mouveNORDEST();
  void mouveNORDOUEST();
  void mouveNULL();
  void mouv(uint16_t );
  void runtime();
};
