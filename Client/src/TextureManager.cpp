//
// TextureManager.cpp for TextureManager in /home/trupin_t/rendu/gomoku_client
//
// Made by Thomas Trupin
// Login   <trupin_t@epitech.net>
//
// Started on Thu Dec 10 16:03:48 2015 Thomas Trupin
// Last update Sat Jan 16 10:20:03 2016 trupin_t
//

#include	"TextureManager.hpp"

#include <iostream>

void		TextureManager::loadTexture(std::string const &name, std::string const &filename)
{
  sf::Texture	tex;

  std::cout << filename << std::endl;
  tex.loadFromFile(filename);
  _textures[name] = tex;
}

void		TextureManager::loadTextureFromImage(std::string const &name,
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

sf::Texture	&TextureManager::getRef(const std::string texture)
{
  return (_textures.at(texture));
}
