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

	int spriteXup = SPRITE_RIGHT_X + SPRITES_SHIFT_DIST * 4
	, spriteXdown = SPRITE_RIGHT_X + SPRITES_SHIFT_DIST * 6
	, spriteXsides = SPRITE_RIGHT_X
	, spriteY = SPRITE_RIGHT_Y;

	bool eatenByPacman;
	float timerDeath;

public:
	Ghost(sf::Texture &image, std::string name);

	float DistanceToPacMan(float FromX, float FromY, float &PacX, float &PacY); // Get distanse to PacMan coordinates from set sell 
	void FindTilesCachMod(float &pacX, float &pacY); // pass float coordinates of PacMan
	void FindTilesDoNotCachMod();
	void UpdateMove();
	void CachCheck(int pacX, int pacY, bool &cached);
	void BustMode(int pacX, int pacY, float &timerBust);
	void GhostManager(float PacManX, float PacManY, bool &cached, float &timerBust);

	~Ghost();
};

