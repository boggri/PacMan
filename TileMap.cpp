#include "TileMap.h"

int const H = 31;
int const W = 28;

// Size of tiles
int const tileSize = 16;

bool isBustMode = false; // When Pacman eats ghosts

std::string StringMap[H]; // Here the tile map will be stored

std::string *Map = StringMap; // definition of global declaration in .h file for ability to acsess it from all pleases