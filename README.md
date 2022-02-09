
# minigames
c++ library for minigames.

## Table of contents

* [Description](#description)
* [Features](#features)
  * [4 in a row](#4-in-a-row)
  * [Reversi](#reversi)
  * [2048](#2048)
* [Documents](#documents)


## Description

You can run some famous boardgames and minigames easily in your code.

This library currently has;

 * 4 in a row
 * reversi
 * 2048


## Features

To use these libraries, you can include `minigames.hpp` in root directory

---

### 4-in-a-row

* firstly, you'll need to make game instance for 4 in a row game.
```
FourInARow::Game game(width, height);
```

* Use [PutCoin()](#fourinarowgameputcoin) to put the coin.
```
game.PutCoin(column);
```

* And don't forget to check game status when you put the coin by [GetGameStatus()](#fourinarowgamegetgamestatus)
```
game.GetGameStatus();
```

* You can [Undo()](#fourinarowgameundo) the game if you made a mistake.
```
game.Undo();
```

* Lazy at displaying the game board? [Print()](#fourinarowgameprint) will do it for you.
```
game.Print();
```

[Here](#fourinarowgame) is more references of the functions supported.

---

### Reversi

* First, you'll need game board to play reversi.
```
Reversi::Game game(width, height);
```

* Use [PutDisc()](#reversigameputdisc) to Put disc on the board.
```
game.Putdisc(x, y);
```

* [Print()](#reversigameprint) to print the reversi board to stdout.
```
game.Print();
```

* And you'll need to check game status using [GetGameStatus()](#reversigamegetgamestatus)
```
game.GetGameStatus();
```

__Notice__ : Undo() is not available. You can't use Undo().

[Here](#reversigame) is more functions you can use for reversi game.

---

### 2048

* First, you can create game by
```
TwoZeroFourEight::Game game();
```

* This game is simple, you can use [ForceBy()](#twozerofoureightgameforceby) to move tiles.
```
game.ForceBy([direction]_2048);
```

* [Print()](#twozerofoureightgameprint) outputs board to stdout.
```
game.Print();
```

[Here](#twozerofoureightgame) is more informations for 2048 game.

---


# Documents

---

## 4InARow.hpp

header for 4 in a row game

### FourInARow::Game

### FourInARow::Game::Game
constructor of FourInARow::Game
```
explicit Game(int width, int height);
Game(const Game& game);
```

* Arguments
  * width : width of the board
  * height : height of the board


### FourInARow::Game::PutCoin
Puts the coin in the specified column.
```
int PutCoin(
    [in]           int column,
    [in][optional] int player
    );
```

* Arguments
  * column : index of column to put the coin.
  * player : specifies the player to put the coin. The function will fail when the wrong player is selected.
* Returns
  * 0 : sccess
  * 1 : wrong turn sepecified
  * 2 : no space to put
  * 3 : wrong column index


### FourInARow::Game::Undo
Undos the game.
```
void Undo(void);
```

### FourInARow::Game::Print
Prints the game.
```
void Print(
    [in][optional] bool useColor          = false,
    [in][optional] int  highlightLastCoin = 0,
    [in][optional] int  highlightWinningLine = 0
    );
```

* Arguments
  * useColor : specifie whether use terminal escape sequences.
  * highlightLastCoin : highlights last put coin.
  * highlightWinningLine : highlights winning line when the game is finished.
  * highlighting options
    * 0 : no highlighting
    * 1 : add asterisk after the number
    * 2 : highlight text (only when useColor == true)


### FourInARow::Game::GetBoardWidth
Returns board width
```
int GetBoardWidth(void);
```

### FourInARow::Game::GetBoardHeight
Returns board height
```
int GetBoardHeight(void);
```


### FourInARow::Game::GetWhichTurn
Returns turn of the game.
```
int GetWhichTurn(void);
```

* 1 : Player1's turn
* 2 : Player2's turn


### FourInARow::Game::GetTurnNumber
Returns number of turn (Nth) turn.
```
int GetTurnNumber(void);
```


### FourInARow::Game::GetGameStatus
Returns status of the game.
```
int GetGameStatus(void);
```

* 0 : normal (game is not ended)
* 1 : player1 won
* 2 : player2 won
* 3 : draw


### FourInARow::Game::GetAt
Returns the status of specified location of the board
```
int GetAt(
    [in]   int x,
    [in]   int y
    );
```

* Arguments
  * x : x position to get.
  * y : y position to get.
* Return
  * 0 : no coin
  * 1 : player1's coin
  * 2 : player2's coin


### FourInARow::Game::GetEntireBoard
copies board data into the buffer given
```
void GetEntireBoard(
    [out]   int* pBoardDest
    );
```

* Arguments
  * pBoardDest : pointer to the buffer where the board data will  be copied.
    * buffer needs to have enough space to write board data.
    * buffer needs int[width * height] of space.


### FourInARow::Game::GetWinningLine
copies winning line data into the buffer given
(winning line means a line where the "4" is connected / "4" is in a row.)
```
void GetWinningLine(
    [out]   int* pWinningLineDest
    );
```

* Arguments
  * pWinningLineDest : pointer to the buffer where the winning line data will be copied.
    * buffer needs int[8] of space to write the data.


### FourInARow::Game::GetGameHistory
copies history data of the game into the buffer given.
```
void GetGameHistory(
    [out]    int* pHistoryDest
    );
```

* Arguments
  * pHistoryDest : A pointer to the buffer where the history will be copied.
    * buffer needs to have int[width \* height \* 2] of space.

#### history data structure
int 1 dimentional array.
The array is treated as 2d array which the size is (width\*height)x2
```c
[
int x1, int y1, // disc position which is put first
int x2, int y2, // disc position which is put second
.....
];
```


---

## Reversi.hpp

header for reversi game

### Reversi::Game

### Reversi::Game::Game
constructor of Reversi::Game
```
explicit Game();
explicit Game(int width, int height);
```

* Arguments
  * width : width of the board (optional)
  * height : height of the board (optional)
* Remarks
  * if the size is not specified, the size will be 8x8.


### Reversi::Game::PutDisc
Puts disc on the board
```
int PutDisc(
    [in]   int x,
    [in]   int y
    );
```

* Arguments
  * x : x position to put.
  * y : y position to put.
* Returns
  * 0 : sccess
  * 1 : wrong position (out of the board)
  * 2 : already put
  * 3 : non-placable position


### Reversi::Game::Print
Prints the board to stdout.
```
void Print(
    [in][optional] bool useColor = false,
    [in][optional] bool printRuler = false,
    [in][optional] int  printPlacable = 0
    );
```

* Arguments
  * useColor : use ascii/anci escape sequence or not.
  * printRuler : print row and column index or not.
  * printPlacable : highlight placable positions or not.
    * 0 : No
    * 1 : Yes (when only useColor == true)


### Reversi::Game::GetBoardWidth
Returns the width of the board.
```
int GetBoardWidth(void);
```


### Reversi::Game::GetBoardHeight
Returns the height of the board.
```
int GetBoardHeight(void);
```


### Reversi::Game::GetAt
Returns state of specified location on the board.
```
int GetAt(
    [in]   int x,
    [in]   int y
    );
```

* Arguments
  * x : x position to get
  * y : y position to get


### Reversi::Game::GetWhichTurn
Returns turn of the game.
```
int GetWhichTurn(void);
```

* 1 : Player1's turn
* 2 : Player2's turn


### Reversi::Game::GetGameStatus
Returns status of the game
```
int GetGameStatus(void);
```

* 0 : the game is continuing.
* 1 : Player1 won
* 2 : Player2 won
* 3 : Draw


### Reversi::Game::GetPlayer1Count
Returns number of disc of player1 on the board.
```
int GetPlayer1Count(void);
```


### Reversi::Game::GetPlayer2Count
Returns number of disc of player2 on the board.
```
int GetPlayer2Count(void);
```


### Reversi::Game::GetPlacablePositions
Returns number of placable positions and placable position.
```
int GetPlacablePositions(
    [out] int*** PlacablePositionsBufAddr
    );
```

* Arguments
  * PlacablePositionsBufAddr : pointer of pointer of pointer of int.
    * In other words, this means pointer of (2D Array).
    * This returns the pointer of buffer of placable positions.
* Returns
  * number of placable positions.

* Example
```c++
int** placable_positions;
int   placable_positions_count;
//
placable_positions_count = GetPlacablePositions(&placable_positions);
//
placable_positions[n][0]; // this is the x position of [n]th placable position
placable_positions[n][1]; // this is the y position of [n]th placable position
```



## 2048.hpp

header for 2048 game.


### TwoZeroFourEight::Game

2048 game class


### TwoZeroFourEight::Game::Game
constructor of TwoZeroFourEight::Game
```
explicit Game();
```


### TwoZeroFourEight::Game::ForceBy
Move Tiles (This means pressing arrow keys in original 2048 game)
```
void ForceBy(
    [in]  int direction
    );
```

* Arguments
  * direction : direction of move.
    * UP\_2048   (0) : up
    * LEFT\_2048 (1) : left
    * RIGHT\_2048(2) : right
    * DOWN\_2048 (3) : down


### TwoZeroFourEight::Game::Print
Print the board to stdout
```
void Print(
    [in][optional]  bool useColor = false,
    [in][optional]  int  cellWidth = 4);
```

* Arguments
  * useColor : specifies whether use ascii/anci escape sequence
  * cellWidth : width of one cell in characters


