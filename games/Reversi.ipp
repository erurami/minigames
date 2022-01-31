
#pragma once

#include "Reversi.hpp"
#include "utils/ArrayUtil.hpp"

// m_pBoard[height][width]

Reversi::Game::Game()
    :Game(8, 8)
{
}

Reversi::Game::Game(int width, int height)
{
    Alloc2dIntArray(&m_pBoard, height, width, 0);

    m_width = width;
    m_height = height;

    m_turnPlayer = 1;
    m_turnNumber = 0;
}

Reversi::Game::~Game()
{
    Free2dIntArray(&m_pBoard, m_height, m_width);
}


void Reversi::Game::Print(bool useColor)
{
    printf("   | ");
    for (int i = 0; i < m_width; i++)
    {
        printf("%2d", i);
    }
    printf("\n");
    for (int i = 0; i < (5 + 2 * m_width); i++)
    {
        printf("-");
    }
    printf("\n");


    for (int i = 0; i < m_height; i++)
    {
        printf("%2d | ", i);

        if (useColor)
        {
            printf("\033[42m");
        }
        for (int j = 0; j < m_width; j++)
        {
            if (useColor)
            {
                switch (m_pBoard[i][j])
                {
                    case 0:
                        printf("\033[32m");
                        break;
                    case 1:
                        printf("\033[30m");
                        break;
                    case 2:
                        printf("\033[37m");
                        break;
                }
                printf("##");
                printf("\033[37m");
            }
            else
            {
                printf("%d ", m_pBoard[i][j]);
            }
        }
        if (useColor)
        {
            printf("\033[m");
        }
        printf("\n");
    }

    if (useColor)
    {
        printf("\033[m");
    }

}


int Reversi::Game::PutDisc(int x, int y)
{
    if (x >= m_width || y >= m_height)
    {
        return 1;
    }
    if (m_pBoard[y][x] != 0)
    {
        return 2;
    }

    m_pBoard[y][x] = m_turnPlayer;

    m_turnNumber++;
    m_turnPlayer = m_turnNumber % 2 + 1;

    return 0;
}

