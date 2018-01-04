#include		<cstdlib>
#include		<sstream>
#include		"Player.hpp"

size_t			Player::idmax = 0;

Player::Player()
{
  std::ostringstream	oss;

  _id = idmax++;
  oss << "unnamed" << _id;
  _name = oss.str();
  _room = NO_ROOM;
  _ready = false;
  _inGame = false;
  start = start = std::clock();
  duration = 0;
  _x = 50;
  _y = rand() % 750 + 50;

  _cmdfunc[0] = &Player::mouveNULL;
  _cmdfunc[1] = &Player::mouveSUD;
  _cmdfunc[2] = &Player::mouveNORD;
  _cmdfunc[3] = &Player::mouveNULL;
  _cmdfunc[4] = &Player::mouveOUEST;
  _cmdfunc[5] = &Player::mouveSUDEST;
  _cmdfunc[6] = &Player::mouveNORDEST;
  _cmdfunc[7] = &Player::mouveOUEST;
  _cmdfunc[8] = &Player::mouveEST;
  _cmdfunc[9] = &Player::mouveSUDOUEST;
  _cmdfunc[10] = &Player::mouveNORDOUEST;
  _cmdfunc[11] = &Player::mouveNORD;
  _cmdfunc[12] = &Player::mouveNULL;
  _cmdfunc[13] = &Player::mouveNORD;
  _cmdfunc[14] = &Player::mouveSUD;
  _cmdfunc[15] = &Player::mouveNULL;
}

Player::~Player()
{
}

size_t			Player::getRoom() const
{
  return _room;
}

void			Player::setRoom(size_t room)
{
  _room = room;
}

size_t			Player::getId() const
{
  return _id;
}

const std::string	&Player::getName() const
{
  return _name;
}

void			Player::setName(const std::string &name)
{
  _name = name;
}

bool			Player::isReady() const
{
  return _ready;
}

void			Player::setReady(bool ready)
{
  _ready = ready;
}

bool			Player::isInGame() const
{
  return _inGame;
}

void		        Player::setInGame(bool inGame)
{
  _inGame = inGame;
}

void Player::mouv(uint16_t i)
{
  (this->*_cmdfunc[i])();
  duration = 0;
  if (_x < 0)
    _x = 0;
  if (_y < 0)
    _y = 0;
}

void Player::mouveSUD()
{
  _y -=  5;
}

void Player::mouveOUEST()
{
  _x -= 5;
}

void Player::mouveEST()
{
  _x += 5;
}

void Player::mouveNORD()
{
  _y += 5;
}

void Player::mouveSUDEST()
{
  _y -= 5;
  _x -= 5;
}

void Player::mouveSUDOUEST()
{
  _y -= 5;
  _x += 5;
}

void Player::mouveNORDEST()
{
  _y += 5;
  _x -= 5;
}

void Player::mouveNORDOUEST()
{
  _y += 5;
  _x += 5;
}

void Player::mouveNULL()
{

}

void Player::runtime()
{
  duration += ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
  start =  std::clock();
}
