
#pragma once
#define _2048_

namespace TwoZeroFourEight
{

class Game
{

    public:

        explicit Game();
        ~Game();

        int GetGameStatus(void);
        int GetGameScore(void);
        int GetAt(int x, int y);

        // 0 : up
        // 1 : left
        // 2 : right
        // 3 : down
        void Move(int direction);

        void Print(int cellWidth = 4);

    private:

        void SpawnRandomTile(void);

        long m_score;

        int** m_pBoard;

};

}

#include "2048.ipp"

