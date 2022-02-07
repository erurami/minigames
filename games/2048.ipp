
#pragma once

#include "2048.hpp"
#include "utils/ArrayUtil.hpp"
#include "utils/RandomUtil.hpp"
#include <math.h>

#ifndef RESETSEED
#include <time.h>
#define RESETSEED (unsigned long)time(NULL)
#endif

#define FIELDSIZE 4

int DigitsOf(int number)
{
    int digits_count = 0;
    while (1)
    {
        digits_count++;
        number /= 10;
        if (number == 0)
        {
            break;
        }
    }
    return digits_count;
}

TwoZeroFourEight::Game::Game()
{
    SetRandomMethod(RM_MIDDLESQUARE, RESETSEED);

    Alloc2dIntArray(&m_pBoard, FIELDSIZE, FIELDSIZE, 0);

    m_score = 0;

    SpawnRandomTile();
    SpawnRandomTile();
}

TwoZeroFourEight::Game::~Game()
{
    Free2dIntArray(&m_pBoard, FIELDSIZE, FIELDSIZE);
}


int _k_MOVES[][2] = {
    { 0, -1},
    {-1,  0},
    { 1,  0},
    { 0,  1},
};

void TwoZeroFourEight::Game::ForceBy(int direction)
{
    bool did_tile_moved = false;
    int x, y;
    Alloc2dIntArray(&m_pMergedCells, FIELDSIZE, FIELDSIZE, 0);
    for (int i = 0; i < FIELDSIZE; i++)
    {
        for (int j = 0; j < FIELDSIZE; j++)
        {
            switch (direction)
            {
                case UP_2048:
                    x = i;
                    y = j;
                    break;
                case LEFT_2048:
                    x = j;
                    y = i;
                    break;
                case RIGHT_2048:
                    x = FIELDSIZE - 1 - j;
                    y = i;
                    break;
                case DOWN_2048:
                    x = i;
                    y = FIELDSIZE - 1 - j;
                    break;
            }

            if (m_pBoard[y][x] != 0)
            {
                did_tile_moved = ForceTile_AtBy(x, y, direction) || did_tile_moved;
            }
        }
    }
    Free2dIntArray(&m_pMergedCells, FIELDSIZE, FIELDSIZE);

    if (did_tile_moved)
    {
        SpawnRandomTile();
        UpdateGameStatus();
    }
}

bool TwoZeroFourEight::Game::ForceTile_AtBy(int x, int y, int direction)
{
    int target_x = x;
    int target_y = y;

    while (1)
    {
        target_x += _k_MOVES[direction][0];
        target_y += _k_MOVES[direction][1];

        if (target_x < 0 || target_x >= FIELDSIZE) break;
        if (target_y < 0 || target_y >= FIELDSIZE) break;

        if (m_pMergedCells[target_y][target_x] == 1) break;

        if (m_pBoard[target_y][target_x] == m_pBoard[y][x]) continue;
        if (m_pBoard[target_y][target_x] == 0) continue;

        break;
    }

    target_x -= _k_MOVES[direction][0];
    target_y -= _k_MOVES[direction][1];


    if ((target_x == x) && (target_y == y))
    {
        return false;
    }

    if (m_pBoard[target_y][target_x] == 0)
    {
        m_pBoard[target_y][target_x] = m_pBoard[y][x];
    }
    else
    {
        m_pBoard[target_y][target_x]++;

        m_pMergedCells[target_y][target_x] = 1;

        m_score += pow(2, m_pBoard[target_y][target_x]);
    }
    m_pBoard[y][x] = 0;
    return true;
}

void TwoZeroFourEight::Game::UpdateGameStatus(void)
{
    bool is_gameover = true;

    for (int y = 0; y < FIELDSIZE; y++)
    {
        for (int x = 0; x < FIELDSIZE; x++)
        {
            if (m_pBoard[y][x] == 0)
            {
                is_gameover = false;
                goto CHECKEND;
            }

            if (y < (FIELDSIZE - 1))
            {
                if (m_pBoard[y + 1][x] == m_pBoard[y][x])
                {
                    is_gameover = false;
                    goto CHECKEND;
                }
            }

            if (x < (FIELDSIZE - 1))
            {
                if (m_pBoard[y][x + 1] == m_pBoard[y][x])
                {
                    is_gameover = false;
                    goto CHECKEND;
                }
            }
        }
    }

    CHECKEND:
    if (is_gameover)
    {
        m_gameStatus = 1;
    }
    else
    {
        m_gameStatus = 0;
    }
    return;
}



void TwoZeroFourEight::Game::SpawnRandomTile(void)
{
    int spawn_in[2] = {0};

    while (1)
    {
        spawn_in[0] = RandomNumber() % FIELDSIZE;
        spawn_in[1] = RandomNumber() % FIELDSIZE;
        if (m_pBoard[spawn_in[1]][spawn_in[0]] == 0)
        {
            break;
        }
    }

    m_pBoard[spawn_in[1]][spawn_in[0]] = (RandomNumber() % 10) == 0 ? 2 : 1;
}


void TwoZeroFourEight::Game::Print(int cellWidth)
{
    int cell_height = (cellWidth + 1) / 2;
    int cell_width = cell_height * 2;

    printf("score : %ld\n", m_score);

    for (int y = 0; y < FIELDSIZE; y++)
    {
        for (int x = 0; x < FIELDSIZE; x++)
        {
            long number_to_print = m_pBoard[y][x] == 0 ? 0 : pow(2, m_pBoard[y][x]);
            printf("%ld", number_to_print);
            printf("%*c", cell_width - DigitsOf(number_to_print), ' ');
        }

        for (int i = 0; i < cell_height; i++)
        {
            printf("\n");
        }
    }
}



