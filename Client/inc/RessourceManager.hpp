//
// RessourceManager.hpp for RessourceManager in /home/trupint/rendu/R-Type/Client
// 
// Made by trupin_t
// Login   <trupint@epitech.net>
// 
// Started on Tue Dec 22 13:23:30 2015 trupin_t
// Last update Sun Jan 24 11:58:01 2016 trupin_t
//

#ifndef RESSOURCEMANAGER_H_
# define RESSOURCEMANAGER_H_

#include	<SFML/Graphics.hpp>
#include	<SFML/Audio.hpp>
#include	<iostream>
#include	<string>
#include	<map>

#define		SPR_DIR(swagg)	"ressources/sprites/" swagg ".png"
#define		GIF_DIR(swagg)	"ressources/sprites/" swagg ".gif"
#define		TTF_DIR(swagg)	"ressources/fonts/" swagg ".ttf"
#define		SND_DIR(swagg)	"ressources/sounds/" swagg ".wav"

class RessourceManager
{
public:
  RessourceManager(){}

  void		loadTexture(std::string const &name, std::string const &filename);
  void		loadSound(std::string const &name, std::string const &filename);
  void		loadFont(std::string const &name, std::string const &filename);

  sf::Texture		&getRef(const std::string texture);
  sf::SoundBuffer	&getSoundRef(const std::string sound);
  sf::Font		&getFontRef(const std::string font);

  void		loadTextureFromImage(std::string const &name, std::string const &filename);

private:
  std::map<std::string, sf::SoundBuffer>	_sounds;
  std::map<std::string, sf::Texture>		_textures;
  std::map<std::string, sf::Font>		_fonts;
};

#endif /*!RESSOURCEMANAGER_H_*/
