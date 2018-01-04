#pragma once

#include		<vector>
#include		<ctime>
#include		"Player.hpp"
#include		"Enemy.hpp"

class			Room
{
private:
  static size_t		idmax;
  size_t		_id;
  std::string		_name;
  Player		*_players[4];
  bool			_inGame;
  std::vector<Enemy *>	_enemies;
  time_t		_lastEnemyTime;

public:
  Room(const std::string &name);
  ~Room();

  bool			addPlayer(Player *player);
  bool			removePlayer(Player *player);
  const Player		*getPlayer(size_t pos) const;
  size_t		getNbPlayer() const;

  size_t		getId() const;

  const std::string	&getName() const;
  void			setName(const std::string &name);

  bool			playersReady() const;
  void		        setInGame(bool inGame);
  bool			isInGame() const;

  void			addEnemy(Enemy *enemy);
  bool			removeEnemy(const Enemy *enemy);
  const std::vector<Enemy *> &getEnemies() const;

  time_t		getLastEnemyTime() const;
  void			updateLastEnemyTime();
};
