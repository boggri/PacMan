#pragma once
#include "includeAllHeaders.h"

class Ghost :
	public Creatures
{
private:
	///CONSTANTS///
	//Sprite list//
	// Creature watchs to the right direction (on sprite list)
	const int SPRITE_RIGHT_X;
	const int SPRITE_RIGHT_Y;

	const int SPRITES_SHIFT_DIST;
	const int SPRITE_WIDTH;
	const int SPRITE_HEIGHT;

public:
	Ghost(sf::Texture &image, std::string name);

	float DistanceToPacMan(float FromX, float FromY, float PacX, float PacY); // Get distanse to PacMan coordinates from set sell 
	void CeckThreeTiles(float pacX, float pacY); // pass float coordinates of PacMan
	void UpdateMove();
	~Ghost();
};

