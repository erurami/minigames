
#pragma once
#define _2048_

#define UP_2048 0
#define LEFT_2048 1
#define RIGHT_2048 2
#define DOWN_2048 3

#define FIELDSIZE 4

#define COLOR_TILE_2    200, 200, 200
#define COLOR_TILE_4    200, 200, 180
#define COLOR_TILE_8    200, 200, 150
#define COLOR_TILE_16   200, 180, 150
#define COLOR_TILE_32   200, 150, 150
#define COLOR_TILE_64   150, 150, 150
#define COLOR_TILE_128  200, 200,  50
#define COLOR_TILE_256  200, 200,  50
#define COLOR_TILE_512  200, 200,  50
#define COLOR_TILE_1024 200, 200,  50
#define COLOR_TILE_2048 200, 200,  50
#define COLOR_TILE_4096 200, 200,  50
#define COLOR_TILE_8192 200, 200,  50

#define COLOR_NUMBER_2      0,   0,   0
#define COLOR_NUMBER_4      0,   0,   0
#define COLOR_NUMBER_8      0,   0,   0
#define COLOR_NUMBER_16     0,   0,   0
#define COLOR_NUMBER_32     0,   0,   0
#define COLOR_NUMBER_64     0,   0,   0
#define COLOR_NUMBER_128    0,   0,   0
#define COLOR_NUMBER_256    0,   0,   0
#define COLOR_NUMBER_512    0,   0,   0
#define COLOR_NUMBER_1024   0,   0,   0
#define COLOR_NUMBER_2048   0,   0,   0
#define COLOR_NUMBER_4096   0,   0,   0
#define COLOR_NUMBER_8192   0,   0,   0

#ifndef RANDOMSEED
#include <time.h>
#define RANDOMSEED (unsigned long)time(NULL)
#endif

#ifndef RANDOMMETHOD
#define RANDOMMETHOD RM_LCG
#endif


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

        void Print(bool useColor = false,
                   int cellWidth = 4);

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

