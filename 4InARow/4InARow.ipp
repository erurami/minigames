
#pragma once

#include "4InARow.hpp"

#include <stdio.h>

FourInARow::Game::Game(int width, int height)
{
    m_width = width;
    m_height = height;

    m_pBoard = new int[width * height];
    for (int i = 0; i < (width * height); i++) m_pBoard[i] = 0;

    m_pGameHistory = new int [width * height * 2];

    m_pWinningLine = new int [8];

    m_turnPlayer = 1;
    m_turnNumber = 0;

    m_gameStatus = 0;

    m_lastX = -1;
    m_lastY = -1;
}

FourInARow::Game::~Game()
{
    delete [] m_pBoard;
    delete [] m_pGameHistory;
    delete [] m_pWinningLine;
}



int FourInARow::Game::PutCoin(int column, int player)
{
    if (player == 0) player = m_turnPlayer;

    if (player != m_turnPlayer)
    {
        return 1;
    }

    if (column >= m_width)
    {
        return 3;
    }



    int node_x_i = column;
    int node_y_i = 0;
    while (1)
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

    m_pGameHistory[m_turnNumber * 2]     = node_x_i;
    m_pGameHistory[m_turnNumber * 2 + 1] = node_y_i;

    m_turnNumber++;
    m_turnPlayer = (m_turnPlayer % 2) + 1;

    m_lastX = node_x_i;
    m_lastY = node_y_i;


    UpdateGameStatus();

    return 0;
}

void FourInARow::Game::Undo(void)
{
    if (m_turnNumber <= 0)
    {
        return;
    }

    m_pBoard[m_lastY * m_width + m_lastX] = 0;
    m_turnNumber--;
    m_turnPlayer = (m_turnNumber % 2) + 1;

    m_lastX = m_pGameHistory[(m_turnNumber - 1) * 2];
    m_lastY = m_pGameHistory[(m_turnNumber - 1) * 2 + 1];
}



// TODO: readable code (use functions...)
void FourInARow::Game::UpdateGameStatus(void)
{
    for (int i = 0; i < 4; i++)
    {
        int searching_x = m_lastX;
        int searching_y = m_lastY;

        while (1)
        {
            switch (i)
            {
                case 0:
                    searching_x--;
                    break;
                case 1:
                    searching_x--;
                    searching_y--;
                    break;
                case 2:
                    searching_y--;
                    break;
                case 3:
                    searching_x++;
                    searching_y--;
                    break;
            };
            if (searching_x <= 0 || searching_x >= (m_width  - 1)||
                searching_y <= 0 || searching_y >= (m_height - 1))
            {
                break;
            }
        }

        int continuing_number = -1;
        int continuing_length = 0;

        int number_now;

        while (1)
        {
            switch (i)
            {
                case 0:
                    searching_x++;
                    break;
                case 1:
                    searching_x++;
                    searching_y++;
                    break;
                case 2:
                    searching_y++;
                    break;
                case 3:
                    searching_x--;
                    searching_y++;
                    break;
            }
            if (searching_x < 0 || searching_x >= m_width ||
                searching_y < 0 || searching_y >= m_height)
            {
                break;
            }

            number_now = m_pBoard[searching_y * m_width + searching_x];
            if (continuing_number == number_now)
            {
                continuing_length++;
            }
            else
            {
                continuing_number = number_now;
                continuing_length = 1;
            }
            m_pWinningLine[(continuing_length - 1) * 2]     = searching_x;
            m_pWinningLine[(continuing_length - 1) * 2 + 1] = searching_y;

            if (continuing_length >= 4)
            {
                continuing_length = 1;
                if (continuing_number != 0)
                {
                    m_gameStatus = continuing_number;
                    return;
                }
            }
        }
    }

    if (m_turnNumber >= (m_width * m_height) && m_gameStatus == 0)
    {
        m_gameStatus = 3;
    }

    return;
}



// TODO : use array to contain number and highlight options and print
void FourInARow::Game::Print(bool useColor,
                             int highlightLastCoin,
                             int highlightWinningLine)
{
    // int **print_buffer_backcolor;
    // int **print_buffer_forecolor;
    // int **print_buffer_printnumber;

    int printing_value;

    for (int y = 0; y < m_height; y++)
    {
        for (int x = 0; x < m_width; x++)
        {
            printing_value = m_pBoard[y * m_width + x];

            if (useColor)
            {
                printf("\033[%dm", printing_value == 0 ? 37 : printing_value + 30);
            }
            if (highlightLastCoin == 2 && x == m_lastX && y == m_lastY)
            {
                printf("\033[44m");
            }


            printf("%d", printing_value);


            if (useColor)
            {
                printf("\033[m");
            }

            if (highlightLastCoin == 1 && x == m_lastX && y == m_lastY)
            {
                printf("*");
            }
            else
            {
                printf(" ");
            }
        }
        printf("\n");
    }
    printf("\033[m");
}

