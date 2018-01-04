#ifndef TEXTUREMANAGER_H_
# define TEXTUREMANAGER_H_

#include	<SFML/Graphics.hpp>
#include	<string>
#include	<map>

#define		SPR_DIR(swagg)	"ressources/sprites/" swagg ".png"
#define		GIF_DIR(swagg)	"ressources/sprites/" swagg ".gif"
#define		JPG_DIR(swagg)	"ressources/sprites/" swagg ".jpg"

class TextureManager
{
public:
  TextureManager(){}

  void		loadTexture(std::string const &name, std::string const &filename);
  void		loadTextureFromImage(std::string const &name, std::string const &filename);
  sf::Texture	&getRef(const std::string texture);


private:
  std::map<std::string, sf::Texture> _textures;
};

#endif /*!TEXTUREMANAGER_H_*/
