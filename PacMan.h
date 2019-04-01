#pragma once
#include "includeAllHeaders.h"

class PacMan: public Creatures
{
private:
	
	int nextSpoatTile; // Potential spoat tile
	int nextDirection; // Potential direction

	///CONSTANTS///
	//Sprite list//
    // Creature watchs to the right direction (on sprite list)
	const int SPRITE_RIGHT_X;
	const int SPRITE_RIGHT_Y;

	const int SPRITES_SHIFT_DIST;
	const int SPRITE_WIDTH;
	const int SPRITE_HEIGHT;

	//PacMan up/down (on sprite list)
	const int SPRITE_DOWN_X; // doesn't used in PacMan obj
	const int SPRITE_UP_Y;
	const int SPRITE_DOWN_Y;

	///Private methods
	void UpdateMove();
	void GetDirection(); //PacMan control
	void CheckForFuturePath();
	void Collision();
	void GetPillsAndPortals();

public:
	// if the Pacman is cached;
	bool cached;
	bool win;
	int pills;

	//Constructor to set Texture
	PacMan(sf::Texture &image, std::string name);

	///public Methods//
	void Update(); // Include other methods
	void AnimationDeath();

	~PacMan();
};

