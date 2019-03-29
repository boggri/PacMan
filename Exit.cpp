#include "Creatures.h"
#include "Exit.h"


Exit::Exit(sf::Texture &image, std::string name)
///Initializer list///
////////////////////////////////////////////
	: Creatures(image, name)
	//Sprite list options
	, SPRITE_RIGHT_X(603)
	, SPRITE_RIGHT_Y(50)
{
	sprite.setScale(1.5, 1.5); // scale size of sprite
	sprite.setTextureRect(sf::IntRect(SPRITE_RIGHT_X, SPRITE_RIGHT_Y, rect.width, rect.height)); // get sprite of ghost when it's not move

	if (name == "Win")
	{
		sprite.setTextureRect(sf::IntRect(459, 222, rect.width, rect.height)); // get sprite of ghost when it's not move
	}
	else if (name == "Lose")
	{
		sprite.setTextureRect(sf::IntRect(459 + 108, 222, rect.width, rect.height)); // get sprite of ghost when it's not move
	}

	sprite.setPosition(rect.left, rect.top); // set start position

	currX = rect.left / tileSize;
	currY = rect.top / tileSize;
}

bool Exit::CheckForExit(int pacX, int pacY)
{
	if (currX == pacX && currY == pacY)
	{
		return true;
	}
	
	return false;
}



Exit::~Exit()
{
}
