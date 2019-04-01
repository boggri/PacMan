#include "Creatures.h"
#include "PacMan.h"


PacMan::PacMan(sf::Texture &image, std::string name)
	///Initializer list///
////////////////////////////////////////////
	: Creatures(image, name)

	//Sprite list options
	, SPRITE_RIGHT_X(456)
	, SPRITE_RIGHT_Y(0)
	, SPRITES_SHIFT_DIST(16)
	, SPRITE_WIDTH(16)
	, SPRITE_HEIGHT(16)

	//PacMan picture coordinates up/down (on sprite list)
	, SPRITE_DOWN_X(456)
	, SPRITE_UP_Y(33)
	, SPRITE_DOWN_Y(48)

	///Constructor
{
	cached = false;
	win = false;
	pills = 0;
	nextDirection = -1;

	sprite.setScale(1.5, 1.5); // scale size of sprite
	sprite.setTextureRect(sf::IntRect(SPRITE_RIGHT_X + SPRITES_SHIFT_DIST * 2, SPRITE_RIGHT_Y, rect.width, rect.height)); // get sprite of pacman when it's not move

	sprite.setPosition(rect.left, rect.top); // set start position
}

///PacMan controls
/////////////////////////////////////
void PacMan::GetDirection()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{		
		nextDirection = UP;
	}												
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{					
		nextDirection = DOWN;
	}												
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{					
		nextDirection = LEFT;
	}												
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		nextDirection = RIGHT;
	}
}

/// Future path collisions check 
void PacMan::CheckForFuturePath()
{
	if (!walk)
	{
		// Calculate nextSpoatTile coordinates 
		switch (nextDirection)
		{
		case UP:
			nextSpoatTile = rect.top - tileSize;
			break;
		case DOWN:
			nextSpoatTile = rect.top + tileSize;
			break;
		case LEFT:
			nextSpoatTile = rect.left - tileSize;
			break;
		case RIGHT:
			nextSpoatTile = rect.left + tileSize;
			break;

		default:
			break;
		}
	
		if (nextDirection == UP || nextDirection == DOWN)
		{
			int oldX = rect.left / tileSize;
			int newY = nextSpoatTile / tileSize;

			// If we can turn => set new nextDirection as curentDirection and walk
			if (!(Map[newY][oldX] == 'W' || Map[newY][oldX] == '&'))
			{
				currSpoatTile = nextSpoatTile;
				currentDirection = nextDirection;
			}
		}
		else if (nextDirection == LEFT || nextDirection == RIGHT)
		{
			int oldY = rect.top / tileSize;
			int newX = nextSpoatTile / tileSize;

			if (!(Map[oldY][newX] == 'W' || Map[oldY][newX] == '&'))
			{
				currSpoatTile = nextSpoatTile;
				currentDirection = nextDirection;
			}
		}
		
	}
}



/// Wall collision
void PacMan::Collision()
{
	if (!walk) // Only if we are on waypoint
	{
		//Check curr direction ! If there is no wall -> initialize movement
		/////////////////////////////////////////////////
		if (currentDirection == RIGHT || currentDirection == LEFT)
		{
			int newX = currSpoatTile / tileSize;
			if (!(Map[currY][newX] == 'W' || Map[currY][newX] == '&'))
			{
				(currentDirection == RIGHT) ? move[RIGHT] = true : move[LEFT] = true;
				walk = true;
			}
		}
		else if (currentDirection == UP || currentDirection == DOWN)
		{
			int newY = currSpoatTile / tileSize;
			if (!(Map[newY][currX] == 'W' || Map[newY][currX] == '&'))
			{
				(currentDirection == UP) ? move[UP] = true : move[DOWN] = true;
				walk = true;
			}
		}
	}
}


///Movement
////////////////////////////////////
void PacMan::UpdateMove()
{
	/// Check if we can turn to the new direction
	CheckForFuturePath();
	/// Check if we can move through current direction
	Collision();

	//Go through way points
	if (walk) // If walk == true
	{
		if (move[UP])
		{
			rect.top -= moveSpead;
			sprite.setTextureRect(sf::IntRect(SPRITE_DOWN_X + SPRITES_SHIFT_DIST * (int(currentFrame)), SPRITE_UP_Y, rect.width, rect.height)); // animation up from sprite list

			if (rect.top <= currSpoatTile) // In case if it will go too far -> set in exact position
			{
				rect.top = currSpoatTile;
				walk = false;
				move[UP] = false;
				currSpoatTile -= tileSize;
				currY = rect.top / tileSize; // Update tile coordinates of PacMan
			}
		}

		else if (move[DOWN])
		{
			rect.top += moveSpead;
			sprite.setTextureRect(sf::IntRect(SPRITE_DOWN_X + SPRITES_SHIFT_DIST * (int(currentFrame)), SPRITE_DOWN_Y, rect.width, rect.height)); // amnimation down from sprite list

			if (rect.top >= currSpoatTile)
			{
				rect.top = currSpoatTile;
				walk = false;
				move[DOWN] = false;
				currSpoatTile += tileSize; // Set forward tile as currSpoat (so we don't stop when nextSpoatTile chainged but not asepted) / (If we wont to turn in the wall we ceep moving by previous direction)
				currY = rect.top / tileSize; // Update tile coordinates of PacMan	
			}
		}
		else if (move[LEFT])
		{
			rect.left -= moveSpead;
			sprite.setTextureRect(sf::IntRect(SPRITE_RIGHT_X + SPRITES_SHIFT_DIST * (int(currentFrame)) + SPRITE_WIDTH, SPRITE_RIGHT_Y, -rect.width, rect.height)); // animation left (inverse reading of right) from sprite list

			if (rect.left <= currSpoatTile)
			{
				rect.left = currSpoatTile;
				walk = false;
				move[LEFT] = false;
				currSpoatTile -= tileSize;
				currX = rect.left / tileSize; // Update tile coordinates of PacMan
			}
		}
		else if (move[RIGHT])
		{
			rect.left += moveSpead;
			sprite.setTextureRect(sf::IntRect(SPRITE_RIGHT_X + SPRITES_SHIFT_DIST * (int(currentFrame)), SPRITE_RIGHT_Y, rect.width, rect.height)); // animation right from sprite list

			if (rect.left >= currSpoatTile)
			{
				rect.left = currSpoatTile;
				walk = false;
				move[RIGHT] = false;
				currSpoatTile += tileSize; 
				currX = rect.left / tileSize; // Update tile coordinates of PacMan
			}
		}

		// Update animation plases in sprite list. Animate and move only if direction is set
		currentFrame += ANIMATION_SPEED;
		if (currentFrame >= NUM_OF_WALK_FRAMES) // loop for animation farmes
		{
			currentFrame -= NUM_OF_WALK_FRAMES;
		}

		//update coordinates of Pacman sprite
		sprite.setPosition(rect.left, rect.top);
	}
	else // if PacMan doesn't move
	{
		sprite.setTextureRect(sf::IntRect(SPRITE_RIGHT_X + SPRITES_SHIFT_DIST * 2, SPRITE_RIGHT_Y, rect.width, rect.height)); // get sprite of pacman when it's not move
	}
}


void PacMan::GetPillsAndPortals(sf::Clock &clockB)
{
	if (!walk)
	{
		int X = rect.left / tileSize;
		int Y = rect.top / tileSize;
		if (Map[Y][X] == '.' || Map[Y][X] == '0')
		{
			if (Map[Y][X] == '0')
			{
				isBustMode = true;
				clockB.restart();
			}

			Map[Y][X] = ' ';
			pills++;
		}	

		// Portal handle
		if (Map[Y][X] == 'Q')
		{
			rect.left = 424;
			currSpoatTile = 424 - tileSize;
			sprite.setPosition(rect.left, rect.top);
		}
		else if (Map[Y][X] == 'q')
		{
			rect.left = 24;
			currSpoatTile = 24 + tileSize;
			sprite.setPosition(rect.left, rect.top);
		}
	}
}

void PacMan::BustTimerUpdate(float &timerBust)
{
	if (timerBust > 10) // Bust mode 10 sec
	{  
		isBustMode = false;
	}
}


void PacMan::AnimationDeath()
{
	if (currentFrame <= 12) // loop for animation farmes
	{
		//Set sprite
		sprite.setTextureRect(sf::IntRect(SPRITE_RIGHT_X + SPRITES_SHIFT_DIST * 3 + SPRITES_SHIFT_DIST * (int(currentFrame)), SPRITE_RIGHT_Y, rect.width, rect.height)); // animation right from sprite list

		//Update animation
		currentFrame += 0.45;
	}
}


void PacMan::Update(sf::Clock &clockB, float &timerBust)
{
	GetDirection(); //PacMan control
	UpdateMove();
	GetPillsAndPortals(clockB);
	
	if (isBustMode)
	{
		BustTimerUpdate(timerBust);
	}
	else // keep this timer at zero;
	{
		clockB.restart();
	}
}

PacMan::~PacMan()
{
}
