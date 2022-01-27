
#pragma once

namespace FourInARow
{

class Game
{

    public:

        explicit Game(int width, int height);
        ~Game();

        int GetBoardWidth(void)  {return m_width;};
        int GetBoardHeight(void) {return m_height;};
        int GetWhichTurn(void)   {return m_turnPlayer;};
        int GetTurnNumber(void)  {return m_turnNumber;};
        int GetGameStatus(void)  {return m_gameStatus;};
        int GetAt(int x, int y)  {return m_pBoard[y * m_width + y];};

        // 0 : sccess
        // 1 : wrong turn
        // 2 : no space
        // 3 : wrong column
        int PutCoin(int column, int player = 0);

        void Undo(void);


        // param : highlightLastCoin
        //
        //            0 : no highlight
        //            1 : add asterisk
        //            2 : highlight text (only when use color)
        void Print(bool useColor = false,
                   int highlightLastCoin = 0);


    private:

        void UpdateGameStatus(void);

        int* m_pBoard;

        int m_width;
        int m_height;

        int m_turnPlayer;
        int m_turnNumber;

        // 0 : normal
        // 1 : 1 won
        // 2 : 2 won
        // 3 : draw
        int m_gameStatus;
        int* m_pWinningLine;


        int* m_pGameHistory;

        int m_lastX;
        int m_lastY;

};

}

#include "4InARow.ipp"

