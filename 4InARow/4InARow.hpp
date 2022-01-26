
#pragma once

namespace FourInARow
{

class Game
{

    public:

        explicit Game(int width, int height);
        ~Game();

        int GetBoardWidth(void)  {return m_width;};
        int GetBoardHeight(void) {return m_height};
        int GetWhichTurn(void)   {return m_turnPlayer;};

        // 0 : sccess
        // 1 : wrong turn
        // 2 : no space
        int PutCoin(int column, int player = 0);

        int GetGameStatus(void);

        void Print(void);


    private:

        void UpdateGameStatus(void);

        int* m_pBoard;

        int m_width;
        int m_height;

        int m_turnPlayer;

};

}

#include "4InARow.ipp"

