#include "includeAllHeaders.h"
#include "TileMap.h"
#include "Creatures.h"
#include "PacMan.h"
#include "Ghost.h"
#include "Exit.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(800, 900), "PacMan [Hrytsenok Bogdan]");
	sf::Event event;
	window.setVerticalSyncEnabled(true); // 60fps

	//Sprite Sourse
	const std::string spriteSrc = "sprites.png";

	sf::Texture pacTexture;
	pacTexture.loadFromFile(spriteSrc);

	SpriteMap map(pacTexture); // Create map

	PacMan player(pacTexture, "PacMan"); // Create pacman

	Ghost ghost0(pacTexture, "Ghost1"); // Create Ghosts
	Ghost ghost1(pacTexture, "Ghost2");

	Exit exit(pacTexture, "Exit"); // Create exit

	sf::RectangleShape rectangle(sf::Vector2f(16, 16)); //size of each map tile

	
	while (window.isOpen()) 
	{
		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed)
				window.close();
		}

		// If player isn't dead and have not won yet
		if (!player.cached && !player.win)
		{
			player.GetDirection(); // get user input if any
			player.UpdateMove(); // move our PacMan
			player.GetPillsAndPortals(); // Eat pills

			ghost0.CeckThreeTiles(player.currX, player.currY); // Set next ditection
			ghost0.UpdateMove(); // move

			ghost1.CeckThreeTiles(player.currX, player.currY);
			ghost1.UpdateMove();

			// Check if the ghosts cached PacMan 
			player.CachCheck(ghost0.currX, ghost0.currY);
			player.CachCheck(ghost1.currX, ghost1.currY);

			window.clear(sf::Color::Black);
			window.draw(map.sprite); // Draw map

			for (int i = 0; i < H; i++)
				for (int j = 0; j < W; j++)
				{
					// if there isn't a pill, colour this tile to black
					if (Map[i][j] == ' ') rectangle.setFillColor(sf::Color::Black);
					if (Map[i][j] == '.' || Map[i][j] == 'Q' || Map[i][j] == 'q' || Map[i][j] == 'w' || Map[i][j] == '&' || Map[i][j] == '0' || Map[i][j] == 'W') continue;

					rectangle.setPosition(j * tileSize, i * tileSize);
					window.draw(rectangle);
				}

			if (player.pills >= 244) // 244 PILLS. If we ate them all -> exit appears.
			{
				window.draw(exit.sprite);
				player.win = exit.CheckForExit(player.currX, player.currY);
			}


			window.draw(player.sprite); // Draw PacMan
			window.draw(ghost0.sprite); // Draw Ghost
			window.draw(ghost1.sprite); // Draw Ghost
			window.display();
		}
		else // if win or lose
		{
			window.clear(sf::Color::Black);
			window.draw(map.sprite); // Draw map

			for (int i = 0; i < H; i++)
				for (int j = 0; j < W; j++)
				{
					//if (Map[i][j] == 'W') rectangle.setFillColor(sf::Color::Blue);///
					if (Map[i][j] == ' ') rectangle.setFillColor(sf::Color::Black);
					if (Map[i][j] == '.' || Map[i][j] == 'Q' || Map[i][j] == 'X' || Map[i][j] == '&' || Map[i][j] == '0' || Map[i][j] == 'W') continue;

					rectangle.setPosition(j * tileSize, i * tileSize);
					window.draw(rectangle);
				}
			
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
		}
	}

}