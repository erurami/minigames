
#pragma once

#include "4InARow.hpp"

#include <stdio.h>

FourInARow::Game::Game(int width, int height)
{
    m_width = width;
    m_height = height;
    m_pBoard = new int[width * height];

    for (int i = 0; i < (width * height); i++)
    {
        m_pBoard[i] = 0;
    }
}

FourInARow::Game::~Game()
{
    delete [] m_pBoard;
}

int FourInARow::Game::GetBoardWidth(void)
{
    return m_width;
}

int FourInARow::Game::GetBoardHeight(void)
{
    return m_height;
}

int FourInARow::Game::PutCoin(int player, int column)
{
}



void FourInARow::Game::Print(void)
{
    for (int y = 0; y < m_height; y++)
    {
        for (int x = 0; x < m_width; x++)
        {
            printf("%d", m_pBoard[y * m_width + x]);
        }
        printf("\n");
    }
}

