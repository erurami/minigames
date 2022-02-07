
#pragma once
#define _2048_

#define UP_2048 0
#define LEFT_2048 1
#define RIGHT_2048 2
#define DOWN_2048 3

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
        void ForceBy(int direction);

        void Print(int cellWidth = 4);

    private:

        bool ForceTile_AtBy(int x, int y, int direction);
        int** m_pMergedCells;

        void SpawnRandomTile(void);

        void UpdateGameStatus(void);


        // 0 : normal
        // 1 : gameover
        int  m_gameStatus;
        long m_score;

        int** m_pBoard;

};

}

#include "2048.ipp"

