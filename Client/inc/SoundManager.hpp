//
// SoundManager.hpp for SoundManager in /home/trupin_t/rendu/LDD
// 
// Made by Thomas Trupin
// Login   <trupin_t@epitech.net>
// 
// Started on Sun Dec 13 06:33:21 2015 Thomas Trupin
// Last update Sun Dec 13 06:38:29 2015 Thomas Trupin
//

#ifndef SOUNDMANAGER_H_
# define SOUNDMANAGER_H_

#include	<SFML/Audio.hpp>
#include	<string>
#include	<map>


class SoundManager
{
public:
  SoundManager(){}

  void		loadSound(std::string const &name, std::string const &filename);
  sf::SoundBuffer	&getRef(const std::string sound);


private:
  std::map<std::string, sf::SoundBuffer> _sounds;
};

#endif /*!SOUNDMANAGER_H_*/
