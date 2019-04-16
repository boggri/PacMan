# PacMan
PacMan game.

Made with SFML libs. Compiled on Visual Studio 2015. The game is written on C++.

If you lose or win just press spase to restart the game. Compiled game is in directory ```exe/```

#To do: 
- rewrite copypast in finctions  ```FindTilesCachMod``` to make sourse code DRY and simplify the logic.
- rewrite ```bool move[]``` array to 1 ```enum``` element with different states.
- base class must not know how it will be used (cleen up statements in constructor of class ```Creatures``` like ```if (name == PacMan)```).
- logic must not know about graphics drawing. In classes of ```PacMan``` and ```Ghosts``` shouldn't be code like ```sprite.setTextureRect``` and lines that define size of sprites.
- details of how the map is drawn should not penetrate into the other classes. Create class map that will hide details like ```if(Map[i][j] == '.')``` (provide encapsulation).
- many functions must be divided into several smaller specialized ones.
