//
// SoundManager.cpp for SoundManager in /home/trupin_t/rendu/LDD
// 
// Made by Thomas Trupin
// Login   <trupin_t@epitech.net>
// 
// Started on Sun Dec 13 06:33:32 2015 Thomas Trupin
// Last update Sun Dec 13 06:39:32 2015 Thomas Trupin
//

#include	"SoundManager.hpp"

void		SoundManager::loadSound(std::string const &name, std::string const &filename)
{
  sf::SoundBuffer	sound;

  sound.loadFromFile(filename);
  _sounds[name] = sound;
}

sf::SoundBuffer	&SoundManager::getRef(const std::string sound)
{
  return (_sounds.at(sound));
}

