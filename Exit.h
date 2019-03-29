#pragma once
#include "includeAllHeaders.h"
class Exit :
	public Creatures
{
private:
	///CONSTANTS///
	//Sprite list//
	//( coordinates on sprite list)
	const int SPRITE_RIGHT_X;
	const int SPRITE_RIGHT_Y;

public:
	Exit(sf::Texture &image, std::string name);
	bool CheckForExit(int pacX, int pacY);

	~Exit();
};

