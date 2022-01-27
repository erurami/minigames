
#pragma once

namespace Reversi
{

class Game
{

    public:

        explicit Game(int width = 8, int height = 8);
        ~Game();

        int GetBoardWidth(void)  {return m_width;};
        int GetBoardHeight(void) {return m_height;};
        int GetWhichTurn(void);
        // return : total placable position count
        int GetPlacablePositions(int*** pPlacePositionBufAddr);

        int PutDisc(int x, int y);

        void Undo(void);

        void Print(void);


    private:

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

