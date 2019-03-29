#include "SpriteMap.h"



SpriteMap::SpriteMap(sf::Texture &image)
{
	sprite.setTexture(image);
	rect = sf::FloatRect(0, 0, 224, 248);
	sprite.setScale(2, 2);

	sprite.setPosition(rect.left, rect.top);
	sprite.setTextureRect(sf::IntRect(0, 0, rect.width, rect.height));
}


SpriteMap::~SpriteMap()
{
}
