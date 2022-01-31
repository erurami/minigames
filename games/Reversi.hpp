
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
        //   3 : non-placable
        int PutDisc(int x, int y);

        void Undo(void);

        // printPlacable : 
        //   0 : no
        //   1 : yes
        void Print(bool useColor = false,
                   bool printRuler = false,
                   int  printPlacable = 0);


    private:

        void UpdatePlacablePos(void);
        bool SearchLine(int fromX, int fromY,
                        int directionX, int directionY,
                        int searchFor);

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

