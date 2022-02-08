
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

* Use [PutCoin()](#FourInARow::Game::PutCoin) to put the coin.
```
game.PutCoin(column);
```

* And don't forget to check game status when you put the coin by [GetGameStatus()](#FourInARow::Game::GetGameStatus)
```
game.GetGameStatus();
```

* You can [Undo()](#FourInARow::Game::Undo) the game if you made a mistake.
```
game.Undo();
```

* Lazy at displaying the game board? [Print()](#FourInARow::Game::Print) will do it for you.
```
game.Print();
```

[Here](#FourInARow::Game) is more references of the functions supported.

---

### Reversi

* First, you'll need game board to play reversi.
```
Reversi::Game game(width, height);
```

* Use [PutDisc()](#Reversi::Game::PutDisc) to Put disc on the board.
```
game.Putdisc(x, y);
```

* [Print()](#Reversi::Game::Print) to print the reversi board to stdout.
```
game.Print();
```

* And you'll need to check game status using [GetGameStatus()](#Reversi::Game::GetGameStatus)
```
game.GetGameStatus();
```

__Notice__ : Undo() is not available. You can't use Undo().

[Here](#Reversi::Game) is more functions you can use for reversi game.

---

### 2048

* First, you can create game by
```
TwoZeroFourEight::Game game();
```

* This game is simple, you can use [ForceBy()](#TwoZeroFourEight::Game::ForceBy) to move tiles.
```
game.ForceBy([direction]_2048);
```

* [Print()](#TwoZeroFourEight::Game::Print) outputs board to stdout.
```
game.Print();
```

[Here](#TwoZeroFourEight::Game) is more informations for 2048 game.

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


### 
