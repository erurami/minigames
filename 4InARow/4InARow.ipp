
#pragma once

#include "4InARow.hpp"

#include <stdio.h>

4InARow::Game::Game(int width, int height)
{
    m_width = width;
    m_height = height;
    m_pBoard = new int[width * height];
}

4InARow::Game::~Game()
{
    delete [] m_pBoard;
}

void 4InARow::Game::GetBoardWidth(void)
{
    return m_width;
}

void 4InARow::Game::GetBoardHeight(void)
{
    return m_height;
}



void 4InARow::Game::Print(void)
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

