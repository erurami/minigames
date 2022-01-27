
#pragma once

#include "Reversi.hpp"
#include "utils/ArrayUtil.hpp"

// m_pBoard[height][width]

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
    Free2dIntArray(&m_pBoard, height, width);
}


