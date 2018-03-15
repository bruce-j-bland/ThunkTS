ThunkTS was built as a coding exercise in developing software architecture for a modular system.

The code contains a game logic engine, as well as a simple ASCII implementation of the game.

The goal is to either trap the other player, or force them to fall into a hole. Further instructions for playing are provided in game. 

Simply run ThunkTS.cpp to begin.

Feel free to edit makeBoard() in Board.cpp to define new game scenerios. The current game engine loop requires exactly two player entities, but is otherwise robust.

New entity logic can be defined by creating new subclasses in Entity.cpp.



Example starting Board State:

   |1|2|3|4|5|6|7|8|9|
 |#|#|#|#|#|#|#|#|#|#|#|
1|#| | | | | | | | | |#|1
2|#| | | | | | | |B| |#|2
3|#| | | | | | | | | |#|3
4|#| | | | | | | | | |#|4
5|#| | | | |X| | | | |#|5
6|#| | | | | | | | | |#|6
7|#| | | | | | | | | |#|7
8|#| |A| | | | | | | |#|8
9|#| | | | | | | | | |#|9
 |#|#|#|#|#|#|#|#|#|#|#|
   |1|2|3|4|5|6|7|8|9|
   

(A and B represent the two players, # represents a Wall Tile, X represents a Hole Tile)



Example finishing Board State:

   |1|2|3|4|5|6|7|8|9|
 |#|#|#|#|#|#|#|#|#|#|#|
1|#| |#| | | | | | | |#|1
2|#| | |#| | | | | | |#|2
3|#| |#| | | | | | |#|#|3
4|#| | | | | | | | | |#|4
5|#| |#| | |X| | | | |#|5
6|#| | | | | | | | | |#|6
7|#| | | | | | | | | |#|7
8|#| | | |#| | | | |A|#|8
9|#| | | | | | | |#|B|#|9
 |#|#|#|#|#|#|#|#|#|#|#|
   |1|2|3|4|5|6|7|8|9|
   
(Player B is trapped by 3 Walls Tiles and Player A, so Player A wins)



Example finishing Board State:

   |1|2|3|4|5|6|7|8|9|
 |#|#|#|#|#|#|#|#|#|#|#|
1|#|B| | | | | | | | |#|1
2|#| | | | | | |#|#| |#|2
3|#| | | | | | | | | |#|3
4|#| | | | | | | | |#|#|4
5|#| | | |#|@| | | | |#|5
6|#| | | | | | | | |#|#|6
7|#| | | | | | | | | |#|7
8|#| | | | | | |#| | |#|8
9|#| | | | | | | |#| |#|9
 |#|#|#|#|#|#|#|#|#|#|#|
   |1|2|3|4|5|6|7|8|9|

(Player A fell into the center hole, so Player B wins)
