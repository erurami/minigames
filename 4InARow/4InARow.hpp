
#pragma once

namespace FourInARow
{

class Game
{

    public:

        explicit Game(int width, int height);
        ~Game();

        int GetBoardWidth(void);
        int GetBoardHeight(void);

        int PutCoin(int player, int column);

        int GetGameStatus(void);

        void Print(void);


    private:

        int* m_pBoard;

        int m_width;
        int m_height;

};

}

#include "4InARow.ipp"

