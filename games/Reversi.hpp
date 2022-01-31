
#pragma once

namespace Reversi
{

class Game
{

    public:

        explicit Game(int width, int height);
        explicit Game();
        ~Game();

        int GetBoardWidth(void)  {return m_width;};
        int GetBoardHeight(void) {return m_height;};
        int GetWhichTurn(void);
        // return : total placable position count
        int GetPlacablePositions(int*** pPlacePositionBufAddr);

        // return :
        //   0 : success
        //   1 : wrong position
        //   2 : already put
        int PutDisc(int x, int y);

        void Undo(void);

        void Print(bool useColor = true);


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

