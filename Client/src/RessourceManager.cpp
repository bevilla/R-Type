//
// RessourceManager.cpp for RessourceManager in /home/trupint/rendu/R-Type/Client
//
// Made by trupin_t
// Login   <trupint@epitech.net>
//
// Started on Tue Dec 22 13:28:20 2015 trupin_t
// Last update Thu Jan 21 12:06:21 2016 trupin_t
//

#include	"RessourceManager.hpp"

void		RessourceManager::loadTexture(std::string const &name, std::string const &filename)
{
  sf::Texture	tex;

  tex.loadFromFile(filename);
  _textures[name] = tex;
}

void		RessourceManager::loadFont(std::string const &name, std::string const &filename)
{
  sf::Font	font;

  font.loadFromFile(filename);
  _fonts[name] = font;
}

void		RessourceManager::loadSound(std::string const &name, std::string const &filename)
{
  sf::SoundBuffer	sound;

  sound.loadFromFile(filename);
  _sounds[name] = sound;
}

sf::Texture	&RessourceManager::getRef(const std::string texture)
{
  return (_textures.at(texture));
}

sf::SoundBuffer	&RessourceManager::getSoundRef(const std::string sound)
{
  return (_sounds.at(sound));
}

sf::Font	&RessourceManager::getFontRef(const std::string font)
{
  return (_fonts.at(font));
}


void		RessourceManager::loadTextureFromImage(std::string const &name,
						     std::string const &filename)
{
  sf::Image tmpI;
  sf::Texture tmpT;

  std::cout << filename << std::endl;
  if (tmpI.loadFromFile(filename))
    {
      tmpI.createMaskFromColor(sf::Color::Black);
      tmpT.loadFromImage(tmpI);
      _textures[name] = tmpT;
    }
  else
    std::cerr << "Ya un schmoll dans le bignou !" << std::endl;
}
