#include "includeAllHeaders.h"
#include "UpdateMap.h"

void UpdateMap(sf::RectangleShape &rectangle, sf::RenderWindow &window)
{
	for (int i = 0; i < H; i++)
		for (int j = 0; j < W; j++)
		{
			// if there isn't a pill, colour this tile to black
			if (Map[i][j] == ' ') rectangle.setFillColor(sf::Color::Black);
			if (Map[i][j] == '.' || Map[i][j] == 'Q' || Map[i][j] == 'q' || Map[i][j] == 'w' || Map[i][j] == '&' || Map[i][j] == '0' || Map[i][j] == 'W') continue;

			rectangle.setPosition(j * tileSize, i * tileSize);
			window.draw(rectangle);
		}
}
