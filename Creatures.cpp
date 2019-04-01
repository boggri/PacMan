#include "Creatures.h"
#include "PacMan.h"
#include <cmath>



Creatures::Creatures(sf::Texture &image, std::string name):
	/// initializer list 
	ANIMATION_SPEED(0.15) // member initializer list
	, NUM_OF_WALK_FRAMES(2)

	/// Constructor
{
	sprite.setTexture(image);
	
	if (name == "PacMan")
	{
		rect = sf::FloatRect(232, 376, 16, 16); //Start coordinates rect.left/rect.top for PacMan and hight/width of PacMan sprite
		sprite.setOrigin(sf::Vector2f(8, 8)); // shift origin of sprite
		currentDirection = -1;
	}
	else if (name == "Ghost1")
	{
		rect = sf::FloatRect(24, 104, 14, 14); //Start coordinates rect.left/rect.top for Ghost spawn and hight/width of Ghost sprite
		sprite.setOrigin(sf::Vector2f(7, 7)); // shift origin of sprite
		currentDirection = 0;
	}
	else if (name == "Ghost2")
	{
		rect = sf::FloatRect(440, 472, 14, 14); //Start coordinates rect.left/rect.top for Ghost spawn and hight/width of Ghost sprite
		sprite.setOrigin(sf::Vector2f(7, 7)); // shift origin of sprite
		currentDirection = 0;
	}
	else if (name == "Exit")
	{
		rect = sf::FloatRect(232, 376, 8, 14); //Start coordinates rect.left/rect.top for Key and hight/width of it sprite
		sprite.setOrigin(sf::Vector2f(4, 7)); // shift origin of sprite
	}
	else if (name == "Win" || name == "Lose")
	{
		rect = sf::FloatRect(222, 230, 90, 16); //Start coordinates rect.left/rect.top for End screen and hight/width of it sprite
		sprite.setOrigin(sf::Vector2f(45, 8)); // shift origin of sprite
	}

	walk = false;
	moveSpead = 2.0; // 2 px per 1 loop
	currentFrame = 0;

	//Assign coordinates of tile in witch creature are now
	currX = rect.left / tileSize;
	currY = rect.top / tileSize;
	
	for (int i = 0; i < 4; i++) { move[i] = false; } // initialize all directions to false
}


Creatures::~Creatures()
{
}
