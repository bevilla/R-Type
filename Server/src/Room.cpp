#include		<sstream>
#include		"Room.hpp"

size_t			Room::idmax = 0;

Room::Room(const std::string &name)
{
  _id = idmax++;
  _name = name;
  _inGame = false;

  for (size_t i = 0; i < 4; i++)
    _players[i] = NULL;

  time(&_lastEnemyTime);
}

Room::~Room()
{
  for (size_t i = 0; i < _enemies.size(); i++)
    delete _enemies[i];
}

bool			Room::addPlayer(Player *player)
{
  for (size_t i = 0; i < 4; i++)
    if (_players[i] == NULL)
      {
	player->setRoom(_id);
	_players[i] = player;
	return true;
      }
  return false;
}

bool			Room::removePlayer(Player *player)
{
  for (size_t i = 0; i < 4; i++)
    if (_players[i] == player)
      {
	player->setRoom(Player::NO_ROOM);
	_players[i] = NULL;
	return true;
      }
  return false;
}

const Player		*Room::getPlayer(size_t pos) const
{
  if (pos >= 0 && pos < 4)
    return _players[pos];
  return NULL;
}

size_t			Room::getNbPlayer() const
{
  size_t	        nb = 0;

  for (size_t i = 0; i < 4; i++)
    if (_players[i])
      nb++;
  return nb;
}

size_t			Room::getId() const
{
  return _id;
}

const std::string	&Room::getName() const
{
  return _name;
}

void			Room::setName(const std::string &name)
{
  _name = name;
}

bool			Room::playersReady() const
{
  bool			ret = false;

  for (size_t i = 0; i < 4; i++)
    if (_players[i])
      ret = _players[i]->isReady();
  return ret;
}

void		        Room::setInGame(bool inGame)
{
  _inGame = inGame;
}

bool			Room::isInGame() const
{
  return _inGame;
}

void			Room::addEnemy(Enemy *enemy)
{
  _enemies.push_back(enemy);
}

bool			Room::removeEnemy(const Enemy *enemy)
{
  for (size_t i = 0; i < _enemies.size(); i++)
    {
      if (_enemies[i] == enemy)
	{
	  delete enemy;
	  _enemies.erase(_enemies.begin() + i);
	  return true;
	}
    }
  return false;
}

const std::vector<Enemy *> &Room::getEnemies() const
{
  return _enemies;
}

time_t			Room::getLastEnemyTime() const
{
  return _lastEnemyTime;
}

void			Room::updateLastEnemyTime()
{
  time(&_lastEnemyTime);
}
