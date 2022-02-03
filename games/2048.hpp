
#pragma once

namespace TwoZeroFourSeven
{

class Game
{

    public:

        explicit Game(int width, int height);
        Game();
        ~Game();

    private:

        int** m_pBoard;

};

}

#include "2048.ipp"

