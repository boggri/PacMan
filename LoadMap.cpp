#include "LoadMap.h"
#include "includeAllHeaders.h"
#include <fstream>
#include <conio.h>

bool LoadMap()
{
	// Create new TileMap
	std::string TempString;
	std::ifstream myfile;
	myfile.open("Level1.txt");

	if (myfile.is_open())
	{
		// Load new tile map
		while (!myfile.eof())
		{
			for (int i = 0; i < H; i++)
			{
				getline(myfile, TempString);
				Map[i] = TempString;
			}
		}
		myfile.close();
		
		return true;
	}
	else
	{
		std::cout << "Unable to open Level1.txt"; // Error masage
		_getch(); //whait to press any kay
		
		return false; // break recursion
	}
}