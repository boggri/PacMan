#include "Creatures.h"
#include "Ghost.h"



Ghost::Ghost(sf::Texture &image, std::string name)
	///Initializer list///
	////////////////////////////////////////////
	: Creatures(image, name)
	
	//Sprite list options
	, SPRITE_RIGHT_X(457)
	, SPRITE_RIGHT_Y(65)
	, SPRITES_SHIFT_DIST(16)
	, SPRITE_WIDTH(14)
	, SPRITE_HEIGHT(14)

	///Constructor///
{
	sprite.setScale(1.5, 1.5); // scale size of sprite
	sprite.setTextureRect(sf::IntRect(SPRITE_RIGHT_X, SPRITE_RIGHT_Y, rect.width, rect.height)); // get sprite of ghost when it's not move

	sprite.setPosition(rect.left, rect.top); // set start position
	
	spriteXup = SPRITE_RIGHT_X + SPRITES_SHIFT_DIST * 4;
	spriteXdown = SPRITE_RIGHT_X + SPRITES_SHIFT_DIST * 6;
	spriteXsides = SPRITE_RIGHT_X;
	spriteY = SPRITE_RIGHT_Y;

	eatenByPacman = false;
	timerDeath = 0;
}


float Ghost::DistanceToPacMan(float FromX, float FromY, float &PacX, float &PacY)
{
	return sqrt(powf(FromX - PacX, 2) + powf(FromY - PacY, 2));  // Distance between two points on the plane
}




void Ghost::FindTilesCachMod(float &pacX, float &pacY)
{
	if (!walk) //Start check only from waypoint
	{
		// remember front tile, left and right tile coordinates
		float FrontTilePos
			, LeftTilePos
			, RightTilePos
			, DistFront = 99999999
			, DistLeft = 99999999
			, DistRight = 99999998;

		// Calculate num of tile
		int FrontTile
			, LeftTile
			, RightTile;

		// Calculate 3 cells to check. That depends of the current direction. Where the pacman looks
		switch (currentDirection)
		{
		case UP:
			FrontTilePos = rect.top - tileSize;
			LeftTilePos = rect.left - tileSize;
			RightTilePos = rect.left + tileSize;

			FrontTile = FrontTilePos / tileSize;
			LeftTile = LeftTilePos / tileSize;
			RightTile = RightTilePos / tileSize;
			
			// check each of thre tile for collision;
			if (!(Map[FrontTile][currX] == 'W' || Map[FrontTile][currX] == '&' || Map[FrontTile][currX] == 'w'))
			{
				move[UP] = true;
				DistFront = DistanceToPacMan(currX, FrontTile, pacX, pacY);
			}
			if (!(Map[currY][LeftTile] == 'W' || Map[currY][LeftTile] == '&' || Map[currY][LeftTile] == 'w'))
			{
				move[LEFT] = true;
				DistLeft = DistanceToPacMan(LeftTile, currY, pacX, pacY);
			}
			if (!(Map[currY][RightTile] == 'W' || Map[currY][RightTile] == '&' || Map[currY][RightTile] == 'w'))
			{
				move[RIGHT] = true;
				DistRight = DistanceToPacMan(RightTile, currY, pacX, pacY);
			}
			
				break;
		case DOWN:
			FrontTilePos = rect.top + tileSize;
			LeftTilePos = rect.left + tileSize;
			RightTilePos = rect.left - tileSize;

			FrontTile = FrontTilePos / tileSize;
			LeftTile = LeftTilePos / tileSize;
			RightTile = RightTilePos / tileSize;
			
			if (!(Map[FrontTile][currX] == 'W' || Map[FrontTile][currX] == '&' || Map[FrontTile][currX] == 'w'))
			{
				move[DOWN] = true;
				DistFront = DistanceToPacMan(currX, FrontTile, pacX, pacY);
			}
			if (!(Map[currY][LeftTile] == 'W' || Map[currY][LeftTile] == '&' || Map[currY][LeftTile] == 'w'))
			{
				move[RIGHT] = true;
				DistLeft = DistanceToPacMan(LeftTile, currY, pacX, pacY);
			}
			if (!(Map[currY][RightTile] == 'W' || Map[currY][RightTile] == '&' || Map[currY][RightTile] == 'w'))
			{
				move[LEFT] = true;
				DistRight = DistanceToPacMan(RightTile, currY, pacX, pacY);
			}
			
			break;
		case LEFT:
			FrontTilePos = rect.left - tileSize;
			LeftTilePos = rect.top + tileSize;
			RightTilePos = rect.top - tileSize;

			FrontTile = FrontTilePos / tileSize;
			LeftTile = LeftTilePos / tileSize;
			RightTile = RightTilePos / tileSize;

			if (!(Map[currY][FrontTile] == 'W' || Map[currY][FrontTile] == '&' || Map[currY][FrontTile] == 'w'))
			{
				move[LEFT] = true;
				DistFront = DistanceToPacMan(FrontTile, currY, pacX, pacY);
			}
			if (!(Map[LeftTile][currX] == 'W' || Map[LeftTile][currX] == '&' || Map[LeftTile][currX] == 'w'))
			{
				move[DOWN] = true;
				DistLeft = DistanceToPacMan(currX, LeftTile, pacX, pacY);
			}
			if (!(Map[RightTile][currX] == 'W' || Map[RightTile][currX] == '&' || Map[RightTile][currX] == 'w'))
			{
				move[UP] = true;
				DistRight = DistanceToPacMan(currX, RightTile, pacX, pacY);
			}
			
			break;
		case RIGHT:
			FrontTilePos = rect.left + tileSize;
			LeftTilePos = rect.top - tileSize;
			RightTilePos = rect.top + tileSize;

			FrontTile = FrontTilePos / tileSize;
			LeftTile = LeftTilePos / tileSize;
			RightTile = RightTilePos / tileSize;
			
			if (!(Map[currY][FrontTile] == 'W' || Map[currY][FrontTile] == '&' || Map[currY][FrontTile] == 'w'))
			{
				move[RIGHT] = true;
				DistFront = DistanceToPacMan(FrontTile, currY, pacX, pacY);
			}
			if (!(Map[LeftTile][currX] == 'W' || Map[LeftTile][currX] == '&' || Map[LeftTile][currX] == 'w'))
			{
				move[UP] = true;
				DistLeft = DistanceToPacMan(currX, LeftTile, pacX, pacY);
			}
			if (!(Map[RightTile][currX] == 'W' || Map[RightTile][currX] == '&' || Map[RightTile][currX] == 'w'))
			{
				move[DOWN] = true;
				DistRight = DistanceToPacMan(currX, RightTile, pacX, pacY);
			}
			
			break;
		default:
			break;
		}
		

		// Selekt cell with less distance to PacMan

		if (DistFront <= DistLeft)
		{
			move[((currentDirection + 4) - 1) % 4] = false; // Feft tile is out // We add 4 to prevent minus value and create cicle loop of direction 0 - 3
			
			if (DistFront <= DistRight)
			{
				move[(currentDirection + 1) % 4] = false; // Rigth tile is out
			}
			else if (DistRight < DistFront)
			{
				move[currentDirection] = false; // Front tile is out
				currentDirection = (currentDirection + 1) % 4; // Turn direction right to 90 degrees right
			}
		}
		else if (DistLeft <= DistRight)
		{
			move[currentDirection] = false; // Front tile is out
			move[(currentDirection + 1) % 4] = false; // Rigth tile is out
			currentDirection = ((currentDirection + 4) - 1) % 4; // Turn direction left to 90 degrees left
			
		}
		else if (DistLeft > DistRight)
		{
			move[currentDirection] = false; // Front tile is out
			move[((currentDirection + 4) - 1) % 4] = false; // Left tile is out
			currentDirection = (currentDirection + 1) % 4; // Turn direction right to 90 degrees left
		}

	}
}


void Ghost::FindTilesDoNotCachMod() // random path generator
{
	if (!walk)
	{
		srand(time(nullptr));
		int Y;
		int X;
		bool findPath = true;
		int reversDir;

		reversDir = (currentDirection + 2) % 4; // 180 degrees (back tile) 
		while (findPath)
		{
			currentDirection = rand() % 4;
			
			if (currentDirection != reversDir) // back tile is not allowed
			{
				switch (currentDirection)
				{
				case UP:
					Y = (rect.top - tileSize) / tileSize;
					X = currX;
					if (!(Map[Y][X] == 'W' || Map[Y][X] == 'w' || Map[Y][X] == '&'))
					{
						findPath = false;
						move[UP] = true;
					}
					break;

				case DOWN:
					Y = (rect.top + tileSize) / tileSize;
					X = currX;
					if (!(Map[Y][X] == 'W' || Map[Y][X] == 'w' || Map[Y][X] == '&'))
					{
						findPath = false;
						move[DOWN] = true;
					}
					break;

				case LEFT:
					Y = currY;
					X = (rect.left - tileSize) / tileSize;
					if (!(Map[Y][X] == 'W' || Map[Y][X] == 'w' || Map[Y][X] == '&'))
					{
						findPath = false;
						move[LEFT] = true;
					}
					break;

				case RIGHT:
					Y = currY;
					X = (rect.left + tileSize) / tileSize;
					if (!(Map[Y][X] == 'W' || Map[Y][X] == 'w' || Map[Y][X] == '&'))
					{
						findPath = false;
						move[RIGHT] = true;
					}
					break;
				default:
					break;
				}

			}
		}
	
	}
}


void Ghost::UpdateMove()
{
	if (!walk)
	{
		switch (currentDirection)
		{
		case UP:
			currSpoatTile = rect.top - tileSize;
			walk = true;
			break;
		case DOWN:
			currSpoatTile = rect.top + tileSize;
			walk = true;
			break;
		case LEFT:
			currSpoatTile = rect.left - tileSize;
			walk = true;
			break;
		case RIGHT:
			currSpoatTile = rect.left + tileSize;
			walk = true;
			break;

		default:
			walk = false;
			break;
		}
	}
	//Go through way points
	if (walk) // If walk == true
	{
		if (move[UP])
		{
			rect.top -= moveSpead;
			sprite.setTextureRect(sf::IntRect(spriteXup + SPRITES_SHIFT_DIST * (int(currentFrame)), spriteY, rect.width, rect.height)); // animation up from sprite list

			if (rect.top <= currSpoatTile) // In case if it will go too far -> set in exact position
			{
				rect.top = currSpoatTile;
				walk = false;
				move[UP] = false;
				currY = rect.top / tileSize; // Update tile coordinates of ghost
			}
		}

		else if (move[DOWN])
		{
			rect.top += moveSpead;
			sprite.setTextureRect(sf::IntRect(spriteXdown + SPRITES_SHIFT_DIST * (int(currentFrame)), spriteY, rect.width, rect.height)); // amnimation down from sprite list

			if (rect.top >= currSpoatTile)
			{
				rect.top = currSpoatTile;
				walk = false;
				move[DOWN] = false;
				currY = rect.top / tileSize; // Update tile coordinates of ghost			
			}
		}
		else if (move[LEFT])
		{
			rect.left -= moveSpead;
			sprite.setTextureRect(sf::IntRect(spriteXsides + SPRITES_SHIFT_DIST * (int(currentFrame)) + SPRITE_WIDTH, spriteY, -rect.width, rect.height)); // animation left (inverse reading of right) from sprite list

			if (rect.left <= currSpoatTile)
			{
				rect.left = currSpoatTile;
				walk = false;
				move[LEFT] = false;
				currX = rect.left / tileSize; // Update tile coordinates of ghost
			}
		}
		else if (move[RIGHT])
		{
			rect.left += moveSpead;
			sprite.setTextureRect(sf::IntRect(spriteXsides + SPRITES_SHIFT_DIST * (int(currentFrame)), spriteY, rect.width, rect.height)); // animation right from sprite list

			if (rect.left >= currSpoatTile)
			{
				rect.left = currSpoatTile;
				walk = false;
				move[RIGHT] = false;
				currX = rect.left / tileSize; // Update tile coordinates of ghost
			}
		}

		// Update animation plases in sprite list. Animate and move only if direction is set
		if (!eatenByPacman)
		{
			currentFrame += 0.10;
			if (currentFrame >= NUM_OF_WALK_FRAMES) // loop for animation farmes
			{
				currentFrame -= NUM_OF_WALK_FRAMES;
			}
		}
		else if (eatenByPacman)
		{
			currentFrame = 0;
		}

		//update coordinates of Pacman sprite
		sprite.setPosition(rect.left, rect.top);
	}
	else
	{
		sprite.setTextureRect(sf::IntRect(spriteXsides, spriteY, rect.width, rect.height)); // get sprite of pacman when it's not move
	}
}


void Ghost::CachCheck(int pacX, int pacY, bool &cached)
{
	if (currX == pacX && currY == pacY)
	{
		cached = true;
	}
}

void Ghost::BustMode(int pacX, int pacY, float &timerBust)
{
	if (isBustMode)
	{
		spriteXup = spriteXdown = spriteXsides = SPRITE_RIGHT_X + SPRITES_SHIFT_DIST * 8;

		if (!eatenByPacman)
		{
			if (currX == pacX && currY == pacY) // If they are in the same tile
			{
				eatenByPacman = true;
				
				// Chainge animation to eaten
				spriteXup = SPRITE_RIGHT_X + SPRITES_SHIFT_DIST * 10;
				spriteXdown = SPRITE_RIGHT_X + SPRITES_SHIFT_DIST * 11;
				spriteXsides = SPRITE_RIGHT_X + SPRITES_SHIFT_DIST * 8;
				spriteY += SPRITES_SHIFT_DIST; // 1 down
			}
		}
		else
		{
			timerDeath += 0.1; // independent counter for death time
		}

	}

	if (timerBust >= 10 || timerDeath >= 50) // if bust mode or period of death is ower set casual sprite
	{
		eatenByPacman = false;
		timerDeath = 0;

		spriteXup = SPRITE_RIGHT_X + SPRITES_SHIFT_DIST * 4;
		spriteXdown = SPRITE_RIGHT_X + SPRITES_SHIFT_DIST * 6;
		spriteXsides = SPRITE_RIGHT_X;
		spriteY = SPRITE_RIGHT_Y;
	}
}


void Ghost::GhostManager(float PacManX, float PacManY, bool &cached, float &timerBust)
{
	if (!isBustMode) // timer 10 sec cach PacMan and 3 sec make random movement 
	{
		FindTilesCachMod(PacManX, PacManY); // pass float coordinates of PacMan
		UpdateMove();
		CachCheck(PacManX, PacManY, cached); // pass int coordinates of PacMan by value (to convert them from float and use operator ==)
	}
	else
	{
		FindTilesDoNotCachMod();
		UpdateMove();
	}
	
	BustMode(PacManX, PacManY, timerBust); // here cause gousts can be geath some time after bust mode is over
}

Ghost::~Ghost()
{
}
