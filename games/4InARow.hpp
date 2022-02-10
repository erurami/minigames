
#pragma once

#define _4INAROW_

namespace FourInARow
{

class Game
{

    public:

        explicit Game(int width, int height);
        Game(const Game& game);
        ~Game();

        Game& operator=(const Game& game);


        int GetBoardWidth(void)  const {return m_width;};
        int GetBoardHeight(void) const {return m_height;};
        int GetWhichTurn(void)   const {return m_turnPlayer;};
        int GetTurnNumber(void)  const {return m_turnNumber;};
        int GetGameStatus(void)  const {return m_gameStatus;};
        int GetAt(int x, int y)  const {return m_pBoard[y * m_width + y];};

        // pBoardDest : pointer to buffer which the board data will be copied.
        //              needs to have ehough space.
        void GetEntireBoard(int* pBoardDest) const;
        // pWinningLineDest : pointer to buffer which the winnning line will be copied.
        //                    winnning line buffer needs int [8] of space.
        void GetWinningLine(int* pWinningLineDest) const;
        // pHistoryDest : pointer to buffer which the history will be copied.
        //                buffer needs int [width * height * 2] of space.
        void GetGameHistory(int* pHistoryDest) const;

        // 0 : sccess
        // 1 : wrong turn
        // 2 : no space
        // 3 : wrong column
        int PutCoin(int column, int player = 0);

        void Undo(void);


        // highlighting parameter options
        //            0 : no highlight
        //            1 : add asterisk
        //            2 : highlight text (only when use color)

        void Print(bool useColor = false,
                   int  highlightLastCoin = 0,
                   int  highlightWinningLine = 0);


    private:

        void UpdateGameStatus(void);

        // return : found win or not
        bool SearchLine_FromTo(int fromX, int fromY, int directionX, int directionY);

        // step once to the direction and if it's out of the board, reverses the position and returns false.
        bool StepOnce(int* x, int* y, int directionX, int directionY);


        void AllocBlankMemberBuffers(void);

        void Reconstruct(const Game& game);


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


#ifdef MINIGAMES_USEDEBUG
        // positions to highlight in next print
        int* m_pHighlightInNextPrint;
        int  m_highlightPointsCount = 0;

        void AddHighlightPosition_AtColour(int x, int y, int colour);
#endif

};

}

#include "4InARow.ipp"

