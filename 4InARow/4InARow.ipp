
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

    m_turnPlayer = 1;
}

FourInARow::Game::~Game()
{
    delete [] m_pBoard;
}


int FourInARow::Game::PutCoin(int column, int player)
{
    if (player == 0) player = m_turnPlayer;

    if (player != m_turnPlayer)
    {
        return 1;
    }

    int node_x_i = column;
    int node_y_i = 0;
    while ()
    {
        if (node_y_i == m_height)
        {
            break;
        }
        if (m_pBoard[node_y_i * m_width + node_x_i] != 0)
        {
            break;
        }

        node_y_i++;
    }

    node_y_i--;

    if (node_y_i < 0)
    {
        return 2;
    }

    m_pBoard[node_y_i * m_width + node_x_i] = player;

    if (m_turnPlayer == 1)
    {
        m_turnPlayer = 2;
    }
    if (m_turnPlayer == 2)
    {
        m_turnPlayer = 1;
    }

    UpdateGameStatus();

    return 0;
}

void FourInARow::Game::UpdateGameStatus(void)
{
}



void FourInARow::Game::Print(void)
{
    for (int y = 0; y < m_height; y++)
    {
        for (int x = 0; x < m_width; x++)
        {
            printf("%d ", m_pBoard[y * m_width + x]);
        }
        printf("\n");
    }
}

