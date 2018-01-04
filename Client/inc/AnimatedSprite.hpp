//
// AnimatedSprite.hpp for AnimatedSprite in /home/trupint/rendu/R-Type/Client
//
// Made by trupin_t
// Login   <trupint@epitech.net>
//
// Started on Sat Jan 16 10:20:00 2016 trupin_t
// Last update Mon Jan 18 12:30:13 2016 Gabriel NOEL
//

#ifndef ANIMATEDSPRITE_H_
# define ANIMATEDSPRITE_H_

#include	<SFML/Graphics.hpp>
#include	<iostream>

class AnimatedSprite
{
public:
  AnimatedSprite();
  AnimatedSprite(sf::Texture &kek , int, int, int, int, int, int, float);
  const AnimatedSprite &operator=(const AnimatedSprite &);
  void		updateMenu(const float dt);
  void		updateExpl(const float dt);
  sf::Sprite	&getSprite();
  void		setPosition(int x, int y);
  void		setPosition(const sf::Vector2f&);
  void		move(int x, int y);
  bool		getRank() const;

  sf::Sprite	_sprite;

private:
  int		_offset_x;
  int		_offset_y;
  int		_width;
  int		_height;
  int		_columns;
  int		_lines;
  int		_originx;
  int		_originy;
  int		_firstFrame;
  int		_lastFrame;
  double	_elapsed;
  double	_total;
  float		_frameTime;
};

#endif /*!ANIMATEDSPRITE_H_*/
