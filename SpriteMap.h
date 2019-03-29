#pragma once
#include "includeAllHeaders.h"

class SpriteMap
{
public:
	sf::Sprite sprite;
	sf::FloatRect rect; // (rect.left, rect.top, width, hight)

	SpriteMap(sf::Texture &image);
	~SpriteMap();
};

