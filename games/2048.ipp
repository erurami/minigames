
#pragma once

#include "2048.hpp"
#include "utils/ArrayUtil.hpp"

#define FIELDWIDTH 4
#define FIELDHEIGHT 4

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
    Alloc2dIntArray(&m_pBoard, 4, 4, 0);

    m_score = 0;
}

TwoZeroFourEight::Game::~Game()
{
    Free2dIntArray(&m_pBoard, 4, 4);
}


void TwoZeroFourEight::Game::Print(int cellWidth)
{
    int cell_height = (cellWidth + 1) / 2;
    int cell_width = cell_height * 2;

    for (int y = 0; y < FIELDHEIGHT; y++)
    {
        for (int x = 0; x < FIELDWIDTH; x++)
        {
            printf("%d", m_pBoard[y][x]);
            printf("%*c", cell_width - DigitsOf(m_pBoard[y][x]), ' ');
        }

        for (int i = 0; i < (cell_height - 1); i++)
        {
            printf("\n");
        }
    }
}



