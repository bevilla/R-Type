//
// AnimatedSprite.cpp for AnimatedSprite in /home/trupint/rendu/R-Type/Client
//
// Made by trupin_t
// Login   <trupint@epitech.net>
//
// Started on Sat Jan 16 10:20:29 2016 trupin_t
// Last update Mon Jan 18 12:39:59 2016 Gabriel NOEL
//

#include	"AnimatedSprite.hpp"

AnimatedSprite::AnimatedSprite()
{}

AnimatedSprite::AnimatedSprite(sf::Texture &texture,
			       int width, int height,
			       int columns, int lines,
			       int originx, int originy,
			       float frameTime)
{
  _width = width;
  _height = height;
  _columns = columns;
  _lines = lines;
  _offset_x = 0;
  _offset_y = 0;
  _elapsed = 0.0;
  _total = 0.0;
  _firstFrame = 1;
  _lastFrame = columns;
  _frameTime = frameTime;
  _originx = originx;
  _originy = originy;
  _sprite.setTexture(texture);
  _sprite.setTextureRect(sf::IntRect(0, 0, width, height));
}

sf::Sprite	&AnimatedSprite::getSprite()
{
  return (_sprite);
}

bool		AnimatedSprite::getRank() const
{
  return (_total >= 1.0 ? true : false);
}

void		AnimatedSprite::setPosition(int x, int y)
{
  _sprite.setPosition(x, y);
}

void		AnimatedSprite::setPosition(const sf::Vector2f&v)
{
  _sprite.setPosition(v);
}

void		AnimatedSprite::move(int x, int y)
{
  _sprite.move(x, y);
}

void		AnimatedSprite::updateMenu(const float dt)
{
  _elapsed += dt;
  if (_elapsed >= _frameTime)
    {
      _elapsed = 0.0;
      _offset_x += 1;
      if (_offset_x >= _columns)
	{
	  _offset_x = 0;
	  _offset_y += 1;
	  if (_offset_y >= _lines)
	    _offset_y = 0;
	}
      _sprite.setTextureRect(sf::IntRect(_originx + _offset_x * _width,
					 _originy + _offset_y * _height,
					 _width,
					 _height));
    }
}

void		AnimatedSprite::updateExpl(const float dt)
{
  _elapsed += dt;
  _total += dt;
  if (_elapsed >= _frameTime)
    {
      _elapsed = 0.0;
      _offset_x += 1;
      if (_offset_x > 5)
	_offset_x -=1;
      _sprite.setTextureRect(sf::IntRect(_originx + _offset_x * _width,
					 _originy + _offset_y * _height,
					 _width,
					 _height));
    }
}

const AnimatedSprite &AnimatedSprite::operator=(AnimatedSprite const&d)
{
  _sprite = d._sprite;
  _offset_x = d._offset_x;
  _offset_y = d._offset_y;
  _width = d._width;
  _height = d._height;
  _columns = d._columns;
  _lines = d._lines;
  _firstFrame = d._firstFrame;
  _lastFrame = d._lastFrame;
  _elapsed = d._elapsed;
  _total = d._total;
  _frameTime = d._frameTime;
  _originx = d._originx;
  _originy = d._originy;
  return *this;
}
