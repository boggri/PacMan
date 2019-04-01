#include "GameRuning.h"

#include "includeAllHeaders.h"
#include "SpriteMap.h"
#include "LoadMap.h"
#include "Creatures.h"
#include "PacMan.h"
#include "Ghost.h"
#include "Exit.h"
#include "UpdateMap.h"

void gameRuning() /// This function restarts the game 
{
	if (restartGame()) { gameRuning(); }// If startGame returns true, then recursin starts.
}

/// This func runs the game and returns true for gameRuning() func to restart the game
bool restartGame()
{
	//If level file doesn't find stop the game  
	if (!LoadMap()) // load new TileMap
	{
		return 0; // break the loop
	}

	sf::RenderWindow window(sf::VideoMode(450, 500), "PacMan [Hrytsenok Bogdan]");
	sf::Event event;
	window.setVerticalSyncEnabled(true); // 60fps

	sf::Texture pacTexture;
	pacTexture.loadFromFile("sprites.png"); //Sprite Sourse

	SpriteMap map(pacTexture); // Create map

	PacMan player(pacTexture, "PacMan"); // Create pacman

	Ghost ghost1(pacTexture, "Ghost1"); // Create Ghosts
	Ghost ghost2(pacTexture, "Ghost2");

	Exit exit(pacTexture, "Exit"); // Create exit key and end screeans

	sf::RectangleShape rectangle(sf::Vector2f(tileSize, tileSize)); //rectangles which have size of map tiles

	while (window.isOpen())
	{
		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed)
			{
				window.close();
				return 0; // to break recursion;
			}
		}

		// If player isn't dead and have not won yet
		if (!player.cached && !player.win)
		{
			player.Update(); //get user input, moving pacman and portals handling

			ghost1.GhostManager(player.currX, player.currY, player.cached); //// Set next ditection, move and check if the PacMan is cached by ghosts 
			ghost2.GhostManager(player.currX, player.currY, player.cached);

			window.clear(sf::Color::Black);
			window.draw(map.sprite); // Draw map

			UpdateMap(rectangle, window); // draw black tiles in pleases where pills are eaten. Pills disappear mechanism

			if (player.pills >= 244) // 244 PILLS. If we ate them all -> exit appears.
			{
				window.draw(exit.sprite);
				player.win = exit.CheckForExit(player.currX, player.currY);
			}

			window.draw(player.sprite); // Draw PacMan
			window.draw(ghost1.sprite); // Draw Ghost
			window.draw(ghost2.sprite); // Draw Ghost
			window.display();
		}
		else // if win or lose
		{
			window.clear(sf::Color::Black);
			window.draw(map.sprite); // Draw map

			UpdateMap(rectangle, window); // draw black tiles in pleases where pills are eaten. Pills disappear mechanism

			if (!player.win)
			{
				player.AnimationDeath();
				Exit lose(pacTexture, "Lose");
				window.draw(lose.sprite);
			}
			else
			{
				Exit win(pacTexture, "Win");
				window.draw(win.sprite);
			}

			window.draw(player.sprite); // Draw PacMan
			window.display();

			/// Restart if pressed spase (recursion)
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) { return true; }
		}
	}
}