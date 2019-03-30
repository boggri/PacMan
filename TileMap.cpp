#include "TileMap.h"

int H = 31;
int W = 28;

// Size of tiles
int tileSize = 16;

const int MapH = 31;
const int MapW = 28;

std::string StringMap[MapH] = {

	"WWWWWWWWWWWWWWWWWWWWWWWWWWWW",
	"W............WW............W",
	"W.WWWW.WWWWW.WW.WWWWW.WWWW.W",
	"W0W  W.W   W.WW.W   W.W  W0W",
	"W.WWWW.WWWWW.WW.WWWWW.WWWW.W",
	"W..........................W",
	"W.WWWW.WW.WWWWWWWW.WW.WWWW.W",
	"W.WWWW.WW.WWWWWWWW.WW.WWWW.W",
	"W......WW....WW....WW......W",
	"WWWWWW.WWWWW WW WWWWW.WWWWWW",
	"     W.WWWWW WW WWWWW.W     ",
	"     W.WW          WW.W     ",
	"     W.WW WWW&&WWW WW.W     ",
	"WWWWWW.WW W      W WW.WWWWWW",
	"Q    w.   W      W   .w    q",
	"WWWWWW.WW W      W WW.WWWWWW",
	"     W.WW WWWWWWWW WW.W     ",
	"     W.WW          WW.W     ",
	"     W.WW WWWWWWWW WW.W     ",
	"WWWWWW.WW WWWWWWWW WW.WWWWWW",
	"W............WW............W",
	"W.WWWW.WWWWW.WW.WWWWW.WWWW.W",
	"W.WWWW.WWWWW.WW.WWWWW.WWWW.W",
	"W0..WW.......  .......WW..0W",
	"WWW.WW.WW.WWWWWWWW.WW.WW.WWW",
	"WWW.WW.WW.WWWWWWWW.WW.WW.WWW",
	"W......WW....WW....WW......W",
	"W.WWWWWWWWWW.WW.WWWWWWWWWW.W",
	"W.WWWWWWWWWW.WW.WWWWWWWWWW.W",
	"W..........................W",
	"WWWWWWWWWWWWWWWWWWWWWWWWWWWW"
};

std::string *Map = StringMap;