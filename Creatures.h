#pragma once
#include "includeAllHeaders.h"
#include <iostream>

class Creatures
{
protected:
	///CONSTANTS///
	// Creature walk animation
	const float ANIMATION_SPEED;
	const int NUM_OF_WALK_FRAMES;

	//Direction
	enum DIRECTION { UP, RIGHT, DOWN, LEFT }; // States of the direction. 
	bool move[4]; // 4 direcrions
	bool walk; // if we are walking = true; 

	float moveSpead; // speed of creature
	float currentFrame; // frame chainger swich

	int currentDirection; // in what side creature moves 
	int currSpoatTile; // next destination cell/tile 

public:
	sf::Sprite sprite;
	sf::FloatRect rect; // (rect.left, rect.top, width, hight) / Coordinates and size

	//Coordinates
	int currX;
	int currY;

	/// Methods ///
	Creatures(sf::Texture &image, std::string name);

	~Creatures();
};

