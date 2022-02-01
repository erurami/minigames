
#pragma once

namespace Reversi
{

class Game
{

    public:

        explicit Game(int width, int height);
        explicit Game();
        ~Game();

        int GetBoardWidth(void)   {return m_width;};
        int GetBoardHeight(void)  {return m_height;};
        int GetAt(int x, int y)   {return m_pBoard[y][x];};
        int GetWhichTurn(void)    {return m_turnPlayer;};
        int GetGameStatus(void)   {return m_gameStatus;};
        int GetPlayer1Count(void) {return m_player1Count;};
        int GetPlayer2Count(void) {return m_player2Count;};
        // return : total placable position count
        int GetPlacablePositions(int*** pPlacePositionBufAddr);

        // return :
        //   0 : success
        //   1 : wrong position
        //   2 : already put
        //   3 : non-placable
        int PutDisc(int x, int y);

        void Undo(void);

        // printPlacable : 
        //   0 : no
        //   1 : yes (only when useColor is true)
        void Print(bool useColor = false,
                   bool printRuler = false,
                   int  printPlacable = 0);


    private:

        void UpdateGameStatus(void);
        void UpdatePlacablePos(void);
        bool SearchLine(int fromX, int fromY,
                        int directionX, int directionY,
                        int searchFor);

        // 0 : game
        // 1 : 1 win
        // 2 : 2 win
        // 3 : draw
        int m_gameStatus;
        int m_player1Count;
        int m_player2Count;

        int** m_pBoard;

        int m_width;
        int m_height;

        int   m_placablePosCount;
        int** m_pPlacablePositions;

        int m_turnPlayer;
        int m_turnNumber;

};

}

#include "Reversi.ipp"

